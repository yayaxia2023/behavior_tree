#include "rm_behavior_tree/rm_behavior_tree.h"

#include "rm_behavior_tree/mynode.h"
#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/loggers/groot2_publisher.h"
// file that contains the custom nodes definitions

int main(int argc, char ** argv)
{
  BT::BehaviorTreeFactory factory;

  rclcpp::init(argc, argv);

  auto node2 = std::make_shared<RmBt>();

  factory.registerFromPlugin("./build/rm_behavior_tree/libmynode_plugin.so");

  factory.registerNodeType<ROS2DecoratorNode>("ROS2DecoratorNode");

  auto tree = factory.createTreeFromFile("./src/rm_behavior_tree/bt_tree.xml");

  BT::Groot2Publisher publisher(tree);

  while (rclcpp::ok()) {
    tree.tickWhileRunning();
    rclcpp::spin_some(node2);
  }

  rclcpp::shutdown();
  return 0;
}