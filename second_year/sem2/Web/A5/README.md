# Recipe Manager (PHP + MySQL)

## Pages

1. `index.php` - home page with navigation
2. `browse.php` - AJAX browsing by recipe type
3. `add.php` - insert recipe
4. `manage.php` - select all recipes + delete/edit actions
5. `edit.php` - update recipe

## Database setup

1. Open `db.php` and set:
   - `DB_HOST`
   - `DB_NAME`
   - `DB_USER`
   - `DB_PASS`
   - `DB_PORT`
2. Run the SQL in `schema.sql` on your MySQL database.

## Notes for lab requirements

- CRUD operations are implemented with prepared statements (SQL injection protection).
- AJAX is used in `browse.php` via `app.js` and `api.php`.
- Previous browse filter is shown using JavaScript (`localStorage`).
- User does not input IDs manually for update/delete; actions come from recipe list buttons.
- Validation exists in both client-side HTML attributes and server-side PHP logic.
