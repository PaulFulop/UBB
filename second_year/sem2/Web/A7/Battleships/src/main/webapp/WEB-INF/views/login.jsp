<%@ page contentType="text/html;charset=UTF-8" %>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Battleships – Login</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/css/style.css">
</head>
<body class="auth-page">
<div class="auth-container">
    <div class="auth-card">
        <div class="logo">BATTLESHIPS</div>
        <h2>Sign In</h2>

        <% if ("1".equals(request.getParameter("registered"))) { %>
            <div class="alert alert-success">Account created! You can now log in.</div>
        <% } %>
        <% if ("1".equals(request.getParameter("logout"))) { %>
            <div class="alert alert-info">You have been logged out.</div>
        <% } %>
        <% if (request.getAttribute("error") != null) { %>
            <div class="alert alert-error">${error}</div>
        <% } %>

        <form method="post" action="${pageContext.request.contextPath}/login" novalidate>
            <div class="form-group">
                <label for="username">Username</label>
                <input type="text" id="username" name="username"
                       value="${username}" required minlength="1"
                       placeholder="Enter your username">
                <span class="field-hint" id="usernameHint"></span>
            </div>
            <div class="form-group">
                <label for="password">Password</label>
                <input type="password" id="password" name="password"
                       required placeholder="Enter your password">
                <span class="field-hint" id="passwordHint"></span>
            </div>
            <button type="submit" class="btn btn-primary btn-full">Login</button>
        </form>

        <p class="auth-link">Don't have an account?
            <a href="${pageContext.request.contextPath}/register">Register here</a>
        </p>
    </div>
</div>

<script>
    document.querySelector('form').addEventListener('submit', function(e) {
        let valid = true;
        const username = document.getElementById('username');
        const password = document.getElementById('password');
        const uHint = document.getElementById('usernameHint');
        const pHint = document.getElementById('passwordHint');

        uHint.textContent = '';
        pHint.textContent = '';

        if (!username.value.trim()) {
            uHint.textContent = 'Username is required.';
            username.classList.add('error');
            valid = false;
        } else {
            username.classList.remove('error');
        }

        if (!password.value) {
            pHint.textContent = 'Password is required.';
            password.classList.add('error');
            valid = false;
        } else {
            password.classList.remove('error');
        }

        if (!valid) e.preventDefault();
    });
</script>
</body>
</html>
