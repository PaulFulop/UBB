<?php

declare(strict_types=1);

require_once __DIR__ . '/db.php';

$id = (int) ($_GET['id'] ?? $_POST['id'] ?? 0);
$errors = [];
$success = '';
$recipeData = [
    'author' => '',
    'name' => '',
    'type' => '',
    'recipe' => '',
];

if ($id <= 0) {
    $errors[] = 'No valid recipe selected.';
} else {
    try {
        $conn = db_connection();

        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            $validation = normalize_recipe_input($_POST);

            if (!$validation['valid']) {
                $errors = $validation['errors'];
                $recipeData = $validation['data'];
            } else {
                $recipeData = $validation['data'];
                $stmtUpdate = $conn->prepare('UPDATE recipes SET author = ?, name = ?, type = ?, recipe = ? WHERE id = ?');
                $stmtUpdate->bind_param('ssssi', $recipeData['author'], $recipeData['name'], $recipeData['type'], $recipeData['recipe'], $id);
                $stmtUpdate->execute();

                $success = 'Recipe updated successfully.';
            }
        }

        if ($errors === [] || $_SERVER['REQUEST_METHOD'] !== 'POST') {
            $stmt = $conn->prepare('SELECT author, name, type, recipe FROM recipes WHERE id = ?');
            $stmt->bind_param('i', $id);
            $stmt->execute();
            $result = $stmt->get_result();
            $row = $result->fetch_assoc();

            if ($row === null) {
                $errors[] = 'Recipe not found.';
            } else {
                $recipeData = $row;
            }
        }
    } catch (Throwable $e) {
        $errors[] = 'Database error: ' . $e->getMessage();
    }
}
?>
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Recipe Manager - Edit</title>
    <link rel="stylesheet" href="styles.css" />
  </head>
  <body>
    <main class="app-shell">
      <header class="hero">
        <h1>Edit Recipe</h1>
        <p>Update recipe details with prefilled data.</p>
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

        <?php if ($errors === [] || $recipeData['name'] !== ''): ?>
          <form method="post" id="recipe-edit-form" class="js-cancel-form">
            <input type="hidden" name="id" value="<?= $id ?>" />

            <label for="name">Recipe name</label>
            <input id="name" name="name" type="text" minlength="2" maxlength="120" required value="<?= esc($recipeData['name']) ?>" />

            <label for="author">Author</label>
            <input id="author" name="author" type="text" minlength="2" maxlength="100" required value="<?= esc($recipeData['author']) ?>" />

            <label for="type">Type</label>
            <input id="type" name="type" type="text" pattern="[A-Za-z ]{3,40}" required value="<?= esc($recipeData['type']) ?>" />

            <label for="recipe">Actual recipe</label>
            <textarea id="recipe" name="recipe" rows="7" minlength="10" maxlength="4000" required><?= esc($recipeData['recipe']) ?></textarea>

            <div class="form-actions">
              <button type="submit">Update recipe</button>
              <a class="button-link ghost js-cancel-link" href="manage.php">Cancel</a>
            </div>
          </form>
        <?php endif; ?>
      </section>
    </main>

    <script src="app.js"></script>
  </body>
</html>
