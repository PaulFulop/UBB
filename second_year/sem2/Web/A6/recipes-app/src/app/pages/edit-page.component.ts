import { CommonModule } from '@angular/common';
import { Component, DestroyRef, OnInit, inject, signal } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { FormBuilder, ReactiveFormsModule, Validators } from '@angular/forms';
import { firstValueFrom } from 'rxjs';
import { takeUntilDestroyed } from '@angular/core/rxjs-interop';

import { Recipe } from '../recipe.model';
import { RecipeApiService, formatHttpError } from '../recipe-api.service';

@Component({
  selector: 'app-edit-page',
  standalone: true,
  imports: [CommonModule, ReactiveFormsModule],
  template: `
    <section class="panel">
      <div class="section-header">
        <div>
          <p class="eyebrow">Edit</p>
          <h2 class="section-title">Update a recipe</h2>
          <p class="section-subtitle">Edit the recipe that was opened from the manage page.</p>
        </div>
      </div>

      <p class="message" [class.error]="isError()">{{ message() }}</p>

      <form [formGroup]="form" (ngSubmit)="updateRecipe()">
        <div class="split-layout">
          <div class="stack">
            <div class="form-field">
              <label for="edit-name">Recipe name</label>
              <input id="edit-name" type="text" formControlName="name" />
            </div>

            <div class="form-field">
              <label for="edit-author">Author</label>
              <input id="edit-author" type="text" formControlName="author" />
            </div>

            <div class="form-field">
              <label for="edit-type">Type</label>
              <input id="edit-type" type="text" formControlName="type" />
            </div>
          </div>

          <div class="form-field">
            <label for="edit-recipe">Actual recipe</label>
            <textarea id="edit-recipe" rows="11" formControlName="recipe"></textarea>
          </div>
        </div>

        <div class="form-actions">
          <button type="submit">Update recipe</button>
        </div>
      </form>
    </section>
  `,
})
export class EditPageComponent implements OnInit {
  private readonly api = inject(RecipeApiService);
  private readonly fb = inject(FormBuilder);
  private readonly route = inject(ActivatedRoute);
  private readonly destroyRef = inject(DestroyRef);

  readonly selectedId = signal<number | null>(null);
  readonly message = signal('Loading recipes...');
  readonly isError = signal(false);

  readonly form = this.fb.nonNullable.group({
    name: ['', [Validators.required, Validators.minLength(2), Validators.maxLength(120)]],
    author: ['', [Validators.required, Validators.minLength(2), Validators.maxLength(100)]],
    type: ['', [Validators.required, Validators.pattern(/^[A-Za-z ]{3,40}$/)]],
    recipe: ['', [Validators.required, Validators.minLength(10), Validators.maxLength(4000)]],
  });

  ngOnInit(): void {
    this.route.queryParamMap.pipe(takeUntilDestroyed(this.destroyRef)).subscribe((params) => {
      const rawId = Number(params.get('id'));
      this.selectedId.set(Number.isInteger(rawId) && rawId > 0 ? rawId : null);
      this.form.reset({ name: '', author: '', type: '', recipe: '' });

      void this.loadRecipe();
    });
  }

  async loadRecipe(showStatus = true): Promise<void> {
    try {
      const selectedId = this.selectedId();
      if (selectedId === null) {
        if (showStatus) {
          this.message.set('Choose a recipe from Manage before editing.');
          this.isError.set(true);
        }
        return;
      }

      const response = await firstValueFrom(this.api.listRecipes('all'));
      const recipe = response.recipes.find((item) => Number(item.id) === selectedId) || null;

      if (!recipe) {
        if (showStatus) {
          this.message.set('Recipe not found.');
          this.isError.set(true);
        }
        return;
      }

      this.form.patchValue({
        name: recipe.name,
        author: recipe.author,
        type: recipe.type,
        recipe: recipe.recipe,
      });
      if (showStatus) {
        this.message.set(`Editing recipe #${recipe.id}: ${recipe.name}`);
        this.isError.set(false);
      }
    } catch (error) {
      this.message.set(formatHttpError(error));
      this.isError.set(true);
    }
  }

  async updateRecipe(): Promise<void> {
    const id = this.selectedId();

    if (id === null) {
      this.message.set('Choose a recipe before updating it.');
      this.isError.set(true);
      return;
    }

    if (this.form.invalid) {
      this.form.markAllAsTouched();
      this.message.set(this.getValidationMessage());
      this.isError.set(true);
      return;
    }

    try {
      this.message.set('Updating recipe...');
      await firstValueFrom(this.api.updateRecipe(id, this.form.getRawValue()));
      this.message.set('Recipe updated!');
      this.isError.set(false);
      await this.loadRecipe(false);
    } catch (error) {
      this.message.set(formatHttpError(error));
      this.isError.set(true);
    }
  }

  private getValidationMessage(): string {
    const errors: string[] = [];

    const name = this.form.controls.name;
    if (name.errors?.['required']) {
      errors.push('Recipe name is required.');
    } else if (name.errors?.['minlength']) {
      errors.push('Recipe name must be at least 2 characters long.');
    } else if (name.errors?.['maxlength']) {
      errors.push('Recipe name must be at most 120 characters long.');
    }

    const author = this.form.controls.author;
    if (author.errors?.['required']) {
      errors.push('Author is required.');
    } else if (author.errors?.['minlength']) {
      errors.push('Author must be at least 2 characters long.');
    } else if (author.errors?.['maxlength']) {
      errors.push('Author must be at most 100 characters long.');
    }

    const type = this.form.controls.type;
    if (type.errors?.['required']) {
      errors.push('Type is required.');
    } else if (type.errors?.['pattern']) {
      errors.push('Type must contain only letters and spaces and be 3 to 40 characters long.');
    }

    const recipe = this.form.controls.recipe;
    if (recipe.errors?.['required']) {
      errors.push('Recipe text is required.');
    } else if (recipe.errors?.['minlength']) {
      errors.push('Recipe text must be at least 10 characters long.');
    } else if (recipe.errors?.['maxlength']) {
      errors.push('Recipe text must be at most 4000 characters long.');
    }

    return errors.length > 0
      ? errors.join(' ')
      : 'Please fix the highlighted fields before updating.';
  }
}
