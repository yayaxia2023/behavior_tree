cmake_minimum_required(VERSION 3.10)
project(rm_behavior_tree)

## Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Export compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#######################
## Find dependencies ##
#######################

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

###########
## Build ##
###########

set(PACKAGE_INCLUDE_DEPENDS
    rm_decision_interfaces
    rclcpp
    std_msgs
    behaviortree_cpp
    behaviortree_ros2
)

# 定义宏函数 add_target_dependencies
function(add_target_dependencies target)
    target_include_directories(${target} PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
    ament_target_dependencies(${target} ${PACKAGE_INCLUDE_DEPENDS})
    target_compile_definitions(${target} PRIVATE BT_PLUGIN_EXPORT)
endfunction()

ament_auto_add_executable(rm_behavior_tree 
    src/rm_behavior_tree.cpp
)

ament_auto_add_library(sub_all_robot_hp SHARED 
    plugins/action/sub_all_robot_hp.cpp
)
add_target_dependencies(sub_all_robot_hp)

ament_auto_add_library(sub_robot_status SHARED 
    plugins/action/sub_robot_status.cpp
)
add_target_dependencies(sub_robot_status)

ament_auto_add_library(sub_game_status SHARED 
    plugins/action/sub_game_status.cpp
)
add_target_dependencies(sub_game_status)

# add_library(UpdateMsg_plugin SHARED 
#     plugins/action/update_msg.cpp
# )
# add_library(PrintFromBlackboard_plugin SHARED 
#     plugins/action/print_from_blackboard.cpp
# )


# add_target_dependencies(UpdateMsg_plugin)
# add_target_dependencies(PrintFromBlackboard_plugin)

ament_auto_package()