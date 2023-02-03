#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include "roverc/msg/wheel_speed.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class Trajectory : public rclcpp::Node
{
public:
	Trajectory()
		: Node("trajectory")
	{
		timer_ = this->create_wall_timer(500ms, std::bind(&Trajectory::timer_callback, this));
		twist_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("RoverC/cmd_vel", qos);
		this->declare_parameter<int>("state", 0);
		this->get_parameter("state", state_);
	}

private:
	void timer_callback()
	{
		geometry_msgs::msg::Twist twist;
		switch(state_) 
		{
			case 0:
				// tout droit pdt 1sec
				twist.linear.set__x(20);
			case 1:
				// tourner droite pdt 2 sec
				twist.angular.set__z(-20);
			case 2:
				// tourner gauche pdt 2 sec
				twist.angular.set__z(20);
			case 3:
				// arriere pdt 2 sec
				twist.linear.set__x(-20);
			default:
				break;
		}
	}

	void distanceCallback(const std_msgs::msg::Float32::SharedPtr msg) const
	{
		RCLCPP_INFO(this->get_logger(), "Distance: [%f], State [%d]", msg->data, state_);
	}

	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;
	rclcpp::SensorDataQoS qos;
	int state_;
};

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<Trajectory>());
	rclcpp::shutdown();
	return 0;
}
