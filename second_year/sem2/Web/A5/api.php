<?php

declare(strict_types=1);

require_once __DIR__ . '/db.php';

header('Content-Type: application/json; charset=utf-8');

function send_json(int $status, array $payload): void
{
    http_response_code($status);
    echo json_encode($payload, JSON_UNESCAPED_UNICODE);
    exit;
}

function get_json_body(): array
{
    $raw = file_get_contents('php://input');
    if ($raw === false || trim($raw) === '') {
        return [];
    }

    $data = json_decode($raw, true);
    if (!is_array($data)) {
        send_json(400, ['error' => 'Invalid JSON body']);
    }

    return $data;
}

$method = $_SERVER['REQUEST_METHOD'] ?? 'GET';
$action = $_GET['action'] ?? '';

try {
    $db = db_connection();

    if ($method === 'GET' && $action === 'types') {
        $result = $db->query('SELECT DISTINCT type FROM recipes ORDER BY type ASC');
        $types = [];

        while ($row = $result->fetch_assoc()) {
            $types[] = $row['type'];
        }

        send_json(200, ['types' => $types]);
    }

    if ($method === 'GET' && $action === 'list') {
        $type = trim((string) ($_GET['type'] ?? ''));

        if ($type !== '' && strtolower($type) !== 'all') {
            $stmt = $db->prepare('SELECT id, author, name, type, recipe, created_at, updated_at FROM recipes WHERE type = ? ORDER BY id DESC');
            $stmt->bind_param('s', $type);
            $stmt->execute();
            $recipes = stmt_fetch_all_assoc($stmt);
        } else {
            $result = $db->query('SELECT id, author, name, type, recipe, created_at, updated_at FROM recipes ORDER BY id DESC');
            $recipes = [];

            while ($row = $result->fetch_assoc()) {
                $recipes[] = $row;
            }
        }

        send_json(200, ['recipes' => $recipes]);
    }

    if ($method === 'POST' && $action === 'create') {
        $validation = normalize_recipe_input(get_json_body());
        if (!$validation['valid']) {
            send_json(422, ['error' => implode(' ', $validation['errors'])]);
        }
        $payload = $validation['data'];

        $stmt = $db->prepare('INSERT INTO recipes (author, name, type, recipe) VALUES (?, ?, ?, ?)');
        $stmt->bind_param('ssss', $payload['author'], $payload['name'], $payload['type'], $payload['recipe']);
        $stmt->execute();

        send_json(201, ['message' => 'Recipe created', 'id' => $db->insert_id]);
    }

    if ($method === 'PUT' && $action === 'update') {
        $id = (int) ($_GET['id'] ?? 0);
        if ($id <= 0) {
            send_json(422, ['error' => 'Valid id is required']);
        }

        $validation = normalize_recipe_input(get_json_body());
        if (!$validation['valid']) {
            send_json(422, ['error' => implode(' ', $validation['errors'])]);
        }
        $payload = $validation['data'];

        $stmt = $db->prepare('UPDATE recipes SET author = ?, name = ?, type = ?, recipe = ? WHERE id = ?');
        $stmt->bind_param('ssssi', $payload['author'], $payload['name'], $payload['type'], $payload['recipe'], $id);
        $stmt->execute();

        if ($stmt->affected_rows === 0) {
            $check = $db->prepare('SELECT id FROM recipes WHERE id = ?');
            $check->bind_param('i', $id);
            $check->execute();
            $existing = stmt_fetch_one_assoc($check);

            if ($existing === null) {
                send_json(404, ['error' => 'Recipe not found']);
            }
        }

        send_json(200, ['message' => 'Recipe updated']);
    }

    if ($method === 'DELETE' && $action === 'delete') {
        $id = (int) ($_GET['id'] ?? 0);
        if ($id <= 0) {
            send_json(422, ['error' => 'Valid id is required']);
        }

        $stmt = $db->prepare('DELETE FROM recipes WHERE id = ?');
        $stmt->bind_param('i', $id);
        $stmt->execute();

        if ($stmt->affected_rows === 0) {
            send_json(404, ['error' => 'Recipe not found']);
        }

        send_json(200, ['message' => 'Recipe deleted']);
    }

    send_json(404, ['error' => 'Unknown endpoint']);
} catch (Throwable $e) {
    send_json(500, ['error' => 'Server error', 'details' => $e->getMessage()]);
}
