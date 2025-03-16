#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sercli/srv/add.hpp"

using namespace std::chrono_literals;

class ClientNode : public rclcpp::Node {
    public:
        ClientNode() : Node("client_node") {
            subscription_ = this->create_subscription<std_msgs::msg::String>("/data", 10, std::bind(&ClientNode::topic_callback, this, std::placeholders::_1));
            

            client_ = this->create_client<sercli::srv::Add>("/add_two_numbers");

            timer_ = this->create_wall_timer(5s, std::bind(&ClientNode::send_service_request, this));

            RCLCPP_INFO(this->get_logger(), "Node Initialized.");
        }

    private:
        void topic_callback(const std_msgs::msg::String::SharedPtr msg) {
            RCLCPP_INFO(this->get_logger(), "Received: '%s'", msg->data.c_str());
        }

        void send_service_request() {
            // Check if service is available
            if (!client_->wait_for_service(1s)) {
                RCLCPP_WARN(this->get_logger(), "Service not available, waiting...");
                return;
            }

            // Create request
            auto request = std::make_shared<sercli::srv::Add::Request>();
            request->a = 10;
            request->b = 20;

            // Send async service request
            auto future = client_->async_send_request(request, 
                std::bind(&ClientNode::service_response_callback, this, std::placeholders::_1));
        }

        void service_response_callback(rclcpp::Client<sercli::srv::Add>::SharedFuture future) {
            try {
                auto response = future.get();
                RCLCPP_INFO(this->get_logger(), "Service Response: Sum = %ld", response->sum);
            } catch (const std::exception &e) {
                RCLCPP_ERROR(this->get_logger(), "Service call failed: %s", e.what());
            }
        }

        // Member variables
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
        rclcpp::Client<sercli::srv::Add>::SharedPtr client_;
        rclcpp::TimerBase::SharedPtr timer_;
};

// Main function
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ClientNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}