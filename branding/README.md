# Tu emulador (basado en Flycast)

Este proyecto es un fork de [Flycast](https://github.com/flyinghead/flycast) con:
- interfaz que cambia sola entre modo táctil y modo gamepad (USB / Bluetooth),
- opción "Auto-start Last Game",
- nombre, ID de paquete e íconos propios (ver abajo),
- compilación automática del APK con GitHub Actions.

## Cambiar nombre y logo

1. Edita `branding/brand.conf` (`APP_NAME` y `APP_ID`).
2. Reemplaza `branding/logo.png` por tu logo:
   - PNG cuadrado, de 512x512 a 1024x1024, con fondo transparente.
   - Opcional: `branding/banner.png` (16:9, por ejemplo 1280x720) para el banner de Android TV.
     Si no existe, se genera centrando el logo.
3. Haz commit y push. GitHub Actions regenera los íconos y compila el APK.

También puedes aplicarlo en local: `./branding/apply_brand.sh`

## Compilar con GitHub Actions

1. Sube el proyecto a tu repositorio de GitHub (ver la guía de subida).
2. Ve a la pestaña **Actions**. El workflow "Build APK" corre con cada push.
   Para lanzarlo a mano: Actions > Build APK > Run workflow.
3. Al terminar (30 a 60 minutos la primera vez), descarga el APK desde **Artifacts**.
4. Para publicarlo en la sección **Releases**, crea una etiqueta: `git tag v1.0 && git push origin v1.0`.

El APK se firma con la llave de depuración del repo, suficiente para instalarlo en tus propios equipos.

## Instalar en la Mi Box S

- Con ADB: `adb connect <ip-de-la-caja>` y luego `adb install -r archivo.apk`.
- O copia el APK a una memoria USB y ábrelo con un explorador de archivos para Android TV.

## Licencia (importante)

Flycast se distribuye bajo **GPL versión 2 o posterior**. Eso permite modificarlo y cambiarle el nombre,
siempre que:
- conserves el archivo `LICENSE` y los avisos de copyright de los archivos originales,
- publiques el código fuente de tu versión a quien reciba el APK (tener el repositorio público,
  o entregar el código junto al APK, lo cumple),
- dejes claro que es una versión modificada (el historial de commits y este README lo hacen).

No uses logos, textos ni recursos de otros emuladores comerciales (por ejemplo Redream, que es de código
cerrado). El logo debe ser original.
