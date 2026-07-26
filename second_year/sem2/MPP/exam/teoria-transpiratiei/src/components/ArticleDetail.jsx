import { motion } from 'framer-motion'
import './ArticleDetail.css'

export default function ArticleDetail({ article, onBack }) {
  const dateStr = new Date(article.date).toLocaleDateString('ro-RO', {
    day: 'numeric',
    month: 'long',
    year: 'numeric',
  })

  const [firstParagraph, ...rest] = article.body

  return (
    <motion.article
      className="article-detail"
      initial={{ opacity: 0, y: 28 }}
      animate={{ opacity: 1, y: 0 }}
      exit={{ opacity: 0, y: -16 }}
      transition={{ duration: 0.5, ease: [0.22, 1, 0.36, 1] }}
    >
      <button className="article-detail__back" onClick={onBack}>
        ← Înapoi la prima pagină
      </button>

      <span className="article-detail__category">{article.category}</span>

      <motion.h1 layoutId={`title-${article.id}`} className="article-detail__title">
        {article.title}
      </motion.h1>

      <div className="article-detail__meta">
        <span>De {article.author}</span>
        <span aria-hidden="true">·</span>
        <span>{dateStr}</span>
        <span aria-hidden="true">·</span>
        <span>{article.readTime} min citire</span>
      </div>

      <motion.figure layoutId={`image-${article.id}`} className="article-detail__media">
        <img src={article.image} alt={article.title} />
        <figcaption>{article.excerpt}</figcaption>
      </motion.figure>

      <motion.div
        className="article-detail__body"
        initial={{ opacity: 0 }}
        animate={{ opacity: 1 }}
        transition={{ delay: 0.15, duration: 0.5 }}
      >
        <p className="article-detail__lead">
          <span className="dropcap">{firstParagraph.charAt(0)}</span>
          {firstParagraph.slice(1)}
        </p>
        {rest.map((paragraph, index) => (
          <p key={index}>{paragraph}</p>
        ))}
      </motion.div>

      <button className="article-detail__back article-detail__back--bottom" onClick={onBack}>
        ← Înapoi la prima pagină
      </button>
    </motion.article>
  )
}
