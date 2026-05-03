package com.battleships.servlet;

import com.battleships.repositories.UserRepository;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.*;
import java.io.IOException;

public class RegisterServlet extends HttpServlet {

    private final UserRepository userRepository = new UserRepository();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        req.getRequestDispatcher("/WEB-INF/views/register.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        String confirm  = req.getParameter("confirmPassword");

        // Validation
        if (username == null || username.trim().length() < 3) {
            req.setAttribute("error", "Username must be at least 3 characters.");
            req.setAttribute("username", username);
            req.getRequestDispatcher("/WEB-INF/views/register.jsp").forward(req, resp);
            return;
        }
        if (password == null || password.length() < 4) {
            req.setAttribute("error", "Password must be at least 4 characters.");
            req.setAttribute("username", username);
            req.getRequestDispatcher("/WEB-INF/views/register.jsp").forward(req, resp);
            return;
        }
        if (!password.equals(confirm)) {
            req.setAttribute("error", "Passwords do not match.");
            req.setAttribute("username", username);
            req.getRequestDispatcher("/WEB-INF/views/register.jsp").forward(req, resp);
            return;
        }

        try {
            int newId = userRepository.register(username.trim(), password);
            if (newId == -1) {
                req.setAttribute("error", "Username already taken. Choose another.");
                req.setAttribute("username", username);
                req.getRequestDispatcher("/WEB-INF/views/register.jsp").forward(req, resp);
                return;
            }
            // Success — redirect to login with a message
            resp.sendRedirect(req.getContextPath() + "/login?registered=1");

        } catch (Exception e) {
            req.setAttribute("error", "Database error: " + e.getMessage());
            req.getRequestDispatcher("/WEB-INF/views/register.jsp").forward(req, resp);
        }
    }
}