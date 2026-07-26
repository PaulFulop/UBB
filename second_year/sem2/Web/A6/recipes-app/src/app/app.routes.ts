import { Routes } from '@angular/router';

import { AddPageComponent } from './pages/add-page.component';
import { BrowsePageComponent } from './pages/browse-page.component';
import { EditPageComponent } from './pages/edit-page.component';
import { HomePageComponent } from './pages/home-page.component';
import { LoginPageComponent } from './pages/login-page.component';
import { RegisterPageComponent } from './pages/register-page.component';
import { ManagePageComponent } from './pages/manage-page.component';
import { authGuard } from './auth.guard';

export const routes: Routes = [
  { path: 'login', component: LoginPageComponent },
  { path: 'register', component: RegisterPageComponent },
  { path: '', component: HomePageComponent, pathMatch: 'full', canActivate: [authGuard] },
  { path: 'browse', component: BrowsePageComponent, canActivate: [authGuard] },
  { path: 'add', component: AddPageComponent, canActivate: [authGuard] },
  { path: 'manage', component: ManagePageComponent, canActivate: [authGuard] },
  { path: 'edit', component: EditPageComponent, canActivate: [authGuard] },
  { path: '**', redirectTo: 'login' },
];
