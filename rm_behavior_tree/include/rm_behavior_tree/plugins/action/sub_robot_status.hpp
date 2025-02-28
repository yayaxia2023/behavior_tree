#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__SUB_ROBOT_STATUS_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__SUB_ROBOT_STATUS_HPP_

#include "behaviortree_ros2/bt_topic_sub_node.hpp"
#include "roborts_msgs/msg/robot_status.hpp"

namespace rm_behavior_tree
{
class SubRobotStatusAction : public BT::RosTopicSubNode<roborts_msgs::msg::RobotStatus>
{
public:
  SubRobotStatusAction(
    const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params);

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("topic_name"),
      BT::OutputPort<roborts_msgs::msg::RobotStatus>("robot_status")};
  }

  BT::NodeStatus onTick(
    const std::shared_ptr<roborts_msgs::msg::RobotStatus> & last_msg) override;
};
}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__SUB_ROBOT_STATUS_HPP_