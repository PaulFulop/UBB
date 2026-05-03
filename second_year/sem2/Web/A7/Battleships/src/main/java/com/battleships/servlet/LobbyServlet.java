package com.battleships.servlet;

import com.battleships.repositories.GameRepository;
import com.battleships.model.Game;
import com.battleships.repositories.GameRepository;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.*;
import java.io.IOException;

/**
 * LobbyServlet handles waiting room / matchmaking.
 *
 * GET  /lobby           → show lobby page
 * POST /lobby action=create  → create a new game
 * POST /lobby action=join    → join an existing game
 * POST /lobby action=cancel  → cancel the player's own WAITING game
 */
public class LobbyServlet extends HttpServlet {

    private final GameRepository gameRepository = new GameRepository();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        int userId = (int) req.getSession().getAttribute("userId");

        try {
            // Check if this player is already in an active game
            Game activeGame = gameRepository.findActiveGameForPlayer(userId);

            if (activeGame != null) {
                if ("PLACING".equals(activeGame.getStatus())) {
                    resp.sendRedirect(req.getContextPath() + "/place-ships?gameId=" + activeGame.getId());
                    return;
                } else if ("PLAYING".equals(activeGame.getStatus()) || "FINISHED".equals(activeGame.getStatus())) {
                    resp.sendRedirect(req.getContextPath() + "/game?gameId=" + activeGame.getId());
                    return;
                } else {
                    // WAITING — player1 is waiting. Show waiting state with cancel option.
                    req.setAttribute("myWaitingGame", activeGame);
                    req.getRequestDispatcher("/WEB-INF/views/lobby.jsp").forward(req, resp);
                    return;
                }
            }

            // Player has no active game — show the lobby.
            // Check if someone else has an open game they can join.
            Game joinableGame = gameRepository.findWaitingGame(userId);
            req.setAttribute("joinableGame", joinableGame);
            req.getRequestDispatcher("/WEB-INF/views/lobby.jsp").forward(req, resp);

        } catch (Exception e) {
            req.setAttribute("error", "Error: " + e.getMessage());
            req.getRequestDispatcher("/WEB-INF/views/lobby.jsp").forward(req, resp);
        }
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        int userId = (int) req.getSession().getAttribute("userId");
        String action = req.getParameter("action");

        try {
            if ("cancel".equals(action)) {
                // Cancel this player's own WAITING game
                String gameIdStr = req.getParameter("gameId");
                if (gameIdStr != null) {
                    int gameId = Integer.parseInt(gameIdStr);
                    gameRepository.cancelGame(gameId, userId);
                }
                resp.sendRedirect(req.getContextPath() + "/lobby");
                return;
            }

            // For create/join, make sure the player isn't already in a game
            Game existingGame = gameRepository.findActiveGameForPlayer(userId);
            if (existingGame != null) {
                resp.sendRedirect(req.getContextPath() + "/lobby");
                return;
            }

            if ("create".equals(action)) {
                gameRepository.createGame(userId);
                resp.sendRedirect(req.getContextPath() + "/lobby");

            } else if ("join".equals(action)) {
                String gameIdStr = req.getParameter("gameId");
                if (gameIdStr == null) {
                    resp.sendRedirect(req.getContextPath() + "/lobby");
                    return;
                }
                int gameId = Integer.parseInt(gameIdStr);
                Game game  = gameRepository.findById(gameId);

                if (game == null || !"WAITING".equals(game.getStatus())) {
                    req.setAttribute("error", "That game is no longer available.");
                    doGet(req, resp);
                    return;
                }
                if (game.getPlayer1Id() == userId) {
                    req.setAttribute("error", "You cannot join your own game.");
                    doGet(req, resp);
                    return;
                }

                gameRepository.joinGame(gameId, userId);
                resp.sendRedirect(req.getContextPath() + "/place-ships?gameId=" + gameId);
            }

        } catch (Exception e) {
            req.setAttribute("error", "Error: " + e.getMessage());
            req.getRequestDispatcher("/WEB-INF/views/lobby.jsp").forward(req, resp);
        }
    }
}