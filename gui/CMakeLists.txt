cmake_minimum_required(VERSION 3.8)
project(gui)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(
  include
  ${GLFW_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui
  ${CMAKE_CURRENT_SOURCE_DIR}/src/implot
  ${CMAKE_CURRENT_SOURCE_DIR}/src/backends
)

set(IMGUI_SRC
  src/imgui/imgui.cpp
  src/imgui/imgui_demo.cpp
  src/imgui/imgui_draw.cpp
  src/imgui/imgui_tables.cpp
  src/imgui/imgui_widgets.cpp
  src/implot/implot_demo.cpp
  src/implot/implot_items.cpp
  src/implot/implot.cpp
  src/backends/imgui_impl_glfw.cpp
  src/backends/imgui_impl_opengl3.cpp
)

add_executable(interface src/interface.cpp ${IMGUI_SRC})
target_compile_features(interface PUBLIC c_std_99 cxx_std_17)
ament_target_dependencies(interface rclcpp)
target_link_libraries(interface glfw GL)

install(TARGETS interface
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY
  DESTINATION share/${PROJECT_NAME}/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
