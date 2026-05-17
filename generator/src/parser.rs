use crate::types::{Section, Subsection};
use std::fs;

pub fn parse_contents(path: &str) -> Vec<Section> {
    let content = fs::read(path).unwrap_or_else(|e| {
        eprintln!("Error opening {}: {}", path, e);
        std::process::exit(1);
    });

    // Skip UTF-16 LE BOM (0xFF 0xFE) if present
    let start = if content.len() >= 2 && content[0] == 0xFF && content[1] == 0xFE {
        2
    } else if content.len() >= 3 && content[0] == 0xEF && content[1] == 0xBB && content[2] == 0xBF {
        3 // UTF-8 BOM
    } else {
        0
    };

    let text = String::from_utf8_lossy(&content[start..]).into_owned();
    let mut lines = text.lines();

    // First token is the divisor character
    let div_char = lines
        .next()
        .and_then(|l| l.chars().find(|c| !c.is_whitespace()))
        .unwrap_or('$');

    let mut sections: Vec<Section> = Vec::new();

    for line in lines {
        // Remove \r and null bytes
        let line: String = line.chars().filter(|&c| c != '\r' && c != '\0').collect();

        if line.is_empty() {
            continue;
        }

        // Skip if line contains '#'
        if line.contains('#') {
            continue;
        }

        if line.starts_with('[') {
            // Section header: [Name] or [!Name] (no_heading)
            let inner = line.trim_matches(|c| c == '[' || c == ']');
            let (no_heading, name) = if let Some(stripped) = inner.strip_prefix('!') {
                (true, stripped.to_string())
            } else {
                (false, inner.to_string())
            };
            sections.push(Section {
                name,
                no_heading,
                subsections: Vec::new(),
            });
        } else {
            // Entry: path $ Display Name  (optional @ to disable hash)
            let div_pos = match line.find(div_char) {
                Some(p) => p,
                None => {
                    eprintln!("Subsection parse error {{{}}}", line);
                    continue;
                }
            };

            let use_hash = !line.contains('@');
            let raw_line = line.replace('@', " ");

            let path = raw_line[..div_pos].trim_end().to_string();
            let display_name = raw_line[div_pos + div_char.len_utf8()..].trim().to_string();

            if sections.is_empty() {
                eprintln!("Subsection given without section {{{}}}", line);
                continue;
            }

            sections.last_mut().unwrap().subsections.push(Subsection {
                path,
                display_name,
                use_hash,
            });
        }
    }

    sections
}
