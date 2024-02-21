#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__PRINT_FROM_BLACKBOARD_H_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__PRINT_FROM_BLACKBOARD_H_

#include <iostream>

#include "behaviortree_cpp/bt_factory.h"
#include "rm_decision_interfaces/msg/all_robot_hp.hpp"

using namespace BT;

namespace rm_behavior_tree
{

class PrintFromBlackboard : public BT::SyncActionNode
{
public:
  PrintFromBlackboard(const std::string & name, const BT::NodeConfig & config)
  : BT::SyncActionNode(name, config)
  {
  }

  NodeStatus tick() override
  {
    Expected<rm_decision_interfaces::msg::AllRobotHP> msg =
      getInput<rm_decision_interfaces::msg::AllRobotHP>("message");
    if (!msg) {
      throw BT::RuntimeError("missing required input [message]: ", msg.error());
    }
    std::cout << "Robot says: " << msg->red_1_robot_hp << std::endl;
    return BT::NodeStatus::SUCCESS;
  }

  static PortsList providedPorts()
  {
    return {InputPort<rm_decision_interfaces::msg::AllRobotHP>("message")};
  }
};
}  // namespace rm_behavior_tree

#endif