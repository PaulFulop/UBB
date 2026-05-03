<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Battleships – Game #${game.id}</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/css/style.css">
</head>
<body>
<nav class="navbar">
    <span class="nav-logo">BATTLESHIPS</span>
    <div class="nav-right">
        <span class="nav-user">${sessionScope.username}</span>
        <a href="${pageContext.request.contextPath}/logout" class="btn btn-sm btn-outline">Logout</a>
    </div>
</nav>

<div class="page-container">

    <%-- ===================== WAITING FOR OPPONENT TO PLACE ===================== --%>
    <c:if test="${game.status == 'PLACING'}">
        <div class="game-status-banner waiting">
            <div class="spinner"></div>
            <span>Waiting for your opponent to place their ships...</span>
        </div>
        <script>
            (function poll() {
                fetch('${pageContext.request.contextPath}/poll?gameId=${game.id}')
                    .then(r => r.json())
                    .then(data => {
                        if (data.status === 'PLAYING') window.location.reload();
                        else setTimeout(poll, 3000);
                    })
                    .catch(() => setTimeout(poll, 3000));
            })();
        </script>
    </c:if>

    <%-- ===================== GAME FINISHED ===================== --%>
    <c:if test="${game.status == 'FINISHED'}">
        <c:choose>
            <c:when test="${game.winnerId == sessionScope.userId}">
                <div class="game-status-banner winner">You win!</div>
            </c:when>
            <c:otherwise>
                <div class="game-status-banner loser">You lost. Better luck next time.</div>
            </c:otherwise>
        </c:choose>
        <div style="text-align:center;margin:1rem;">
            <a href="${pageContext.request.contextPath}/lobby" class="btn btn-primary">Back to Lobby</a>
        </div>
    </c:if>

    <%-- ===================== GAME IN PROGRESS / FINISHED BOARDS ===================== --%>
    <c:if test="${game.status == 'PLAYING' or game.status == 'FINISHED'}">

        <div class="turn-banner" id="turnBanner">
            <c:if test="${game.status == 'PLAYING'}">
                <c:choose>
                    <c:when test="${isMyTurn}">
                        <strong>Your turn.</strong> Click on the enemy grid to fire.
                    </c:when>
                    <c:otherwise>
                        <strong>Opponent's turn.</strong> Waiting...
                    </c:otherwise>
                </c:choose>
            </c:if>
        </div>

        <div id="shotMessage" class="shot-message hidden"></div>

        <%-- Forfeit button — only shown while game is still active --%>
        <c:if test="${game.status == 'PLAYING'}">
            <div class="forfeit-bar">
                <form method="post" action="${pageContext.request.contextPath}/forfeit"
                      onsubmit="return confirm('Forfeit this game? You will be recorded as the loser.')">
                    <input type="hidden" name="gameId" value="${game.id}">
                    <button type="submit" class="btn btn-danger btn-sm">Forfeit</button>
                </form>
            </div>
        </c:if>

        <div class="game-boards">

            <!-- MY GRID: my ships + where opponent has shot me -->
            <div class="board-section">
                <h2>Your Fleet</h2>
                <div class="grid-header-row">
                    <div class="corner-cell"></div>
                    <c:forEach begin="0" end="${gridSize - 1}" var="c">
                        <div class="grid-col-label">${['A','B','C','D','E','F','G','H'][c]}</div>
                    </c:forEach>
                </div>
                <c:forEach begin="0" end="${gridSize - 1}" var="r">
                    <div class="grid-row">
                        <div class="grid-row-label">${r + 1}</div>
                        <c:forEach begin="0" end="${gridSize - 1}" var="c">
                            <div class="grid-cell my-cell cell-${myGrid[r][c]}"
                                 data-row="${r}" data-col="${c}"
                                 title="${myGrid[r][c]}">
                            </div>
                        </c:forEach>
                    </div>
                </c:forEach>
            </div>

            <!-- TARGET GRID: where I am shooting -->
            <div class="board-section">
                <h2>Enemy Waters</h2>
                <div class="grid-header-row">
                    <div class="corner-cell"></div>
                    <c:forEach begin="0" end="${gridSize - 1}" var="c">
                        <div class="grid-col-label">${['A','B','C','D','E','F','G','H'][c]}</div>
                    </c:forEach>
                </div>
                <c:forEach begin="0" end="${gridSize - 1}" var="r">
                    <div class="grid-row">
                        <div class="grid-row-label">${r + 1}</div>
                        <c:forEach begin="0" end="${gridSize - 1}" var="c">
                            <div class="grid-cell target-cell cell-${targetGrid[r][c]}"
                                 data-row="${r}" data-col="${c}"
                                 title="${targetGrid[r][c]}"
                                 onclick="fireShot(this, ${r}, ${c})">
                            </div>
                        </c:forEach>
                    </div>
                </c:forEach>
            </div>

        </div>
    </c:if>

</div>

<script>
    const GAME_ID    = ${game.id};
    const MY_USER_ID = ${sessionScope.userId};
    let myTurn       = ${isMyTurn};
    let gameStatus   = '${game.status}';

    // Count how many incoming shots were already rendered by the server on page load.
    // The poll will send the full list — we skip everything up to this index
    // and only apply shots beyond it.
    let knownIncomingCount = document.querySelectorAll('.my-cell.cell-HIT, .my-cell.cell-MISS').length;

    // Disable clicking on cells already shot (rendered from DB on page load)
    document.querySelectorAll('.target-cell').forEach(cell => {
        if (cell.classList.contains('cell-HIT') ||
            cell.classList.contains('cell-MISS') ||
            cell.classList.contains('cell-SUNK')) {
            cell.onclick = null;
            cell.style.cursor = 'default';
        }
    });

    let pollTimer = null;

    function schedulePoll(delayMs) {
        clearTimeout(pollTimer);
        pollTimer = setTimeout(runPoll, delayMs);
    }

    function runPoll() {
        if (gameStatus !== 'PLAYING') return;

        fetch('${pageContext.request.contextPath}/poll?gameId=' + GAME_ID)
            .then(r => r.json())
            .then(data => {
                if (data.error) { schedulePoll(3000); return; }

                if (data.status === 'FINISHED') {
                    window.location.reload();
                    return;
                }

                // Apply any incoming shots the server has that we haven't painted yet
                if (data.incomingShots) {
                    data.incomingShots.forEach(s => applyIncomingShot(s.row, s.col, s.result));
                }

                const nowMyTurn = data.isMyTurn;

                if (nowMyTurn && !myTurn) {
                    myTurn = true;
                    updateTurnBanner(true);
                    showMessage("Your turn!", 'info');
                }

                if (!nowMyTurn && myTurn) {
                    myTurn = false;
                    updateTurnBanner(false);
                }

                schedulePoll(nowMyTurn ? 3000 : 500);
            })
            .catch(() => schedulePoll(3000));
    }

    function fireShot(cell, row, col) {
        if (!myTurn) {
            showMessage("It's not your turn!", 'warn');
            return;
        }
        if (gameStatus !== 'PLAYING') return;

        if (cell && (cell.classList.contains('cell-HIT') ||
            cell.classList.contains('cell-MISS') ||
            cell.classList.contains('cell-SUNK'))) {
            showMessage('You already shot here!', 'warn');
            return;
        }

        myTurn = false;
        updateTurnBanner(false);

        fetch('${pageContext.request.contextPath}/shoot', {
            method: 'POST',
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
            body: new URLSearchParams({ gameId: GAME_ID, row: row, col: col })
        })
            .then(r => r.json())
            .then(data => {
                if (data.error) {
                    showMessage('ERROR: ' + data.error, 'error');
                    myTurn = true;
                    updateTurnBanner(true);
                    return;
                }

                // Paint the cell immediately — player sees result right away
                if (cell) {
                    cell.classList.remove('cell-UNKNOWN');
                    cell.classList.add('cell-' + data.result);
                    // cell.textContent = data.result === 'MISS' ? 'o' : 'X';
                    cell.title = data.result;
                    cell.onclick = null;
                    cell.style.cursor = 'default';
                }

                if (data.result === 'HIT')  showMessage('Hit!', 'success');
                if (data.result === 'SUNK') showMessage('You sunk a ship!', 'success');
                if (data.result === 'MISS') showMessage('Miss. Opponent\'s turn.', 'info');

                if (data.gameOver) {
                    gameStatus = 'FINISHED';
                    document.getElementById('turnBanner').innerHTML =
                        '<strong>You win! All enemy ships sunk.</strong>';
                    setTimeout(() => window.location.reload(), 1500);
                } else {
                    schedulePoll(500);
                }
            })
            .catch(() => {
                showMessage('Network error. Please try again.', 'error');
                myTurn = true;
                updateTurnBanner(true);
            });
    }

    function applyIncomingShot(row, col, result) {
        const cells = document.querySelectorAll('.my-cell');

        const cell = Array.from(cells).find(c =>
            Number(c.dataset.row) === Number(row) &&
            Number(c.dataset.col) === Number(col)
        );

        if (!cell) {
            return;
        }

        cell.classList.remove('cell-SHIP', 'cell-EMPTY');
        cell.classList.add(result === 'MISS' ? 'cell-MISS' : 'cell-HIT');
        // cell.textContent = result === 'MISS' ? 'o' : 'X';
        cell.title = result;
    }

    function updateTurnBanner(isMine) {
        const banner = document.getElementById('turnBanner');
        if (isMine) {
            banner.innerHTML = '<strong>Your turn.</strong> Click on the enemy grid to fire.';
            banner.className = 'turn-banner my-turn';
        } else {
            banner.innerHTML = '<strong>Opponent\'s turn.</strong> Waiting...';
            banner.className = 'turn-banner opp-turn';
        }
    }

    function showMessage(msg, type) {
        const el = document.getElementById('shotMessage');
        el.textContent = msg;
        el.className = 'shot-message msg-' + type;
        clearTimeout(el._timer);
        el._timer = setTimeout(() => el.className = 'shot-message hidden', 4000);
    }

    if (gameStatus === 'PLAYING') {
        schedulePoll(0);
    }
</script>
</body>
</html>

<%--TODO remove all comments after understanding the project--%>