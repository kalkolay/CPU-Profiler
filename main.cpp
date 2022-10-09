#include "src/Consumption/ConsumptionManager.h"

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);

    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                          "Профилировщик нагрузок CPU", nullptr, nullptr);

    if (window == nullptr)
    {
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = true;

    if (glewInit() != GLEW_OK)
        return EXIT_FAILURE;

    std::unique_ptr<ConsumptionManager> manager( new ConsumptionManager() );

    while ( !glfwWindowShouldClose(window) )
    {
        glfwPollEvents();

        manager->draw();

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}
