#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__IS_OUTPOST_OK_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__IS_OUTPOST_OK_HPP_

#include "behaviortree_cpp/condition_node.h"
#include "roborts_msgs/msg/robot_status.hpp"
#include "roborts_msgs/msg/game_robot_hp.hpp"

namespace rm_behavior_tree
{

enum TeamColor {
  RED = 0,
  BLUE = 1
};

class IsOutpostOKAction : public BT::SimpleConditionNode
{
public:
  IsOutpostOKAction(const std::string & name, const BT::NodeConfig & config);

  // BT::NodeStatus checkGameStart(BT::TreeNode & self_node)
  BT::NodeStatus checkRobotStatus();

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<roborts_msgs::msg::GameRobotHP>("all_robot_hp"),
      BT::InputPort<roborts_msgs::msg::RobotStatus>("robot_status"),
      BT::InputPort<int>("hp_threshold")};
  }
};
}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__IS_OUTPOST_OK_HPP_