import { Routes } from '@angular/router';

import { AddPageComponent } from './pages/add-page.component';
import { BrowsePageComponent } from './pages/browse-page.component';
import { EditPageComponent } from './pages/edit-page.component';
import { HomePageComponent } from './pages/home-page.component';
import { ManagePageComponent } from './pages/manage-page.component';

export const routes: Routes = [
  { path: '', component: HomePageComponent, pathMatch: 'full' },
  { path: 'browse', component: BrowsePageComponent },
  { path: 'add', component: AddPageComponent },
  { path: 'manage', component: ManagePageComponent },
  { path: 'edit', component: EditPageComponent },
  { path: '**', redirectTo: '' },
];
