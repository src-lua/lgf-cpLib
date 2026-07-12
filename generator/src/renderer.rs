use crate::config::{HASH_LEN, USE_HASH};
use crate::hasher::annotate_with_hashes;
use crate::processor::process_file;
use crate::types::{FileKind, Section};
use std::fs;

pub fn render(sections: &[Section]) -> String {
    let mut out = String::new();
    out.push_str("#import \"lib.typ\": hashed_raw\n\n");

    for section in sections {
        if section.subsections.is_empty() {
            continue;
        }

        if section.no_heading {
            out.push_str("#pagebreak()\n\n");
        } else {
            out.push_str(&format!("= {}\n\n", section.name));
        }

        for sub in &section.subsections {
            let kind = FileKind::from_path(&sub.path);

            // .typ files: include directly (extra/ content)
            if kind == FileKind::Typ {
                out.push_str(&format!("#include \"{}\"\n\n", sub.path));
                continue;
            }

            // Process source file → temp/
            let (temp_path, ok) = process_file(&sub.path);
            if !ok {
                eprintln!("Skipping {}", sub.path);
                continue;
            }

            // Subsection heading
            out.push_str(&format!("== {}\n", sub.display_name));

            let do_hash = USE_HASH && sub.use_hash && kind == FileKind::Cpp;

            if do_hash {
                let content = fs::read_to_string(&temp_path).unwrap_or_default();
                let mut lines = annotate_with_hashes(&content, HASH_LEN);

                // Trim trailing None entries
                while lines.last().map(|(h, _)| h.is_none()) == Some(true) {
                    lines.pop();
                }

                if lines.is_empty() {
                    out.push_str("#line(length: 100%, stroke: 0.3pt + gray)\n\n");
                    continue;
                }

                let hash_array: Vec<String> = lines
                    .iter()
                    .map(|(h, _)| match h {
                        Some(s) => format!("\"{}\"", s),
                        None => "\"   \"".to_string(),
                    })
                    .collect();

                let line_array: Vec<String> = lines
                    .iter()
                    .map(|(_, l)| format!("\"{}\"", l.replace('\\', "\\\\").replace('"', "\\\"")))
                    .collect();

                let comment_array: Vec<String> = lines
                    .iter()
                    .map(|(h, l)| {
                        // in_comment: None hash AND line is not blank = inside block comment
                        let is_blank = l.trim().is_empty();
                        let in_comment = h.is_none() && !is_blank;
                        if in_comment {
                            "true".to_string()
                        } else {
                            "false".to_string()
                        }
                    })
                    .collect();

                out.push_str(&format!(
                    "#hashed_raw(({},), ({},), ({},))\n",
                    hash_array.join(", "),
                    line_array.join(", "),
                    comment_array.join(", "),
                ));
            } else {
                let lang = kind.lang_str();
                out.push_str(&format!(
                    "#raw(read(\"{}\"), lang: \"{}\", block: true)\n",
                    temp_path, lang
                ));
            }

            out.push_str("#line(length: 100%, stroke: 0.3pt + gray)\n\n");
        }
    }

    out
}
