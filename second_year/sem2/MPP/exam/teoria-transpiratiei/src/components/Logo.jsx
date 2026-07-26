// Vintage "wax seal" emblem: a droplet inside a double ring, with the
// publication name set on a circular path, evoking an old broadsheet crest.
export default function Logo({ size = 64, className = '' }) {
  return (
    <svg
      className={`logo-mark ${className}`}
      width={size}
      height={size}
      viewBox="0 0 200 200"
      role="img"
      aria-label="Emblema Teoria Transpirației"
    >
      <defs>
        <path id="logo-arc-top" d="M 26 104 A 74 74 0 1 1 174 104" />
      </defs>

      <circle cx="100" cy="100" r="96" className="logo-ring-outer" />
      <circle cx="100" cy="100" r="82" className="logo-ring-inner" />

      <text className="logo-arc-text">
        <textPath href="#logo-arc-top" startOffset="50%" textAnchor="middle">
          TEORIA TRANSPIRAȚIEI
        </textPath>
      </text>

      <path
        className="logo-drop"
        d="M100 56 C 126 92, 138 114, 100 146 C 62 114, 74 92, 100 56 Z"
      />

      <line x1="64" y1="160" x2="136" y2="160" className="logo-underline" />
      <text x="100" y="180" textAnchor="middle" className="logo-est">
        EST. MDCCCXCVII
      </text>
    </svg>
  )
}
