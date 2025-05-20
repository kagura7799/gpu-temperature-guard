#include <iostream>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "GLFW/glfw3.h"
#include "fonts/NotoSans-VariableFont_wdth,wght_font.h"
#include <string>

static GLFWwindow* window = nullptr;

struct Configuration
{
    int max_value_temp;
    std::string current_value_temp;
    bool notification;
    bool play_sound;
    bool overlay;
};

struct Colors
{
    static const inline ImVec4 red = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    static const inline ImVec4 white = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
};

static Configuration config = {30, "- C", false, false, false};

static void GLFWErrorCallback(int error, const char* description)
{
    std::cout << "GLFW Error " << description << " code : " << error << '\n';
}

void imguiMenu()
{
    glfwSetErrorCallback(GLFWErrorCallback);
    if (!glfwInit())
    {
        std::cout << "Failed to initialize glfw" << '\n';
        return;
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    window = glfwCreateWindow(1000, 400, "ImGUI", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
     
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls (optional)
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    ImFont* NotoSans_font = io.Fonts->AddFontFromMemoryTTF(
        NotoSans_VariableFont_wdth_wght_ttf,    
        NotoSans_VariableFont_wdth_wght_ttf_len,
        32.0f
    );

    ImFont* font_big = io.Fonts->AddFontFromMemoryTTF(
        NotoSans_VariableFont_wdth_wght_ttf,
        NotoSans_VariableFont_wdth_wght_ttf_len,
        250.f
    );

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    ImGui::StyleColorsDark();

    glfwSetWindowSize(window, 1000, 400);
    glfwSetWindowPos(window, 100, 100);

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int screenWidth, screenHeight;
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        screenWidth = mode->width;
        screenHeight = mode->height;

        ImGui::SetNextWindowSize(ImVec2(1000, 400), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);

        ImGui::Begin("GPU Temperature Guard");

        ImGui::SetCursorPos(ImVec2(900, 380));
        ImGui::PushItemWidth(280);
        ImGui::SliderInt("Max temp", &config.max_value_temp, 30, 100);
        ImGui::PopItemWidth();

        ImGui::SetCursorPos(ImVec2(900, 430));
        ImGui::Checkbox("Notification", &config.notification);
        ImGui::SetCursorPos(ImVec2(900, 470));
        ImGui::Checkbox("Play audio", &config.play_sound);
        ImGui::SetCursorPos(ImVec2(900, 510));
        ImGui::Checkbox("Temperature overlay", &config.overlay);
        
        //ImGui::PushStyleColor(ImGuiCol_Text, (config.max_value_temp > config.current_value_temp ? Colors::red : Colors::white));
        
        ImGui::PushFont(font_big);
        ImGui::SetCursorPos(ImVec2(950, 70));
        ImGui::PushStyleColor(ImGuiCol_Text, Colors::white);
        ImGui::Text("%s", config.current_value_temp.c_str());
        ImGui::SetWindowFontScale(0.6f);
        ImGui::PopStyleColor();
        ImGui::PopFont();

        ImGui::End();
        ImGui::Render();

        int displayW, displayH;
        glfwGetFramebufferSize(window, &displayW, &displayH);
        glViewport(0, 0, displayW, displayH);
        glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w, clearColor.z * clearColor.w, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backupCurrentContext);
        }

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}