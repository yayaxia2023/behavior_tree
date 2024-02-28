#include "rm_behavior_tree/plugins/action/send_goal.hpp"

#include <iostream>

namespace rm_behavior_tree
{

SendGoalAction::SendGoalAction(
  const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params)
: RosTopicPubNode<geometry_msgs::msg::PoseStamped>(name, conf, params)
{
}

bool SendGoalAction::setMessage(geometry_msgs::msg::PoseStamped & msg)
{
  auto res = getInput<geometry_msgs::msg::PoseStamped>("goal_pose");
  if (!res) {
    throw BT::RuntimeError("error reading port [goal_pose]:", res.error());
  }
  geometry_msgs::msg::PoseStamped goal = res.value();

  msg.header.stamp = rclcpp::Clock().now();
  msg.header.frame_id = "map";
  msg.pose.position.x = goal.pose.position.x;
  msg.pose.position.y = goal.pose.position.y;
  msg.pose.position.z = goal.pose.position.z;
  msg.pose.orientation.x = goal.pose.orientation.x;
  msg.pose.orientation.y = goal.pose.orientation.y;
  msg.pose.orientation.z = goal.pose.orientation.z;
  msg.pose.orientation.w = goal.pose.orientation.w;

  // clang-format off
  std::cout << "Goal_pose: [ "
    << std::fixed << std::setprecision(1)
    << goal.pose.position.x << ", "
    << goal.pose.position.y << ", "
    << goal.pose.position.z << ", "
    << goal.pose.orientation.x << ", "
    << goal.pose.orientation.y << ", "
    << goal.pose.orientation.z << ", "
    << goal.pose.orientation.w << " ]\n";
  // clang-format on

  return true;
}

}  // namespace rm_behavior_tree

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(rm_behavior_tree::SendGoalAction, "SendGoal");