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
        String message = "";

        try {
            int gameId = Integer.parseInt(req.getParameter("gameId"));
            int row    = Integer.parseInt(req.getParameter("row"));
            int col    = Integer.parseInt(req.getParameter("col"));

            Game game = gameRepository.findById(gameId);

            if (game == null || !"PLAYING".equals(game.getStatus())) {
                json.put("error", "Game is not in playing state.");
                resp.getWriter().write(json.toString());
                return;
            }

            if (game.getCurrentTurnPlayerId() == null || game.getCurrentTurnPlayerId() != userId) {
                json.put("error", "It's not your turn.");
                resp.getWriter().write(json.toString());
                return;
            }

            if (row < 0 || row >= GameConstants.GRID_SIZE || col < 0 || col >= GameConstants.GRID_SIZE) {
                json.put("error", "Invalid coordinates.");
                resp.getWriter().write(json.toString());
                return;
            }

            if (shotRepository.alreadyShot(gameId, userId, row, col)) {
                json.put("error", "You already shot at that position.");
                resp.getWriter().write(json.toString());
                return;
            }

            int opponentId = (game.getPlayer1Id() == userId) ? game.getPlayer2Id() : game.getPlayer1Id();

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

            int totalOpponentShipCells = opponentShips.stream()
                    .mapToInt(Ship::getLength).sum();

            int totalHitsOnOpponent = shotRepository.countHitsOnPlayer(gameId, opponentId);

            if ("HIT".equals(result) && hitShip != null) {
                List<Shot> previousShots = shotRepository.getShotsByPlayer(gameId, userId);
                int hitsOnThisShip = 0;
                for (int[] cell : hitShip.getCells()) {
                    boolean cellWasHit = false;
                    for (Shot prevShot : previousShots) {
                        if (prevShot.getTargetRow() == cell[0] && prevShot.getTargetCol() == cell[1]) {
                            cellWasHit = true;
                            break;
                        }
                    }
                    if (cellWasHit) hitsOnThisShip++;
                }
                ++hitsOnThisShip;
                ++totalHitsOnOpponent;

                if (hitsOnThisShip >= hitShip.getLength()) {
                    result = "SUNK";
                }
                else{
                    int remainingHits = totalOpponentShipCells - totalHitsOnOpponent;
                    message = "You still have " + remainingHits + " hits.";
                    json.put("remainingHits", message);
                }
            }

            Shot shot = new Shot();
            shot.setGameId(gameId);
            shot.setShooterPlayerId(userId);
            shot.setTargetRow(row);
            shot.setTargetCol(col);
            shot.setResult(result);
            shotRepository.saveShot(shot);

            json.put("result", result);

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