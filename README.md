# ROS 2 GSoC Problems

This repository contains solutions to problems given by mentors for Google Summer of Code (GSoC). The focus of this repository is to demonstrate basic ROS 2 functionalities, including subscribing to a topic and sending a service request.

## Table of Contents
- [ROS 2 GSoC Problems]([#ros-2-gsoc-problems](https://pal-robotics.com/2025-google-summer-code-proposals/))
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Setup](#setup)
  - [Usage](#usage)

## Introduction

The goal of this repository is to provide examples of basic ROS 2 operations. Specifically, it includes:
- Subscribing to a topic
- Sending a service request

## Setup

To set up the environment, follow these steps:

1. Install ROS 2 following the official [installation guide](https://docs.ros.org/en/foxy/Installation.html).
2. Clone this repository:
    ```sh
    git clone https://github.com/yourusername/ros2_gsoc_problems.git
    cd ros2_gsoc_problems
    ```
3. Source the ROS 2 setup script:
    ```sh
    source /opt/ros/foxy/setup.bash
    ```
4. Build the workspace:
    ```sh
    colcon build
    ```

## Usage

To run the examples, use the following commands:

1. Open a new terminal and source the ROS 2 setup script:
    ```sh
    source /opt/ros/foxy/setup.bash
    ```
2. Source the workspace:
    ```sh
    source install/setup.bash
    ```
3. Run the Client node:
    ```sh
    ros2 run sercli cli
    ```
4. In another terminal, run the Server node:
    ```sh
    ros2 run sercli serv
    ```
5. In another terminal, run the Publisher node:
    ```sh
    ros2 run sercli pub
    ```
