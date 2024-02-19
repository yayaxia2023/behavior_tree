#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_GOAL_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_GOAL_HPP_

#include <iostream>

#include "behaviortree_cpp/basic_types.h"
#include "behaviortree_cpp/behavior_tree.h"
#include "behaviortree_ros2/bt_topic_pub_node.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"

namespace rm_behavior_tree
{
using BT::NodeStatus;

class SendGoalAction : public BT::RosTopicPubNode<geometry_msgs::msg::Twist>
{
public:
  SendGoalAction(
    const std::string & instance_name, const BT::NodeConfig & conf,
    const BT::RosNodeParams & params)
  : RosTopicPubNode<geometry_msgs::msg::Twist>(instance_name, conf, params)
  {
    // Initialize your node here if needed
  }

  bool setMessage(geometry_msgs::msg::Twist & msg) override;

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<float>("linear_x"),
      BT::InputPort<float>("linear_y"),
      BT::InputPort<float>("linear_z"),
      BT::InputPort<float>("angular_x"),
      BT::InputPort<float>("angular_y"),
      BT::InputPort<float>("angular_z"),
      BT::OutputPort<geometry_msgs::msg::Twist>("goal_pose")};
  }
};

}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_GOAL_HPP_