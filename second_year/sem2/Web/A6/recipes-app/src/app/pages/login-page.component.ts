import { CommonModule } from '@angular/common';
import { ChangeDetectionStrategy, Component, inject } from '@angular/core';
import { FormBuilder, ReactiveFormsModule, Validators } from '@angular/forms';
import { RouterLink } from '@angular/router';
import { Router } from '@angular/router';
import { firstValueFrom } from 'rxjs';

import { AuthService } from '../auth.service';
import { formatHttpError } from '../recipe-api.service';

@Component({
  selector: 'app-login-page',
  changeDetection: ChangeDetectionStrategy.OnPush,
  imports: [CommonModule, ReactiveFormsModule, RouterLink],
  template: `
    <section class="panel login-panel">
      <div class="section-header">
        <div>
          <p class="eyebrow">Authentication</p>
          <h2 class="section-title">Login required</h2>
          <p class="section-subtitle">Enter your username and password to use the recipe app.</p>
        </div>
      </div>

      <p class="message" [class.error]="isError" [class.pending]="isSubmitting">{{ message }}</p>

      <form [formGroup]="form" (ngSubmit)="submit()" novalidate>
        <div class="form-field">
          <label for="username">Username</label>
          <input id="username" type="text" formControlName="username" autocomplete="username" />
        </div>

        <div class="form-field">
          <label for="password">Password</label>
          <input
            id="password"
            type="password"
            formControlName="password"
            autocomplete="current-password"
          />
        </div>

        <div class="form-actions">
          <button type="submit" [disabled]="isSubmitting">Login</button>
          <button type="button" class="secondary" routerLink="/register">Create account</button>
        </div>
      </form>
    </section>
  `,
})
export class LoginPageComponent {
  private readonly auth = inject(AuthService);
  private readonly fb = inject(FormBuilder);
  private readonly router = inject(Router);

  isSubmitting = false;
  isError = false;
  message = 'Please log in to continue.';

  readonly form = this.fb.nonNullable.group({
    username: ['', [Validators.required, Validators.minLength(2), Validators.maxLength(80)]],
    password: ['', [Validators.required, Validators.minLength(4), Validators.maxLength(200)]],
  });

  async submit(): Promise<void> {
    if (this.form.invalid) {
      this.form.markAllAsTouched();
      this.message = this.getValidationMessage();
      this.isError = true;
      this.isSubmitting = false;
      return;
    }

    this.isSubmitting = true;
    this.isError = false;
    this.message = 'Signing in...';

    try {
      await firstValueFrom(this.auth.login(this.form.getRawValue()));
      this.message = 'Login successful. Redirecting...';
      await this.router.navigate(['/']);
    } catch (error) {
      this.message = formatHttpError(error);
      this.isError = true;
      this.form.reset({ username: '', password: '' });
    } finally {
      this.isSubmitting = false;
    }
  }

  private getValidationMessage(): string {
    const errors: string[] = [];

    const username = this.form.controls.username;
    if (username.errors?.['required']) {
      errors.push('Username is required.');
    } else if (username.errors?.['minlength']) {
      errors.push('Username must be at least 2 characters long.');
    } else if (username.errors?.['maxlength']) {
      errors.push('Username must be at most 80 characters long.');
    }

    const password = this.form.controls.password;
    if (password.errors?.['required']) {
      errors.push('Password is required.');
    } else if (password.errors?.['minlength']) {
      errors.push('Password must be at least 4 characters long.');
    } else if (password.errors?.['maxlength']) {
      errors.push('Password must be at most 200 characters long.');
    }

    if (errors.length === 0) {
      return 'Please check your input.';
    }

    return errors.join(' ');
  }
}
