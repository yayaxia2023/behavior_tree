#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_GOAL_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_GOAL_HPP_

#include <iostream>

#include "behaviortree_cpp/basic_types.h"
#include "behaviortree_cpp/behavior_tree.h"
#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/contrib/json.hpp"
#include "behaviortree_ros2/bt_topic_pub_node.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "rclcpp/rclcpp.hpp"

struct PoseStamped
{
  float position_x;
  float position_y;
  float position_z;
  float orientation_x;
  float orientation_y;
  float orientation_z;
  float orientation_w;
};

namespace BT
{
template <>
inline PoseStamped convertFromString(StringView str)
{
  auto parts = splitString(str, ';');
  if (parts.size() != 7) {
    throw RuntimeError("invalid input)");
  } else {
    PoseStamped output;
    output.position_x = convertFromString<double>(parts[0]);
    output.position_y = convertFromString<double>(parts[1]);
    output.position_z = convertFromString<double>(parts[2]);
    output.orientation_x = convertFromString<double>(parts[3]);
    output.orientation_y = convertFromString<double>(parts[4]);
    output.orientation_z = convertFromString<double>(parts[5]);
    output.orientation_w = convertFromString<double>(parts[6]);
    return output;
  }
}
}  // namespace BT

// Allows PoseStamped to be visualized in Groot2
void PoseStampedToJson(nlohmann::json & j, const PoseStamped & p)
{
  j["position_x"] = p.position_x;
  j["position_y"] = p.position_y;
  j["position_z"] = p.position_z;
  j["orientation_x"] = p.orientation_x;
  j["orientation_y"] = p.orientation_y;
  j["orientation_z"] = p.orientation_z;
  j["orientation_w"] = p.orientation_w;
}

namespace rm_behavior_tree
{

/**
 * @brief 发送给 Navigation2 目标位置点
 * @param parameter-goal_pose发送到的ROS话题id
 * RMUL中，中心增益区：(3.0，0.4) 右侧攻击点：(5.3 -1.35)
 */
class SendGoalAction : public BT::RosTopicPubNode<geometry_msgs::msg::PoseStamped>
{
public:
  SendGoalAction(
    const std::string & instance_name, const BT::NodeConfig & conf,
    const BT::RosNodeParams & params)
  : RosTopicPubNode<geometry_msgs::msg::PoseStamped>(instance_name, conf, params)
  {
  }

  bool setMessage(geometry_msgs::msg::PoseStamped & msg) override
  {
    auto res = getInput<PoseStamped>("goal_pose");
    if (!res) {
      throw BT::RuntimeError("error reading port [goal_pose]:", res.error());
    }
    PoseStamped goal = res.value();

    msg.header.stamp = rclcpp::Clock().now();
    msg.header.frame_id = "map";
    msg.pose.position.x = goal.position_x;
    msg.pose.position.y = goal.position_y;
    msg.pose.position.z = goal.position_z;
    msg.pose.orientation.x = goal.orientation_x;
    msg.pose.orientation.y = goal.orientation_y;
    msg.pose.orientation.z = goal.orientation_z;
    msg.pose.orientation.w = goal.orientation_w;

    printf(
      "Goal_pose: [ %.1f, %.1f, %.1f, %.1f, %.1f, %.1f, %.1f ]\n", goal.position_x, goal.position_x,
      goal.position_z, goal.orientation_x, goal.orientation_y, goal.orientation_z,
      goal.orientation_w);

    return true;
  }

  static BT::PortsList providedPorts()
  {
    const char * description = "Input ROS geometry_msgs::msg::PoseStamped msg";
    return {BT::InputPort<PoseStamped>("goal_pose", description)};
  }
};

}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_GOAL_HPP_