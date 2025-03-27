#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__IS_AREA_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__IS_AREA_HPP_

#include "behaviortree_cpp/condition_node.h"

namespace rm_behavior_tree
{

class IsAreaAction : public BT::SimpleConditionNode
{
public:
IsAreaAction(const std::string & name, const BT::NodeConfig & config);

  BT::NodeStatus checkArea();

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("current_area"),
      BT::InputPort<std::string>("set_area"),
    };
  }
};
}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__IS_AREA_HPP_