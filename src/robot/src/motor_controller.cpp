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
	}

private:
	void twistCallback(const geometry_msgs::msg::Twist::SharedPtr msg) const
	{
		const double LXLY = (2.0 + 2.75) / 100;
		const double RAY = (1.75) / 100;
		roverc::msg::WheelSpeed wheels;
		wheels.front_left = (msg->linear.x - msg->linear.y - LXLY * msg->angular.z) / RAY;
		wheels.front_right = (msg->linear.x + msg->linear.y + LXLY * msg->angular.z) / RAY;
		wheels.rear_left = 1.0 * (msg->linear.x + msg->linear.y - LXLY * msg->angular.z) / RAY;
		wheels.rear_right = (msg->linear.x - msg->linear.y + LXLY * msg->angular.z) / RAY;
		wheels_pub_->publish(wheels);

		RCLCPP_INFO(this->get_logger(), "Twist: [lx: %f, ly: %f, wz: %f]", msg->linear.x, msg->linear.y, msg->angular.z);
	}

	rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr twist_sub_;
	rclcpp::Publisher<roverc::msg::WheelSpeed>::SharedPtr wheels_pub_;
	rclcpp::SensorDataQoS qos;
};

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<MotorController>());
	rclcpp::shutdown();
	return 0;
}
