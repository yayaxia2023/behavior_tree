#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_GOAL_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_GOAL_HPP_

#include "behaviortree_cpp/contrib/json.hpp"
#include "behaviortree_ros2/bt_topic_pub_node.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "rm_behavior_tree/bt_conversions.hpp"

// Allows PoseStamped to be visualized in Groot2
void PoseStampedToJson(nlohmann::json & j, const geometry_msgs::msg::PoseStamped & p)
{
  j["position_x"] = p.pose.position.x;
  j["position_y"] = p.pose.position.y;
  j["position_z"] = p.pose.position.z;
  j["orientation_x"] = p.pose.orientation.x;
  j["orientation_y"] = p.pose.orientation.y;
  j["orientation_z"] = p.pose.orientation.z;
  j["orientation_w"] = p.pose.orientation.w;
}

namespace rm_behavior_tree
{

class SendGoalAction : public BT::RosTopicPubNode<geometry_msgs::msg::PoseStamped>
{
public:
  SendGoalAction(
    const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params);

  bool setMessage(geometry_msgs::msg::PoseStamped & msg) override;

  static BT::PortsList providedPorts()
  {
    return {BT::InputPort<geometry_msgs::msg::PoseStamped>("goal_pose")};
  }
};
}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_GOAL_HPP_