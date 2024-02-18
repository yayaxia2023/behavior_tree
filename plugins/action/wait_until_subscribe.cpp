#include "rm_behavior_tree/plugins/action/wait_until_subscribe.h"

#include <memory>
#include <string>

namespace rm_behavior_tree
{

WaitUntilSubscribe::WaitUntilSubscribe(
  const std::string & name, const BT::NodeConfiguration & config)
: BT::SyncActionNode(name, config)
{
}

BT::NodeStatus WaitUntilSubscribe::tick()
{
  rm_decision_interfaces::msg::AllRobotHP all_robot_hp;
  rm_decision_interfaces::msg::FriendLocation friend_location;
  rm_decision_interfaces::msg::RFID rfid;

  rm_decision_interfaces::msg::RobotStatus robot_status;
  getInput("robot_hp", all_robot_hp);
  getInput("friend_location", friend_location);
  getInput("rfid", rfid);
  getInput("robot_status", robot_status);

  std::cout << "blue_1_robot_hp: " << all_robot_hp.blue_1_robot_hp << std::endl;
  std::cout << "hero_x_location: " << friend_location.hero_x << std::endl;
  std::cout << "RFID: " << rfid.rfid_patrol_status << std::endl;

  return BT::NodeStatus::SUCCESS;
}

}  // namespace rm_behavior_tree

#include "behaviortree_cpp/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<rm_behavior_tree::WaitUntilSubscribe>("WaitUntilSubscribe");
}