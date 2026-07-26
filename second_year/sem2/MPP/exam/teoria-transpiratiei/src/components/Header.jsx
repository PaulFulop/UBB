import Logo from "./Logo";
import "./Header.css";

const SECTIONS = [
  "Societate",
  "Știință",
  "Sport",
  "Opinie",
  "Cultură",
  "Sănătate",
];

export default function Header({
  onLogoClick,
  activeCategory,
  onCategorySelect,
}) {
  const today = new Date().toLocaleDateString("ro-RO", {
    weekday: "long",
    year: "numeric",
    month: "long",
    day: "numeric",
  });

  return (
    <header className="masthead">
      <div className="masthead__top">
        <span>{today}</span>
        <span className="masthead__edition">
          Ediția de Vară · Anul CXXVII · Nr. 247
        </span>
        <span>Preț: 2 Lei (+ TVA în sudoare)</span>
      </div>

      <div className="masthead__rule masthead__rule--thin" />

      <button
        className="masthead__main"
        onClick={onLogoClick}
        aria-label="Mergi la prima pagină"
      >
        <Logo size={76} className="masthead__logo" />
        <h1 className="masthead__title">Teoria Transpirației</h1>
        <p className="masthead__tagline">
          „Adevărul transpiră, chiar dacă nu vrea"
        </p>
      </button>

      <div className="masthead__rule masthead__rule--thick" />

      <nav className="masthead__nav" aria-label="Secțiuni">
        <button
          className={`masthead__nav-item ${activeCategory === null ? "is-active" : ""}`}
          onClick={() => onCategorySelect(null)}
        >
          Toate
        </button>
        {SECTIONS.map((section) => (
          <button
            key={section}
            className={`masthead__nav-item ${activeCategory === section ? "is-active" : ""}`}
            onClick={() => onCategorySelect(section)}
          >
            {section}
          </button>
        ))}
      </nav>

      <div className="masthead__rule masthead__rule--thin" />
    </header>
  );
}
