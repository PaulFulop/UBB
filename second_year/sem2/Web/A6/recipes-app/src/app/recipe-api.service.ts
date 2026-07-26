import { HttpClient, HttpErrorResponse } from '@angular/common/http';
import { inject, Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { environment } from '../environments/environment';
import { Recipe, RecipeInput } from './recipe.model';

interface TypesResponse {
  types: string[];
}

interface RecipesResponse {
  recipes: Recipe[];
}

interface ActionResponse {
  message: string;
}

const BACKEND_URL = environment.backendUrl;

@Injectable({ providedIn: 'root' })
export class RecipeApiService {
  private readonly http = inject(HttpClient);

  getTypes(): Observable<TypesResponse> {
    return this.http.get<TypesResponse>(`${BACKEND_URL}/recipes/types`);
  }

  listRecipes(type = 'all'): Observable<RecipesResponse> {
    return this.http.get<RecipesResponse>(
      `${BACKEND_URL}/recipes?type=${encodeURIComponent(type)}`,
    );
  }

  createRecipe(payload: RecipeInput): Observable<ActionResponse & { id: number }> {
    return this.http.post<ActionResponse & { id: number }>(`${BACKEND_URL}/recipes`, payload);
  }

  updateRecipe(id: number, payload: RecipeInput): Observable<ActionResponse> {
    return this.http.put<ActionResponse>(`${BACKEND_URL}/recipes/${id}`, payload);
  }

  deleteRecipe(id: number): Observable<ActionResponse> {
    return this.http.delete<ActionResponse>(`${BACKEND_URL}/recipes/${id}`);
  }
}

export function formatHttpError(error: unknown): string {
  if (error instanceof HttpErrorResponse) {
    if (typeof error.error?.error === 'string') {
      return error.error.error;
    }

    if (typeof error.error?.message === 'string') {
      return error.error.message;
    }

    return error.message || 'Request failed.';
  }

  if (error instanceof Error) {
    return error.message;
  }

  return 'Request failed.';
}
