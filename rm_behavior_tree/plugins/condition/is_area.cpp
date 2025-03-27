#include "rm_behavior_tree/plugins/condition/is_area.hpp"

namespace rm_behavior_tree
{

  IsAreaAction::IsAreaAction(const std::string & name, const BT::NodeConfig & config)
: BT::SimpleConditionNode(name, std::bind(&IsAreaAction::checkArea, this), config)
{
}

BT::NodeStatus IsAreaAction::checkArea()
{
  auto current_area = getInput<std::string>("current_area");
  auto set_area = getInput<std::string>("set_area");
  if (!current_area) {
    // std::cout << "missing required input [game_status]" << '\n';
    return BT::NodeStatus::FAILURE;
  }

  if (current_area == set_area) {
    // 机器人受到攻击
    return BT::NodeStatus::SUCCESS;
  }

  return BT::NodeStatus::FAILURE;
}

}  // namespace rm_behavior_tree

#include "behaviortree_cpp/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<rm_behavior_tree::IsAreaAction>("IsArea");
}