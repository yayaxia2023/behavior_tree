#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__UPDATE_MSG_H_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__UPDATE_MSG_H_

#include <iostream>
#include <rm_decision_interfaces/msg/detail/game_status__struct.hpp>
#include <rm_decision_interfaces/msg/detail/robot_status__struct.hpp>

#include "behaviortree_cpp/behavior_tree.h"
#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_ros2/bt_topic_sub_node.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rm_decision_interfaces/msg/all_robot_hp.hpp"
#include "rm_decision_interfaces/msg/game_status.hpp"
#include "rm_decision_interfaces/msg/robot_status.hpp"

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
    const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params)
  : RosTopicSubNode<rm_decision_interfaces::msg::AllRobotHP>(name, conf, params)
  {
  }

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("topic_name"),
      BT::OutputPort<rm_decision_interfaces::msg::AllRobotHP>("robot_hp")};
  }

  BT::NodeStatus onTick(
    const std::shared_ptr<rm_decision_interfaces::msg::AllRobotHP> & last_msg) override
  {
    if (last_msg)  // empty if no new message received, since the last tick
    {
      RCLCPP_INFO(
        logger(), "[%s] new message, red_1_robot_hp: %s", name().c_str(),
        std::to_string(last_msg->red_1_robot_hp).c_str());
      setOutput("robot_hp", *last_msg);
    }
    return BT::NodeStatus::SUCCESS;
  }
};

class SubRobotStatusAction : public BT::RosTopicSubNode<rm_decision_interfaces::msg::RobotStatus>
{
public:
  SubRobotStatusAction(
    const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params)
  : RosTopicSubNode<rm_decision_interfaces::msg::RobotStatus>(name, conf, params)
  {
  }

  BT::NodeStatus onTick(
    const std::shared_ptr<rm_decision_interfaces::msg::RobotStatus> & last_msg) override
  {
    if (last_msg)  // empty if no new message received, since the last tick
    {
      RCLCPP_INFO(
        logger(), "[%s] new message, shooter_heat: %s", name().c_str(),
        std::to_string(last_msg->shooter_heat).c_str());
      setOutput("robot_status", *last_msg);
    }
    return BT::NodeStatus::SUCCESS;
  }

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("topic_name"),
      BT::OutputPort<rm_decision_interfaces::msg::RobotStatus>("robot_status")};
  }
};

class SubGameStatusAction : public BT::RosTopicSubNode<rm_decision_interfaces::msg::GameStatus>
{
public:
  SubGameStatusAction(
    const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params)
  : RosTopicSubNode<rm_decision_interfaces::msg::GameStatus>(name, conf, params)
  {
  }

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("topic_name"),
      BT::OutputPort<rm_decision_interfaces::msg::GameStatus>("game_status")};
  }

  BT::NodeStatus onTick(
    const std::shared_ptr<rm_decision_interfaces::msg::GameStatus> & last_msg) override
  {
    if (last_msg)  // empty if no new message received, since the last tick
    {
      RCLCPP_INFO(
        logger(), "[%s] new message, game_progress: %s", name().c_str(),
        std::to_string(last_msg->game_progress).c_str());
      setOutput("game_status", *last_msg);
    }
    return BT::NodeStatus::SUCCESS;
  }
};

}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__UPDATE_MSG_H_