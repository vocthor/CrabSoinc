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

class TofServoing : public rclcpp::Node
{
public:
	TofServoing()
		: Node("tof_servoing")
	{
		dist_sub_ = this->create_subscription<std_msgs::msg::Float32>("RoverC/distance", qos, std::bind(&TofServoing::distanceCallback, this, _1));
		twist_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("RoverC/cmd_vel", qos);
		this->declare_parameter<int>("minDistance", 100);
		this->get_parameter("minDistance", distance_);
		this->declare_parameter<double>("lambdaKp", 0.02);
		this->get_parameter("lambdaKp", lambda_Kp_);
	}

private:
	void distanceCallback(const std_msgs::msg::Float32::SharedPtr msg) const
	{
		geometry_msgs::msg::Twist twist;
		twist.linear.set__x((msg->data - distance_) * lambda_Kp_);
		twist_pub_->publish(twist);
	}

	rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr dist_sub_;
	rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;
	rclcpp::SensorDataQoS qos;
	int distance_;
	double lambda_Kp_;
};

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<TofServoing>());
	rclcpp::shutdown();
	return 0;
}
