<?php

declare(strict_types=1);
?>
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Recipe Manager - Home</title>
    <link rel="stylesheet" href="styles.css" />
  </head>
  <body>
    <main class="app-shell">
      <header class="hero">
        <h1>Recipe Manager</h1>
        <p>PHP + MySQL web app with AJAX browsing and full CRUD.</p>
      </header>

      <section class="panel nav-grid">
        <a class="nav-card" href="browse.php">
          <h2>Browse Recipes</h2>
          <p>Filter by type with asynchronous AJAX loading.</p>
        </a>

        <a class="nav-card" href="add.php">
          <h2>Add Recipe</h2>
          <p>Create a new recipe with client and server validation.</p>
        </a>

        <a class="nav-card" href="manage.php">
          <h2>Manage Recipes</h2>
          <p>Edit or delete recipes without typing IDs manually.</p>
        </a>

        <a class="nav-card" href="edit.php">
          <h2>Edit Page</h2>
          <p>Dedicated edit interface reached from manage list.</p>
        </a>

        <a class="nav-card" href="api.php?action=list&type=all">
          <h2>API Preview</h2>
          <p>JSON endpoint for recipes list (debug/testing).</p>
        </a>
      </section>
    </main>
  </body>
</html>
