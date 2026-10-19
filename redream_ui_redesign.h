// Redream-like Grid UI & Pause Menu Redesign for Recast / Flycast
// Este módulo define una cuadrícula de juegos estilizada tipo Redream con tarjetas rounded,
// miniaturas de portadas/save states y un menú de pausa moderno y amigable.

#ifndef REDREAM_UI_REDESIGN_H
#ifndef REDREAM_UI_REDESIGN_H
#define REDREAM_UI_REDESIGN_H

#include <vector>
#include <string>

struct GameEntry {
    std::string title;
    std::string path;
    std::string coverArtUrl;
    bool hasSaveState;
};

// Configuración de interfaz amigable (Estilo Redream Grid)
inline void ApplyRedreamFriendlyStyle() {
    // Estilo visual Redream: Bordes suaves, tarjetas amplias, colores limpios
    ImGuiStyle& style = ImGui::GetStyle();
    
    style.WindowPadding            = ImVec2(16, 16);
    style.FramePadding             = ImVec2(12, 8);
    style.ItemSpacing              = ImVec2(16, 16);
    style.ItemInnerSpacing         = ImVec2(10, 10);
    style.TouchExtraPadding        = ImVec2(0, 0);
    style.IndentSpacing            = 20.0f;
    style.ScrollbarSize            = 12.0f;
    style.GrabMinSize              = 12.0f;
    
    style.WindowRounding           = 12.0f; // Esquinas redondeadas suaves
    style.ChildRounding            = 10.0f;
    style.FrameRounding            = 8.0f;
    style.PopupRounding            = 10.0f;
    style.ScrollbarRounding        = 12.0f;
    style.GrabRounding             = 8.0f;
    style.TabRounding              = 8.0f;
    
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg]      = ImVec4(0.06f, 0.06f, 0.08f, 1.00f); // #0F0F14 (Oscuro profundo)
    colors[ImGuiCol_ChildBg]       = ImVec4(0.10f, 0.10f, 0.13f, 1.00f); // #1A1A21 (Tarjeta de juego)
    colors[ImGuiCol_PopupBg]       = ImVec4(0.08f, 0.08f, 0.11f, 0.96f);
    colors[ImGuiCol_Border]        = ImVec4(0.18f, 0.18f, 0.24f, 0.35f);
    colors[ImGuiCol_FrameBg]       = ImVec4(0.14f, 0.14f, 0.18f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]= ImVec4(0.22f, 0.22f, 0.28f, 1.00f);
    colors[ImGuiCol_Button]        = ImVec4(0.16f, 0.16f, 0.22f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.26f, 0.34f, 1.00f);
    colors[ImGuiCol_ButtonActive]  = ImVec4(0.85f, 0.20f, 0.25f, 1.00f); // Rojo Redream Accent
}

// Renderizador de cuadrícula amigable tipo Redream
inline void RenderRedreamGameGrid(const std::vector<GameEntry>& games) {
    float cardWidth = 200.0f;
    float cardHeight = 280.0f;
    float panelWidth = ImGui::GetContentRegionAvail().x;
    int columns = (int)(panelWidth / (cardWidth + 16.0f));
    if (columns < 1) columns = 1;

    ImGui::Columns(columns, nullptr, false);

    for (size_t i = 0; i < games.size(); ++i) {
        ImGui::PushID((int)i);
        
        // Tarjeta de juego redondeada
        ImGui::BeginChild("GameCard", ImVec2(cardWidth, cardHeight), true, ImGuiWindowFlags_NoScrollbar);
        
        // Espacio para la Carátula / Save State Preview
        ImGui::Button(" [ CARÁTULA / STATE ] ", ImVec2(cardWidth - 16.0f, 180.0f));
        
        // Título del juego
        ImGui::TextWrapped("%s", games[i].title.c_str());
        
        if (games[i].hasSaveState) {
            ImGui::TextColored(ImVec4(0.3f, 0.9f, 0.4f, 1.0f), "● Save State Listo");
        }

        ImGui::EndChild();
        ImGui::PopID();

        ImGui::NextColumn();
    }

    ImGui::Columns(1);
}

// Menú de Pausa Estilizado (Overlay Limpio)
inline void RenderRedreamPauseMenu(bool* p_open) {
    if (!*p_open) return;

    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(360, 420));

    if (ImGui::Begin("MENÚ DE PAUSA", p_open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize)) {
        ImGui::Spacing();
        if (ImGui::Button("CONTINUAR JUEGO", ImVec2(-1, 45))) { *p_open = false; }
        ImGui::Spacing();
        if (ImGui::Button("GUARDAR ESTADO (QUICK SAVE)", ImVec2(-1, 45))) { /* Save State */ }
        ImGui::Spacing();
        if (ImGui::Button("CARGAR ESTADO (QUICK LOAD)", ImVec2(-1, 45))) { /* Load State */ }
        ImGui::Spacing();
        if (ImGui::Button("OPCIONES Y CONTROLES", ImVec2(-1, 45))) { /* Settings */ }
        ImGui::Spacing();
        if (ImGui::Button("SALIR AL MENÚ PRINCIPAL", ImVec2(-1, 45))) { /* Exit */ }
        
        ImGui::End();
    }
}

#endif
