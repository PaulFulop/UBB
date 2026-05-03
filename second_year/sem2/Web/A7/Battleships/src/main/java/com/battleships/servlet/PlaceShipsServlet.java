package com.battleships.servlet;

import com.battleships.repositories.GameRepository;
import com.battleships.repositories.ShipRepository;
import com.battleships.model.Game;
import com.battleships.model.Ship;
import com.battleships.util.GameConstants;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.*;
import java.io.IOException;
import java.util.List;

/**
 * PlaceShipsServlet
 *
 * GET  /place-ships?gameId=X  → Show the ship placement grid
 * POST /place-ships            → Submit ship placements (2 ships)
 */
public class PlaceShipsServlet extends HttpServlet {

    private final GameRepository gameRepository = new GameRepository();
    private final ShipRepository shipRepository = new ShipRepository();

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
            Game game = gameRepository.findById(gameId);

            // Security: make sure this player belongs to this game
            if (game == null || (game.getPlayer1Id() != userId &&
                    (game.getPlayer2Id() == null || game.getPlayer2Id() != userId))) {
                resp.sendRedirect(req.getContextPath() + "/lobby");
                return;
            }

            // If game already PLAYING/FINISHED, redirect
            if ("PLAYING".equals(game.getStatus()) || "FINISHED".equals(game.getStatus())) {
                resp.sendRedirect(req.getContextPath() + "/game?gameId=" + gameId);
                return;
            }

            // Load any ships already placed by this player
            List<Ship> myShips = shipRepository.getShipsForPlayer(gameId, userId);

            req.setAttribute("game",    game);
            req.setAttribute("myShips", myShips);
            req.setAttribute("gridSize", GameConstants.GRID_SIZE);
            req.setAttribute("ship1Length", GameConstants.SHIP_1_LENGTH);
            req.setAttribute("ship2Length", GameConstants.SHIP_2_LENGTH);
            req.getRequestDispatcher("/WEB-INF/views/place_ships.jsp").forward(req, resp);

        } catch (NumberFormatException e) {
            resp.sendRedirect(req.getContextPath() + "/lobby");
        } catch (Exception e) {
            req.setAttribute("error", "Error: " + e.getMessage());
            req.getRequestDispatcher("/WEB-INF/views/place_ships.jsp").forward(req, resp);
        }
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        int userId = (int) req.getSession().getAttribute("userId");

        try {
            int gameId = Integer.parseInt(req.getParameter("gameId"));
            Game game  = gameRepository.findById(gameId);

            if (game == null || (game.getPlayer1Id() != userId &&
                    (game.getPlayer2Id() == null || game.getPlayer2Id() != userId))) {
                resp.sendRedirect(req.getContextPath() + "/lobby");
                return;
            }

            // Parse ship 1
            int s1Row  = Integer.parseInt(req.getParameter("ship1Row"));
            int s1Col  = Integer.parseInt(req.getParameter("ship1Col"));
            String s1O = req.getParameter("ship1Orientation");

            // Parse ship 2
            int s2Row  = Integer.parseInt(req.getParameter("ship2Row"));
            int s2Col  = Integer.parseInt(req.getParameter("ship2Col"));
            String s2O = req.getParameter("ship2Orientation");

            // Validate orientations
            if (!isValidOrientation(s1O) || !isValidOrientation(s2O)) {
                setErrorAndForward(req, resp, gameId, "Invalid orientation.");
                return;
            }

            // Delete previously placed ships (allow re-placement before confirming)
            shipRepository.deleteShipsForPlayer(gameId, userId);

            // Validate and save ship 1
            if (!shipRepository.isValidPlacement(gameId, userId, s1Row, s1Col,
                    GameConstants.SHIP_1_LENGTH, s1O)) {
                setErrorAndForward(req, resp, gameId, "Ship 1 placement is out of bounds or overlaps.");
                return;
            }
            Ship ship1 = new Ship();
            ship1.setGameId(gameId);
            ship1.setOwnerPlayerId(userId);
            ship1.setShipIndex(1);
            ship1.setStartRow(s1Row);
            ship1.setStartCol(s1Col);
            ship1.setLength(GameConstants.SHIP_1_LENGTH);
            ship1.setOrientation(s1O);
            shipRepository.saveShip(ship1);

            // Validate and save ship 2
            if (!shipRepository.isValidPlacement(gameId, userId, s2Row, s2Col,
                    GameConstants.SHIP_2_LENGTH, s2O)) {
                setErrorAndForward(req, resp, gameId, "Ship 2 placement is out of bounds or overlaps.");
                return;
            }
            Ship ship2 = new Ship();
            ship2.setGameId(gameId);
            ship2.setOwnerPlayerId(userId);
            ship2.setShipIndex(2);
            ship2.setStartRow(s2Row);
            ship2.setStartCol(s2Col);
            ship2.setLength(GameConstants.SHIP_2_LENGTH);
            ship2.setOrientation(s2O);
            shipRepository.saveShip(ship2);

            // Mark this player as ready
            gameRepository.setPlayerReady(gameId, userId);

            // Redirect to game page (will show "waiting for opponent" if not both ready)
            resp.sendRedirect(req.getContextPath() + "/game?gameId=" + gameId);

        } catch (NumberFormatException e) {
            resp.sendRedirect(req.getContextPath() + "/lobby");
        } catch (Exception e) {
            req.setAttribute("error", "Error saving ships: " + e.getMessage());
            req.getRequestDispatcher("/WEB-INF/views/place_ships.jsp").forward(req, resp);
        }
    }

    private boolean isValidOrientation(String o) {
        return "HORIZONTAL".equals(o) || "VERTICAL".equals(o);
    }

    private void setErrorAndForward(HttpServletRequest req, HttpServletResponse resp,
                                    int gameId, String msg)
            throws ServletException, IOException {
        try {
            Game game = gameRepository.findById(gameId);
            req.setAttribute("game",    game);
            req.setAttribute("error",   msg);
            req.setAttribute("gridSize", GameConstants.GRID_SIZE);
            req.setAttribute("ship1Length", GameConstants.SHIP_1_LENGTH);
            req.setAttribute("ship2Length", GameConstants.SHIP_2_LENGTH);
        } catch (Exception ignored) {}
        req.getRequestDispatcher("/WEB-INF/views/place_ships.jsp").forward(req, resp);
    }
}