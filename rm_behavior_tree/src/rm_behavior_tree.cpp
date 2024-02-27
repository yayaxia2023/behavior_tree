#include "rm_behavior_tree/rm_behavior_tree.h"

#include <iostream>
#include <memory>
#include <string>

#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/json_export.h"
#include "behaviortree_cpp/loggers/groot2_publisher.h"
#include "behaviortree_cpp/utils/shared_library.h"
#include "behaviortree_ros2/plugins.hpp"
// #include "rm_behavior_tree/plugins/action/judge.h"
// #include "rm_behavior_tree/plugins/action/print_from_blackboard.h"
#include "rm_behavior_tree/plugins/action/send_goal.h"
// #include "rm_behavior_tree/plugins/action/update_msg.h"

int main(int argc, char ** argv)
{
  std::cout << "Start RM_Behavior_Tree" << '\n';

  rclcpp::init(argc, argv);
  BT::BehaviorTreeFactory factory;

  BT::RosNodeParams params_update_msg;
  params_update_msg.nh = std::make_shared<rclcpp::Node>("update_msg");

  const std::vector<std::string> ros_plugin_libs = {
    "sub_all_robot_hp",
    "sub_robot_status",
    "sub_game_status",
  };

  for (const auto & p : ros_plugin_libs) {
    RegisterRosNode(factory, BT::SharedLibrary::getOSName(p), params_update_msg);
  }

  // for (const auto & p : plugin_libs) {
  //   factory.registerFromPlugin(BT::SharedLibrary::getOSName(p));
  // }

  // RegisterRosNode(factory, "libsub_all_robot_hp.so", BT::RosNodeParams());

  // BT::RosNodeParams params_send_goal;
  // params_send_goal.nh = std::make_shared<rclcpp::Node>("SendGoal");
  // params_send_goal.default_port_value = "goal_pose";
  // factory.registerNodeType<rm_behavior_tree::SendGoalAction>("SendGoal", params_send_goal);

  // BT::RosNodeParams params_update_msg;
  // params_update_msg.nh = std::make_shared<rclcpp::Node>("UpdateMsg");
  // factory.registerNodeType<rm_behavior_tree::SubAllRobotHPAction>(
  //   "SubAllRobotHP", params_update_msg);
  // factory.registerNodeType<rm_behavior_tree::SubRobotStatusAction>(
  //   "SubRobotStatus", params_update_msg);
  // factory.registerNodeType<rm_behavior_tree::SubGameStatusAction>(
  //   "SubGameStatus", params_update_msg);

  // factory.registerNodeType<rm_behavior_tree::PrintFromBlackboard>("PrintFromBlackboard");
  // factory.registerNodeType<rm_behavior_tree::IsGameStartAction>("IsGameStart");
  // factory.registerNodeType<rm_behavior_tree::IsStatusOKAction>("IsStatusOK");
  // factory.registerNodeType<rm_behavior_tree::IsAttakedAction>("IsAttaked");
  // factory.registerNodeType<rm_behavior_tree::IsFriendOKAction>("IsFriendOK");

  // Allow Groot2 to visualize custom type
  BT::RegisterJsonDefinition<PoseStamped>(PoseStampedToJson);

  const std::string tree_path = "./rm_decision_ws/rm_behavior_tree/rm_behavior_tree.xml";
  auto tree = factory.createTreeFromFile(tree_path);

  // Connect the Groot2Publisher. This will allow Groot2 to get the tree and poll status updates.
  const unsigned port = 1667;
  BT::Groot2Publisher publisher(tree, port);

  while (rclcpp::ok()) {
    tree.tickWhileRunning();
  }

  rclcpp::shutdown();
  return 0;
}