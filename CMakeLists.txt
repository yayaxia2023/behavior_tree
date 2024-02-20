cmake_minimum_required(VERSION 3.8)
project(rm_behavior_tree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THIS_PACKAGE_INCLUDE_DEPENDS
    rm_decision_interfaces
    rclcpp
    std_msgs
    behaviortree_cpp
    behaviortree_ros2
)

find_package(ament_cmake_auto REQUIRED)

ament_auto_find_build_dependencies()

ament_auto_add_executable(rm_behavior_tree 
    src/rm_behavior_tree.cpp
)
# ament_auto_add_executable(send_goal 
#     plugins/action/send_goal.cpp
# )

# 定义宏函数 add_target_dependencies
function(add_target_dependencies target)
    target_include_directories(${target} PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
    ament_target_dependencies(${target} ${THIS_PACKAGE_INCLUDE_DEPENDS})
endfunction()

add_library(WaitUntilSubscribe_plugin SHARED 
    plugins/action/wait_until_subscribe.cpp
)
add_library(SendGoal_plugin SHARED 
    plugins/action/send_goal.cpp
)
add_library(UpdateMsg_plugin SHARED 
    plugins/action/update_msg.cpp
)

target_compile_definitions(WaitUntilSubscribe_plugin PRIVATE BT_PLUGIN_EXPORT)
target_compile_definitions(SendGoal_plugin PRIVATE BT_PLUGIN_EXPORT)
target_compile_definitions(UpdateMsg_plugin PRIVATE BT_PLUGIN_EXPORT)

add_target_dependencies(WaitUntilSubscribe_plugin)
add_target_dependencies(SendGoal_plugin)
add_target_dependencies(UpdateMsg_plugin)

ament_auto_package()