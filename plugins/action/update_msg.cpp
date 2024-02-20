#include "rm_behavior_tree/plugins/action/update_msg.h"

namespace rm_behavior_tree
{

BT::NodeStatus SubAllRobotHPAction::onTick(
  const std::shared_ptr<rm_decision_interfaces::msg::AllRobotHP> & last_msg)
{
  if (last_msg)  // empty if no new message received, since the last tick
  {
    RCLCPP_INFO(
      logger(), "[%s] new message: %s", name().c_str(),
      std::to_string(last_msg->red_1_robot_hp).c_str());
    setOutput("robot_hp", *last_msg);
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace rm_behavior_tree

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(rm_behavior_tree::SubAllRobotHPAction, "SubAllRobotHP");