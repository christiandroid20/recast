#!/usr/bin/env bash
# Aplica la marca definida en branding/brand.conf al proyecto Android:
#  - nombre visible de la app
#  - applicationId
#  - íconos (desde branding/logo.png y, opcionalmente, branding/banner.png)
# Es idempotente: se puede ejecutar las veces que quieras.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BRAND="$ROOT/branding"
ANDROID="$ROOT/shell/android-studio/flycast"
RES="$ANDROID/src/main/res"

# shellcheck source=/dev/null
source <(tr -d '\r' < "$BRAND/brand.conf")

if ! [[ "$APP_NAME" =~ ^[A-Za-z0-9][A-Za-z0-9\ ._-]*$ ]]; then
    echo "APP_NAME inválido: usa solo letras, números, espacios, punto o guion." >&2
    exit 1
fi
if ! [[ "$APP_ID" =~ ^[a-z][a-z0-9_]*(\.[a-z][a-z0-9_]*)+$ ]]; then
    echo "APP_ID inválido: ejemplo válido com.miemulador.app (minúsculas y puntos)." >&2
    exit 1
fi

# 1) Nombre visible
sed -i -E "s|(<string name=\"app_name\" translatable=\"false\">)[^<]*(</string>)|\1${APP_NAME}\2|" \
    "$RES/values/donottranslate.xml"

# 2) applicationId (el paquete Java/JNI com.flycast.emulator no se toca a propósito)
sed -i -E "s|applicationId = \"[^\"]*\"|applicationId = \"${APP_ID}\"|" \
    "$ANDROID/build.gradle.kts"

# 3) Íconos
IM=""
if command -v magick >/dev/null 2>&1; then IM="magick"
elif command -v convert >/dev/null 2>&1; then IM="convert"; fi

if [ -f "$BRAND/logo.png" ] && [ -n "$IM" ]; then
    # Ícono del launcher en cada densidad que usa el proyecto
    for entry in ldpi:36 mdpi:48 hdpi:72 xhdpi:96 xxhdpi:144; do
        density="${entry%%:*}"; size="${entry##*:}"
        mkdir -p "$RES/drawable-$density"
        $IM "$BRAND/logo.png" -background none -strip -depth 8 -resize "${size}x${size}" \
            -gravity center -extent "${size}x${size}" "$RES/drawable-$density/ic_launcher.png"
    done
    # Banner de Android TV (320x180): usa branding/banner.png si existe,
    # si no, centra el logo sobre fondo transparente.
    mkdir -p "$RES/drawable-xhdpi"
    if [ -f "$BRAND/banner.png" ]; then
        $IM "$BRAND/banner.png" -background none -strip -depth 8 -resize 320x180 \
            -gravity center -extent 320x180 "$RES/drawable-xhdpi/ic_banner.png"
    else
        $IM "$BRAND/logo.png" -background none -strip -depth 8 -resize x140 \
            -gravity center -extent 320x180 "$RES/drawable-xhdpi/ic_banner.png"
    fi
    echo "Íconos generados desde branding/logo.png"
else
    echo "Sin branding/logo.png (o sin ImageMagick): se conservan los íconos actuales."
fi

echo "Marca aplicada: '$APP_NAME' ($APP_ID)"
