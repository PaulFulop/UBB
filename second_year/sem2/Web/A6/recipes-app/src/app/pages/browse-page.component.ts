import { CommonModule } from '@angular/common';
import { Component, OnInit, inject, signal } from '@angular/core';
import { FormControl, ReactiveFormsModule } from '@angular/forms';
import { firstValueFrom } from 'rxjs';

import { Recipe } from '../recipe.model';
import { RecipeApiService, formatHttpError } from '../recipe-api.service';

@Component({
  selector: 'app-browse-page',
  standalone: true,
  imports: [CommonModule, ReactiveFormsModule],
  template: `
    <section class="panel">
      <div class="section-header">
        <div>
          <p class="eyebrow">Browse</p>
          <h2 class="section-title">Recipes by type</h2>
          <p class="section-subtitle">
            AJAX calls load the recipe list without reloading the page.
          </p>
        </div>
      </div>

      <div class="browse-controls">
        <div class="field-inline">
          <label for="type-filter">Recipe type</label>
          <select id="type-filter" [formControl]="typeControl" (change)="loadRecipes()">
            <option *ngFor="let type of types()" [value]="type">{{ type }}</option>
          </select>
        </div>
      </div>

      <p class="previous-filter">
        Previous filter used: <strong>{{ previousFilter() }}</strong>
      </p>

      <p class="message" [class.error]="isError()">{{ message() }}</p>

      <div class="table-wrap">
        <table>
          <thead>
            <tr>
              <th>Name</th>
              <th>Author</th>
              <th>Type</th>
              <th>Recipe</th>
            </tr>
          </thead>
          <tbody>
            <tr *ngIf="recipes().length === 0">
              <td colspan="4">No recipes found for this filter.</td>
            </tr>
            <tr *ngFor="let recipe of recipes()">
              <td>{{ recipe.name }}</td>
              <td>{{ recipe.author }}</td>
              <td>{{ recipe.type }}</td>
              <td>{{ recipe.recipe }}</td>
            </tr>
          </tbody>
        </table>
      </div>
    </section>
  `,
})
export class BrowsePageComponent implements OnInit {
  private readonly api = inject(RecipeApiService);

  readonly typeControl = new FormControl('all', { nonNullable: true });
  readonly types = signal<string[]>(['all']);
  readonly recipes = signal<Recipe[]>([]);
  readonly previousFilter = signal(localStorage.getItem('lastRecipeFilter') || 'none');
  readonly message = signal('');
  readonly isError = signal(false);

  ngOnInit(): void {
    void this.loadTypes().then(() => this.loadRecipes());
  }

  async loadTypes(): Promise<void> {
    try {
      const response = await firstValueFrom(this.api.getTypes());
      const list = ['all', ...response.types];
      this.types.set(list);

      if (!list.includes(this.typeControl.value)) {
        this.typeControl.setValue('all');
      }
    } catch (error) {
      this.message.set(formatHttpError(error));
      this.isError.set(true);
    }
  }

  async loadRecipes(): Promise<void> {
    try {
      this.message.set('Loading recipes...');
      this.isError.set(false);

      const selectedType = this.typeControl.value || 'all';
      const response = await firstValueFrom(this.api.listRecipes(selectedType));

      this.recipes.set(response.recipes);
      this.previousFilter.set(selectedType);
      localStorage.setItem('lastRecipeFilter', selectedType);
      this.message.set(`Loaded ${response.recipes.length} recipe(s) for filter: ${selectedType}`);
    } catch (error) {
      this.message.set(formatHttpError(error));
      this.isError.set(true);
    }
  }
}
