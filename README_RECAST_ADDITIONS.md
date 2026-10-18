# Additions for christiandroid20/recast

Este archivo ZIP contiene los siguientes componentes listos para ser incorporados al repositorio:

1. `.github/workflows/build.yml`
   - Workflow completo de GitHub Actions para compilar automáticamente **Android (APK)**, **Linux (Binary)** y **Windows (x64)** en cada push/PR.

2. `branding/`
   - `logo.svg`: Isotipo/Logo vectorizado principal de Recast.
   - `ic_banner.svg`: Banner para Android TV (1280x720).
   - `icon_hos.svg`: Icono optimizado para Horizon OS / Nintendo Switch (256x256).

## Cómo aplicarlo:
Extrae la carpeta directamente en la raíz de tu repositorio `recast` y realiza el commit/push correspondiente:

```bash
git add .
git commit -m "Add GitHub Actions CI/CD workflows and branding assets for Recast"
git push
```
