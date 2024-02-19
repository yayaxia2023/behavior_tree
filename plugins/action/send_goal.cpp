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