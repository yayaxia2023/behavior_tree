#include "rm_behavior_tree/plugins/action/send_goal.h"

#include <cstdio>

namespace rm_behavior_tree
{

bool SendGoalAction::setMessage(geometry_msgs::msg::PoseStamped & msg)
{
  auto res = getInput<PoseStamped>("goal_pose");
  if (!res) {
    throw BT::RuntimeError("error reading port [goal_pose]:", res.error());
  }
  PoseStamped goal = res.value();

  msg.header.stamp = rclcpp::Clock().now();
  msg.header.frame_id = "map";
  msg.pose.position.x = goal.position_x;
  msg.pose.position.y = goal.position_y;
  msg.pose.position.z = goal.position_z;
  msg.pose.orientation.x = goal.orientation_x;
  msg.pose.orientation.y = goal.orientation_y;
  msg.pose.orientation.z = goal.orientation_z;
  msg.pose.orientation.w = goal.orientation_w;

  printf(
    "Goal_pose: [ %.1f, %.1f, %.1f, %.1f, %.1f, %.1f, %.1f ]\n", goal.position_x, goal.position_x,
    goal.position_z, goal.orientation_x, goal.orientation_y, goal.orientation_z,
    goal.orientation_w);

  return true;
}

}  // namespace rm_behavior_tree

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(rm_behavior_tree::SendGoalAction, "SendGoal");