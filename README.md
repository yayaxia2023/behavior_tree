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

    ```zsh
    sudo apt install ros-humble-behaviortree-cpp
    ```

2. 克隆仓库

    ```zsh
    git clone https://gitee.com/SMBU-POLARBEAR/rm_behavior_tree.git
    cd rm_behavior_tree
    ```

3. 编译

    ```zsh
    colcon build --symlink-install --cmake-args -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    ```

## 使用方法

1. 开启[虚拟裁判系统话题发布](./rm_decision_interfaces/publish_script.sh)

    ```zsh
    ./rm_decision_ws/rm_decision_interfaces/publish_script.sh
    ```

2. 启动行为树

    ```zsh
    ros2 run rm_behavior_tree rm_behavior_tree
    ```

## 使用 Groot 可视化行为树

1. 下载 [Groot Linux installer](https://www.behaviortree.dev/groot)

2. 安装 Groot

    ```zsh
    chmod +x Groot2-*-linux-installer.run
    ./Groot2-*-linux-installer.run
    ```

3. 运行 Groot

    ```zsh
    cd ~/Groot2/bin
    ./groot2
    ```

4. 在 Groot 中打开 [rm_behavior_tree.xml](./rm_behavior_tree/rm_behavior_tree.xml)
