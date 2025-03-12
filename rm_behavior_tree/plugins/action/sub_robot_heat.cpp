#include "rm_behavior_tree/plugins/action/sub_robot_heat.hpp"

namespace rm_behavior_tree
{

SubRobotHeatAction::SubRobotHeatAction(
  const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params)
: BT::RosTopicSubNode<roborts_msgs::msg::RobotHeat>(name, conf, params)
{
}

BT::NodeStatus SubRobotHeatAction::onTick(
  const std::shared_ptr<roborts_msgs::msg::RobotHeat> & last_msg)
{
  if (last_msg)  // empty if no new message received, since the last tick
  {
    // RCLCPP_DEBUG(
    //   logger(), "[%s] new message, shooter_heat: %s", name().c_str(),
    //   std::to_string(last_msg->shooter_heat).c_str());
    setOutput("robot_heat", *last_msg);
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace rm_behavior_tree

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(rm_behavior_tree::SubRobotHeatAction, "SubRobotHeat");