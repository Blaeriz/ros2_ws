#include "rclcpp/rclcpp.hpp"
#include "sercli/srv/add.hpp"


class Server : public rclcpp::Node {

  public:
    Server() : Node("add_two_numbers") {
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two numbers");

      auto add_nums = [this](
        const std::shared_ptr<sercli::srv::Add::Request> request,
        std::shared_ptr<sercli::srv::Add::Response> response) -> void {
          std::string state = "False";
          response->sum = request->a + request->b;
          RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld",
                request->a, request->b);
          RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
        };
      server = this->create_service<sercli::srv::Add>("add_two_numbers", add_nums);
    }
  
    private:
      rclcpp::Service<sercli::srv::Add>::SharedPtr server;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Server>());
  rclcpp::shutdown();
  return 0;
}