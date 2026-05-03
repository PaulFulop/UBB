<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Battleships – Lobby</title>
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
    <h1>Game Lobby</h1>

    <c:if test="${not empty error}">
        <div class="alert alert-error">${error}</div>
    </c:if>

    <%-- ======================================================= --%>
    <%-- THIS PLAYER CREATED A GAME AND IS WAITING FOR OPPONENT  --%>
    <%-- ======================================================= --%>
    <c:if test="${not empty myWaitingGame}">
        <div class="lobby-card waiting">
            <h2>Waiting for an opponent</h2>
            <p>Your game is open. Another player needs to log in and join.</p>
            <div class="spinner"></div>
            <p class="small">Checking automatically every few seconds...</p>

            <form method="post" action="${pageContext.request.contextPath}/lobby"
                  onsubmit="return confirm('Cancel this game?')">
                <input type="hidden" name="action"  value="cancel">
                <input type="hidden" name="gameId"  value="${myWaitingGame.id}">
                <button type="submit" class="btn btn-danger btn-sm" style="margin-top:1rem;">
                    Cancel Game
                </button>
            </form>
        </div>

        <script>
            // Poll until someone joins, then redirect to ship placement
            (function pollForJoin() {
                fetch('${pageContext.request.contextPath}/poll?gameId=${myWaitingGame.id}')
                    .then(r => r.json())
                    .then(data => {
                        if (data.status === 'PLACING') {
                            window.location.href = '${pageContext.request.contextPath}/place-ships?gameId=${myWaitingGame.id}';
                        } else if (data.status === 'CANCELLED') {
                            window.location.href = '${pageContext.request.contextPath}/lobby';
                        } else {
                            setTimeout(pollForJoin, 3000);
                        }
                    })
                    .catch(() => setTimeout(pollForJoin, 3000));
            })();
        </script>
    </c:if>

    <%-- ======================================================= --%>
    <%-- PLAYER HAS NO ACTIVE GAME — show lobby options         --%>
    <%-- ======================================================= --%>
    <c:if test="${empty myWaitingGame}">
        <div class="lobby-options">

                <%-- Join card — shown when a game is available (initially from server render) --%>
            <div id="joinCard" class="lobby-card join-card <c:if test='${empty joinableGame}'>hidden</c:if>">
                <h2>Game Available</h2>
                <p>Player <strong id="joinPlayerName">${joinableGame.player1Username}</strong> is waiting for an opponent.</p>
                <form method="post" action="${pageContext.request.contextPath}/lobby" id="joinForm">
                    <input type="hidden" name="action"  value="join">
                    <input type="hidden" name="gameId"  id="joinGameId" value="${joinableGame.id}">
                    <button type="submit" class="btn btn-primary">Join Game</button>
                </form>
            </div>

                <%-- Create card --%>
            <div class="lobby-card create-card">
                <h2>Create New Game</h2>
                <p>Start a game and wait for another player to join.</p>
                <form method="post" action="${pageContext.request.contextPath}/lobby">
                    <input type="hidden" name="action" value="create">
                    <button type="submit" class="btn btn-secondary">Create Game</button>
                </form>
            </div>

        </div>

        <script>
            // Poll lobby every 3s to automatically show/hide the join card
            // when another player creates or cancels a game.
            (function pollLobby() {
                fetch('${pageContext.request.contextPath}/lobby-poll')
                    .then(r => r.json())
                    .then(data => {
                        const card      = document.getElementById('joinCard');
                        const nameEl    = document.getElementById('joinPlayerName');
                        const gameIdEl  = document.getElementById('joinGameId');

                        if (data.hasGame) {
                            nameEl.textContent   = data.player1;
                            gameIdEl.value       = data.gameId;
                            card.classList.remove('hidden');
                        } else {
                            card.classList.add('hidden');
                        }

                        setTimeout(pollLobby, 3000);
                    })
                    .catch(() => setTimeout(pollLobby, 4000));
            })();
        </script>
    </c:if>

    <div class="lobby-info">
        <h3>Testing with two players</h3>
        <ol>
            <li>Open two different browsers (e.g. Chrome and Firefox) or use an Incognito window.</li>
            <li>Register and log in as different users in each window.</li>
            <li>One player clicks <em>Create Game</em>. The other window will show a <em>Join Game</em> button automatically.</li>
            <li>Both players place their ships, then take turns firing.</li>
        </ol>
    </div>
</div>
</body>
</html>

