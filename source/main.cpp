#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#define DIRECTINPUT_VERSION 0x0800

//Verzeichnisse
#include "main.h"
#include "../external/pictures/logo.h"
#include "../external/fontawesome/font_awesome.h"
#include "../external/fontawesome/font_awesome.cpp"

//Librarys
#include <filesystem>
#include <string>
#include <fstream>
#include <Windows.h>

int main(int, char**)
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    RECT desktop;
    GetWindowRect(GetDesktopWindow(), &desktop);
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, AppClass, NULL };
    RegisterClassEx(&wc);

    hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED,
        AppClass,
        AppName,
        WS_POPUP,
        0,
        0,
        screenWidth,
        screenHeight,
        0,
        0,
        wc.hInstance,
        0
    );

    //SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, ULW_COLORKEY);

    if (CreateDeviceD3D(hwnd) < 0)
    {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    DefaultFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeui.ttf", 20.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    /*
    An hier kommt mein Edited Code
    */
    // MEINE FONTS
    ImFont* tahoma_big_font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\Tahoma.ttf", 19.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    ImFont* tahoma_font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\Tahoma.ttf", 15.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    ImFont* tahoma9px_font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\Tahoma.ttf", 9.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    ImFont* bauhaus_font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\BAUHS93.ttf", 25.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    ImFont* bauhaus40px_font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\BAUHS93.ttf", 40.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    IM_ASSERT(tahoma_font != nullptr);
    // MEINE ICONS
    ImFont* icons_font = nullptr;
    static const ImWchar icon_ranges[]{ 0xf000, 0xf3ff, 0 };
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 3;
    icons_config.OversampleV = 3;
    icons_font = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 19.5f, &icons_config, icon_ranges);
    // MEIN STYLE
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding = ImVec2(8.00f, 8.00f);
    style.FramePadding = ImVec2(5.00f, 2.00f);
    style.ItemSpacing = ImVec2(6.00f, 6.00f);
    style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
    style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
    style.IndentSpacing = 25;
    style.ScrollbarSize = 13;
    style.GrabMinSize = 10;
    style.WindowBorderSize = 1;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 1;
    style.FrameBorderSize = 1;
    style.TabBorderSize = 1;
    style.WindowRounding = 2;
    style.ChildRounding = 2;
    style.FrameRounding = 2;
    style.PopupRounding = 2;
    style.ScrollbarRounding = 3;
    style.GrabRounding = 3;
    style.TabRounding = 4;
    // MEINE FARBEN
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.075f, 0.075f, 0.075f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.2824, 0.2824, 0.2824, 1.0);
    colors[ImGuiCol_ChildBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
    colors[ImGuiCol_Separator] = ImVec4(0.2824, 0.2824, 0.2824, 1.0);
    // MEINE CHEAT SETTINGS
    bool aimbot = false;
    bool aimbot_fov = false;
    bool aim_vis_check = false;
    bool aim_team_check = false;
    bool rcs = false;
    float aim_fov_float = 5.0f;
    float aim_smooth_float = 5.0f;
    float rcs_yaw_float = 5.0f;
    float rcs_pitch_float = 5.0f;
    int aimbot_key = 0;
    int aimbot_bone = 0;
    static ImVec4 aim_fov_col = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
    // TAB SETTINGS
    bool tab1_open = true;
    bool tab2_open = false;
    bool tab3_open = false;
    bool tab4_open = false;
    bool tab5_open = false;
    // WINDOW SETTINGS
    bool login_window = true;
    bool menu_window = false;
    bool menuVisible = false;
    // STRING VARS FOR LOGIN
    static char username[32] = "";
    static char passwort[32] = "";
    static char key[6] = "";
    // THE FILE SYSTEM
    const int maxFiles = 100;
    const std::string configFolderPath = "ownd_config";
    std::string configFiles[maxFiles];
    


    

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    static bool open = true;
    DWORD dwFlag = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
    char somelogin[25] = "";
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }
        if (!open) ExitProcess(EXIT_SUCCESS);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (login_window) 
        {
            ImGui::SetNextWindowSize(ImVec2(loginX, loginY));
            ImGui::Begin("ownned_login", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);
            {
                //Schließen - Klein machen
                ImGui::PushStyleColor((ImGuiCol_Button), ImVec4(0, 0, 0, 0));
                ImGui::PushStyleColor((ImGuiCol_ButtonHovered), ImVec4(0, 0, 0, 0));
                ImGui::PushStyleColor((ImGuiCol_ButtonActive), ImVec4(0, 0, 0, 0));
                ImGui::PushFont(tahoma_font);
                ImGui::SetCursorPos(ImVec2(270, 5));
                if (ImGui::Button("X", ImVec2(20, 20)))
                {
                    exit(0);
                }
                ImGui::PopFont();
                ImGui::PopStyleColor(3);


                ImGui::SetCursorPos(ImVec2(55, 30));
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0235f, 0.7490f, 0.7490f, 1.0f));
                ImGui::PushFont(bauhaus40px_font);
                ImGui::Text("ownned.ext");               // Display some text (you can use a format strings too)
                ImGui::PopFont();
                ImGui::PopStyleColor();
                
                ImGui::PushFont(tahoma_big_font);

                ImGui::SetCursorPos(ImVec2(30, 100));
                ImGui::BeginChild("##login_inputs", ImVec2(237, 270), true);
                {
                    ImGui::PushStyleColor((ImGuiCol_Button), ImVec4(0.06f, 0.06f, 0.06f, 1.00f));
                    ImGui::PushStyleColor((ImGuiCol_ButtonHovered), ImVec4(0.06f, 0.06f, 0.06f, 1.00f));
                    ImGui::PushStyleColor((ImGuiCol_ButtonActive), ImVec4(0.06f, 0.06f, 0.06f, 1.00f));
                    ImGui::PushStyleColor((ImGuiCol_FrameBg), ImVec4(0.06f, 0.06f, 0.06f, 0.70f));

                    ImGui::SetCursorPos(ImVec2(15, 20));
                    ImGui::PushFont(icons_font);
                    ImGui::Button("  ", ImVec2(39,39));
                    ImGui::SameLine();
                    ImGui::SetCursorPos(ImVec2(28, 12));
                    ImGui::Text(ICON_FA_USER);
                    ImGui::PopFont();

                    ImGui::SetCursorPos(ImVec2(70, 20));
                    ImGui::PushStyleVar((ImGuiStyleVar_FramePadding), ImVec2(10, 10));
                    ImGui::PushItemWidth(150);
                    ImGui::InputTextWithHint("", "Username", username, IM_ARRAYSIZE(username));
                    ImGui::PopItemWidth();

                    ImGui::SetCursorPos(ImVec2(15, 70));
                    ImGui::PushFont(icons_font);
                    ImGui::Button("   ", ImVec2(39, 39));
                    ImGui::SameLine();
                    ImGui::SetCursorPos(ImVec2(26, 55));
                    ImGui::Text(ICON_FA_KEY);
                    ImGui::PopFont();

                    ImGui::SetCursorPos(ImVec2(70, 70));
                    ImGui::PushItemWidth(150);
                    ImGui::InputTextWithHint(" ", "Password", passwort, IM_ARRAYSIZE(passwort));
                    ImGui::PopItemWidth();


                    ImGui::PopStyleVar();
                    ImGui::PopStyleColor(4);
                

                    ImGui::PushStyleColor((ImGuiCol_Button), ImVec4(0.06f, 0.06f, 0.06f, 1.00f));
                    ImGui::PushStyleColor((ImGuiCol_ButtonHovered), ImVec4(0.09f, 0.09f, 0.09f, 1.00f));
                    ImGui::PushStyleColor((ImGuiCol_ButtonActive), ImVec4(0.0235f, 0.7490f, 0.7490f, 0.5f));
                    ImGui::PushStyleColor((ImGuiCol_FrameBg), ImVec4(0.06f, 0.06f, 0.06f, 0.70f));
                    ImGui::SetCursorPos(ImVec2(75, 215));
                    if (ImGui::Button("LOGIN", ImVec2(90, 35)))
                    {
                        if ((strcmp(username, "ikwy") == 0) && (strcmp(passwort, "admin") == 0))
                        {
                            login_window = false;
                            menu_window = true;
                        }
                    }
                    ImGui::PopStyleColor(4);

                }
                ImGui::EndChild();


                ImGui::PopFont();
            }
            ImGui::End();

        }
        
        if (menu_window)
        {
            if (GetAsyncKeyState(VK_INSERT) & 1) 
            {
                menuVisible = !menuVisible;
            }

            if (menuVisible) 
            {
                ImGui::SetNextWindowSize(ImVec2(menuX, menuY));
                ImGui::Begin("ownned_menu", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);
                {
                    static float f = 0.0f;
                    static int counter = 0;

                    //Logo
                    ImGui::SetCursorPos(ImVec2(10, 3));
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0235f, 0.7490f, 0.7490f, 1.0f));
                    ImGui::PushFont(bauhaus_font);
                    ImGui::Text("ownned.ext");               // Display some text (you can use a format strings too)
                    ImGui::PopFont();
                    ImGui::PopStyleColor();

                    ImGui::SameLine();
                    ImGui::SetCursorPos(ImVec2(135, 7));
                    ImGui::PushFont(tahoma_font);
                    ImGui::Text("| [BETA Ver. 0.1.1] by ikwy (%.1f FPS)", io.Framerate);
                    ImGui::PopFont();

                    //Schließen - Klein machen
                    ImGui::PushStyleColor((ImGuiCol_Button), ImVec4(0, 0, 0, 0));
                    ImGui::PushStyleColor((ImGuiCol_ButtonHovered), ImVec4(0, 0, 0, 0));
                    ImGui::PushStyleColor((ImGuiCol_ButtonActive), ImVec4(0, 0, 0, 0));
                    ImGui::PushFont(tahoma_font);
                    ImGui::SetCursorPos(ImVec2(570, 5));
                    if (ImGui::Button("X", ImVec2(20, 20)))
                    {
                        exit(0);
                    }
                    ImGui::PopFont();
                    ImGui::PopStyleColor(3);

                    //kleiner strich unter namen und so
                    ImGui::SetCursorPos(ImVec2(10, 30));
                    ImGui::Separator();

                    //Mein Tab mit funktion und so
                    ImGui::SetCursorPos(ImVec2(10, 40));
                    ImGui::BeginChild("##tab", ImVec2(50, 400), true);

                    ImGui::PushStyleColor((ImGuiCol_Button), ImVec4(0.06f, 0.06f, 0.06f, 1.00f));
                    ImGui::PushStyleColor((ImGuiCol_ButtonHovered), ImVec4(0.09f, 0.09f, 0.09f, 1.00f));
                    ImGui::PushStyleColor((ImGuiCol_ButtonActive), ImVec4(0.0235f, 0.7490f, 0.7490f, 0.5f));
                    ImGui::PushFont(icons_font);

                    if (ImGui::Button("", ImVec2(35, 35))) {
                        tab1_open = true;
                        tab2_open = false;
                        tab3_open = false;
                        tab4_open = false;
                        tab5_open = false;
                    }
                    ImGui::SameLine();
                    ImGui::SetCursorPos(ImVec2(18, 0 - 1));
                    ImGui::Text(ICON_FA_CROSSHAIRS);

                    if (ImGui::Button(" ", ImVec2(35, 35))) {
                        tab1_open = false;
                        tab2_open = true;
                        tab3_open = false;
                        tab4_open = false;
                        tab5_open = false;
                    }
                    ImGui::SameLine();
                    ImGui::SetCursorPos(ImVec2(16, 38));
                    ImGui::Text(ICON_FA_EYE);

                    if (ImGui::Button("  ", ImVec2(35, 35))) {
                        tab1_open = false;
                        tab2_open = false;
                        tab3_open = true;
                        tab4_open = false;
                        tab5_open = false;
                    }
                    ImGui::SameLine();
                    ImGui::SetCursorPos(ImVec2(17, 77));
                    ImGui::Text(ICON_FA_COG);

                    int buttPosY = 316;
                    ImGui::SetCursorPos(ImVec2(8, buttPosY));

                    if (ImGui::Button("   ", ImVec2(35, 35))) {
                        tab1_open = false;
                        tab2_open = false;
                        tab3_open = false;
                        tab4_open = true;
                        tab5_open = false;
                    }
                    ImGui::SameLine();
                    ImGui::SetCursorPos(ImVec2(20, 308));
                    ImGui::Text(ICON_FA_TINT);

                    ImGui::SetCursorPos(ImVec2(8, buttPosY + 41));

                    if (ImGui::Button("    ", ImVec2(35, 35))) {
                        tab1_open = false;
                        tab2_open = false;
                        tab3_open = false;
                        tab4_open = false;
                        tab5_open = true;
                    }
                    ImGui::SameLine();
                    ImGui::SetCursorPos(ImVec2(16, 348));
                    ImGui::Text(ICON_FA_FOLDER);


                    ImGui::PopFont();
                    ImGui::PopStyleColor(3);
                    ImGui::EndChild();

                    if (tab1_open)
                    {
                        //Das rechte Fenster für die einstellungen
                        ImGui::SetCursorPos(ImVec2(70, 40));
                        ImGui::BeginChild("##tab1_right", ImVec2(520, 400), true);
                        ImGui::PushFont(tahoma_big_font);
                        ImGui::SetCursorPos(ImVec2(233, 3));
                        ImGui::Text("Aimbot");
                        ImGui::PopFont();
                        ImGui::SetCursorPos(ImVec2(0, 25));
                        ImGui::Separator();

                        //styleaaaaaaaaaaa
                        ImGui::PushStyleColor((ImGuiCol_Button), ImVec4(0.06f, 0.06f, 0.06f, 1.00f));
                        ImGui::PushStyleColor((ImGuiCol_ButtonHovered), ImVec4(0.09f, 0.09f, 0.09f, 1.00f));
                        ImGui::PushStyleColor((ImGuiCol_ButtonActive), ImVec4(0.0235f, 0.7490f, 0.7490f, 0.5f));
                        ImGui::PushStyleColor((ImGuiCol_ChildBg), ImVec4(0.06f, 0.06f, 0.06f, 0.70f));
                        ImGui::PushStyleColor((ImGuiCol_FrameBg), ImVec4(0.06f, 0.06f, 0.06f, 0.70f));
                        ImGui::PushStyleColor((ImGuiCol_FrameBgHovered), ImVec4(0.09f, 0.09f, 0.09f, 1.00f));
                        ImGui::PushStyleColor((ImGuiCol_FrameBgActive), ImVec4(0.0235f, 0.7490f, 0.7490f, 0.5f));
                        ImGui::PushStyleColor((ImGuiCol_CheckMark), ImVec4(0.0235f, 0.7490f, 0.7490f, 1.0f));

                        ImGui::PushFont(tahoma_font);

                        ImGui::Checkbox("Enable Aimbot", &aimbot);

                        ImGui::PushItemWidth(150);
                        ImGui::Combo("Aimbot Key", &aimbot_key, "Mouse Left\0Mouse Right\0Mouse Wheel\0Mouse 4\0Mouse 5\0\0");
                        ImGui::PopItemWidth();

                        ImGui::Checkbox("Aimbot FOV", &aimbot_fov);
                        ImGui::SameLine();
                        ImGui::SetCursorPos(ImVec2(210, 80));
                        ImGui::ColorEdit4("MyColor##3", (float*)&aim_fov_col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

                        ImGui::PushItemWidth(150);
                        ImGui::SliderFloat("FOV Size", &aim_fov_float, 0.0f, 10.0f, "%.1f");
                        ImGui::PopItemWidth();

                        ImGui::PushItemWidth(150);
                        ImGui::Combo("Aimbot Bone", &aimbot_bone, "Head\0Neck\0Stomach\0Pelvis\0Legs\0\0");
                        ImGui::PopItemWidth();

                        ImGui::PushItemWidth(150);
                        ImGui::SliderFloat("Smoothing", &aim_smooth_float, 0.0f, 10.0f, "%.1f");
                        ImGui::PopItemWidth();

                        ImGui::Checkbox("Visible Check", &aim_vis_check);
                        ImGui::Checkbox("Team Check", &aim_team_check);

                        ImGui::SetCursorPos(ImVec2(260, 30));
                        ImGui::Checkbox("Enable RCS", &rcs);

                        ImGui::SetCursorPosX(260);
                        ImGui::PushItemWidth(150);
                        ImGui::SliderFloat("RCS Yaw", &rcs_yaw_float, 0.0f, 10.0f, "%.1f");
                        ImGui::PopItemWidth();

                        ImGui::SetCursorPosX(260);
                        ImGui::PushItemWidth(150);
                        ImGui::SliderFloat("RCS Pitch", &rcs_pitch_float, 0.0f, 10.0f, "%.1f");
                        ImGui::PopItemWidth();

                        ImGui::PopFont();

                        ImGui::PushFont(tahoma_big_font);
                        ImGui::SetCursorPos(ImVec2(233, 343));
                        ImGui::Text("Weapons");
                        ImGui::PopFont();
                        ImGui::SetCursorPos(ImVec2(0, 365)); // 22
                        ImGui::Separator();

                        ImGui::PushFont(tahoma_font);

                        int wepButtonStartPosX = 70;
                        ImGui::SetCursorPos(ImVec2(wepButtonStartPosX, 372));
                        if (ImGui::Button("PISTOL", ImVec2(70, 20))) {
                            //
                        }

                        ImGui::SetCursorPos(ImVec2(wepButtonStartPosX + 80, 372));
                        if (ImGui::Button("RIFLE", ImVec2(70, 20))) {
                            //
                        }

                        ImGui::SetCursorPos(ImVec2(wepButtonStartPosX + 160, 372));
                        if (ImGui::Button("SMG", ImVec2(70, 20))) {
                            //
                        }

                        ImGui::SetCursorPos(ImVec2(wepButtonStartPosX + 240, 372));
                        if (ImGui::Button("SHOTGUN", ImVec2(70, 20))) {
                            //
                        }

                        ImGui::SetCursorPos(ImVec2(wepButtonStartPosX + 320, 372));
                        if (ImGui::Button("SNIPER", ImVec2(70, 20))) {
                            //
                        }

                        ImGui::PopFont();

                        ImGui::PopStyleColor(8);

                        ImGui::EndChild();
                    }
                    else if (tab2_open)
                    {
                        //Das rechte Fenster für die einstellungen
                        ImGui::SetCursorPos(ImVec2(70, 40));
                        ImGui::BeginChild("##tab2_right", ImVec2(520, 400), true);
                        ImGui::PushFont(tahoma_font);

                        ImGui::PushFont(tahoma_big_font);
                        ImGui::SetCursorPos(ImVec2(237, 3));
                        ImGui::Text("Visual");
                        ImGui::PopFont();

                        ImGui::SetCursorPos(ImVec2(0, 25));
                        ImGui::Separator();
                        ImGui::PopFont();

                        // style für buttons und childbg
                        ImGui::PushStyleColor((ImGuiCol_Button), ImVec4(0.06f, 0.06f, 0.06f, 1.00f));
                        ImGui::PushStyleColor((ImGuiCol_ButtonHovered), ImVec4(0.09f, 0.09f, 0.09f, 1.00f));
                        ImGui::PushStyleColor((ImGuiCol_ButtonActive), ImVec4(0.0235f, 0.7490f, 0.7490f, 0.5f));
                        ImGui::PushStyleColor((ImGuiCol_ChildBg), ImVec4(0.06f, 0.06f, 0.06f, 0.70f));
                        ImGui::PushStyleColor((ImGuiCol_FrameBg), ImVec4(0.06f, 0.06f, 0.06f, 0.70f));
                        ImGui::PushFont(tahoma_font);

                        // preview fenster

                        ImGui::SetCursorPos(ImVec2(312, 31));
                        ImGui::BeginChild("##esp_preview", ImVec2(200, 361), true);

                        ImGui::PushFont(tahoma_big_font);
                        ImGui::SetCursorPos(ImVec2(73, 5));
                        ImGui::Text("Preview");
                        ImGui::Separator();
                        ImGui::PopFont();

                        ImGui::EndChild();

                        ImGui::PopFont();
                        ImGui::PopStyleColor(5);

                        ImGui::EndChild();
                    }
                    else if (tab3_open)
                    {
                        //Das rechte Fenster für die einstellungen
                        ImGui::SetCursorPos(ImVec2(70, 40));
                        ImGui::BeginChild("##tab3_right", ImVec2(520, 400), true);
                        ImGui::PushFont(tahoma_font);

                        ImGui::PushFont(tahoma_big_font);
                        ImGui::SetCursorPos(ImVec2(212, 3));
                        ImGui::Text("Miscellaneous");
                        ImGui::PopFont();

                        ImGui::SetCursorPos(ImVec2(0, 25));
                        ImGui::Separator();

                        if (ImGui::Button("Suizid", ImVec2(100, 100)))
                        {                           // Buttons return true when clicked (most widgets return true when edited/activated)
                            counter++;
                        }
                        ImGui::SameLine();
                        ImGui::Text("Suizid Versuch = %d", counter);

                        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                        ImGui::PopFont();

                        ImGui::EndChild();
                    }
                    else if (tab4_open)
                    {
                        ImGui::SetCursorPos(ImVec2(70, 40));
                        ImGui::BeginChild("##tab4_right", ImVec2(520, 400), true);
                        ImGui::PushFont(tahoma_big_font);
                        ImGui::SetCursorPos(ImVec2(237, 3));
                        ImGui::Text("Colors");
                        ImGui::PopFont();
                        ImGui::SetCursorPos(ImVec2(0, 25));
                        ImGui::Separator();

                        ImGui::PushFont(tahoma_font);



                        ImGui::PopFont();

                        ImGui::EndChild();
                    }
                    else if (tab5_open)
                    {
                        ImGui::SetCursorPos(ImVec2(70, 40));
                        ImGui::BeginChild("##tab5_right", ImVec2(520, 400), true);
                        ImGui::PushFont(tahoma_big_font);
                        ImGui::SetCursorPos(ImVec2(237, 3));
                        ImGui::Text("Config");
                        ImGui::PopFont();
                        ImGui::SetCursorPos(ImVec2(0, 25));
                        ImGui::Separator();

                        // style für buttons und childbg
                        ImGui::PushStyleColor((ImGuiCol_Button), ImVec4(0.06f, 0.06f, 0.06f, 1.00f));
                        ImGui::PushStyleColor((ImGuiCol_ButtonHovered), ImVec4(0.09f, 0.09f, 0.09f, 1.00f));
                        ImGui::PushStyleColor((ImGuiCol_ButtonActive), ImVec4(0.0235f, 0.7490f, 0.7490f, 0.5f));
                        ImGui::PushStyleColor((ImGuiCol_ChildBg), ImVec4(0.06f, 0.06f, 0.06f, 0.70f));
                        ImGui::PushStyleColor((ImGuiCol_FrameBg), ImVec4(0.06f, 0.06f, 0.06f, 0.70f));
                        ImGui::PushFont(tahoma_font);

                        // Check if folder is valid if not create folder
                        if (!std::filesystem::exists(configFolderPath)) {
                            std::filesystem::create_directory(configFolderPath);
                        }

                        // eigentlicher code
                        ImGui::BeginChild("##config_list", ImVec2(200, 335), true);
                        {
                            int fileCount = 0;

                            // Überprüfe, ob der angegebene Ordner existiert
                            if (std::filesystem::is_directory(configFolderPath)) {
                                for (const auto& entry : std::filesystem::directory_iterator(configFolderPath)) {
                                    if (!entry.is_directory() && fileCount < maxFiles) {
                                        // Prüfe, ob die Datei eine Textdatei ist
                                        if (entry.path().extension() == ".txt") {
                                            configFiles[fileCount] = entry.path().filename().string();
                                            fileCount++;
                                        }
                                    }
                                }
                            }

                            // Zeige die gefundenen Textdateien im ImGui-Menü an
                            for (int i = 0; i < fileCount; ++i) {
                                if (ImGui::MenuItem(configFiles[i].c_str())) {
                                    // Hier kannst du die Logik einfügen, um die ausgewählte Textdatei zu öffnen oder zu laden
                                    // Zum Beispiel: loadConfigFile(configFiles[i]);
                                }
                            }
                        }
                        ImGui::EndChild();

                        //LINKS
                        ImGui::SetCursorPos(ImVec2(73, 372));
                        if (ImGui::Button("REFRESH", ImVec2(70, 20))) {
                            //
                        }

                        ImGui::SetCursorPos(ImVec2(220, 33));

                        ImGui::BeginChild("##user_info", ImVec2(240, 40), true);

                        ImGui::Text("%s", username);

                        ImGui::EndChild();

                        //RECHTS
                        ImGui::SetCursorPos(ImVec2(220, 347));

                        ImGui::PushItemWidth(235);
                        static char cfgName[32] = "";
                        ImGui::InputTextWithHint("NAME", "CONFIG.TXT", cfgName, IM_ARRAYSIZE(cfgName));
                        ImGui::PopItemWidth();

                        ImGui::SetCursorPos(ImVec2(220, 372));
                        if (ImGui::Button("SAVE", ImVec2(70, 20))) {
                            std::string cfgSaveName = cfgName;
                            std::ofstream file("ownd_config/" + cfgSaveName + ".txt");
                        }

                        ImGui::SetCursorPos(ImVec2(300, 372));
                        if (ImGui::Button("LOAD", ImVec2(70, 20))) {
                            //
                        }

                        ImGui::SetCursorPos(ImVec2(380, 372));
                        if (ImGui::Button("DELETE", ImVec2(70, 20))) {
                            //
                        }

                        //style ausmachen
                        ImGui::PopFont();
                        ImGui::PopStyleColor(5);

                        ImGui::EndChild();
                    }
                }
                ImGui::End();
            }
        }

        ImGui::EndFrame();

        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    CleanupDeviceD3D();
    DestroyWindow(hwnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}
