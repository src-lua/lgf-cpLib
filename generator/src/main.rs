mod config;
mod hasher;
mod parser;
mod processor;
mod renderer;
mod types;

fn main() {
    let sections = parser::parse_contents("contents.txt");

    let typ_output = renderer::render(&sections);

    std::fs::write("contents.typ", &typ_output).unwrap_or_else(|e| {
        eprintln!("Error writing contents.typ: {}", e);
        std::process::exit(1);
    });

    println!("contents.typ generated ({} sections)", sections.len());
}
