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

function normalize_auth_input(array $source): array
{
    $username = trim((string) ($source['username'] ?? ''));
    $password = (string) ($source['password'] ?? '');

    $errors = [];

    if ($username === '' || mb_strlen($username) < 2 || mb_strlen($username) > 80) {
        $errors[] = 'Username must be between 2 and 80 characters.';
    }

    if ($password === '' || mb_strlen($password) < 4 || mb_strlen($password) > 200) {
        $errors[] = 'Password must be between 4 and 200 characters.';
    }

    return [
        'valid' => $errors === [],
        'errors' => $errors,
        'data' => [
            'username' => $username,
            'password' => $password,
        ],
    ];
}

$method = $_SERVER['REQUEST_METHOD'] ?? 'GET';
$path = trim(parse_url($_SERVER['REQUEST_URI'] ?? '', PHP_URL_PATH) ?? '', '/');
$segments = $path === '' ? [] : array_values(array_filter(explode('/', $path), static fn ($segment) => $segment !== ''));
$apiIndex = array_search('api.php', $segments, true);
$resourceIndex = $apiIndex === false ? 0 : $apiIndex + 1;
$resource = $segments[$resourceIndex] ?? '';
$pathValue = $segments[$resourceIndex + 1] ?? null;
$id = is_string($pathValue) && ctype_digit($pathValue) ? (int) $pathValue : null;

try {
    $db = db_connection();

    if ($resource === 'login' && $method === 'POST') {
        $validation = normalize_auth_input(get_json_body());
        if (!$validation['valid']) {
            send_json(422, ['error' => implode(' ', $validation['errors'])]);
        }

        $payload = $validation['data'];

        $stmt = $db->prepare('SELECT Id FROM users WHERE Username = ? AND Password = ? LIMIT 1');
        $stmt->bind_param('ss', $payload['username'], $payload['password']);
        $stmt->execute();
        $user = stmt_fetch_one_assoc($stmt);

        if ($user === null) {
            send_json(401, ['error' => 'Invalid username or password']);
        }

        send_json(200, ['message' => 'Login successful']);
    }

    if ($resource === 'register' && $method === 'POST') {
        $validation = normalize_auth_input(get_json_body());
        if (!$validation['valid']) {
            send_json(422, ['error' => implode(' ', $validation['errors'])]);
        }

        $payload = $validation['data'];

        $check = $db->prepare('SELECT Id FROM users WHERE Username = ? LIMIT 1');
        $check->bind_param('s', $payload['username']);
        $check->execute();
        $existing = stmt_fetch_one_assoc($check);

        if ($existing !== null) {
            send_json(409, ['error' => 'Username already exists']);
        }

        $stmt = $db->prepare('INSERT INTO users (Username, Password) VALUES (?, ?)');
        $stmt->bind_param('ss', $payload['username'], $payload['password']);
        $stmt->execute();

        send_json(201, ['message' => 'Registration successful']);
    }

    if ($resource === 'recipes') {
        if ($method === 'GET' && $pathValue === 'types') {
            $result = $db->query('SELECT DISTINCT type FROM recipes ORDER BY type ASC');
            $types = [];

            while ($row = $result->fetch_assoc()) {
                $types[] = $row['type'];
            }

            send_json(200, ['types' => $types]);
        }

        if ($method === 'GET') {
            $type = trim((string) ($_GET['type'] ?? ''));

            if ($id !== null) {
                $stmt = $db->prepare('SELECT id, author, name, type, recipe FROM recipes WHERE id = ?');
                $stmt->bind_param('i', $id);
                $stmt->execute();
                $recipe = stmt_fetch_one_assoc($stmt);

                if ($recipe === null) {
                    send_json(404, ['error' => 'Recipe not found']);
                }

                send_json(200, ['recipe' => $recipe]);
            }

            if ($type !== '' && strtolower($type) !== 'all') {
                $stmt = $db->prepare('SELECT id, author, name, type, recipe FROM recipes WHERE type = ? ORDER BY id DESC');
                $stmt->bind_param('s', $type);
                $stmt->execute();
                $recipes = stmt_fetch_all_assoc($stmt);
            } else {
                $result = $db->query('SELECT id, author, name, type, recipe FROM recipes ORDER BY id DESC');
                $recipes = [];

                while ($row = $result->fetch_assoc()) {
                    $recipes[] = $row;
                }
            }

            send_json(200, ['recipes' => $recipes]);
        }

        if ($method === 'POST') {
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

        if ($method === 'PUT') {
            if ($id === null || $id <= 0) {
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

        if ($method === 'DELETE') {
            if ($id === null || $id <= 0) {
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
    }

    send_json(404, ['error' => 'Unknown endpoint']);
} catch (Throwable $e) {
    send_json(500, ['error' => 'Server error', 'details' => $e->getMessage()]);
}
