# Script de Limpieza Local y Branding para Recast v1.0
import os
import re
import shutil

def clean_and_patch():
    print("=== PASO 1: LIMPIEZA DE RESIDUALES Y ARCHIVOS TEMPORALES ===")
    residuals = ['build', 'out', 'bin', 'obj', '.vs', '.idea', 'recast.nro', 'flycast.nro', 'recast.exe', 'flycast.exe']
    
    for item in residuals:
        if os.path.exists(item):
            if os.path.isdir(item):
                try:
                    shutil.rmtree(item)
                    print(f"Directorio eliminado: {item}")
                except Exception as e:
                    print(f"No se pudo borrar {item}: {e}")
            else:
                try:
                    os.remove(item)
                    print(f"Archivo eliminado: {item}")
                except Exception as e:
                    print(f"No se pudo borrar {item}: {e}")

    print("\n=== PASO 2: APLICANDO REEMPLAZO DE MARCA Y VERSIÓN 1.0 ===")
    extensions = {'.cpp', '.h', '.c', '.hpp', '.xml', '.txt', '.cmake', '.rc', '.in'}
    ignore_dirs = {'.git', 'build', '.vs', '.idea', 'oe'}
    
    updated_count = 0
    for root, dirs, files in os.walk('.'):
        dirs[:] = [d for d in dirs if d not in ignore_dirs]
        for file in files:
            ext = os.path.splitext(file)[1].lower()
            if ext in extensions:
                path = os.path.join(root, file)
                try:
                    with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    
                    new_content = content.replace('Flycast', 'Recast').replace('flycast', 'recast').replace('FLYCAST', 'RECAST')
                    new_content = re.sub(r'#define\s+BUILD_VERSION\s+".*?"', '#define BUILD_VERSION "1.0"', new_content)
                    
                    if new_content != content:
                        with open(path, 'w', encoding='utf-8') as f:
                            f.write(new_content)
                        updated_count += 1
                except Exception:
                    pass
                    
    print(f"=== PROCESO LOCAL FINALIZADO: {updated_count} archivos actualizados a Recast v1.0 ===")

if __name__ == "__main__":
    clean_and_patch()
