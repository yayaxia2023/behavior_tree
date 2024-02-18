//头文件
#include "behaviortree_cpp/behavior_tree.h"
#include "behaviortree_cpp/bt_factory.h"
#include "rclcpp/rclcpp.hpp"
#include "rm_decision_interfaces/msg/all_robot_hp.hpp"
#include "rm_decision_interfaces/msg/friend_location.hpp"
#include "rm_decision_interfaces/msg/rfid.hpp"
#include "rm_decision_interfaces/msg/robot_status.hpp"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1;
using namespace std::chrono_literals;
#ifndef RM_BT_H
#define RM_BT_H

//值的定义
rm_decision_interfaces::msg::RFID RFID_VALUE;
rm_decision_interfaces::msg::RobotStatus ROBOT_STATUS_VALUE;
rm_decision_interfaces::msg::FriendLocation FRIEND_LOCATION_VALUE;
rm_decision_interfaces::msg::AllRobotHP ROBOT_HP_VALUE;

//创建ros对行为树的修饰器
class ROS2DecoratorNode : public BT::SyncActionNode
{
public:
  ROS2DecoratorNode(const std::string & name, const BT::NodeConfig & config)
  : BT::SyncActionNode(name, config)
  {
  }

  BT::NodeStatus tick() override
  {
    //端口映射
    setOutput("rfid", RFID_VALUE);
    setOutput("robot_status", ROBOT_STATUS_VALUE);
    setOutput("friend_location", FRIEND_LOCATION_VALUE);
    setOutput("robot_hp", ROBOT_HP_VALUE);

    return BT::NodeStatus::SUCCESS;
  }

  static BT::PortsList providedPorts()
  {
    return {
      //端口注册
      BT::OutputPort<rm_decision_interfaces::msg::RFID>("rfid"),
      BT::OutputPort<rm_decision_interfaces::msg::RobotStatus>("robot_status"),
      BT::OutputPort<rm_decision_interfaces::msg::FriendLocation>("friend_location"),
      BT::OutputPort<rm_decision_interfaces::msg::AllRobotHP>("robot_hp"),

    };
  }
};

class RmBt : public rclcpp::Node
{
public:
  RmBt() : Node("RM_bt")
  {
    RCLCPP_INFO(this->get_logger(), "RM_bt,go");
    //创建订阅方

    subscription_rfid = this->create_subscription<rm_decision_interfaces::msg::RFID>(
      "rfid", 10, std::bind(&RmBt::topicCallbackRfid, this, std::placeholders::_1));

    subscription_robot_status = this->create_subscription<rm_decision_interfaces::msg::RobotStatus>(
      "robot_status", 10,
      std::bind(&RmBt::topicCallbackRobotStatus, this, std::placeholders::_1));

    subscription_friend_location =
      this->create_subscription<rm_decision_interfaces::msg::FriendLocation>(
        "friend_location", 10,
        std::bind(&RmBt::topicCallbackFriendLocation, this, std::placeholders::_1));

    subscription_robot_hp = this->create_subscription<rm_decision_interfaces::msg::AllRobotHP>(
      "robot_hp", 10, std::bind(&RmBt::topicCallbackRobotHp, this, std::placeholders::_1));

    //创建发布方
  }
  //回调函数

  void topicCallbackRfid(const rm_decision_interfaces::msg::RFID & msg) { RFID_VALUE = msg; }

  void topicCallbackRobotStatus(const rm_decision_interfaces::msg::RobotStatus & msg)
  {
    ROBOT_STATUS_VALUE = msg;
  }

  void topicCallbackFriendLocation(const rm_decision_interfaces::msg::FriendLocation & msg)
  {
    FRIEND_LOCATION_VALUE = msg;
  }

  void topicCallbackRobotHp(const rm_decision_interfaces::msg::AllRobotHP & msg)
  {
    ROBOT_HP_VALUE = msg;
  }

  //定时器

private:
  //初始化订阅方

  rclcpp::Subscription<rm_decision_interfaces::msg::RFID>::SharedPtr subscription_rfid;

  rclcpp::Subscription<rm_decision_interfaces::msg::RobotStatus>::SharedPtr
    subscription_robot_status;

  rclcpp::Subscription<rm_decision_interfaces::msg::FriendLocation>::SharedPtr
    subscription_friend_location;

  rclcpp::Subscription<rm_decision_interfaces::msg::AllRobotHP>::SharedPtr subscription_robot_hp;

  //初始化发布方
};

#endif