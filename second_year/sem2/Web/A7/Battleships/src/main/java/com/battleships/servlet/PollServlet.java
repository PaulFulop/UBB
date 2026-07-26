package com.battleships.servlet;

import com.battleships.repositories.GameRepository;
import com.battleships.repositories.ShotRepository;
import com.battleships.model.Game;
import com.battleships.model.Shot;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.*;
import org.json.JSONObject;
import java.io.IOException;
import java.util.List;

public class PollServlet extends HttpServlet {

    private final GameRepository gameRepository = new GameRepository();
    private final ShotRepository shotRepository = new ShotRepository();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        resp.setContentType("application/json");
        resp.setCharacterEncoding("UTF-8");

        int userId = (int) req.getSession().getAttribute("userId");
        JSONObject json = new JSONObject();

        try {
            int gameId = Integer.parseInt(req.getParameter("gameId"));
            Game game  = gameRepository.findById(gameId);

            if (game == null) {
                json.put("error", "Game not found.");
                resp.getWriter().write(json.toString());
                return;
            }

            json.put("status", game.getStatus());
            json.put("player1Id", game.getPlayer1Id());
            json.put("player2Id", game.getPlayer2Id() != null ? game.getPlayer2Id() : JSONObject.NULL);
            json.put("player1Ready", game.isPlayer1Ready());
            json.put("player2Ready", game.isPlayer2Ready());
            json.put("currentTurnPlayerId",
                    game.getCurrentTurnPlayerId() != null ? game.getCurrentTurnPlayerId() : JSONObject.NULL);
            json.put("winnerId",
                    game.getWinnerId() != null ? game.getWinnerId() : JSONObject.NULL);
            json.put("isMyTurn",
                    game.getCurrentTurnPlayerId() != null && game.getCurrentTurnPlayerId() == userId);
            json.put("player1Username", game.getPlayer1Username());
            json.put("player2Username", game.getPlayer2Username() != null ? game.getPlayer2Username() : JSONObject.NULL);

            List<Shot> incomingShots = shotRepository.getShotsAgainstPlayer(gameId, userId);
            org.json.JSONArray shotsArray = new org.json.JSONArray();
            for (Shot s : incomingShots) {
                JSONObject shotObj = new JSONObject();
                shotObj.put("row",    s.getTargetRow());
                shotObj.put("col",    s.getTargetCol());
                shotObj.put("result", s.getResult());
                shotsArray.put(shotObj);
            }
            json.put("incomingShots", shotsArray);

        } catch (Exception e) {
            json.put("error", "Server error: " + e.getMessage());
        }

        resp.getWriter().write(json.toString());
    }
}