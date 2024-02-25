#!/bin/zsh

source install/setup.zsh

ros2 topic pub -r 10 /robot_status rm_decision_interfaces/msg/RobotStatus "{
    robot_id: 7,
    current_hp: 200,
    shooter_heat: 19,
    hp_deduction_reason: 0,
}" &

ros2 topic pub -r 1 /game_status rm_decision_interfaces/msg/GameStatus "{
    game_progress: 4,
    stage_remain_time: 5,
}" &

ros2 topic pub -r 3 /robot_hp rm_decision_interfaces/msg/AllRobotHP "{
    red_1_robot_hp: 200,
    red_2_robot_hp: 90,
    red_3_robot_hp: 100,
    red_4_robot_hp: 40,
    red_5_robot_hp: 200,
    red_7_robot_hp: 200,
    red_outpost_hp: 0,
    red_base_hp: 30,
    blue_1_robot_hp: 95,
    blue_2_robot_hp: 85,
    blue_3_robot_hp: 75,
    blue_4_robot_hp: 200,
    blue_5_robot_hp: 55,
    blue_7_robot_hp: 45,
    blue_outpost_hp: 35,
    blue_base_hp: 25
}" &

wait
