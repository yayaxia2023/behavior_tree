#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__IS_DETECT_ENEMY_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__IS_DETECT_ENEMY_HPP_

#include <auto_aim_interfaces/msg/detail/armors__struct.hpp>
#include "behaviortree_cpp/condition_node.h"
#include "auto_aim_interfaces/msg/armors.hpp"

namespace rm_behavior_tree
{

/**
 * @brief condition节点，用于判断视野内是否存在有效敌人
 * @param[in] message 识别模块的检测结果序列
 */
class IsDetectEnemyAction : public BT::SimpleConditionNode
{
public:
  IsDetectEnemyAction(const std::string & name, const BT::NodeConfig & config);

  // BT::NodeStatus checkGameStart(BT::TreeNode & self_node)
  BT::NodeStatus detectEnemyStatus();

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<auto_aim_interfaces::msg::Armors>("message")};
  }
};
}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__IS_FRIEND_OK_HPP_