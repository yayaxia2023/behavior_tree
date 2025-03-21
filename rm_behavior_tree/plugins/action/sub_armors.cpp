#include "rm_behavior_tree/plugins/action/sub_armors.hpp"

namespace rm_behavior_tree
{

SubArmorsAction::SubArmorsAction(
  const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params)
: BT::RosTopicSubNode<rm_interfaces::msg::Armors>(name, conf, params)
{
}

BT::NodeStatus SubArmorsAction::onTick(
  const std::shared_ptr<rm_interfaces::msg::Armors> & last_msg)
{
  if (last_msg) {
    // std::cerr << "Missing required [message]" << '\n';
    setOutput("armors", *last_msg);
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace rm_behavior_tree

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(rm_behavior_tree::SubArmorsAction, "SubArmors");