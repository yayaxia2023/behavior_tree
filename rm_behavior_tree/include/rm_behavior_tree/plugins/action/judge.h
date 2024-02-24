#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__JUDGE_H_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__JUDGE_H_

#include <behaviortree_cpp/basic_types.h>

#include "behaviortree_cpp/bt_factory.h"
#include "rm_decision_interfaces/msg/game_status.hpp"
#include "rm_decision_interfaces/msg/robot_status.hpp"

using namespace BT;

namespace rm_behavior_tree
{

/**
 * @brief 用于判断游戏是否开始
 * @param message 比赛状态话题id
 */
class IsGameStartAction : public BT::SyncActionNode
{
public:
  /**
   * @brief 构造函数
   * @param name 节点名称
   * @param config 节点配置
   */
  IsGameStartAction(const std::string & name, const BT::NodeConfig & config)
  : BT::SyncActionNode(name, config)
  {
  }

  /**
   * @brief 执行节点逻辑
   * @return 节点状态
   */
  NodeStatus tick() override
  {
    auto msg = getInput<rm_decision_interfaces::msg::GameStatus>("message");
    if (!msg) {
      // throw BT::RuntimeError("missing required input [game_status]: ", msg.error());
      return BT::NodeStatus::FAILURE;
      std::cout << "missing required input [game_status]" << '\n';
    }

    std::unordered_map<int, std::string> game_status_map = {
      {0, "未开始比赛"}, {1, "准备阶段"},    {2, "十五秒裁判系统自检阶段"},
      {3, "五秒倒计时"}, {4, "比赛开始!!!"}, {5, "比赛结算中"},
    };

    if (game_status_map.find(msg->game_progress) != game_status_map.end()) {
      std::cout << game_status_map[msg->game_progress] << '\n';
      return (msg->game_progress == 4) ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
    } else {
      std::cout << "未知状态" << '\n';
      return BT::NodeStatus::FAILURE;
    }
  }

  static PortsList providedPorts()
  {
    return {InputPort<rm_decision_interfaces::msg::GameStatus>("message")};
  }
};

/**
 * @brief Action节点，用于判断机器人状态是否正常
 * 
 * 该节点从输入端口获取机器人状态消息、血量阈值和热量阈值，并根据条件判断机器人状态是否正常。
 * 如果机器人状态不正常（血量低于阈值或热量高于阈值），返回失败；否则返回成功。
 * @param message 机器人状态话题id
 * @param hp_threshold 最低血量阈值（哨兵最大血量600）
 * @param heat_threshold 最大热量阈值（哨兵最高热量400）
 */
class IsStatusOKAction : public BT::SyncActionNode
{
public:
  IsStatusOKAction(const std::string & name, const BT::NodeConfig & config)
  : BT::SyncActionNode(name, config)
  {
  }

  NodeStatus tick() override
  {
    int hp_threshold, heat_threshold;
    auto msg = getInput<rm_decision_interfaces::msg::RobotStatus>("message");
    getInput("hp_threshold", hp_threshold);
    getInput("heat_threshold", heat_threshold);

    if (!msg) {
      // throw BT::RuntimeError("missing required input [game_status]: ", msg.error());
      return BT::NodeStatus::FAILURE;
      std::cout << "missing required input [game_status]" << '\n';
    }

    if (msg->current_hp < hp_threshold || msg->shooter_heat > heat_threshold) {
      std::cout << "血量/热量达到预警值" << '\n';
      return BT::NodeStatus::FAILURE;
    } else {
      std::cout << "血量/热量正常" << '\n';
      return BT::NodeStatus::SUCCESS;
    }
  }

  static PortsList providedPorts()
  {
    return {
      InputPort<rm_decision_interfaces::msg::RobotStatus>("message"),
      InputPort<int>("hp_threshold"), InputPort<int>("heat_threshold")};
  }
};

}  // namespace rm_behavior_tree

#endif