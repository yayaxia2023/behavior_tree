#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__UPDATE_MSG_H_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__UPDATE_MSG_H_

#include <iostream>

#include "behaviortree_cpp/behavior_tree.h"
#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_ros2/bt_topic_sub_node.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rm_decision_interfaces/msg/all_robot_hp.hpp"

struct AllRobotHp
{
  int red_1_robot_hp;
  int red_2_robot_hp;
  int red_3_robot_hp;
  int red_4_robot_hp;
  int red_5_robot_hp;
  int red_7_robot_hp;
  int red_outpost_hp;
  int red_base_hp;
  int blue_1_robot_hp;
  int blue_2_robot_hp;
  int blue_3_robot_hp;
  int blue_4_robot_hp;
  int blue_5_robot_hp;
  int blue_7_robot_hp;
  int blue_outpost_hp;
  int blue_base_hp;
};

namespace rm_behavior_tree
{

class SubAllRobotHPAction : public BT::RosTopicSubNode<rm_decision_interfaces::msg::AllRobotHP>
{
public:
  SubAllRobotHPAction(
    const std::string & instance_name, const BT::NodeConfig & conf,
    const BT::RosNodeParams & params)
  : RosTopicSubNode<rm_decision_interfaces::msg::AllRobotHP>(instance_name, conf, params)
  {
  }

  BT::NodeStatus onTick(
    const std::shared_ptr<rm_decision_interfaces::msg::AllRobotHP> & last_msg) override;

  static BT::PortsList providedPorts()
  {
    const char * description = "All robot HP message received from the game controller.";
    return {BT::OutputPort<rm_decision_interfaces::msg::AllRobotHP>("robot_hp", description)};
  }
};

}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__UPDATE_MSG_H_