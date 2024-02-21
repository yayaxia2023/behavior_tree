# rm_behavior_tree

仍在开发中...

本仓库为 [pb_rm_simulation](https://gitee.com/SMBU-POLARBEAR/pb_rmsimulation) 的子仓库

## 环境配置

当前开发环境为 Ubuntu22.04, ROS2 humble

1. 安装依赖

    ```bash
    sudo apt install ros-humble-behaviortree-cpp
    ```

## 文件结构

- BehaviorTree.ROS2

    forcked from [BehaviorTree/BehaviorTree.ROS2](https://github.com/BehaviorTree/BehaviorTree.ROS2), provides a standard way to implement:

  - Action clients
  - Service Clients
  - Topic Subscribers
  - Topic Publishers

- rm_behavior_tree

    Robomaster 哨兵决策树部分

- rm_decision_interfaces

    对接裁判系统的自定义 ROS 消息类型
