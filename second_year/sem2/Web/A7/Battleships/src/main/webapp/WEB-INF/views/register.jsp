<%@ page contentType="text/html;charset=UTF-8" %>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Battleships – Register</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/css/style.css">
</head>
<body class="auth-page">
<div class="auth-container">
    <div class="auth-card">
        <div class="logo">⚓ BATTLESHIPS</div>
        <h2>Create Account</h2>

        <% if (request.getAttribute("error") != null) { %>
            <div class="alert alert-error">${error}</div>
        <% } %>

        <form method="post" action="${pageContext.request.contextPath}/register" novalidate>
            <div class="form-group">
                <label for="username">Username</label>
                <input type="text" id="username" name="username"
                       value="${username}" required minlength="3"
                       placeholder="At least 3 characters">
                <span class="field-hint" id="usernameHint"></span>
            </div>
            <div class="form-group">
                <label for="password">Password</label>
                <input type="password" id="password" name="password"
                       required minlength="4" placeholder="At least 4 characters">
                <span class="field-hint" id="passwordHint"></span>
            </div>
            <div class="form-group">
                <label for="confirmPassword">Confirm Password</label>
                <input type="password" id="confirmPassword" name="confirmPassword"
                       required placeholder="Repeat your password">
                <span class="field-hint" id="confirmHint"></span>
            </div>
            <button type="submit" class="btn btn-primary btn-full">Register</button>
        </form>

        <p class="auth-link">Already have an account?
            <a href="${pageContext.request.contextPath}/login">Login here</a>
        </p>
    </div>
</div>

<script>
    document.querySelector('form').addEventListener('submit', function(e) {
        let valid = true;
        const username = document.getElementById('username');
        const password = document.getElementById('password');
        const confirm  = document.getElementById('confirmPassword');
        const uHint = document.getElementById('usernameHint');
        const pHint = document.getElementById('passwordHint');
        const cHint = document.getElementById('confirmHint');

        [uHint, pHint, cHint].forEach(h => h.textContent = '');
        [username, password, confirm].forEach(f => f.classList.remove('error'));

        if (username.value.trim().length < 3) {
            uHint.textContent = 'Username must be at least 3 characters.';
            username.classList.add('error');
            valid = false;
        }
        if (password.value.length < 4) {
            pHint.textContent = 'Password must be at least 4 characters.';
            password.classList.add('error');
            valid = false;
        }
        if (password.value !== confirm.value) {
            cHint.textContent = 'Passwords do not match.';
            confirm.classList.add('error');
            valid = false;
        }

        if (!valid) e.preventDefault();
    });
</script>
</body>
</html>
