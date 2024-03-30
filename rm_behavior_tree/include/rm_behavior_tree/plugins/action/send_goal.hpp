#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_GOAL_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_GOAL_HPP_

#include "behaviortree_cpp/contrib/json.hpp"
#include "behaviortree_ros2/bt_action_node.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "nav2_msgs/action/navigate_to_pose.hpp"
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

class SendGoalAction : public BT::RosActionNode<nav2_msgs::action::NavigateToPose>
{
public:
  SendGoalAction(
    const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params);

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<geometry_msgs::msg::PoseStamped>("goal_pose"),
      BT::InputPort<std::string>("action_name")};
  }

  bool setGoal(Goal & goal) override;

  void onHalt() override;

  BT::NodeStatus onResultReceived(const WrappedResult & wr) override;

  BT::NodeStatus onFeedback(const std::shared_ptr<const Feedback> feedback) override;

  BT::NodeStatus onFailure(BT::ActionNodeErrorCode error) override;
};
}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_GOAL_HPP_