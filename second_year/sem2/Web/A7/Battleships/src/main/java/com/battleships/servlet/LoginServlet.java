package com.battleships.servlet;

import com.battleships.repositories.GameRepository;
import com.battleships.repositories.UserRepository;
import com.battleships.model.User;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.*;
import java.io.IOException;

public class LoginServlet extends HttpServlet {

    private final UserRepository userRepository = new UserRepository();
    private final GameRepository gameRepository = new GameRepository();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        // If already logged in, go to lobby
        HttpSession session = req.getSession(false);
        if (session != null && session.getAttribute("userId") != null) {
            resp.sendRedirect(req.getContextPath() + "/lobby");
            return;
        }
        req.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");

        // Validation
        if (username == null || username.trim().isEmpty()) {
            req.setAttribute("error", "Username is required.");
            req.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(req, resp);
            return;
        }
        if (password == null || password.trim().isEmpty()) {
            req.setAttribute("error", "Password is required.");
            req.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(req, resp);
            return;
        }

        try {
            User user = userRepository.login(username.trim(), password);
            if (user == null) {
                req.setAttribute("error", "Invalid username or password.");
                req.setAttribute("username", username);
                req.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(req, resp);
                return;
            }

            // Cancel any stale WAITING games this user left behind from a previous session
            gameRepository.abandonWaitingGamesFor(user.getId());

            // Create session
            HttpSession session = req.getSession(true);
            session.setAttribute("userId",   user.getId());
            session.setAttribute("username", user.getUsername());

            resp.sendRedirect(req.getContextPath() + "/lobby");

        } catch (Exception e) {
            req.setAttribute("error", "Database error: " + e.getMessage());
            req.getRequestDispatcher("/WEB-INF/views/login.jsp").forward(req, resp);
        }
    }
}