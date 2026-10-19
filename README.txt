# Paquete Limpio Manual - Recast v1.0

## Instrucciones de Reinstalación Limpia:
1. Borra por completo cualquier archivo o carpeta residual antigua (`build`, `.github`, etc.) en la raíz de tu clon de Flycast.
2. Descomprime este ZIP y copia todo directamente en la raíz de tu repositorio local.
3. (Opcional) Puedes ejecutar `python3 clean_and_patch.py` en tu terminal local antes de subirlo si deseas limpiar y parchar tu entorno de desarrollo en tu PC.
4. Abre **GitHub Desktop**, haz commit de los cambios y presiona **Push origin**.
5. GitHub Actions se encargará de clonar los submódulos de forma recursiva, instalar las dependencias necesarias de Linux, limpiar la caché y compilar **Recast v1.0** exitosamente.
