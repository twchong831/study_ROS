#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

#include <memory>

// notifing status
void add(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
		std::shared_ptr<example_interfaces::srv::AddTwoInts::Response>		response)
{
	response->sum = request->a + request->b;
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld",
				request->a, request->b);
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
}

int main(int argc, char** argv)
{
	// init 
	rclcpp::init(argc, argv);

	// create ros2 node
	std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_server");

	// create service "add_two_ints"
	// automatically advertises using network with "add" Func.
	rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service = 
		node->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", &add);
	
	// print log Message
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

	// spin node
	rclcpp::spin(node);
	rclcpp::shutdown();
}