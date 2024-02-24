#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__JUDGE_H_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__JUDGE_H_

#include "behaviortree_cpp/bt_factory.h"
#include "rm_decision_interfaces/msg/game_status.hpp"

using namespace BT;

namespace rm_behavior_tree
{

class IsGameStartAction : public BT::SyncActionNode
{
public:
  IsGameStartAction(const std::string & name, const BT::NodeConfig & config)
  : BT::SyncActionNode(name, config)
  {
  }

  NodeStatus tick() override
  {
    auto msg = getInput<rm_decision_interfaces::msg::GameStatus>("message");
    if (!msg) {
      // throw BT::RuntimeError("missing required input [game_status]: ", msg.error());
      return BT::NodeStatus::FAILURE;
      std::cout << "missing required input [game_status]" << std::endl;
    }

    std::unordered_map<int, std::string> game_status_map = {
      {0, "未开始比赛"}, {1, "准备阶段"},    {2, "十五秒裁判系统自检阶段"},
      {3, "五秒倒计时"}, {4, "比赛开始!!!"}, {5, "比赛结算中"},
    };

    if (game_status_map.find(msg->game_progress) != game_status_map.end()) {
      std::cout << game_status_map[msg->game_progress] << std::endl;
      return (msg->game_progress == 4) ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
    } else {
      std::cout << "未知状态" << std::endl;
      return BT::NodeStatus::FAILURE;
    }
  }

  static PortsList providedPorts()
  {
    return {InputPort<rm_decision_interfaces::msg::GameStatus>("message")};
  }
};

}  // namespace rm_behavior_tree

#endif