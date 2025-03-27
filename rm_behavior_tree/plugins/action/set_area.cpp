#include "rm_behavior_tree/plugins/action/set_area.hpp"

namespace rm_behavior_tree
{

  SetAreaAction::SetAreaAction(
  const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
}

BT::NodeStatus SetAreaAction::tick()
{

  auto msg = getInput<std::string>("set_area");
  setOutput("area", *msg);
  
  return BT::NodeStatus::SUCCESS;
}
}  // namespace rm_behavior_tree

#include "behaviortree_cpp/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<rm_behavior_tree::SetAreaAction>("SetArea");
}