package com.battleships.servlet;

import com.battleships.repositories.GameRepository;
import com.battleships.repositories.ShipRepository;
import com.battleships.repositories.ShotRepository;
import com.battleships.model.Game;
import com.battleships.model.Ship;
import com.battleships.model.Shot;
import com.battleships.util.GameConstants;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.*;
import java.io.IOException;
import java.util.List;

/**
 * GameServlet
 * GET /game?gameId=X → Show the game board for both players.
 */
public class GameServlet extends HttpServlet {

    private final GameRepository gameRepository = new GameRepository();
    private final ShipRepository shipRepository = new ShipRepository();
    private final ShotRepository shotRepository = new ShotRepository();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        int userId = (int) req.getSession().getAttribute("userId");
        String gameIdStr = req.getParameter("gameId");

        if (gameIdStr == null) {
            resp.sendRedirect(req.getContextPath() + "/lobby");
            return;
        }

        try {
            int gameId = Integer.parseInt(gameIdStr);
            Game game  = gameRepository.findById(gameId);

            // Verify this player belongs to the game
            if (game == null || (game.getPlayer1Id() != userId &&
                    (game.getPlayer2Id() == null || game.getPlayer2Id() != userId))) {
                resp.sendRedirect(req.getContextPath() + "/lobby");
                return;
            }

            // Determine opponent ID
            int opponentId = (game.getPlayer1Id() == userId)
                    ? (game.getPlayer2Id() != null ? game.getPlayer2Id() : -1)
                    : game.getPlayer1Id();

            // My ships (visible to me always)
            List<Ship> myShips = shipRepository.getShipsForPlayer(gameId, userId);

            // Shots I fired (shown on opponent's grid)
            List<Shot> myShotsOnOpponent = shotRepository.getShotsByPlayer(gameId, userId);

            // Shots opponent fired at me (shown on my grid)
            List<Shot> opponentShotsOnMe = shotRepository.getShotsAgainstPlayer(gameId, userId);

            // Build grid states as 2D arrays for JSP rendering
            // myGrid: shows my ships + opponent's hits on me
            // targetGrid: shows my shots on opponent (hits/misses only, not ship positions)
            String[][] myGrid     = buildMyGrid(myShips, opponentShotsOnMe);
            String[][] targetGrid = buildTargetGrid(myShotsOnOpponent);

            boolean isMyTurn = game.getCurrentTurnPlayerId() != null
                    && game.getCurrentTurnPlayerId() == userId;

            req.setAttribute("game",       game);
            req.setAttribute("myGrid",     myGrid);
            req.setAttribute("targetGrid", targetGrid);
            req.setAttribute("isMyTurn",   isMyTurn);
            req.setAttribute("gridSize",   GameConstants.GRID_SIZE);
            req.setAttribute("opponentId", opponentId);

            req.getRequestDispatcher("/WEB-INF/views/game.jsp").forward(req, resp);

        } catch (Exception e) {
            req.setAttribute("error", "Error loading game: " + e.getMessage());
            req.getRequestDispatcher("/WEB-INF/views/game.jsp").forward(req, resp);
        }
    }

    /**
     * My grid: cells are SHIP, HIT (opponent hit my ship), MISS (opponent missed), or EMPTY.
     */
    private String[][] buildMyGrid(List<Ship> myShips, List<Shot> opponentShots) {
        int size = GameConstants.GRID_SIZE;
        String[][] grid = new String[size][size];
        for (int r = 0; r < size; r++)
            for (int c = 0; c < size; c++)
                grid[r][c] = "EMPTY";

        // Mark ship cells
        for (Ship s : myShips) {
            for (int[] cell : s.getCells()) {
                grid[cell[0]][cell[1]] = "SHIP";
            }
        }

        // Apply opponent's shots on top
        for (Shot shot : opponentShots) {
            int r = shot.getTargetRow();
            int c = shot.getTargetCol();
            if ("HIT".equals(shot.getResult()) || "SUNK".equals(shot.getResult())) {
                grid[r][c] = "HIT";
            } else {
                grid[r][c] = "MISS";
            }
        }

        return grid;
    }

    /**
     * Target grid: only shows where I shot (HIT, MISS, SUNK), everything else is UNKNOWN.
     */
    private String[][] buildTargetGrid(List<Shot> myShots) {
        int size = GameConstants.GRID_SIZE;
        String[][] grid = new String[size][size];
        for (int r = 0; r < size; r++)
            for (int c = 0; c < size; c++)
                grid[r][c] = "UNKNOWN";

        for (Shot shot : myShots) {
            grid[shot.getTargetRow()][shot.getTargetCol()] = shot.getResult();
        }

        return grid;
    }
}