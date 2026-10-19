# Script de Limpieza y Parcheo Automático Total para Recast v1.0
import os
import re
import shutil

def run_auto_clean_and_patch():
    print("=== 1. LIMPIANDO COMPILACIONES Y ARCHIVOS GENERADOS ANTERIORES ===")
    
    # Directorios y archivos generados que deben eliminarse por completo
    dirs_to_remove = ['build', 'out', 'bin', 'obj', '.vs', '.idea']
    files_to_remove = ['recast.nro', 'flycast.nro', 'recast.exe', 'flycast.exe']

    for d in dirs_to_remove:
        if os.path.exists(d):
            try:
                shutil.rmtree(d)
                print(f"Directorio eliminado: {d}")
            except Exception as e:
                print(f"No se pudo eliminar {d}: {e}")

    for f in files_to_remove:
        if os.path.exists(f):
            try:
                os.remove(f)
                print(f"Archivo generado eliminado: {f}")
            except Exception as e:
                pass

    print("\n=== 2. FORZANDO NOMBRE RECAST Y VERSIÓN 1.0 EN TODO EL CÓDIGO ===")
    
    extensions = {'.cpp', '.h', '.c', '.hpp', '.xml', '.txt', '.cmake', '.rc', '.in', '.properties'}
    ignore_dirs = {'.git', 'build', '.vs', '.idea', 'oe'}
    
    for root, dirs, files in os.walk('.'):
        dirs[:] = [d for d in dirs if d not in ignore_dirs]
        for file in files:
            ext = os.path.splitext(file)[1].lower()
            if ext in extensions:
                filepath = os.path.join(root, file)
                try:
                    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    
                    # Reemplazo estricto de nombres
                    new_content = content.replace('Flycast', 'Recast')
                    new_content = new_content.replace('flycast', 'recast')
                    new_content = new_content.replace('FLYCAST', 'RECAST')
                    
                    # Forzar versión 1.0 limpia (reemplazando hashes de git antiguos)
                    new_content = re.sub(r'#define\s+BUILD_VERSION\s+".*?"', '#define BUILD_VERSION "1.0"', new_content)
                    new_content = re.sub(r'#define\s+GIT_HASH\s+".*?"', '#define GIT_HASH "1.0"', new_content)
                    
                    # Sobreescribir tema azul por defecto si existe gui_style.cpp o gui.cpp
                    if "gui_style" in file.lower() or "gui.cpp" in file.lower():
                        new_content = new_content.replace('ImVec4(0.20f, 0.40f, 0.70f', 'ImVec4(0.06f, 0.06f, 0.08f')
                        new_content = new_content.replace('ImVec4(0.26f, 0.59f, 0.98f', 'ImVec4(0.16f, 0.16f, 0.22f')

                    if new_content != content:
                        with open(filepath, 'w', encoding='utf-8') as f:
                            f.write(new_content)
                except Exception as e:
                    pass

    print("\n=== 3. PARCHEO Y LIMPIEZA COMPLETA PARA RECAST v1.0 LISTO ===")

if __name__ == "__main__":
    run_auto_clean_and_patch()
