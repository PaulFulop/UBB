import { motion } from "framer-motion";
import ArticleCard from "./ArticleCard";
import "./ArticleList.css";

const containerVariants = {
  hidden: {},
  visible: {
    transition: { staggerChildren: 0.07 },
  },
};

export default function ArticleList({ articles, onSelect }) {
  if (articles.length === 0) {
    return (
      <motion.div
        className="article-list"
        initial={{ opacity: 0 }}
        animate={{ opacity: 1 }}
      >
        <p className="article-list__empty">
          Niciun articol în această secțiune. Verificați mai târziu.
        </p>
      </motion.div>
    );
  }

  const [lead, ...rest] = articles;

  return (
    <motion.div
      className="article-list"
      initial="hidden"
      animate="visible"
      exit={{ opacity: 0, transition: { duration: 0.2 } }}
      variants={containerVariants}
    >
      <div className="article-list__grid">
        <ArticleCard article={lead} onSelect={onSelect} variant="lead" />
        {rest.map((article) => (
          <ArticleCard
            key={article.id}
            article={article}
            onSelect={onSelect}
            variant="standard"
          />
        ))}
      </div>
    </motion.div>
  );
}
