#include "rm_behavior_tree/plugins/action/scan_status.hpp"

namespace rm_behavior_tree
{

ScanStatusAction::ScanStatusAction(
  const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params)
: RosTopicPubNode<std_msgs::msg::Bool>(name, conf, params)
{
}

bool ScanStatusAction::setMessage(std_msgs::msg::Bool & msg)
{
  auto res = getInput<bool>("scan_status");
  if (!res) {
    throw BT::RuntimeError("error reading port [scan_status]:", res.error());
  }
  bool scan_status = res.value();

  msg.data = scan_status;

  // clang-format off
  std::cout << "Scan_status: [ "
    << scan_status<<" ]\n";
  // clang-format on

  return true;
}

}  // namespace rm_behavior_tree

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(rm_behavior_tree::ScanStatusAction, "ScanStatus");