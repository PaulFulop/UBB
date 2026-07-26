import { useState } from "react";
import { AnimatePresence } from "framer-motion";
import Header from "./components/Header";
import ArticleList from "./components/ArticleList";
import ArticleDetail from "./components/ArticleDetail";
import { articles } from "./data/articles";

export default function App() {
  const [selectedId, setSelectedId] = useState(null);
  const [activeCategory, setActiveCategory] = useState(null);

  const selectedArticle = articles.find((article) => article.id === selectedId);
  const filteredArticles = activeCategory
    ? articles.filter((article) => article.category === activeCategory)
    : articles;

  const handleCategorySelect = (category) => {
    setActiveCategory(category);
    setSelectedId(null); // go back to the list when switching sections
  };

  const handleLogoClick = () => {
    setSelectedId(null);
    setActiveCategory(null);
  };

  return (
    <div className="page">
      <Header
        onLogoClick={handleLogoClick}
        activeCategory={activeCategory}
        onCategorySelect={handleCategorySelect}
      />

      <main className="main">
        <AnimatePresence mode="wait">
          {selectedArticle ? (
            <ArticleDetail
              key={`detail-${selectedArticle.id}`}
              article={selectedArticle}
              onBack={() => setSelectedId(null)}
            />
          ) : (
            <ArticleList
              key={`list-${activeCategory ?? "all"}`}
              articles={filteredArticles}
              onSelect={setSelectedId}
            />
          )}
        </AnimatePresence>
      </main>

      <footer className="footer">
        <p>
          &copy; {new Date().getFullYear()} Teoria Transpirației — toate
          drepturile (de a transpira) rezervate.
        </p>
      </footer>
    </div>
  );
}
