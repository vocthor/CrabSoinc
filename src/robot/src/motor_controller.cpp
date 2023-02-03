#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/float32.hpp"
#include "roverc/msg/wheel_speed.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class MotorController : public rclcpp::Node
{
public:
	MotorController()
		: Node("motor_controller")
	{
		twist_sub_ = this->create_subscription<geometry_msgs::msg::Twist>("RoverC/cmd_vel", qos, std::bind(&MotorController::twistCallback, this, _1));
		wheels_pub_ = this->create_publisher<roverc::msg::WheelSpeed>("RoverC/wheels", qos);
		this->declare_parameter<int>("state", 0);
		this->get_parameter("state", state_);
	}

private:
	void twistCallback(const geometry_msgs::msg::Twist::SharedPtr msg) const
	{

		roverc::msg::WheelSpeed wheels;
		wheels.front_right = msg->linear.x - msg->linear.y - (1.5 + 3.5) * msg->angular.z;
		wheels.front_left = msg->linear.x + msg->linear.y + (1.5 + 3.5) * msg->angular.z;
		wheels.rear_right = 1.1 * (msg->linear.x + msg->linear.y - (1.5 + 3.5) * msg->angular.z);
		wheels.rear_left = msg->linear.x - msg->linear.y + (1.5 + 3.5) * msg->angular.z;
		wheels_pub_->publish(wheels);

		RCLCPP_INFO(this->get_logger(), "Twist: [lx: %f, ly: %f, wz: %f], State [%d]", msg->linear.x, msg->linear.y, msg->angular.z, state_);
	}

	rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr twist_sub_;
	rclcpp::Publisher<roverc::msg::WheelSpeed>::SharedPtr wheels_pub_;
	rclcpp::SensorDataQoS qos;
	int state_;
};

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<MotorController>());
	rclcpp::shutdown();
	return 0;
}
