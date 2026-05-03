package com.battleships.filter;

import jakarta.servlet.*;
import jakarta.servlet.http.*;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;

/**
 * SessionFilter: Every request goes through here.
 * If the user is not logged in, they are redirected to /login.
 * Public paths (login, register, static resources) are whitelisted.
 */
public class SessionFilter implements Filter {

    // These paths are accessible WITHOUT being logged in
    private static final List<String> PUBLIC_PATHS = Arrays.asList(
            "/login", "/register"
    );

    @Override
    public void doFilter(ServletRequest req, ServletResponse res, FilterChain chain)
            throws IOException, ServletException {

        HttpServletRequest  request  = (HttpServletRequest)  req;
        HttpServletResponse response = (HttpServletResponse) res;

        String path = request.getServletPath();

        // Allow public paths and static resources (CSS, JS, images)
        boolean isPublic = PUBLIC_PATHS.contains(path)
                || path.startsWith("/css/")
                || path.startsWith("/js/")
                || path.startsWith("/images/");

        if (isPublic) {
            chain.doFilter(req, res);
            return;
        }

        // Check session
        HttpSession session = request.getSession(false);
        boolean loggedIn = (session != null && session.getAttribute("userId") != null);

        if (!loggedIn) {
            response.sendRedirect(request.getContextPath() + "/login");
            return;
        }

        chain.doFilter(req, res);
    }
}