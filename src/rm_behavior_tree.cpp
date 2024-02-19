#include "rm_behavior_tree/rm_behavior_tree.h"

#include <iostream>
#include <memory>
#include <string>

#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/loggers/groot2_publisher.h"
#include "behaviortree_ros2/plugins.hpp"
#include "rm_behavior_tree/plugins/action/send_goal.h"

int main(int argc, char ** argv)
{
  std::cout << "Start RM_Behavior_Tree" << std::endl;

  rclcpp::init(argc, argv);

  std::unique_ptr<BT::BehaviorTreeFactory> factory = std::make_unique<BT::BehaviorTreeFactory>();

  BT::RosNodeParams params_send_goal;
  params_send_goal.nh = std::make_shared<rclcpp::Node>("SendGoal");
  params_send_goal.default_port_value = "goal_pose";

  RegisterRosNode(*factory, "./build/rm_behavior_tree/libSendGoal_plugin.so", params_send_goal);

  const std::string tree_path = "./src/rm_decision/rm_behavior_tree/rm_behavior_tree.xml";
  auto tree = factory->createTreeFromFile(tree_path);

  while (rclcpp::ok()) {
    tree.tickWhileRunning();
  }

  rclcpp::shutdown();
  return 0;
}