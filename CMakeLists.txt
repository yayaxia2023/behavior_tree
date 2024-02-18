cmake_minimum_required(VERSION 3.8)
project(rm_behavior_tree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THIS_PACKAGE_INCLUDE_DEPENDS
    rm_decision_interfaces
    rclcpp
    std_msgs
    behaviortree_cpp     
)

find_package(ament_cmake_auto REQUIRED)

ament_auto_find_build_dependencies()

ament_auto_add_executable(rm_behavior_tree 
    src/rm_behavior_tree.cpp
)

# 定义宏函数 add_target_dependencies
function(add_target_dependencies target)
    target_include_directories(${target} PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
    ament_target_dependencies(${target} ${THIS_PACKAGE_INCLUDE_DEPENDS})
endfunction()

add_library(WaitUntilSubscribe_plugin SHARED 
    bt_node_self/wait_until_subscribe.cpp
)

target_compile_definitions(WaitUntilSubscribe_plugin PRIVATE BT_PLUGIN_EXPORT)

add_target_dependencies(WaitUntilSubscribe_plugin)

ament_auto_package ()