package com.battleships.servlet;

import com.battleships.repositories.GameRepository;
import com.battleships.model.Game;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.*;
import java.io.IOException;

public class ForfeitServlet extends HttpServlet {

    private final GameRepository gameRepository = new GameRepository();

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        int userId = (int) req.getSession().getAttribute("userId");

        try {
            int gameId = Integer.parseInt(req.getParameter("gameId"));
            Game game  = gameRepository.findById(gameId);

            if (game == null) {
                resp.sendRedirect(req.getContextPath() + "/lobby");
                return;
            }
            boolean belongs = game.getPlayer1Id() == userId ||
                    (game.getPlayer2Id() != null && game.getPlayer2Id() == userId);
            if (!belongs) {
                resp.sendRedirect(req.getContextPath() + "/lobby");
                return;
            }

            if (!"PLAYING".equals(game.getStatus())) {
                resp.sendRedirect(req.getContextPath() + "/game?gameId=" + gameId);
                return;
            }

            gameRepository.forfeitGame(gameId, userId);
            resp.sendRedirect(req.getContextPath() + "/game?gameId=" + gameId);

        } catch (NumberFormatException e) {
            resp.sendRedirect(req.getContextPath() + "/lobby");
        } catch (Exception e) {
            resp.sendRedirect(req.getContextPath() + "/lobby");
        }
    }
}