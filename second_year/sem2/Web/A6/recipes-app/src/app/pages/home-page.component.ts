import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterLink } from '@angular/router';

@Component({
  selector: 'app-home-page',
  standalone: true,
  imports: [CommonModule, RouterLink],
  template: `
    <section class="panel">
      <div class="section-header">
        <div>
          <h2 class="section-title">Recipe Manager Dashboard</h2>
        </div>
      </div>

      <div class="nav-grid">
        <a class="nav-card" routerLink="/browse">
          <h2>Browse Recipes</h2>
          <p>Load recipes by type, remember the previous filter, and render the result table.</p>
        </a>

        <a class="nav-card" routerLink="/add">
          <h2>Add Recipe</h2>
          <p>Submit a new recipe through the PHP API using an Angular reactive form.</p>
        </a>

        <a class="nav-card" routerLink="/manage">
          <h2>Manage Recipes</h2>
          <p>Review all recipes, delete entries, and jump to the edit screen.</p>
        </a>

        <a class="nav-card" routerLink="/edit">
          <h2>Edit Recipe</h2>
          <p>Select a recipe and update its author, type, name, or body.</p>
        </a>
      </div>
    </section>
  `,
})
export class HomePageComponent {}
