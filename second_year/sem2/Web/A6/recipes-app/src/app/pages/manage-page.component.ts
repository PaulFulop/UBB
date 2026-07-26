import { CommonModule } from '@angular/common';
import { Component, OnInit, inject, signal } from '@angular/core';
import { RouterLink } from '@angular/router';
import { firstValueFrom } from 'rxjs';

import { Recipe } from '../recipe.model';
import { RecipeApiService, formatHttpError } from '../recipe-api.service';

@Component({
  selector: 'app-manage-page',
  standalone: true,
  imports: [CommonModule, RouterLink],
  template: `
    <section class="panel">
      <div class="section-header">
        <div>
          <p class="eyebrow">Manage</p>
          <h2 class="section-title">All recipes</h2>
          <p class="section-subtitle">Delete or edit recipes without typing the ids manually.</p>
        </div>
      </div>

      <p class="message" [class.error]="isError()">{{ message() }}</p>

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
            <tr *ngIf="recipes().length === 0">
              <td colspan="5">No recipes found.</td>
            </tr>
            <tr *ngFor="let recipe of recipes()">
              <td>{{ recipe.name }}</td>
              <td>{{ recipe.author }}</td>
              <td>{{ recipe.type }}</td>
              <td>{{ recipe.recipe }}</td>
              <td class="actions">
                <a class="button-link" [routerLink]="['/edit']" [queryParams]="{ id: recipe.id }"
                  >Edit</a
                >
                <button type="button" class="danger" (click)="deleteRecipe(recipe)">Delete</button>
              </td>
            </tr>
          </tbody>
        </table>
      </div>
    </section>
  `,
})
export class ManagePageComponent implements OnInit {
  private readonly api = inject(RecipeApiService);

  readonly recipes = signal<Recipe[]>([]);
  readonly message = signal('Loading recipes...');
  readonly isError = signal(false);

  ngOnInit(): void {
    void this.refreshRecipes();
  }

  async refreshRecipes(): Promise<void> {
    try {
      const response = await firstValueFrom(this.api.listRecipes('all'));
      this.recipes.set(response.recipes);
      this.message.set(`Loaded ${response.recipes.length} recipe(s).`);
      this.isError.set(false);
    } catch (error) {
      this.message.set(formatHttpError(error));
      this.isError.set(true);
    }
  }

  async deleteRecipe(recipe: Recipe): Promise<void> {
    const confirmed = window.confirm('Delete this recipe? This action cannot be undone.');
    if (!confirmed) {
      return;
    }

    try {
      this.message.set('Deleting recipe...');
      await firstValueFrom(this.api.deleteRecipe(recipe.id));
      await this.refreshRecipes();
      this.message.set('Recipe deleted successfully.');
      this.isError.set(false);
    } catch (error) {
      this.message.set(formatHttpError(error));
      this.isError.set(true);
    }
  }
}
