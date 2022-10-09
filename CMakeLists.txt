cmake_minimum_required(VERSION 3.14)
PROJECT(CPU-Profiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-target arm64-apple-macos11 -framework Cocoa -framework IOKit -framework OpenGL")

set(GLEW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/3rdParties/glew/2.2.0_1/include")
set(GLFW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/3rdParties/glfw/3.3.3/include")
set(INCLUDE_DIRS     ${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})

set(GLEW_LIBRARY     "${PROJECT_SOURCE_DIR}/3rdParties/glew/2.2.0_1/lib/libGLEW.a")
set(GLFW_LIBRARY     "${PROJECT_SOURCE_DIR}/3rdParties/glfw/3.3.3/lib/libglfw3.a")
set(LIBRARIES        ${GLEW_LIBRARY} ${GLFW_LIBRARY})

add_executable(${CMAKE_PROJECT_NAME}
        main.cpp
        src/Utilities/Constants.h
        src/Shader/Shader.cpp
        src/Shader/Shader.h
        src/Consumption/BaseWorker.cpp
        src/Consumption/BaseWorker.h
        src/Consumption/TotalConsumption.cpp
        src/Consumption/TotalConsumption.h
        src/Consumption/CoresConsumption.cpp
        src/Consumption/CoresConsumption.h
        src/Consumption/ConsumptionManager.cpp
        src/Consumption/ConsumptionManager.h)

include_directories(${INCLUDE_DIRS})

target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBRARIES})
