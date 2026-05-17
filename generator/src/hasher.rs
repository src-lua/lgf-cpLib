/// Port of md5hsh.cpp: strip_comments + getCodeHash
/// Uses the `md5` crate instead of OpenSSL.

#[derive(Debug, Clone, Copy, PartialEq)]
enum St {
    Normal,
    PossibleComment,
    LineComment,
    BlockComment,
    InStr,
    InStrEsc,
    InChar,
    InCharEsc,
    InRaw,
}

pub fn strip_comments(s: &str) -> String {
    let bytes: Vec<char> = s.chars().collect();
    let n = bytes.len();
    let mut out = String::with_capacity(s.len());
    let mut st = St::Normal;
    let mut i = 0usize;
    let mut raw_end = String::new();

    while i < n {
        let c = bytes[i];
        match st {
            St::Normal => {
                if c == '/' {
                    st = St::PossibleComment;
                    i += 1;
                } else if c == '"' {
                    out.push(c);
                    st = St::InStr;
                    i += 1;
                } else if c == '\'' {
                    out.push(c);
                    st = St::InChar;
                    i += 1;
                } else if c == 'R' && i + 1 < n && bytes[i + 1] == '"' {
                    // Raw string R"delim(...)delim"
                    let mut j = i + 2;
                    let mut delim = String::new();
                    while j < n && bytes[j] != '(' && bytes[j] != '\n' {
                        delim.push(bytes[j]);
                        j += 1;
                    }
                    if j < n && bytes[j] == '(' {
                        raw_end = format!("){}\"", delim);
                        // emit R"delim(
                        out.extend(&bytes[i..=j]);
                        i = j + 1;
                        st = St::InRaw;
                    } else {
                        out.push(c);
                        i += 1;
                    }
                } else {
                    out.push(c);
                    i += 1;
                }
            }
            St::PossibleComment => {
                if i >= n {
                    out.push('/');
                    st = St::Normal;
                } else if bytes[i] == '/' {
                    st = St::LineComment;
                    i += 1;
                } else if bytes[i] == '*' {
                    st = St::BlockComment;
                    i += 1;
                } else {
                    out.push('/');
                    st = St::Normal;
                    // don't advance i, reprocess
                }
            }
            St::LineComment => {
                if c == '\n' {
                    out.push('\n');
                    st = St::Normal;
                }
                i += 1;
            }
            St::BlockComment => {
                if c == '*' && i + 1 < n && bytes[i + 1] == '/' {
                    i += 2;
                    st = St::Normal;
                } else {
                    i += 1;
                }
            }
            St::InStr => {
                out.push(c);
                if c == '\\' {
                    st = St::InStrEsc;
                } else if c == '"' {
                    st = St::Normal;
                }
                i += 1;
            }
            St::InStrEsc => {
                out.push(c);
                st = St::InStr;
                i += 1;
            }
            St::InChar => {
                out.push(c);
                if c == '\\' {
                    st = St::InCharEsc;
                } else if c == '\'' {
                    st = St::Normal;
                }
                i += 1;
            }
            St::InCharEsc => {
                out.push(c);
                st = St::InChar;
                i += 1;
            }
            St::InRaw => {
                // Find raw_end in remaining string
                let remaining: String = bytes[i..].iter().collect();
                if let Some(pos) = remaining.find(&raw_end) {
                    let end = i + pos + raw_end.chars().count();
                    out.extend(&bytes[i..end]);
                    i = end;
                    st = St::Normal;
                } else {
                    // No closing found, emit rest
                    out.extend(&bytes[i..n]);
                    i = n;
                    st = St::Normal;
                }
            }
        }
    }

    if st == St::PossibleComment {
        out.push('/');
    }

    out
}

fn hash_fast(s: &str, dig: usize) -> String {
    let stripped = strip_comments(s);
    let normalized: String = stripped.chars().filter(|c| !c.is_whitespace()).collect();
    let digest = md5::compute(normalized.as_bytes());
    let hex = format!("{:x}", digest);
    let result = &hex[..dig.min(hex.len())];
    result.to_uppercase()
}

/// Port of getCodeHash: annotates each line with a 3-char hash showing context.
/// Returns the annotated code string (hash prefix per line).
/// In Typst we use this differently: just return the single hash for the whole file.
#[allow(dead_code)]
pub fn get_file_hash(code: &str, dig: usize) -> String {
    // For Typst we just display one hash in the subsection heading.
    // Use the same logic as hash_fast on the whole file.
    hash_fast(code, dig)
}

/// Returns per-line hash annotations: (Option<hash>, line_content).
/// Lines that are empty or pure comments get None.
pub fn annotate_with_hashes(code: &str, dig: usize) -> Vec<(Option<String>, String)> {
    let mut out = Vec::new();
    let mut context_stack: Vec<String> = vec![String::new(); 100];
    let mut block_comment = false;

    for line in code.lines() {
        let mut t = line.to_string();

        for c in line.chars() {
            if c == '{' {
                context_stack.push(String::new());
            } else if c == '}' && context_stack.len() > 1 {
                let top = context_stack.pop().unwrap();
                t = top + line;
            }
        }

        let trimmed = line.trim();
        let is_comment_start = trimmed.is_empty()
            || trimmed.starts_with("//")
            || trimmed.starts_with("/*")
            || trimmed.starts_with('*');

        if !block_comment && trimmed.starts_with("/*") {
            block_comment = true;
        }
        let effectively_comment = is_comment_start || block_comment;
        if block_comment && trimmed.contains("*/") {
            block_comment = false;
        }

        let hash = if effectively_comment {
            None
        } else {
            Some(hash_fast(&t, dig))
        };

        out.push((hash, line.to_string()));

        if let Some(top) = context_stack.last_mut() {
            top.push_str(&t);
            top.push('\n');
        }
    }

    out
}
