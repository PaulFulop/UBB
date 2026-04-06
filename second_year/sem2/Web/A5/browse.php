<?php

declare(strict_types=1);
?>
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Recipe Manager - Browse</title>
    <link rel="stylesheet" href="styles.css" />
  </head>
  <body>
    <main class="app-shell">
      <header class="hero">
        <h1>Browse Recipes</h1>
        <p>Use AJAX to load recipes by selected type.</p>
      </header>

      <nav class="top-nav">
        <a href="index.php">Home</a>
        <a href="add.php">Add</a>
        <a href="manage.php">Manage</a>
      </nav>

      <section class="panel">
        <div class="browse-controls">
          <div class="field-inline">
            <label for="type-filter">Recipe type</label>
            <select id="type-filter">
              <option value="all">all</option>
            </select>
          </div>
          <button type="button" id="browse-btn">Load recipes</button>
        </div>

        <p class="previous-filter">Previous filter used: <strong id="previous-filter-value">none</strong></p>

        <div class="table-wrap">
          <table>
            <thead>
              <tr>
                <th>Name</th>
                <th>Author</th>
                <th>Type</th>
                <th>Recipe</th>
              </tr>
            </thead>
            <tbody id="browse-recipes-body"></tbody>
          </table>
        </div>
        <p id="browse-message" class="message"></p>
      </section>
    </main>

    <script src="app.js"></script>
  </body>
</html>
