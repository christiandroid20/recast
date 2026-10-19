# Pack de Instalación Manual - Recast v1.0

Este paquete contiene todos los componentes necesarios para transformar completamente tu proyecto a **Recast v1.0** con interfaz amigable, cuadrícula de juegos, miniaturas de save states y menú de pausa moderno.

## Estructura de Archivos:
1. `.github/workflows/build.yml`: Flujo de integración continua para GitHub Actions.
2. `core/ui/recast_ui_theme.h`: Cabecera de ImGui con el tema oscuro (#0F0F14), cuadrícula de juegos e interfaz amigable.
3. `apply_recast_v1.py`: Script de automatización en Python que barre el código fuente y reemplaza las referencias a Recast v1.0.

## Instrucciones de Instalación Manual:
1. Copia la carpeta `.github` y la carpeta `core` directamente en la raíz de tu proyecto local.
2. Copia `apply_recast_v1.py` en la raíz del proyecto.
3. Abre **GitHub Desktop**:
   - Verás automáticamente detectados los nuevos archivos agregados.
   - Escribe un commit como `Integracion Recast v1.0 UI y Branding`.
   - Haz clic en **Commit to main** y luego en **Push origin**.
