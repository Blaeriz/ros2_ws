cmake_minimum_required(VERSION 3.8)
project(sercli)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(serv src/serv.cpp)
ament_target_dependencies(serv rclcpp)

add_executable(cli src/cli.cpp)
ament_target_dependencies(cli rclcpp std_msgs)

install(TARGETS
  cli
  serv
  DESTINATION lib/${PROJECT_NAME})

set(srv_files
  "srv/Add.srv"
)
rosidl_generate_interfaces(${PROJECT_NAME}
  ${srv_files}
)
ament_export_dependencies(rosidl_default_runtime)

rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} rosidl_typesupport_cpp)

target_link_libraries(serv "${cpp_typesupport_target}")
target_link_libraries(cli "${cpp_typesupport_target}")


ament_package()
