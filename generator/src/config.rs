pub const USE_HASH: bool = true;
pub const HASH_LEN: usize = 3;

pub const IGNORED_LINES: &[&str] = &[
    "#include <bits/stdc++.h>",
    "using namespace std;",
    "#pragma once",
    "#define pii pair<int, int>",
    "#define pii pair<int,int>",
    "#define ll long long",
    "using pii = pair<int,int>;",
    "using pii = pair<int, int>;",
    "using ll = long long;",
    "using ll = long long int;",
    "using ull = unsigned long long;",
    "using ull = unsigned long long int;",
    "using ld = double;",
    "using ld = long double;",
    "LATEX_IGNORED_LINE",
    "Credits: ",
    "/********",
    "********/",
    "LATEX_DESC_BEGIN",
    "LATEX_DESC_END",
    "\t//////////////////////",
];

pub const IGNORED_SUBSTRINGS: &[&str] = &["std::", "LATEX_DESC_BEGIN", "LATEX_DESC_END"];

pub const IGNORED_INTERVAL_BGN: &str = "LATEX_IGNORED_BEGIN";
pub const IGNORED_INTERVAL_END: &str = "LATEX_IGNORED_END";

pub const DESC_BGN: &str = "LATEX_DESC_BEGIN";
pub const DESC_END: &str = "LATEX_DESC_END";

pub fn normalize_char(c: char) -> Option<char> {
    match c {
        'ç' | 'Ç' => Some('c'),
        'ã' | 'â' | 'á' | 'à' | 'ä' | 'å' => Some('a'),
        'Ã' | 'Â' | 'Á' | 'À' => Some('A'),
        'é' | 'è' | 'ê' | 'ë' => Some('e'),
        'É' | 'È' | 'Ê' | 'Ë' => Some('E'),
        'í' | 'ì' | 'î' | 'ï' => Some('i'),
        'ó' | 'ò' | 'ô' | 'õ' => Some('o'),
        'Ó' | 'Ò' | 'Ô' | 'Õ' => Some('O'),
        'ú' | 'ù' | 'û' | 'ü' => Some('u'),
        'Ú' | 'Ù' | 'Û' | 'Ü' => Some('U'),
        'ñ' => Some('n'),
        'ý' | 'ÿ' => Some('y'),
        '\u{2019}' => Some('\''),
        '\u{03B1}' => Some('a'),
        '\u{2013}' => Some('-'),
        _ => None,
    }
}

pub fn normalize_string(s: &str) -> String {
    s.chars().map(|c| normalize_char(c).unwrap_or(c)).collect()
}
