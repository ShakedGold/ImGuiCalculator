#include "Calculator.h"
#include "Expression.h"

#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

int main()
{
    // Initialize GLFW
    if (!glfwInit())
        return 1;

    // Create a GLFW window
    int width = 212, height = 370;
    GLFWwindow *window = glfwCreateWindow(width, height, "ImGui Example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImGuiStyle &style = ImGui::GetStyle();
    style.FrameRounding = 8.f;
    float SCALE = 2.0f;
    io.Fonts->AddFontFromFileTTF("Roboto.ttf", 30);
    ImFontConfig cfg;
    cfg.SizePixels = 13 * SCALE;
    ImGui::GetIO().Fonts->AddFontDefault(&cfg);

    Calculator::Calc calculator("");

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Your ImGui code here
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(width, height));
        Calculator::Render(calculator);

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

// int main() {
//    Expression::Expression tree("12-8");
// }