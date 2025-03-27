#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__SET_AREA_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__SET_AREA_HPP_

#include "behaviortree_cpp/behavior_tree.h"
#include "behaviortree_cpp/bt_factory.h"


namespace rm_behavior_tree
{
class SetAreaAction : public BT::SyncActionNode
{
public:
  SetAreaAction(
    const std::string & name, const BT::NodeConfig & conf);

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("set_area"),
      BT::OutputPort<std::string>("area")};
  }

  BT::NodeStatus tick() override;
};
}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__SET_AREA_HPP_