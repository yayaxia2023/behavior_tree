#include "rm_behavior_tree/plugins/condition/is_attacked.hpp"

namespace rm_behavior_tree
{

IsAttakedAction::IsAttakedAction(const std::string & name, const BT::NodeConfig & config)
: BT::SimpleConditionNode(name, std::bind(&IsAttakedAction::checkRobotAttacked, this), config)
{
}

BT::NodeStatus IsAttakedAction::checkRobotAttacked()
{
  auto msg = getInput<rm_decision_interfaces::msg::RobotStatus>("message");

  if (!msg) {
    std::cout << "missing required input [game_status]" << '\n';
    return BT::NodeStatus::FAILURE;
  }

  std::map<int, std::string> hp_deduction_reason_map = {
    {0, "装甲模块被弹丸攻击导致扣血"}, {1, "裁判系统重要模块离线导致扣血"},
    {2, "射击初速度超限导致扣血"},     {3, "枪口热量超限导致扣血"},
    {4, "底盘功率超限导致扣血"},       {5, "装甲模块受到撞击导致扣血"},
  };

  int hp_deduction_reason = msg->hp_deduction_reason;
  if (hp_deduction_reason_map.find(hp_deduction_reason) != hp_deduction_reason_map.end()) {
    std::cout << hp_deduction_reason_map[hp_deduction_reason] << '\n';
  } else {
    std::cout << "未知扣血原因" << '\n';
  }

  if (hp_deduction_reason == 0 || hp_deduction_reason == 5) {
    // 弹丸攻击导致扣血 or 装甲模块受到撞击导致扣血
    return BT::NodeStatus::SUCCESS;
  }

  return BT::NodeStatus::FAILURE;
}

}  // namespace rm_behavior_tree

#include "behaviortree_cpp/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<rm_behavior_tree::IsAttakedAction>("IsAttaked");
}
