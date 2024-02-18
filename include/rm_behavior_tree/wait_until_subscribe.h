//头文件
#include <iostream>

#include "behaviortree_cpp/behavior_tree.h"
#include "behaviortree_cpp/bt_factory.h"
#include "rm_decision_interfaces/msg/all_robot_hp.hpp"
#include "rm_decision_interfaces/msg/friend_location.hpp"
#include "rm_decision_interfaces/msg/rfid.hpp"
#include "rm_decision_interfaces/msg/robot_status.hpp"
namespace WaitUntilSubscribe
{
using BT::NodeStatus;
//行为树节点类

//WaitUntilSubscribe叶节点
class WaitUntilSubscribe : public BT::SyncActionNode
{
public:
  WaitUntilSubscribe(const std::string & name, const BT::NodeConfig & config) : BT::SyncActionNode(name, config)
  {
  }
  // 给该节点申明端口
  static BT::PortsList providedPorts()
  {
    return {
      //端口设置
      BT::InputPort<rm_decision_interfaces::msg::RFID>("rfid"),
      BT::InputPort<rm_decision_interfaces::msg::RobotStatus>("robot_status"),
      BT::InputPort<rm_decision_interfaces::msg::FriendLocation>("friend_location"),
      BT::InputPort<rm_decision_interfaces::msg::AllRobotHP>("robot_hp"),
    };
  }
  BT::NodeStatus tick() override
  {
    //实现功能
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
};

inline void RegisterNodes(BT::BehaviorTreeFactory & factory)
{
  //注册节点
  factory.registerNodeType<WaitUntilSubscribe>("WaitUntilSubscribe");
}
}  // namespace WaitUntilSubscribe