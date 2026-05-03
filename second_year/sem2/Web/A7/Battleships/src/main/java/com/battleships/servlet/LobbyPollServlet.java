package com.battleships.servlet;
import com.battleships.model.Game;
import com.battleships.repositories.GameRepository;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.*;
import org.json.JSONObject;
import java.io.IOException;

/**
 * LobbyPollServlet
 *
 * GET /lobby-poll
 *
 * Called by the lobby page every few seconds.
 * Returns JSON describing whether a joinable game exists.
 * This is what makes Player 2's screen update automatically
 * when Player 1 creates a game — without either player refreshing.
 */
public class LobbyPollServlet extends HttpServlet {

    private final GameRepository gameDAO = new GameRepository();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        resp.setContentType("application/json");
        resp.setCharacterEncoding("UTF-8");

        int userId = (int) req.getSession().getAttribute("userId");
        JSONObject json = new JSONObject();

        try {
            Game joinable = gameDAO.findWaitingGame(userId);
            if (joinable != null) {
                json.put("hasGame",    true);
                json.put("gameId",     joinable.getId());
                json.put("player1",    joinable.getPlayer1Username());
            } else {
                json.put("hasGame", false);
            }
        } catch (Exception e) {
            json.put("error", e.getMessage());
        }

        resp.getWriter().write(json.toString());
    }
}