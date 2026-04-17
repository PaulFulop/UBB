export interface Recipe {
  id: number;
  author: string;
  name: string;
  type: string;
  recipe: string;
  created_at?: string;
  updated_at?: string;
}

export interface RecipeInput {
  author: string;
  name: string;
  type: string;
  recipe: string;
}
