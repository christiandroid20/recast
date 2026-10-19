// Recast v1.0 - Modern UI Theme & Grid Layout (Redream Parity)
#ifndef RECAST_UI_THEME_H
#define RECAST_UI_THEME_H

#include "imgui.h"
#include <vector>
#include <string>

struct RecastGameItem {
    std::string title;
    std::string path;
    std::string coverPath;
    bool hasSaveState;
    std::string saveStatePreviewPath;
};

// Apply Recast v1.0 Modern Dark Palette & Rounded Aesthetics
inline void ApplyRecastTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    
    // Spacing & Padding
    style.WindowPadding            = ImVec2(16.0f, 16.0f);
    style.FramePadding             = ImVec2(12.0f, 8.0f);
    style.ItemSpacing              = ImVec2(16.0f, 16.0f);
    style.ItemInnerSpacing         = ImVec2(10.0f, 10.0f);
    style.IndentSpacing            = 20.0f;
    style.ScrollbarSize            = 12.0f;
    style.GrabMinSize              = 12.0f;
    
    // Rounded Corners (Soft Redream-style edges)
    style.WindowRounding           = 12.0f;
    style.ChildRounding            = 10.0f;
    style.FrameRounding            = 8.0f;
    style.PopupRounding            = 10.0f;
    style.ScrollbarRounding        = 12.0f;
    style.GrabRounding             = 8.0f;
    style.TabRounding              = 8.0f;
    
    // Color Palette (#0F0F14 deep background, #1A1A21 cards)
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.50f, 0.55f, 1.00f);
    colors[ImGuiCol_WindowBg]              = ImVec4(0.06f, 0.06f, 0.08f, 1.00f); // #0F0F14
    colors[ImGuiCol_ChildBg]               = ImVec4(0.10f, 0.10f, 0.13f, 1.00f); // #1A1A21
    colors[ImGuiCol_PopupBg]               = ImVec4(0.08f, 0.08f, 0.11f, 0.96f);
    colors[ImGuiCol_Border]                = ImVec4(0.18f, 0.18f, 0.24f, 0.35f);
    colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]               = ImVec4(0.14f, 0.14f, 0.18f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.22f, 0.22f, 0.28f, 1.00f);
    colors[ImGuiCol_FrameBgActive]         = ImVec4(0.28f, 0.28f, 0.35f, 1.00f);
    colors[ImGuiCol_TitleBg]               = ImVec4(0.06f, 0.06f, 0.08f, 1.00f);
    colors[ImGuiCol_TitleBgActive]         = ImVec4(0.08f, 0.08f, 0.11f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.06f, 0.06f, 0.08f, 1.00f);
    colors[ImGuiCol_MenuBarBg]             = ImVec4(0.10f, 0.10f, 0.13f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.06f, 0.06f, 0.08f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.20f, 0.20f, 0.26f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.28f, 0.28f, 0.35f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.35f, 0.35f, 0.42f, 1.00f);
    colors[ImGuiCol_CheckMark]             = ImVec4(0.85f, 0.20f, 0.25f, 1.00f);
    colors[ImGuiCol_SliderGrab]            = ImVec4(0.85f, 0.20f, 0.25f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.95f, 0.30f, 0.35f, 1.00f);
    colors[ImGuiCol_Button]                = ImVec4(0.16f, 0.16f, 0.22f, 1.00f);
    colors[ImGuiCol_ButtonHovered]         = ImVec4(0.26f, 0.26f, 0.34f, 1.00f);
    colors[ImGuiCol_ButtonActive]          = ImVec4(0.85f, 0.20f, 0.25f, 1.00f);
    colors[ImGuiCol_Header]                = ImVec4(0.16f, 0.16f, 0.22f, 1.00f);
    colors[ImGuiCol_HeaderHovered]         = ImVec4(0.26f, 0.26f, 0.34f, 1.00f);
    colors[ImGuiCol_HeaderActive]          = ImVec4(0.85f, 0.20f, 0.25f, 1.00f);
}

// Render Recast Game Grid with Save State Previews
inline void RenderRecastGameGrid(const std::vector<RecastGameItem>& games) {
    float cardWidth = 210.0f;
    float cardHeight = 290.0f;
    float availWidth = ImGui::GetContentRegionAvail().x;
    int columns = (int)(availWidth / (cardWidth + 16.0f));
    if (columns < 1) columns = 1;

    ImGui::Columns(columns, nullptr, false);

    for (size_t i = 0; i < games.size(); ++i) {
        ImGui::PushID((int)i);
        
        ImGui::BeginChild("GameCard", ImVec2(cardWidth, cardHeight), true, ImGuiWindowFlags_NoScrollbar);
        
        ImGui::Button(" [ PORTADA / SAVE STATE ] ", ImVec2(cardWidth - 16.0f, 180.0f));
        
        ImGui::Spacing();
        ImGui::TextWrapped("%s", games[i].title.c_str());
        
        if (games[i].hasSaveState) {
            ImGui::TextColored(ImVec4(0.30f, 0.90f, 0.45f, 1.00f), "● Save State Disponible");
        } else {
            ImGui::TextColored(ImVec4(0.50f, 0.50f, 0.55f, 1.00f), "Sin partida guardada");
        }

        ImGui::EndChild();
        ImGui::PopID();
        ImGui::NextColumn();
    }

    ImGui::Columns(1);
}

// Render Clean In-Game Pause Menu Overlay
inline void RenderRecastPauseMenu(bool* p_open) {
    if (!*p_open) return;

    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(380, 440));

    if (ImGui::Begin("RECAST v1.0 - MENÚ DE PAUSA", p_open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize)) {
        ImGui::Spacing();
        if (ImGui::Button("CONTINUAR JUEGO", ImVec2(-1, 48))) { *p_open = false; }
        ImGui::Spacing();
        if (ImGui::Button("GUARDAR ESTADO RÁPIDO", ImVec2(-1, 48))) { /* Save State logic */ }
        ImGui::Spacing();
        if (ImGui::Button("CARGAR ESTADO RÁPIDO", ImVec2(-1, 48))) { /* Load State logic */ }
        ImGui::Spacing();
        if (ImGui::Button("AJUSTES DE CONTROLES Y VIDEO", ImVec2(-1, 48))) { /* Settings logic */ }
        ImGui::Spacing();
        if (ImGui::Button("SALIR AL MENÚ PRINCIPAL", ImVec2(-1, 48))) { /* Exit logic */ }
        
        ImGui::End();
    }
}

#endif // RECAST_UI_THEME_H
