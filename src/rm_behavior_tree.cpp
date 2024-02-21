#include "rm_behavior_tree/rm_behavior_tree.h"

#include <iostream>
#include <memory>
#include <string>

#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/json_export.h"
#include "behaviortree_cpp/loggers/groot2_publisher.h"
#include "behaviortree_ros2/plugins.hpp"
#include "rm_behavior_tree/plugins/action/print_from_blackboard.h"
#include "rm_behavior_tree/plugins/action/send_goal.h"
#include "rm_behavior_tree/plugins/action/update_msg.h"

int main(int argc, char ** argv)
{
  std::cout << "Start RM_Behavior_Tree" << std::endl;

  rclcpp::init(argc, argv);
  BT::BehaviorTreeFactory factory;

  BT::RosNodeParams params_send_goal;
  params_send_goal.nh = std::make_shared<rclcpp::Node>("SendGoal");
  params_send_goal.default_port_value = "goal_pose";
  factory.registerNodeType<rm_behavior_tree::SendGoalAction>("SendGoal", params_send_goal);

  BT::RosNodeParams params_update_msg;
  params_update_msg.nh = std::make_shared<rclcpp::Node>("UpdateMsg");
  factory.registerNodeType<rm_behavior_tree::SubAllRobotHPAction>(
    "SubAllRobotHP", params_update_msg);
  factory.registerNodeType<rm_behavior_tree::SubRobotStatusAction>(
    "SubRobotStatus", params_update_msg);

  factory.registerNodeType<rm_behavior_tree::PrintFromBlackboard>("PrintFromBlackboard");

  // Allow Groot2 to visualize custom type
  BT::RegisterJsonDefinition<PoseStamped>(PoseStampedToJson);

  const std::string tree_path = "./src/rm_decision/rm_behavior_tree/rm_behavior_tree.xml";
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