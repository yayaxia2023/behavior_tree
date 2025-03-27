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
find_package(roborts_msgs REQUIRED)
ament_auto_find_build_dependencies()

###########
## Build ##
###########

set(PACKAGE_INCLUDE_DEPENDS
    rm_decision_interfaces
    rclcpp
    std_msgs
    nav2_msgs
    behaviortree_cpp
    behaviortree_ros2
    roborts_msgs
    rm_interfaces
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
# Controllers
ament_auto_add_library(decision_switch SHARED
    plugins/control/decision_switch.cpp
)
add_target_dependencies(decision_switch)

# Decorators
ament_auto_add_library(rate_controller SHARED 
    plugins/decorator/rate_controller.cpp
)
add_target_dependencies(rate_controller)

# Conditions
ament_auto_add_library(is_game_time SHARED 
    plugins/condition/is_game_time.cpp
)
add_target_dependencies(is_game_time)

ament_auto_add_library(is_status_ok SHARED 
    plugins/condition/is_status_ok.cpp
)
add_target_dependencies(is_status_ok)

ament_auto_add_library(is_attacked SHARED 
    plugins/condition/is_attacked.cpp
)
add_target_dependencies(is_attacked)

ament_auto_add_library(is_friend_ok SHARED 
    plugins/condition/is_friend_ok.cpp
)
add_target_dependencies(is_friend_ok)

ament_auto_add_library(is_outpost_ok SHARED 
    plugins/condition/is_outpost_ok.cpp
)
add_target_dependencies(is_outpost_ok)

ament_auto_add_library(is_detect_enemy SHARED 
    plugins/condition/is_detect_enemy.cpp
)
add_target_dependencies(is_detect_enemy)

ament_auto_add_library(is_target SHARED 
    plugins/condition/is_target.cpp
)
add_target_dependencies(is_target)

# Actions
ament_auto_add_library(send_goal SHARED 
    plugins/action/send_goal.cpp
)
add_target_dependencies(send_goal)

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

ament_auto_add_library(sub_armors SHARED 
    plugins/action/sub_armors.cpp
)
add_target_dependencies(sub_armors)

ament_auto_add_library(sub_decision_num SHARED
    plugins/action/sub_decision_num.cpp
)
add_target_dependencies(sub_decision_num)

ament_auto_add_library(get_current_location SHARED 
    plugins/action/get_current_location.cpp
)
add_target_dependencies(get_current_location)

ament_auto_add_library(move_around SHARED 
    plugins/action/move_around.cpp
)
add_target_dependencies(move_around)

ament_auto_add_library(robot_control SHARED 
    plugins/action/robot_control.cpp
)
add_target_dependencies(robot_control)

ament_auto_add_library(sub_robot_heat SHARED 
    plugins/action/sub_robot_heat.cpp
)
add_target_dependencies(sub_robot_heat)

ament_auto_add_library(sub_target SHARED 
    plugins/action/sub_target.cpp
)

add_target_dependencies(sub_target)

ament_auto_add_library(sub_robot_hurt SHARED 
    plugins/action/sub_robot_hurt.cpp
)

add_target_dependencies(sub_robot_hurt)

ament_auto_add_library(set_area SHARED 
    plugins/action/set_area.cpp
)

add_target_dependencies(set_area)

ament_auto_add_library(is_area SHARED 
    plugins/condition/is_area.cpp
)

add_target_dependencies(is_area)

ament_auto_add_library(print_message SHARED 
    plugins/action/print_message.cpp
)

add_target_dependencies(print_message)

ament_auto_package(
  INSTALL_TO_SHARE
  launch
  config
)