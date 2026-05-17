use crate::config::*;
use std::fs;
use std::path::Path;

/// Process a source file: filter boilerplate, normalize UTF-8, strip ignored content.
/// Writes result to temp/<path> (with leading ../ and ./ removed).
/// Returns (temp_path, success).
pub fn process_file(input_path: &str) -> (String, bool) {
    let output_path = derive_temp_path(input_path);

    let content = match fs::read_to_string(input_path) {
        Ok(c) => c,
        Err(e) => {
            eprintln!("Error opening input file: {}: {}", input_path, e);
            return (output_path, false);
        }
    };

    let processed = filter_content(&content);

    // Ensure output directory exists
    if let Some(parent) = Path::new(&output_path).parent() {
        if let Err(e) = fs::create_dir_all(parent) {
            eprintln!("Error creating directory {}: {}", parent.display(), e);
            return (output_path, false);
        }
    }

    if let Err(e) = fs::write(&output_path, &processed) {
        eprintln!("Error writing output file {}: {}", output_path, e);
        return (output_path, false);
    }

    (output_path, true)
}

/// Derive temp path: remove leading ../ or ./ segments, prepend "temp/"
pub fn derive_temp_path(path: &str) -> String {
    let mut p = path;
    loop {
        if let Some(rest) = p.strip_prefix("../") {
            p = rest;
        } else if let Some(rest) = p.strip_prefix("./") {
            p = rest;
        } else {
            break;
        }
    }
    format!("temp/{}", p)
}

fn filter_content(content: &str) -> String {
    let mut can_begin = false;
    let mut in_ignore_interval = false;
    let mut in_desc = false;
    let mut result = String::new();

    for line in content.lines() {
        let mut line = trim_trailing(line);
        let mut ignore = false;

        // Desc begin
        if line.contains(DESC_BGN) {
            in_desc = true;
        }

        // Ignore interval
        if line.contains(IGNORED_INTERVAL_BGN) {
            in_ignore_interval = true;
        }
        if in_ignore_interval {
            ignore = true;
        }
        if line.contains(IGNORED_INTERVAL_END) {
            in_ignore_interval = false;
        }

        // Description lines: always skip
        if in_desc && !ignore {
            if line.contains(DESC_END) {
                in_desc = false;
            }
            continue;
        }
        if line.contains(DESC_END) {
            in_desc = false;
        }

        let blank = line.is_empty();

        // Check ignored lines
        if !blank {
            for pattern in IGNORED_LINES {
                if line.contains(pattern) {
                    ignore = true;
                    break;
                }
            }
        }

        // Skip leading blank lines before first real content
        if !ignore && !blank {
            can_begin = true;
        }
        if !can_begin || ignore {
            continue;
        }

        // Normalize UTF-8
        line = normalize_string(&line);

        // Remove ignored substrings
        for sub in IGNORED_SUBSTRINGS {
            line = line.replace(sub, "");
        }

        // Truncate lines that would wrap in the Typst column
        let line = if line.chars().count() > MAX_LINE_LEN {
            let mut s: String = line.chars().take(MAX_LINE_LEN - 1).collect();
            s.push('\u{2026}'); // …
            s
        } else {
            line
        };

        result.push_str(&line);
        result.push('\n');
    }

    // Trim trailing whitespace/newlines
    let trimmed = result.trim_end().to_string();
    if trimmed.is_empty() {
        trimmed
    } else {
        trimmed + "\n"
    }
}

fn trim_trailing(s: &str) -> String {
    s.trim_end().to_string()
}
