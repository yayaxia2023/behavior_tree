#include "rm_behavior_tree/plugins/action/send_goal.h"

namespace rm_behavior_tree
{

bool SendGoalAction::setMessage(geometry_msgs::msg::Twist & msg)
{
  float linear_x, linear_y, linear_z, angular_x, angular_y, angular_z;

  getInput("linear_x", linear_x);
  getInput("linear_y", linear_y);
  getInput("linear_z", linear_z);
  getInput("angular_x", angular_x);
  getInput("angular_y", angular_y);
  getInput("angular_z", angular_z);

  msg.linear.x = linear_x;
  msg.linear.y = linear_y;
  msg.linear.z = linear_z;
  msg.angular.x = angular_x;
  msg.angular.y = angular_y;
  msg.angular.z = angular_z;

  std::cout << "linear_x: " << linear_x << std::endl;
  std::cout << "angular_y: " << angular_y << std::endl;

  return true;
}

}  // namespace rm_behavior_tree

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(rm_behavior_tree::SendGoalAction, "SendGoal");

// Simple tree, used to execute once each action.
static const char * XML_TEXT = R"(
  <root BTCPP_format="4">
    <BehaviorTree>
      <Sequence>
        <SendGoal linear_x="0"
                linear_y="1"
                linear_z="2"
                angular_x="3"
                angular_y="10"
                angular_z="5"/>
      </Sequence>
    </BehaviorTree>
  </root>
 )";

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto nh = std::make_shared<rclcpp::Node>("subscriber_test");

  BT::BehaviorTreeFactory factory;

  BT::RosNodeParams params;
  params.nh = nh;
  params.default_port_value = "btcpp_string";
  factory.registerNodeType<rm_behavior_tree::SendGoalAction>("SendGoal", params);

  auto tree = factory.createTreeFromText(XML_TEXT);

  while (rclcpp::ok()) {
    tree.tickWhileRunning();
  }

  return 0;
}