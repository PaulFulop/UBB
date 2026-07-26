<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Battleships – Place Your Ships</title>
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
    <h1>Place Your Ships</h1>
    <p class="subtitle">Game #${game.id} — Click on the grid to position each ship.</p>

    <c:if test="${not empty error}">
        <div class="alert alert-error">${error}</div>
    </c:if>

    <div class="placement-layout">
        <div class="placement-sidebar">
            <div class="ship-panel">
                <h3>Your Ships</h3>

                <div class="ship-item" id="ship1-panel">
                    <div class="ship-label">
                        <span class="ship-number">Ship 1</span>
                        <span class="ship-size">(${ship1Length} cells)</span>
                        <span class="ship-status" id="ship1-status">Not placed</span>
                    </div>
                    <div class="ship-controls">
                        <label>Orientation:</label>
                        <select id="ship1-orientation">
                            <option value="HORIZONTAL">Horizontal →</option>
                            <option value="VERTICAL">Vertical ↓</option>
                        </select>
                    </div>
                </div>

                <div class="ship-item" id="ship2-panel">
                    <div class="ship-label">
                        <span class="ship-number">Ship 2</span>
                        <span class="ship-size">(${ship2Length} cells)</span>
                        <span class="ship-status" id="ship2-status">Not placed</span>
                    </div>
                    <div class="ship-controls">
                        <label>Orientation:</label>
                        <select id="ship2-orientation">
                            <option value="HORIZONTAL">Horizontal →</option>
                            <option value="VERTICAL">Vertical ↓</option>
                        </select>
                    </div>
                </div>

                <div class="placement-tip">
                    <p>Click a grid cell to place the selected ship there.</p>
                    <p>Click again on a placed ship to re-place it.</p>
                </div>

                <form method="post" action="${pageContext.request.contextPath}/place-ships" id="placeForm">
                    <input type="hidden" name="gameId" value="${game.id}">
                    <input type="hidden" name="ship1Row" id="ship1Row">
                    <input type="hidden" name="ship1Col" id="ship1Col">
                    <input type="hidden" name="ship1Orientation" id="ship1OrientationInput">
                    <input type="hidden" name="ship2Row" id="ship2Row">
                    <input type="hidden" name="ship2Col" id="ship2Col">
                    <input type="hidden" name="ship2Orientation" id="ship2OrientationInput">
                    <button type="button" class="btn btn-primary btn-full" id="confirmBtn" disabled
                            onclick="confirmPlacement()">
                        Confirm Placement
                    </button>
                </form>
            </div>
        </div>

        <div class="grid-wrapper">
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
                        <div class="grid-cell placement-cell"
                             data-row="${r}" data-col="${c}"
                             onclick="cellClick(${r}, ${c})">
                        </div>
                    </c:forEach>
                </div>
            </c:forEach>
        </div>
    </div>
</div>

<script>
    const GRID_SIZE   = ${gridSize};
    const SHIP1_LEN   = ${ship1Length};
    const SHIP2_LEN   = ${ship2Length};
    const COLS_LABELS = ['A','B','C','D','E','F','G','H'];

    let ships = {
        1: null,
        2: null
    };
    let placingShip = 1;

    function getOrientation(shipNum) {
        return document.getElementById('ship' + shipNum + '-orientation').value;
    }

    function getLength(shipNum) {
        return shipNum === 1 ? SHIP1_LEN : SHIP2_LEN;
    }

    function cellClick(row, col) {
        const orientation = getOrientation(placingShip);
        const len = getLength(placingShip);

        if (orientation === 'HORIZONTAL' && col + len > GRID_SIZE) {
            alert('Ship ' + placingShip + ' goes out of bounds horizontally. Choose a different cell.');
            return;
        }
        if (orientation === 'VERTICAL' && row + len > GRID_SIZE) {
            alert('Ship ' + placingShip + ' goes out of bounds vertically. Choose a different cell.');
            return;
        }


        const otherShipNum = placingShip === 1 ? 2 : 1;
        if (ships[otherShipNum]) {
            const newCells = getCells(row, col, len, orientation);
            const otherCells = getCells(
                ships[otherShipNum].row,
                ships[otherShipNum].col,
                getLength(otherShipNum),
                ships[otherShipNum].orientation
            );
            for (const nc of newCells) {
                for (const oc of otherCells) {
                    if (nc[0] === oc[0] && nc[1] === oc[1]) {
                        alert('Ships cannot overlap!');
                        return;
                    }
                }
            }
        }

        ships[placingShip] = { row, col, orientation };

        renderGrid();
        updateStatus();

        if (placingShip === 1 && !ships[2]) placingShip = 2;
        else if (placingShip === 2 && !ships[1]) placingShip = 1;
    }

    function getCells(row, col, len, orientation) {
        const cells = [];
        for (let i = 0; i < len; i++) {
            if (orientation === 'HORIZONTAL') cells.push([row, col + i]);
            else cells.push([row + i, col]);
        }
        return cells;
    }

    function renderGrid() {
        const cells = document.querySelectorAll('.placement-cell');

        cells.forEach(cell => {
            cell.className = 'grid-cell placement-cell';
            cell.title = '';
        });


        for (const shipNum of [1, 2]) {
            const s = ships[shipNum];
            if (!s) continue;

            const shipCells = getCells(
                s.row,
                s.col,
                getLength(shipNum),
                s.orientation
            );

            shipCells.forEach(([r, c]) => {
                const cell = Array.from(cells).find(el =>
                    Number(el.dataset.row) === r &&
                    Number(el.dataset.col) === c
                );

                if (cell) {
                    cell.classList.add('ship-' + shipNum);
                    cell.title = 'Ship ' + shipNum;
                }
            });
        }
    }

    function updateStatus() {
        for (const shipNum of [1, 2]) {
            const statusEl = document.getElementById('ship' + shipNum + '-status');
            if (ships[shipNum]) {
                const s = ships[shipNum];
                statusEl.textContent = COLS_LABELS[s.col] + (s.row + 1) + ' ' + s.orientation.charAt(0);
                statusEl.style.color = '#2ecc71';
            } else {
                statusEl.textContent = 'Not placed';
                statusEl.style.color = '#e74c3c';
            }
        }

        const allPlaced = ships[1] && ships[2];
        document.getElementById('confirmBtn').disabled = !allPlaced;
    }

    document.getElementById('ship1-orientation').addEventListener('change', () => {
        ships[1] = null;  // reset ship 1 when orientation changes
        placingShip = 1;
        renderGrid();
        updateStatus();
    });
    document.getElementById('ship2-orientation').addEventListener('change', () => {
        ships[2] = null;
        placingShip = 2;
        renderGrid();
        updateStatus();
    });

    function confirmPlacement() {
        if (!ships[1] || !ships[2]) {
            alert('Please place both ships before confirming.');
            return;
        }

        document.getElementById('ship1Row').value = ships[1].row;
        document.getElementById('ship1Col').value = ships[1].col;
        document.getElementById('ship1OrientationInput').value = ships[1].orientation;
        document.getElementById('ship2Row').value = ships[2].row;
        document.getElementById('ship2Col').value = ships[2].col;
        document.getElementById('ship2OrientationInput').value = ships[2].orientation;

        document.getElementById('placeForm').submit();
    }

    document.getElementById('ship1-panel').addEventListener('click', () => { placingShip = 1; highlightActive(); });
    document.getElementById('ship2-panel').addEventListener('click', () => { placingShip = 2; highlightActive(); });

    function highlightActive() {
        document.getElementById('ship1-panel').classList.toggle('active-ship', placingShip === 1);
        document.getElementById('ship2-panel').classList.toggle('active-ship', placingShip === 2);
    }

    document.querySelectorAll('.placement-cell').forEach(cell => {
        cell.addEventListener('mouseenter', function() {
            const r = parseInt(this.dataset.row);
            const c = parseInt(this.dataset.col);
            const orientation = getOrientation(placingShip);
            const len = getLength(placingShip);
            const cells = getCells(r, c, len, orientation);
            cells.forEach(([pr, pc]) => {
                const el = document.querySelector(`.placement-cell[data-row="${pr}"][data-col="${pc}"]`);
                if (el && !el.classList.contains('ship-1') && !el.classList.contains('ship-2')) {
                    el.classList.add('preview');
                }
            });
        });
        cell.addEventListener('mouseleave', function() {
            document.querySelectorAll('.placement-cell.preview').forEach(el => el.classList.remove('preview'));
        });
    });

    highlightActive();
</script>
</body>
</html>
