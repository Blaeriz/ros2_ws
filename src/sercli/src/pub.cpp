#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);  // Initialize ROS 2

  // Create a node
  auto node = rclcpp::Node::make_shared("minimal_publisher");

  // Create a publisher for the "topic" topic with queue size 10
  auto publisher = node->create_publisher<std_msgs::msg::String>("data", 10);

  rclcpp::Rate loop_rate(1);  // 1 Hz (1 message per second)
  int count = 0;

  while (rclcpp::ok()) {
    auto message = std_msgs::msg::String();
    message.data = "Hello, ROS 2 Jazzy! " + std::to_string(count++);

    // Publish the message
    RCLCPP_INFO(node->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher->publish(message);

    rclcpp::spin_some(node); 
    loop_rate.sleep();       
  }

  rclcpp::shutdown();  
  return 0;
}