// Dear ImGui: standalone example application for SDL2 + SDL_Renderer
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

// Important to understand: SDL_Renderer is an _optional_ component of SDL. We do not recommend you use SDL_Renderer
// because it provide a rather limited API to the end-user. We provide this backend for the sake of completeness.
// For a multi-platform app consider using e.g. SDL+DirectX on Windows and SDL+OpenGL on Linux/OSX.

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl.h"
#include "imgui/backends/imgui_impl_sdlrenderer.h"

#include "imnodes/imnodes.h"

#include <stdio.h>
#include <SDL.h>
#include <nfd.h>

#include "ProjectManager.h"

#include "widgets/MapWindow.h"

#include <iostream>

// To get console back on windows
#undef main

std::shared_ptr<Model::Project> currentProject = ProjectManager::NewProject();


void MainMenuBar_OpenFile()
{
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_OpenDialog( NULL, NULL, &outPath );

    if ( result == NFD_OKAY ) {
        puts("Success!");
        puts(outPath);
        free(outPath);

        std::string openFilename = std::string(outPath);

        currentProject = ProjectManager::LoadFromFile(openFilename.c_str());
    }
    else if ( result == NFD_CANCEL ) {
        puts("User pressed cancel.");
    }
    else {
        printf("Error: %s\n", NFD_GetError() );
    }

}

void MainMenuBar_SaveFile()
{
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_SaveDialog( NULL, NULL, &outPath );

    if ( result == NFD_OKAY ) {
        puts("Success!");
        puts(outPath);
        free(outPath);

        std::string saveFilename = std::string(outPath);

        ProjectManager::SaveToFile(currentProject, saveFilename.c_str());
    }
    else if ( result == NFD_CANCEL ) {
        puts("User pressed cancel.");
    }
    else {
        printf("Error: %s\n", NFD_GetError() );
    }
}

bool show_palettes = true;
bool show_textures = true;

void MainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Project", NULL)) {

                //currentProject = ProjectManager::NewProject();


            }

            if(ImGui::MenuItem("Open", NULL)){

                MainMenuBar_OpenFile();
            }
            ImGui::Separator();
            //ImGui::MenuItem("Save", NULL);

            if(ImGui::MenuItem("Save As...", NULL)){
                MainMenuBar_SaveFile();
            }


            ImGui::Separator();
            ImGui::MenuItem("Exit", NULL);
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Project"))
        {
            ImGui::MenuItem("Palettes", NULL, &show_palettes);
            ImGui::MenuItem("Textures", NULL, &show_textures);

            ImGui::EndMenu();
        }


        //if (ImGui::MenuItem("MenuItem")) {} // You can also use MenuItem() inside a menu bar!
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("About", NULL);

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

}



void Project_Palettes()
{
    static Model::Palette* selectedPalette = NULL;

    ImGui::Begin("Palettes");

    ImGui::Columns(2);

    ImGui::ListBoxHeader("##Palette:");
    for (auto& palette : currentProject->palettes)
    {
        auto isSelected = selectedPalette != NULL && &palette == selectedPalette;

        std::string& item_name = palette.name;
        if (ImGui::Selectable(item_name.c_str(), isSelected))
        {
            selectedPalette = &palette;
            // handle selection
        }
    }
    ImGui::ListBoxFooter();

    ImGui::NextColumn();
    if(selectedPalette != NULL) {

        ImGui::Text(selectedPalette->name.c_str());

        for(auto i=0;i<selectedPalette->colours.size();i++){

            ImGui::ColorEdit3((std::string("##color") + std::to_string(i)).c_str(), (float*)&selectedPalette->colours[i].rgb, ImGuiColorEditFlags_DisplayHex);

        }

        if(ImGui::Button("Add")){
            selectedPalette->colours.push_back(Model::Colour());
        }

    }

    ImGui::End();
}

void Project_Textures()
{
    static Model::Texture* selectedTexture = NULL;

    ImGui::Begin("Textures");

    ImGui::Columns(2);

    ImGui::ListBoxHeader("##Texture:");
    for (auto& texture : currentProject->textures)
    {
        auto isSelected = selectedTexture != NULL && &texture == selectedTexture;

        std::string& item_name = texture.name;
        if (ImGui::Selectable(item_name.c_str(), isSelected))
        {
            selectedTexture = &texture;
            // handle selection
        }
    }
    ImGui::ListBoxFooter();

    ImGui::NextColumn();
    if(selectedTexture != NULL) {

        ImGui::Text(selectedTexture->name.c_str());


        ImGui::Image(selectedTexture->texture,
                     ImVec2(selectedTexture->surface->w, selectedTexture->surface->h));

    }

    ImGui::End();
}



void ProjectWindows()
{
    if(show_palettes){
        Project_Palettes();
    }
    if(show_textures){
        Project_Textures();
    }
}

void NodeWindow()
{
    const int hardcoded_node_id = 1;
    const int hardcoded_node_id2 = 2;

    ImNodes::BeginNodeEditor();

    ImNodes::BeginNode(hardcoded_node_id);

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("output node");
    ImNodes::EndNodeTitleBar();

    const int output_attr_id = 2;
    ImNodes::BeginOutputAttribute(output_attr_id);
// in between Begin|EndAttribute calls, you can call ImGui
// UI functions
    ImGui::Text("output pin");
    ImNodes::EndOutputAttribute();

    ImGui::Dummy(ImVec2(80.0f, 45.0f));
    ImNodes::EndNode();

    ImNodes::BeginNode(hardcoded_node_id2);
    ImGui::Dummy(ImVec2(80.0f, 45.0f));
    ImNodes::EndNode();

    ImNodes::MiniMap();
    ImNodes::EndNodeEditor();
}




// Main code
int main(int, char**) {

    std::cout << "Hello world" << std::endl;


    // Setup SDL
    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    currentProject = ProjectManager::LoadFromFile("demo-proj/project.json");



    //ProjectManager::SaveToFile(project, "project2.json");

    // Setup window
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Wolfshark Retro Level Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);

    // Setup SDL_Renderer instance
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        SDL_Log("Error creating SDL_Renderer!");
        return false;
    }

    MapWindow *mapWindow = new MapWindow(renderer, std::make_shared<Model::Map>(currentProject->maps[0]));


    //SDL_RendererInfo info;
    //SDL_GetRendererInfo(renderer, &info);
    //SDL_Log("Current SDL_Renderer: %s", info.name);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImNodes::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 6.0f;

//    style.WindowBorderSize = 2.0f;
//    style.WindowPadding = ImVec2(4,4);
//    style.FramePadding = ImVec2(8,8);

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);


    for(auto& texture : currentProject->textures)
    {
        texture.texture = SDL_CreateTextureFromSurface(renderer, texture.surface);
    }


    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the io cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();


        MainMenuBar();
        ProjectWindows();

        NodeWindow();

        mapWindow->Draw();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();

    ImNodes::DestroyContext();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
