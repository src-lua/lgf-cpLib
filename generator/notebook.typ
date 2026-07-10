// ── Metadata ─────────────────────────────────────────────────────────────────
#let university       = "Centro de Informática - UFPE"
#let university-short = "CIn - UFPE"
#let teamname         = "Lua | lgf-cplib"
#let authorname       = "Lua Guimarães Fernandes"

// ── Colors (Catppuccin Latte) ─────────────────────────────────────────────────
#import "@preview/catppuccin:1.1.0": get-flavor
#let _ctp       = get-flavor("latte").colors
#let _bw        = sys.inputs.at("bw", default: "false") == "true"
#let ctp-text   = _ctp.text.rgb
#let ctp-sub0   = _ctp.subtext0.rgb
#let ctp-surf2  = _ctp.surface2.rgb
#let ctp-blue   = _ctp.text.rgb
#let ctp-teal   = _ctp.blue.rgb
#let gray5      = if _bw { black } else { _ctp.overlay0.rgb }

// ── Page setup ───────────────────────────────────────────────────────────────
// A4 landscape: 841.89 × 595.28 pt
#set page(
  width: 841.89pt,
  height: 595.28pt,
  margin: (left: 0.6cm, right: 1.3cm, top: 0.4cm, bottom: 0.4cm),
  fill: if _bw { white } else { _ctp.base.rgb },
  header: none,
  footer: none,
)

// Vertical sidebar: team info top, page number bottom — in right margin
#let _sidebar_x = 841.89pt - 0.6cm - 0.65cm
#let _page_h    = 595.28pt
#set page(header: context {
  set text(size: 7pt, font: "JetBrains Mono", fill: ctp-text)
  let info = box([#university | #authorname])
  let num  = box(width: 1cm, align(center)[*#counter(page).display()*])
  let si = measure(info)
  let sn = measure(num)
  let cx = _sidebar_x + si.height / 2
  place(top + left, dx: _sidebar_x, dy: 0.4cm,
    rotate(90deg, reflow: false, origin: top + left,
      box(width: _page_h, info)
    )
  )
  place(top + left, dx: cx - 0.5cm - 4pt, dy: _page_h - sn.height - 0.4cm,
    num
  )
})

// ── Fonts & base text ────────────────────────────────────────────────────────
#set text(font: "JetBrains Mono", size: 6.5pt, lang: "pt", fill: ctp-text)
#set par(leading: 3pt, spacing: 3pt)

// ── Headings ─────────────────────────────────────────────────────────────────
#show heading.where(level: 1): it => {
  block(above: 5pt, below: 2pt)[
    #line(length: 100%, stroke: 0.5pt + ctp-surf2)
    #text(size: 8pt, weight: "bold", fill: ctp-blue)[#it.body]
    #line(length: 100%, stroke: 0.3pt + ctp-surf2)
  ]
}

#show heading.where(level: 2): it => {
  block(above: 5pt, below: 5pt)[
    #text(size: 7pt, weight: "semibold", fill: ctp-teal)[#it.body]
  ]
}

// ── Raw blocks ───────────────────────────────────────────────────────────────
#set raw(theme: "Catppuccin Latte.tmTheme")
#show raw.where(block: true): it => {
  set par(leading: 4.5pt, spacing: 0pt)
  set text(size: 5.5pt)
  it
}

// ── 3-column content ─────────────────────────────────────────────────────────
#columns(3, gutter: 6pt)[
  #place(top + left, dx: 8pt, dy: 1pt,
    text(size: 6pt, fill: gray5)[#datetime.today().display("[day]/[month]/[year]")]
  )
  #align(center)[
    #grid(columns: (auto, auto, auto), column-gutter: 6pt, align: horizon,
      text(size: 11pt, weight: "bold")[#teamname | #university-short],
      image("assets/maratonacin-logo.svg", height: 24pt),
      image("assets/cin-symbol.svg", height: 18pt),
    )
  ]

  #v(4pt)

  #outline(depth: 2, indent: 6pt)

  #v(4pt)

  #include "contents.typ"
]
