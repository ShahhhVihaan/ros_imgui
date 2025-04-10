#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"

#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include "rclcpp/rclcpp.hpp"


bool PingTest(const char* robot_ip, const char* host_ip)
{
    // Implement ping test logic here
    // Return true if successful, false otherwise
    std::cout << "Hello Ping Test! - " << robot_ip << " " << host_ip << std::endl;
    return false;
}

void LaunchROS2Driver()
{
    // Implement ROS2 launch command for the driver
    std::cout << "Hello Driver Test!" << std::endl;
}

void LaunchMoveItSetup()
{
    // Implement ROS2 launch command for MoveIt setup
    std::cout << "Hello MoveIt Test!" << std::endl;

}

void MoveRobotToHomePosition()
{
    // Implement ROS node call to move robot to home position
    std::cout << "Hello Go To Home Test!" << std::endl;
}

void MoveRobotToSleepPosition()
{
    // Implement ROS node call to move robot to sleep position
    std::cout << "Hello Go To Sleep Test!" << std::endl;

}

// // Data arrays for plotting (to be filled with actual data)
// float velocity_data_x[data_count];
// float velocity_data_y[data_count];
// float acceleration_data_x[data_count];
// float acceleration_data_y[data_count];

void ShowRobotControlWindow()
{
    static char robot_ip[128] = "";
    static char host_ip[128] = "";
    static bool is_connected = false;

    ImGui::Begin("Robot Control Window");

    // Robot Connection Information
    ImGui::Text("Robot Connection Information");
    ImGui::InputText("Robot IP", robot_ip, IM_ARRAYSIZE(robot_ip));
    ImGui::InputText("Host IP", host_ip, IM_ARRAYSIZE(host_ip));

    if (ImGui::Button("Connect"))
    {
        // Perform ping test to check connection
        is_connected = PingTest(robot_ip, host_ip);
    }

    ImGui::SameLine();
    if (is_connected)
    {
        ImGui::Text("Status: Connected");
    }
    else
    {
        ImGui::Text("Status: Not Connected");
    }

    ImGui::Separator();

    // ROS2 Launch Commands
    ImGui::Text("ROS2 Launch Commands");

    if (ImGui::Button("Launch Driver"))
    {
        // Call ros2 launch command for the driver
        LaunchROS2Driver();
    }

    ImGui::SameLine();
    if (ImGui::Button("Launch MoveIt Setup"))
    {
        // Call ros2 launch command for MoveIt setup
        LaunchMoveItSetup();
    }

    ImGui::SameLine();
    if (ImGui::Button("Home Position"))
    {
        // Call ros node to move robot to home position
        MoveRobotToHomePosition();
    }

    ImGui::SameLine();
    if (ImGui::Button("Sleep Position"))
    {
        // Call ros node to move robot to sleep position
        MoveRobotToSleepPosition();
    }

    ImGui::Separator();

    // Velocity and Acceleration Graph
    ImGui::Text("End Effector Velocity and Acceleration");

    // if (ImPlot::BeginPlot("Velocity and Acceleration"))
    // {
    //     // Plot velocity and acceleration data here
    //     ImPlot::PlotLine("Velocity", velocity_data_x, velocity_data_y, data_count);
    //     ImPlot::PlotLine("Acceleration", acceleration_data_x, acceleration_data_y, data_count);
    //     ImPlot::EndPlot();
    // }

    ImGui::End();
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Main code
int main(int argc, char** argv)
{   
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("interface_node");

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Test Window", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui and ImPlot context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    bool show_demo_window = true;
    bool show_plot_window = true;
    bool show_another_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (rclcpp::ok() && !glfwWindowShouldClose(window))
    {

        rclcpp::spin_some(node);
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
        
        if (show_plot_window)
            ImPlot::ShowDemoWindow(&show_plot_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Plot Window", &show_plot_window);
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            // ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            // ImGui::Text("Hello from another window!");
            // if (ImGui::Button("Close Me"))
            //     show_another_window = false;
            // ImGui::End();
            ShowRobotControlWindow();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    rclcpp::shutdown();
    return 0;
}
