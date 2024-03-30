#include "rm_behavior_tree/plugins/action/stop_scan_status.hpp"

namespace rm_behavior_tree
{

ScanStatusAction::ScanStatusAction(
  const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params)
: RosTopicPubNode<std_msgs::msg::Bool>(name, conf, params)
{
}

bool ScanStatusAction::setMessage(std_msgs::msg::Bool & msg)
{
  auto res = getInput<bool>("stop_scan_status");
  if (!res) {
    throw BT::RuntimeError("error reading port [stop_scan_status]:", res.error());
  }
  bool stop_scan_status = res.value();

  msg.data = stop_scan_status;

  // clang-format off
  std::cout << "stop_scan_status: [ "
    << stop_scan_status<<" ]\n";
  // clang-format on

  return true;
}

}  // namespace rm_behavior_tree

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(rm_behavior_tree::ScanStatusAction, "ScanStatus");