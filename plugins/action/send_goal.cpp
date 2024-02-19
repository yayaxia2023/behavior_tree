#include "rm_behavior_tree/plugins/action/send_goal.h"

namespace rm_behavior_tree
{

bool SendGoalAction::setMessage(geometry_msgs::msg::PoseStamped & msg)
{
  float position_x, position_y, position_z;
  float orientation_x, orientation_y, orientation_z, orientation_w;

  getInput("position_x", position_x);
  getInput("position_y", position_y);
  getInput("position_z", position_z);
  getInput("orientation_x", orientation_x);
  getInput("orientation_y", orientation_y);
  getInput("orientation_z", orientation_z);
  getInput("orientation_w", orientation_w);

  msg.pose.position.x = position_x;
  msg.pose.position.y = position_y;
  msg.pose.position.z = position_z;
  msg.pose.orientation.x = orientation_x;
  msg.pose.orientation.y = orientation_y;
  msg.pose.orientation.z = orientation_z;
  msg.pose.orientation.w = orientation_w;
  msg.header.stamp = rclcpp::Clock().now();
  msg.header.frame_id = "map";

  std::cout << "position_x: " << position_x << std::endl;
  std::cout << "orientation_w: " << orientation_w << std::endl;

  return true;
}

}  // namespace rm_behavior_tree

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(rm_behavior_tree::SendGoalAction, "SendGoal");