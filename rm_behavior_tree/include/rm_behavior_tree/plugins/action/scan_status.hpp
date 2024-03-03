#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__SCAN_STATUS_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__SCAN_STATUS_HPP_

#include <std_msgs/msg/detail/bool__struct.hpp>
#include "behaviortree_cpp/contrib/json.hpp"
#include "behaviortree_ros2/bt_topic_pub_node.hpp"
#include "std_msgs/msg/bool.hpp"
#include "rm_behavior_tree/bt_conversions.hpp"

namespace rm_behavior_tree
{

class ScanStatusAction : public BT::RosTopicPubNode<std_msgs::msg::Bool>
{
public:
  ScanStatusAction(
    const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params);

  bool setMessage(std_msgs::msg::Bool & msg) override;

  static BT::PortsList providedPorts()
  {
    return {BT::InputPort<bool>("scan_status")};
  }
};
}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_GOAL_HPP_