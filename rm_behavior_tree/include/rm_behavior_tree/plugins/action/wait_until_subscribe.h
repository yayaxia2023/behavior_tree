#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__WAIT_UNTIL_SUBSCRIBE_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__WAIT_UNTIL_SUBSCRIBE_HPP_

#include <iostream>

#include "behaviortree_cpp/behavior_tree.h"
#include "rclcpp/rclcpp.hpp"
#include "rm_decision_interfaces/msg/all_robot_hp.hpp"
#include "rm_decision_interfaces/msg/friend_location.hpp"
#include "rm_decision_interfaces/msg/rfid.hpp"
#include "rm_decision_interfaces/msg/robot_status.hpp"
namespace rm_behavior_tree
{
using BT::NodeStatus;

class WaitUntilSubscribeAction : public BT::SyncActionNode
{
public:
  WaitUntilSubscribeAction(const std::string & name, const BT::NodeConfig & config);

  BT::NodeStatus tick() override;

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<rm_decision_interfaces::msg::RFID>("rfid"),
      BT::InputPort<rm_decision_interfaces::msg::RobotStatus>("robot_status"),
      BT::InputPort<rm_decision_interfaces::msg::FriendLocation>("friend_location"),
      BT::InputPort<rm_decision_interfaces::msg::AllRobotHP>("robot_hp"),
    };
  }
};

}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__WAIT_UNTIL_SUBSCRIBE_HPP_