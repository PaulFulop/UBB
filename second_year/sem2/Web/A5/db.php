<?php

declare(strict_types=1);

const DB_HOST = 'localhost';
const DB_NAME = 'recipes_lab';
const DB_USER = 'root';
const DB_PASS = '';
const DB_PORT = 3306;

function db_connection(): mysqli
{
    static $conn = null;

    if ($conn instanceof mysqli) {
        return $conn;
    }

    mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);

    $conn = new mysqli(DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT);
    $conn->set_charset('utf8mb4');

    return $conn;
}

function normalize_recipe_input(array $source): array
{
    $author = trim((string) ($source['author'] ?? ''));
    $name = trim((string) ($source['name'] ?? ''));
    $type = trim((string) ($source['type'] ?? ''));
    $recipe = trim((string) ($source['recipe'] ?? ''));

    $errors = [];

    if ($author === '' || mb_strlen($author) < 2 || mb_strlen($author) > 100) {
        $errors[] = 'Author must be between 2 and 100 characters.';
    }

    if ($name === '' || mb_strlen($name) < 2 || mb_strlen($name) > 120) {
        $errors[] = 'Recipe name must be between 2 and 120 characters.';
    }

    if (!preg_match('/^[A-Za-z ]{3,40}$/', $type)) {
        $errors[] = 'Type can contain only letters and spaces (3-40 chars).';
    }

    if ($recipe === '' || mb_strlen($recipe) < 10 || mb_strlen($recipe) > 4000) {
        $errors[] = 'Recipe text must be between 10 and 4000 characters.';
    }

    return [
        'valid' => $errors === [],
        'errors' => $errors,
        'data' => [
            'author' => $author,
            'name' => $name,
            'type' => $type,
            'recipe' => $recipe,
        ],
    ];
}

function esc(string $value): string
{
    return htmlspecialchars($value, ENT_QUOTES | ENT_SUBSTITUTE, 'UTF-8');
}
