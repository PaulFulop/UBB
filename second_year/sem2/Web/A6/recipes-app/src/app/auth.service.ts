import { HttpClient } from '@angular/common/http';
import { Injectable, inject } from '@angular/core';
import { Observable, tap } from 'rxjs';
import { environment } from '../environments/environment';

interface LoginPayload {
  username: string;
  password: string;
}

interface LoginResponse {
  message?: string;
}

const AUTH_BASE_URL = environment.backendUrl;

@Injectable({ providedIn: 'root' })
export class AuthService {
  private readonly http = inject(HttpClient);
  isAuthenticated = false;

  login(payload: LoginPayload): Observable<LoginResponse> {
    return this.http.post<LoginResponse>(`${AUTH_BASE_URL}/login`, payload).pipe(
      tap(() => {
        this.isAuthenticated = true;
      }),
    );
  }

  register(payload: LoginPayload): Observable<LoginResponse> {
    return this.http.post<LoginResponse>(`${AUTH_BASE_URL}/register`, payload).pipe(
      tap(() => {
        this.isAuthenticated = true;
      }),
    );
  }

  logout(): void {
    this.isAuthenticated = false;
  }
}
