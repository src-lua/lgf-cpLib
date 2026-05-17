import os

code_dir = "../lgf-cplib"
extra_dir = "./extra"
div_char = '$'

print(div_char)
print("# First line is the divisor character used to separate the file name from it's title!!!\n# Don't change the first line!!!")

note = f'''
# Any line followed by a '#' character is ignored
# Section headings must be in square brackets
# Subsections within a section should follow the format:
# (filename within code directory)(divisor character:{div_char})(subsection title)
# div character:{div_char}

# If you add an '@' at the end of a file title, that file will not be hashed, even if use_hash is true.
'''
print(note)

# Helper to create human-readable names from filenames
def format_name(filename):
    """Convert filename to readable title"""
    name = filename.replace('.hpp', '').replace('.cpp', '').replace('.h', '')
    name = name.replace('-', ' ').replace('_', ' ')
    # Capitalize words
    return ' '.join(word.capitalize() for word in name.split())

# Helper to recursively collect files
def collect_files(directory, prefix=""):
    """Recursively collect all code files in directory"""
    files = []
    try:
        items = sorted(os.listdir(directory))
    except FileNotFoundError:
        return []

    for item in items:
        full_path = os.path.join(directory, item)
        if os.path.isfile(full_path) and (item.endswith('.hpp') or item.endswith('.cpp') or item.endswith('.h')):
            rel_path = os.path.relpath(full_path, code_dir)
            files.append((rel_path, format_name(item)))
        elif os.path.isdir(full_path):
            # Recursively collect from subdirectories
            subfiles = collect_files(full_path, prefix)
            files.extend(subfiles)

    return files

# Automatically discover all directories in lgf-cplib/
def get_section_name(directory_name):
    """Convert directory name to section title"""
    name = directory_name.replace('-', ' ').replace('_', ' ')
    return ' '.join(word.capitalize() for word in name.split())

# Collect all directories in lgf-cplib/
try:
    all_dirs = sorted([d for d in os.listdir(code_dir)
                       if os.path.isdir(os.path.join(code_dir, d))])
except FileNotFoundError:
    all_dirs = []

# Generate contents for each directory
for directory in all_dirs:
    section_name = get_section_name(directory)
    dir_path = os.path.join(code_dir, directory)

    print(f'[{section_name}]')

    # Collect all files recursively from this directory
    section_files = collect_files(dir_path)

    # Print with aligned formatting
    if section_files:
        longestPath = max(len(filepath) for filepath, _ in section_files)
        for filepath, description in section_files:
            full_filepath = f"{code_dir}/{filepath}"
            spaces = ' ' * (longestPath - len(filepath))
            print(f"{full_filepath} {spaces} {div_char} {description}")

    print()

# Extra content section
if os.path.exists(extra_dir):
    print()
    print("## Extra content - tex files ##")
    print('[Extra]')

    extra_files = []
    for arquivo in sorted(os.listdir(extra_dir)):
        if os.path.isfile(os.path.join(extra_dir, arquivo)) and arquivo.endswith('.tex'):
            extra_files.append(arquivo)

    if extra_files:
        longestPath = max(len(arquivo) for arquivo in extra_files)
        for arquivo in extra_files:
            spaces = ' ' * (longestPath - len(arquivo))
            name = arquivo.replace('.tex', '').replace('-', ' ').replace('_', ' ').title()
            print(f"{extra_dir}/{arquivo} {spaces} {div_char} {name}")
