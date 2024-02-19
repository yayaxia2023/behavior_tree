#include "rm_behavior_tree/rm_behavior_tree.h"

#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/loggers/groot2_publisher.h"
#include "behaviortree_ros2/plugins.hpp"
#include "rm_behavior_tree/plugins/action/send_goal.h"
#include "rm_behavior_tree/plugins/action/wait_until_subscribe.h"

int main(int argc, char ** argv)
{
  BT::BehaviorTreeFactory factory;

  rclcpp::init(argc, argv);

  auto node2 = std::make_shared<RmBt>();

  BT::RosNodeParams params;

  RegisterRosNode(factory, "./build/rm_behavior_tree/libSendGoal_plugin.so", params);
  factory.registerFromPlugin("./build/rm_behavior_tree/libWaitUntilSubscribe_plugin.so");

  factory.registerNodeType<ROS2DecoratorNode>("ROS2DecoratorNode");

  auto tree = factory.createTreeFromFile("./src/rm_decision/rm_behavior_tree/bt_tree.xml");

  BT::Groot2Publisher publisher(tree);

  while (rclcpp::ok()) {
    tree.tickWhileRunning();
    rclcpp::spin_some(node2);
  }

  rclcpp::shutdown();
  return 0;
}