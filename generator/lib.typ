// Shared definitions imported by contents.typ
#import "@preview/catppuccin:1.1.0": get-flavor
#let _ctp = get-flavor("latte").colors
#let _bw  = sys.inputs.at("bw", default: "false") == "true"
#let _comment_fill = if _bw { luma(25%) } else {
  _ctp.overlay1.rgb.darken(36%)
}
#let _hash_fill    = if _bw { luma(25%) } else {
  _ctp.overlay0.rgb.darken(36%)
}

#let hash_col_width  = 2.2em
#let font_size       = 7.8pt
#let hash_font_size  = 6.3pt
#let line_height     = font_size

// hashes: array of hash strings ("XYZ" or "   ")
// lines:  array of strings (one per code line)
// in_comment: array of bools (true = inside block comment, render as gray text)
#let hashed_raw(hashes, lines, in_comment, lang: "cpp") = {
  grid(
    columns: (hash_col_width, 1fr),
    column-gutter: 0pt,
    row-gutter: 0pt,
    ..hashes.zip(lines).zip(in_comment).map(((( h, l), c)) => {
      if c {
        (
          block(height: line_height, spacing: 0pt, width: hash_col_width),
          block(height: line_height, spacing: 0pt, clip: true,
            align(horizon + left,
              text(size: font_size, fill: _comment_fill, font: "JetBrains Mono",
                raw(l)
              )
            )
          ),
        )
      } else {
        let h_line = if l.trim() == "" { line_height * 0.4 } else { line_height }
        (
          block(height: h_line, spacing: 0pt, width: hash_col_width,
            align(horizon)[
              #set text(size: hash_font_size, fill: _hash_fill)
              #h
            ]
          ),
          block(height: h_line, spacing: 0pt, clip: true,
            align(horizon + left)[
              #set text(size: font_size, weight: 520)
              #box(raw(l, lang: lang))
            ]
          ),
        )
      }
    }).flatten()
  )
}
