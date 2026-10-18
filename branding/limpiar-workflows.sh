#!/usr/bin/env bash
# Borra los workflows de Flycast que no se usan en este fork (Switch, UWP, BSD, etc.).
# Ejecutalo con: bash branding/limpiar-workflows.sh
cd "$(dirname "${BASH_SOURCE[0]}")/.."
for f in bsd c-cpp crowdin_prep crowdin_translate switch uwp; do
    rm -f ".github/workflows/$f.yml"
done
echo "Listo. Workflows restantes:"
ls .github/workflows
