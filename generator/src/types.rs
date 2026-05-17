#[derive(Debug, Clone, PartialEq)]
pub enum FileKind {
    Cpp,
    Java,
    Python,
    Shell,
    Typ,
    Text,
}

impl FileKind {
    pub fn from_path(path: &str) -> Self {
        let ext = path.rsplit('.').next().unwrap_or("").to_lowercase();
        match ext.as_str() {
            "c" | "cc" | "cpp" | "h" | "hpp" => FileKind::Cpp,
            "java" => FileKind::Java,
            "py" => FileKind::Python,
            "sh" => FileKind::Shell,
            "typ" => FileKind::Typ,
            _ => FileKind::Text,
        }
    }

    pub fn lang_str(&self) -> &'static str {
        match self {
            FileKind::Cpp => "cpp",
            FileKind::Java => "java",
            FileKind::Python => "python",
            FileKind::Shell => "bash",
            FileKind::Typ | FileKind::Text => "text",
        }
    }
}

#[derive(Debug, Clone)]
pub struct Subsection {
    pub path: String,
    pub display_name: String,
    pub use_hash: bool,
}

#[derive(Debug, Clone)]
pub struct Section {
    pub name: String,
    pub no_heading: bool,
    pub subsections: Vec<Subsection>,
}
