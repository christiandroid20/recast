# Python Automator for Recast v1.0 Transformation
import os
import re

def transform_to_recast():
    print("=== INICIANDO TRANSFORMACIÓN COMPLETA A RECAST v1.0 ===")
    
    extensions = {'.cpp', '.h', '.c', '.hpp', '.xml', '.txt', '.cmake', '.rc', '.in', '.properties'}
    ignore_dirs = {'.git', 'build', '.vs', '.idea', 'oe'}
    
    replaced_files = 0
    
    for root, dirs, files in os.walk('.'):
        dirs[:] = [d for d in dirs if d not in ignore_dirs]
        for file in files:
            ext = os.path.splitext(file)[1].lower()
            if ext in extensions:
                filepath = os.path.join(root, file)
                try:
                    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    
                    # 1. Branding replacements
                    new_content = content.replace('Flycast', 'Recast')
                    new_content = new_content.replace('flycast', 'recast')
                    new_content = new_content.replace('FLYCAST', 'RECAST')
                    
                    # 2. Force Version 1.0
                    new_content = re.sub(r'#define\s+BUILD_VERSION\s+".*?"', '#define BUILD_VERSION "1.0"', new_content)
                    
                    if new_content != content:
                        with open(filepath, 'w', encoding='utf-8') as f:
                            f.write(new_content)
                        replaced_files += 1
                except Exception as e:
                    print(f"Error procesando {filepath}: {e}")
                    
    print(f"=== REEMPLAZO COMPLETADO: {replaced_files} ARCHIVOS ACTUALIZADOS A RECAST v1.0 ===")

if __name__ == "__main__":
    transform_to_recast()
