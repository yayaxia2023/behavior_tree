#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_GOAL_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_GOAL_HPP_

#include <iostream>

#include "behaviortree_cpp/basic_types.h"
#include "behaviortree_cpp/behavior_tree.h"
#include "behaviortree_ros2/bt_topic_pub_node.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "rclcpp/rclcpp.hpp"

namespace rm_behavior_tree
{
using BT::NodeStatus;

class SendGoalAction : public BT::RosTopicPubNode<geometry_msgs::msg::PoseStamped>
{
public:
  SendGoalAction(
    const std::string & instance_name, const BT::NodeConfig & conf,
    const BT::RosNodeParams & params)
  : RosTopicPubNode<geometry_msgs::msg::PoseStamped>(instance_name, conf, params)
  {
  }

  bool setMessage(geometry_msgs::msg::PoseStamped & msg) override;

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<float>("position_x"),
      BT::InputPort<float>("position_y"),
      BT::InputPort<float>("position_z"),
      BT::InputPort<float>("orientation_x"),
      BT::InputPort<float>("orientation_y"),
      BT::InputPort<float>("orientation_z"),
      BT::InputPort<float>("orientation_w"),
      BT::OutputPort<geometry_msgs::msg::PoseStamped>("goal_pose")};
  }
};

}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_GOAL_HPP_