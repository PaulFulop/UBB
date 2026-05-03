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
import org.json.JSONObject;
import java.io.IOException;
import java.util.List;

/**
 * ShotServlet - handles AJAX POST when a player fires a shot.
 *
 * POST /shoot
 * Parameters: gameId, row, col
 * Returns JSON: { result, gameOver, winner, nextTurn }
 */
public class ShotServlet extends HttpServlet {

    private final GameRepository gameRepository = new GameRepository();
    private final ShipRepository shipRepository = new ShipRepository();
    private final ShotRepository shotRepository = new ShotRepository();

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        resp.setContentType("application/json");
        resp.setCharacterEncoding("UTF-8");

        int userId = (int) req.getSession().getAttribute("userId");
        JSONObject json = new JSONObject();

        try {
            int gameId = Integer.parseInt(req.getParameter("gameId"));
            int row    = Integer.parseInt(req.getParameter("row"));
            int col    = Integer.parseInt(req.getParameter("col"));

            Game game = gameRepository.findById(gameId);

            // Validate game state
            if (game == null || !"PLAYING".equals(game.getStatus())) {
                json.put("error", "Game is not in playing state.");
                resp.getWriter().write(json.toString());
                return;
            }

            // Validate it's this player's turn
            if (game.getCurrentTurnPlayerId() == null || game.getCurrentTurnPlayerId() != userId) {
                json.put("error", "It's not your turn.");
                resp.getWriter().write(json.toString());
                return;
            }

            // Validate coordinates
            if (row < 0 || row >= GameConstants.GRID_SIZE || col < 0 || col >= GameConstants.GRID_SIZE) {
                json.put("error", "Invalid coordinates.");
                resp.getWriter().write(json.toString());
                return;
            }

            // Check if already shot here
            if (shotRepository.alreadyShot(gameId, userId, row, col)) {
                json.put("error", "You already shot at that position.");
                resp.getWriter().write(json.toString());
                return;
            }

            // Determine opponent
            int opponentId = (game.getPlayer1Id() == userId) ? game.getPlayer2Id() : game.getPlayer1Id();

            // Check if any of the opponent's ships is at this cell
            List<Ship> opponentShips = shipRepository.getShipsForPlayer(gameId, opponentId);
            String result = "MISS";
            Ship hitShip  = null;

            for (Ship s : opponentShips) {
                if (s.occupies(row, col)) {
                    hitShip = s;
                    result = "HIT";
                    break;
                }
            }

            // Check if the hit ship is fully sunk
            if ("HIT".equals(result) && hitShip != null) {
                // Count hits on this specific ship
                List<Shot> previousShots = shotRepository.getShotsByPlayer(gameId, userId);
                int hitsOnThisShip = 0;
                for (int[] cell : hitShip.getCells()) {
                    // count previously recorded hits on this ship's cells
                    boolean cellWasHit = false;
                    for (Shot prevShot : previousShots) {
                        if (prevShot.getTargetRow() == cell[0] && prevShot.getTargetCol() == cell[1]) {
                            cellWasHit = true;
                            break;
                        }
                    }
                    if (cellWasHit) hitsOnThisShip++;
                }
                // +1 for the current shot
                hitsOnThisShip++;

                if (hitsOnThisShip >= hitShip.getLength()) {
                    result = "SUNK";
                }
            }

            // Save the shot
            Shot shot = new Shot();
            shot.setGameId(gameId);
            shot.setShooterPlayerId(userId);
            shot.setTargetRow(row);
            shot.setTargetCol(col);
            shot.setResult(result);
            shotRepository.saveShot(shot);

            json.put("result", result);

            // Check win condition: total ship cells for the opponent
            int totalOpponentShipCells = opponentShips.stream()
                    .mapToInt(Ship::getLength).sum();
            int totalHitsOnOpponent = shotRepository.countHitsOnPlayer(gameId, opponentId);

            boolean gameOver = (totalHitsOnOpponent >= totalOpponentShipCells);

            if (gameOver) {
                gameRepository.finishGame(gameId, userId);
                json.put("gameOver", true);
                json.put("winner", req.getSession().getAttribute("username"));
            } else {
                json.put("gameOver", false);
                // Switch turn
                gameRepository.switchTurn(gameId, opponentId);
                json.put("nextTurn", opponentId);
            }

        } catch (NumberFormatException e) {
            json.put("error", "Invalid parameters.");
        } catch (Exception e) {
            json.put("error", "Server error: " + e.getMessage());
        }

        resp.getWriter().write(json.toString());
    }
}