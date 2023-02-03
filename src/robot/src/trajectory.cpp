#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <ctime>

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
		start_time_ = time(0);
	}

private:
	void timer_callback()
	{
		geometry_msgs::msg::Twist twist;
		time_t actual_time = time(0);
		switch (state_)
		{
		case 0:
			// tout droit pdt 1sec
			twist.linear.set__x(20);
			if (difftime(actual_time, start_time_) >= 1)
			{
				start_time_ = actual_time;
				state_ = 1;
			}
			break;
		case 1:
			// tourner droite pdt 2 sec
			twist.angular.set__z(-20);
			if (difftime(actual_time, start_time_) >= 2)
			{
				start_time_ = actual_time;
				state_ = 2;
			}
			break;
		case 2:
			// tourner gauche pdt 2 sec
			twist.angular.set__z(20);
			if (difftime(actual_time, start_time_) >= 2)
			{
				start_time_ = actual_time;
				state_ = 3;
			}
			break;
		case 3:
			// arriere pdt 1 sec
			twist.linear.set__x(-20);
			if (difftime(actual_time, start_time_) >= 1)
			{
				start_time_ = actual_time;
				state_ = 4;
			}
			break;
		default:
			twist.linear.set__x(0);
			twist.angular.set__z(0);
			break;
		}
		twist_pub_->publish(twist);
	}

	void distanceCallback(const std_msgs::msg::Float32::SharedPtr msg) const
	{
		RCLCPP_INFO(this->get_logger(), "Distance: [%f], State [%d]", msg->data, state_);
	}

	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;
	rclcpp::SensorDataQoS qos;
	int state_;
	time_t start_time_;
};

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<Trajectory>());
	rclcpp::shutdown();
	return 0;
}
