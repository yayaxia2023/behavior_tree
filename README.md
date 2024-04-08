# rm_behavior_tree

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![State-of-the-art Shitcode](https://img.shields.io/static/v1?label=State-of-the-art&message=Shitcode&color=7B5804)](https://github.com/trekhleb/state-of-the-art-shitcode)

仍在开发中... 屎山代码，请勿用于生产环境

本仓库为 [RM2024_SMBU_auto_sentry_ws](https://gitee.com/SMBU-POLARBEAR/RM2024_SMBU_auto_sentry_ws) 的子模块，**与父仓库的其他模块存在依赖关系**

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

## 环境配置

当前开发环境为 Ubuntu22.04, ROS2 humble, BehaviorTree.CPP 4.5

1. 安装依赖

    ```sh
    sudo apt install ros-humble-behaviortree-cpp
    ```

2. 克隆仓库

    ```sh
    git clone https://gitee.com/SMBU-POLARBEAR/rm_behavior_tree.git
    cd rm_behavior_tree
    ```

3. 编译

    ```sh
    colcon build --symlink-install --cmake-args -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    ```

## 使用方法

1. 开启[虚拟裁判系统话题发布](./rm_decision_interfaces/publish_script.sh)

    ```sh
    ./rm_decision_ws/rm_decision_interfaces/publish_script.sh
    ```

2. 启动行为树

    ```sh
    ros2 launch rm_behavior_tree rm_behavior_tree.launch.py \
    style:=retreat_attack_left \
    use_sim_time:=True
    ```

## 当前的行为树预设

- attack_left

    自身状态良好时，向敌方左侧进攻；若队友平均血量少于敌方平均血量，回退到中心增益点；血量低时，回退补给区；撤退过程中若被攻击，再次根据状态判断是否打断撤退任务；被攻击时，可原地走位；

- attack_right

    同上，但向右侧进攻。

- retreat_attack_left

    继承，自身状态良好时，向左侧进攻...；  
    添加特性：比赛最后1:30，固定回退到己方基地前侧墙边。

## 使用 Groot 可视化行为树

1. 下载 [Groot Linux installer](https://www.behaviortree.dev/groot)

2. 安装 Groot

    ```sh
    chmod +x Groot2-*-linux-installer.run
    ./Groot2-*-linux-installer.run
    ```

3. 运行 Groot

    ```sh
    cd ~/Groot2/bin
    ./groot2
    ```

4. 在 Groot 中打开 [rm_behavior_tree.xml](./rm_behavior_tree/rm_behavior_tree.xml)
