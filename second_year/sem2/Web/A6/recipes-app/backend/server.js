const express = require('express');
const cors = require('cors');
const mysql = require('mysql2/promise');

const app = express();
const port = process.env.PORT || 3000;

const dbConfig = {
  host: '127.0.0.1',
  user: 'root',
  password: '',
  database: 'recipes_lab',
  port: 3306,
};

app.use(cors());
app.use(express.json());

function sendJson(res, status, payload) {
  return res.status(status).json(payload);
}

function normalizeAuthInput(body) {
  const username = String(body && body.username ? body.username : '').trim();
  const password = String(body && body.password ? body.password : '');
  const errors = [];

  if (username.length < 2 || username.length > 80) {
    errors.push('Username must be between 2 and 80 characters.');
  }

  if (password.length < 4 || password.length > 200) {
    errors.push('Password must be between 4 and 200 characters.');
  }

  return {
    valid: errors.length === 0,
    errors: errors,
    data: {
      username: username,
      password: password,
    },
  };
}

function normalizeRecipeInput(body) {
  const author = String(body && body.author ? body.author : '').trim();
  const name = String(body && body.name ? body.name : '').trim();
  const type = String(body && body.type ? body.type : '').trim();
  const recipe = String(body && body.recipe ? body.recipe : '').trim();
  const errors = [];

  if (author.length < 2 || author.length > 100) {
    errors.push('Author must be between 2 and 100 characters.');
  }

  if (name.length < 2 || name.length > 120) {
    errors.push('Recipe name must be between 2 and 120 characters.');
  }

  if (!/^[A-Za-z ]{3,40}$/.test(type)) {
    errors.push('Type can contain only letters and spaces (3-40 chars).');
  }

  if (recipe.length < 10 || recipe.length > 4000) {
    errors.push('Recipe text must be between 10 and 4000 characters.');
  }

  return {
    valid: errors.length === 0,
    errors: errors,
    data: {
      author: author,
      name: name,
      type: type,
      recipe: recipe,
    },
  };
}

async function main() {
  const db = await mysql.createConnection(dbConfig);

  app.get('/', function (req, res) {
    sendJson(res, 200, { message: 'Recipes backend running' });
  });

  app.post('/login', async function (req, res) {
    const validation = normalizeAuthInput(req.body);
    if (!validation.valid) {
      return sendJson(res, 401, { error: validation.errors.join(' ') });
    }

    const payload = validation.data;
    const [rows] = await db.execute(
      'SELECT Id FROM users WHERE Username = ? AND Password = ? LIMIT 1',
      [payload.username, payload.password],
    );

    if (rows.length === 0) {
      return sendJson(res, 401, { error: 'Invalid username or password' });
    }

    return sendJson(res, 200, { message: 'Login successful' });
  });

  app.post('/register', async function (req, res) {
    const validation = normalizeAuthInput(req.body);
    if (!validation.valid) {
      return sendJson(res, 422, { error: validation.errors.join(' ') });
    }

    const payload = validation.data;
    const [existingRows] = await db.execute('SELECT Id FROM users WHERE Username = ? LIMIT 1', [
      payload.username,
    ]);

    if (existingRows.length > 0) {
      return sendJson(res, 409, { error: 'Username already exists' });
    }

    await db.execute('INSERT INTO users (Username, Password) VALUES (?, ?)', [
      payload.username,
      payload.password,
    ]);

    return sendJson(res, 201, { message: 'Registration successful' });
  });

  app.get('/recipes/types', async function (req, res) {
    const [rows] = await db.execute('SELECT DISTINCT type FROM recipes ORDER BY type ASC');
    const types = [];

    for (let i = 0; i < rows.length; i += 1) {
      types.push(rows[i].type);
    }

    return sendJson(res, 200, { types: types });
  });

  app.get('/recipes', async function (req, res) {
    const type = String(req.query.type ? req.query.type : '').trim();

    if (type !== '' && type.toLowerCase() !== 'all') {
      const [rows] = await db.execute(
        'SELECT id, author, name, type, recipe FROM recipes WHERE type = ? ORDER BY id DESC',
        [type],
      );
      return sendJson(res, 200, { recipes: rows });
    }

    const [rows] = await db.execute(
      'SELECT id, author, name, type, recipe FROM recipes ORDER BY author ASC',
    );
    const recipes = rows;
    return sendJson(res, 200, { recipes: recipes });
  });

  app.post('/recipes', async function (req, res) {
    const validation = normalizeRecipeInput(req.body);
    if (!validation.valid) {
      return sendJson(res, 422, { error: validation.errors.join(' ') });
    }

    const payload = validation.data;
    const [result] = await db.execute(
      'INSERT INTO recipes (author, name, type, recipe) VALUES (?, ?, ?, ?)',
      [payload.author, payload.name, payload.type, payload.recipe],
    );

    return sendJson(res, 201, { message: 'Recipe created', id: result.insertId });
  });

  app.put('/recipes/:id', async function (req, res) {
    const id = parseInt(req.params.id, 10);
    if (!id || id <= 0) {
      return sendJson(res, 422, { error: 'Valid id is required' });
    }

    const validation = normalizeRecipeInput(req.body);
    if (!validation.valid) {
      return sendJson(res, 422, { error: validation.errors.join(' ') });
    }

    const payload = validation.data;
    const [result] = await db.execute(
      'UPDATE recipes SET author = ?, name = ?, type = ?, recipe = ? WHERE id = ?',
      [payload.author, payload.name, payload.type, payload.recipe, id],
    );

    if (result.affectedRows === 0) {
      const [rows] = await db.execute('SELECT id FROM recipes WHERE id = ?', [id]);
      if (rows.length === 0) {
        return sendJson(res, 404, { error: 'Recipe not found' });
      }
    }

    return sendJson(res, 200, { message: 'Recipe updated' });
  });

  app.delete('/recipes/:id', async function (req, res) {
    const id = parseInt(req.params.id, 10);
    if (!id || id <= 0) {
      return sendJson(res, 422, { error: 'Valid id is required' });
    }

    const [result] = await db.execute('DELETE FROM recipes WHERE id = ?', [id]);
    if (result.affectedRows === 0) {
      return sendJson(res, 404, { error: 'Recipe not found' });
    }

    return sendJson(res, 200, { message: 'Recipe deleted' });
  });

  app.use(function (req, res) {
    sendJson(res, 404, { error: 'Unknown endpoint' });
  });

  app.listen(port, function () {
    console.log('Recipes backend running on http://localhost:' + port);
  });
}

main().catch(function (error) {
  console.error('Failed to start backend');
  console.error(error);
  process.exit(1);
});
