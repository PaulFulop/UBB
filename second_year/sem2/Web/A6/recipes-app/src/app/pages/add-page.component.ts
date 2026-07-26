import { CommonModule } from '@angular/common';
import { Component, inject, signal } from '@angular/core';
import { FormBuilder, ReactiveFormsModule, Validators } from '@angular/forms';
import { firstValueFrom } from 'rxjs';
import { Router } from '@angular/router';

import { RecipeApiService, formatHttpError } from '../recipe-api.service';

@Component({
  selector: 'app-add-page',
  standalone: true,
  imports: [CommonModule, ReactiveFormsModule],
  template: `
    <section class="panel">
      <div class="section-header">
        <div>
          <p class="eyebrow">Add</p>
          <h2 class="section-title">Insert a new recipe</h2>
          <p class="section-subtitle">This form posts JSON to the PHP backend with HttpClient.</p>
        </div>
      </div>

      <p class="message" [class.error]="isError()">{{ message }}</p>

      <form [formGroup]="form" (ngSubmit)="submit()">
        <div class="split-layout">
          <div class="stack">
            <div class="form-field">
              <label for="name">Recipe name</label>
              <input id="name" type="text" formControlName="name" />
            </div>

            <div class="form-field">
              <label for="author">Author</label>
              <input id="author" type="text" formControlName="author" />
            </div>

            <div class="form-field">
              <label for="type">Type</label>
              <input id="type" type="text" formControlName="type" />
            </div>
          </div>

          <div class="form-field">
            <label for="recipe">Actual recipe</label>
            <textarea id="recipe" rows="11" formControlName="recipe"></textarea>
          </div>
        </div>

        <div class="form-actions">
          <button type="submit">Add recipe</button>
          <button type="button" class="secondary" (click)="resetForm()">Clear</button>
        </div>
      </form>
    </section>
  `,
})
export class AddPageComponent {
  private readonly api = inject(RecipeApiService);
  private readonly fb = inject(FormBuilder);
  private readonly router = new Router();

  message = 'Fill the form and submit to create a recipe.';
  readonly isError = signal(false);

  readonly form = this.fb.nonNullable.group({
    name: ['', [Validators.required, Validators.minLength(2), Validators.maxLength(120)]],
    author: ['', [Validators.required, Validators.minLength(2), Validators.maxLength(100)]],
    type: ['', [Validators.required, Validators.pattern(/^[A-Za-z ]{3,40}$/)]],
    recipe: ['', [Validators.required, Validators.minLength(10), Validators.maxLength(4000)]],
  });

  async submit(): Promise<void> {
    if (this.form.invalid) {
      this.form.markAllAsTouched();
      this.message = this.getValidationMessage();
      this.isError.set(true);
      return;
    }

    try {
      this.message = 'Saving recipe...';
      this.isError.set(false);
      await firstValueFrom(this.api.createRecipe(this.form.getRawValue()));
      this.message = 'Recipe created!';
      this.resetForm();
    } catch (error) {
      this.message = formatHttpError(error);
      this.isError.set(true);
    }
  }

  resetForm(): void {
    this.form.reset({
      name: '',
      author: '',
      type: '',
      recipe: '',
    });
    this.isError.set(false);
    this.router.navigateByUrl('/browse');
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
      : 'Please fix the highlighted fields before submitting.';
  }
}
