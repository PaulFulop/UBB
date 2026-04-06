<?php

declare(strict_types=1);

require_once __DIR__ . '/db.php';

$errors = [];
$success = '';

if ($_SERVER['REQUEST_METHOD'] === 'POST' && ($_POST['action'] ?? '') === 'delete') {
    $id = (int) ($_POST['id'] ?? 0);

    if ($id <= 0) {
        $errors[] = 'Invalid recipe selected for delete.';
    } else {
        try {
            $conn = db_connection();
            $stmt = $conn->prepare('DELETE FROM recipes WHERE id = ?');
            $stmt->bind_param('i', $id);
            $stmt->execute();

            if ($stmt->affected_rows > 0) {
                $success = 'Recipe deleted successfully.';
            } else {
                $errors[] = 'Recipe not found.';
            }
        } catch (Throwable $e) {
            $errors[] = 'Database error: ' . $e->getMessage();
        }
    }
}

$recipes = [];

try {
    $conn = db_connection();
    $result = $conn->query('SELECT id, author, name, type, recipe FROM recipes ORDER BY id DESC');
    while ($row = $result->fetch_assoc()) {
        $recipes[] = $row;
    }
} catch (Throwable $e) {
    $errors[] = 'Database error: ' . $e->getMessage();
}
?>
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Recipe Manager - Manage</title>
    <link rel="stylesheet" href="styles.css" />
  </head>
  <body>
    <main class="app-shell">
      <header class="hero">
        <h1>Manage Recipes</h1>
        <p>Edit and delete recipes by selecting entries from the list.</p>
      </header>

      <nav class="top-nav">
        <a href="index.php">Home</a>
        <a href="browse.php">Browse</a>
        <a href="add.php">Add</a>
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

        <div class="table-wrap">
          <table>
            <thead>
              <tr>
                <th>Name</th>
                <th>Author</th>
                <th>Type</th>
                <th>Recipe</th>
                <th>Actions</th>
              </tr>
            </thead>
            <tbody>
              <?php if ($recipes === []): ?>
                <tr>
                  <td colspan="5">No recipes found.</td>
                </tr>
              <?php else: ?>
                <?php foreach ($recipes as $recipe): ?>
                  <tr>
                    <td><?= esc($recipe['name']) ?></td>
                    <td><?= esc($recipe['author']) ?></td>
                    <td><?= esc($recipe['type']) ?></td>
                    <td><?= esc($recipe['recipe']) ?></td>
                    <td class="actions">
                      <a class="button-link" href="edit.php?id=<?= (int) $recipe['id'] ?>">Edit</a>
                      <form method="post" class="inline-form js-delete-form">
                        <input type="hidden" name="action" value="delete" />
                        <input type="hidden" name="id" value="<?= (int) $recipe['id'] ?>" />
                        <button type="submit" class="danger">Delete</button>
                      </form>
                    </td>
                  </tr>
                <?php endforeach; ?>
              <?php endif; ?>
            </tbody>
          </table>
        </div>
      </section>
    </main>

    <script src="app.js"></script>
  </body>
</html>
