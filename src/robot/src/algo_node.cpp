#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include "roverc/msg/wheel_speed.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class AlgoNode : public rclcpp::Node
{
public:
	AlgoNode()
		: Node("algo_node")
	{
		timer_ = this->create_wall_timer(500ms, std::bind(&AlgoNode::timer_callback, this));
		dist_sub_ = this->create_subscription<std_msgs::msg::Float32>("RoverC/distance", qos, std::bind(&AlgoNode::distanceCallback, this, _1));
		wheels_pub_ = this->create_publisher<roverc::msg::WheelSpeed>("RoverC/wheels", qos);
		this->declare_parameter<int>("state", 0);
		this->get_parameter("state", state_);
	}

private:
	void timer_callback()
	{
		roverc::msg::WheelSpeed wheels;
		wheels.front_right = 40;
		wheels.front_left = -40;
		wheels.rear_right = -43;
		wheels.rear_left = 40;
		wheels_pub_->publish(wheels);
	}

	void distanceCallback(const std_msgs::msg::Float32::SharedPtr msg) const
	{
		RCLCPP_INFO(this->get_logger(), "Distance: [%f], State [%d]", msg->data, state_);
	}

	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr dist_sub_;
	rclcpp::Publisher<roverc::msg::WheelSpeed>::SharedPtr wheels_pub_;
	rclcpp::SensorDataQoS qos;
	int state_;
};

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<AlgoNode>());
	rclcpp::shutdown();
	return 0;
}
