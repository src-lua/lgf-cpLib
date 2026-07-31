// ── Metadata ─────────────────────────────────────────────────────────────────
#let university       = "Centro de Informática - UFPE"
#let university-short = "CIn - UFPE"
#let teamname         = "Lua @ lgf-CPLib"
#let authorname       = "Lua Guimarães Fernandes"

// ── Colors (Catppuccin Latte) ─────────────────────────────────────────────────
#import "@preview/catppuccin:1.1.0": get-flavor
#let _ctp       = get-flavor("latte").colors
#let _bw        = sys.inputs.at("bw", default: "false") == "true"
#let _build_time = sys.inputs.at("build_time", default: datetime.today().display("[day]/[month]/[year]"))
#let ctp-text   = if _bw { black } else { _ctp.text.rgb }
#let ctp-sub0   = _ctp.subtext0.rgb
#let ctp-surf2  = if _bw { luma(65%) } else { _ctp.surface2.rgb }
#let ctp-blue   = if _bw { black } else { _ctp.text.rgb }
#let ctp-teal   = if _bw { black } else { _ctp.blue.rgb }

// ── Document metadata (PDF properties) ────────────────────────────────────────
#set document(title: teamname + " Notebook", author: authorname)

// ── Page setup ───────────────────────────────────────────────────────────────
// A4 landscape: 841.89 × 595.28 pt
#set page(
  width: 841.89pt,
  height: 595.28pt,
  margin: (left: 0.6cm, right: 1.3cm, top: 0.6cm, bottom: 0.6cm),
  fill: white,
  columns: 3,
  header: none,
  footer: none,
)
#set columns(gutter: 6pt)

// Vertical sidebar: team info top, page number bottom — in right margin
#let _sidebar_x = 841.89pt - 0.6cm - 0.65cm
#let _page_h    = 595.28pt
#set page(header: context {
  set text(size: 7pt, font: "JetBrains Mono", fill: ctp-text)
  let info = box([#university | #authorname])
  let bt   = box([#_build_time])
  let num  = box(width: 1cm, align(center)[*#counter(page).display()*])
  let si = measure(info)
  let sbt = measure(bt)
  let sn = measure(num)
  let cx = _sidebar_x + si.height / 2
  let num_dy = _page_h - sn.height - 0.4cm
  place(top + left, dx: _sidebar_x, dy: 0.4cm,
    rotate(90deg, reflow: false, origin: top + left,
      box(width: _page_h, info)
    )
  )
  place(top + left, dx: _sidebar_x, dy: num_dy - sbt.width - 12pt,
    rotate(90deg, reflow: false, origin: top + left, bt)
  )
  place(top + left, dx: cx - 0.5cm - 5.55pt, dy: num_dy,
    num
  )
})

// ── Fonts & base text ────────────────────────────────────────────────────────
#set text(font: "JetBrains Mono", size: 6.5pt, lang: "pt", fill: ctp-text)
#set par(leading: 3pt, spacing: 3pt)

// ── Headings ─────────────────────────────────────────────────────────────────
#show heading.where(level: 1): it => {
  block(above: 5pt, below: 2pt)[
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
#set raw(theme: if _bw { "grayscale.tmTheme" } else {
  "Catppuccin Latte.tmTheme"
})
#show raw.where(block: true): it => {
  set par(leading: 4.5pt, spacing: 0pt)
  set text(size: 5.5pt)
  it
}

// ── Content (colunas no nível da página) ─────────────────────────────────────
#align(center)[
  #grid(columns: (auto, auto, auto), column-gutter: 6pt, align: horizon,
    text(size: 11pt, weight: "bold")[#teamname | #university-short],
    image(if _bw { "assets/maratonacin-logo-bw.svg" } else {
      "assets/maratonacin-logo.svg" }, height: 24pt),
    image(if _bw { "assets/cin-symbol-bw.svg" } else {
      "assets/cin-symbol.svg" }, height: 18pt),
  )
]

#v(4pt)

#outline(depth: 2, indent: 6pt)

#v(4pt)

#include "contents.typ"
