import { motion } from 'framer-motion'
import './ArticleCard.css'

const cardVariants = {
  hidden: { opacity: 0, y: 26 },
  visible: { opacity: 1, y: 0, transition: { duration: 0.55, ease: [0.22, 1, 0.36, 1] } },
}

export default function ArticleCard({ article, onSelect, variant = 'standard' }) {
  return (
    <motion.article
      className={`article-card article-card--${variant}`}
      variants={cardVariants}
      whileHover={{ y: -4 }}
      whileTap={{ scale: 0.99 }}
      onClick={() => onSelect(article.id)}
      role="button"
      tabIndex={0}
      onKeyDown={(e) => {
        if (e.key === 'Enter' || e.key === ' ') onSelect(article.id)
      }}
    >
      <div className="article-card__media">
        <motion.img
          layoutId={`image-${article.id}`}
          src={article.image}
          alt={article.title}
        />
      </div>
      <div className="article-card__body">
        <span className="article-card__category">{article.category}</span>
        <motion.h2 layoutId={`title-${article.id}`} className="article-card__title">
          {article.title}
        </motion.h2>
        <p className="article-card__excerpt">{article.excerpt}</p>
        <div className="article-card__meta">
          <span>{article.author}</span>
          <span aria-hidden="true">·</span>
          <span>{article.readTime} min citire</span>
        </div>
      </div>
    </motion.article>
  )
}
