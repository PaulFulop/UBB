<?php

declare(strict_types=1);

require_once __DIR__ . '/db.php';

$errors = [];
$success = '';
$values = [
    'author' => '',
    'name' => '',
    'type' => '',
    'recipe' => '',
];

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $validation = normalize_recipe_input($_POST);
    $values = $validation['data'];

    if (!$validation['valid']) {
        $errors = $validation['errors'];
    } else {
        try {
            $conn = db_connection();
            $stmt = $conn->prepare('INSERT INTO recipes(author, name, type, recipe) VALUES (?, ?, ?, ?)');
            $stmt->bind_param('ssss', $values['author'], $values['name'], $values['type'], $values['recipe']);
            $stmt->execute();

            $success = 'Recipe added successfully.';
            $values = ['author' => '', 'name' => '', 'type' => '', 'recipe' => ''];
        } catch (Throwable $e) {
            $errors[] = 'Database error: ' . $e->getMessage();
        }
    }
}
?>
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Recipe Manager - Add</title>
    <link rel="stylesheet" href="styles.css" />
  </head>
  <body>
    <main class="app-shell">
      <header class="hero">
        <h1>Add Recipe</h1>
        <p>Insert a new recipe in the MySQL database.</p>
      </header>

      <nav class="top-nav">
        <a href="index.php">Home</a>
        <a href="browse.php">Browse</a>
        <a href="manage.php">Manage</a>
      </nav>

      <section class="panel">
        <?php if ($success !== ''): ?>
          <p class="message"><?= esc($success) ?></p>
        <?php endif; ?>

        <?php if ($errors !== []): ?>
          <div class="message error">
            <?php foreach ($errors as $error): ?>
              <p><?= esc($error) ?></p>
            <?php endforeach; ?>
          </div>
        <?php endif; ?>

        <form method="post" id="recipe-create-form">
          <label for="name">Recipe name</label>
          <input id="name" name="name" type="text" minlength="2" maxlength="120" required value="<?= esc($values['name']) ?>" />

          <label for="author">Author</label>
          <input id="author" name="author" type="text" minlength="2" maxlength="100" required value="<?= esc($values['author']) ?>" />

          <label for="type">Type</label>
          <input id="type" name="type" type="text" pattern="[A-Za-z ]{3,40}" required value="<?= esc($values['type']) ?>" />

          <label for="recipe">Actual recipe</label>
          <textarea id="recipe" name="recipe" rows="7" minlength="10" maxlength="4000" required><?= esc($values['recipe']) ?></textarea>

          <div class="form-actions">
            <button type="submit">Add recipe</button>
            <a class="button-link ghost" href="index.php">Cancel</a>
          </div>
        </form>
      </section>
    </main>
  </body>
</html>
