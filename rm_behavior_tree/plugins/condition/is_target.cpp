#include "rm_behavior_tree/plugins/condition/is_target.hpp"

namespace rm_behavior_tree
{

IsTargetAction::IsTargetAction(const std::string & name, const BT::NodeConfig & config)
: BT::SimpleConditionNode(name, std::bind(&IsTargetAction::detectEnemyStatus, this), config)
{
}

BT::NodeStatus IsTargetAction::detectEnemyStatus()
{
  auto msg = getInput<rm_interfaces::msg::Target>("message");

  if (!msg) {
    std::cerr << "Missing required input [message]" << '\n';
    return BT::NodeStatus::FAILURE;
  }

  if (!msg->tracking) {
    // std::cout << "未检测到敌人" << '\n';
    return BT::NodeStatus::FAILURE;
  } else {
    // std::cout << "检测到敌人" << '\n';
    return BT::NodeStatus::SUCCESS;
  }
}

}  // namespace rm_behavior_tree

#include "behaviortree_cpp/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<rm_behavior_tree::IsTargetAction>("IsTarget");
}