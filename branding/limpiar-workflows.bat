@echo off
REM Borra los workflows de Flycast que no se usan en este fork (Switch, UWP, BSD, etc.).
REM Ejecutalo desde la carpeta raiz del repo: branding\limpiar-workflows.bat
cd /d "%~dp0.."
for %%f in (bsd c-cpp crowdin_prep crowdin_translate switch uwp) do if exist ".github\workflows\%%f.yml" del /q ".github\workflows\%%f.yml"
echo Listo. Workflows restantes:
dir /b .github\workflows
