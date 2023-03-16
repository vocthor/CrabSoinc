#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <cmath>

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/u_int16_multi_array.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

#define DEST_R 110
#define DEST_B 70

class MapServoingHolonome : public rclcpp::Node
{
public:
	MapServoingHolonome()
		: Node("map_servoing_holonome")
	{
		rgbc_sub_ = this->create_subscription<std_msgs::msg::UInt16MultiArray>("RoverC/rgbc", qos, std::bind(&MapServoingHolonome::rgbcCallback, this, _1));
		rgbc2_sub_ = this->create_subscription<std_msgs::msg::UInt16MultiArray>("RoverC/rgbc2", qos, std::bind(&MapServoingHolonome::rgbc2Callback, this, _1));
		twist_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("RoverC/cmd_vel", qos);
	}

private:
	void rgbcCallback(const std_msgs::msg::UInt16MultiArray::SharedPtr msg)
	{
		data_front_ = msg->data;
		flagC1 = true;
		if (flagC2)
		{
			double alpha = atan2(DEST_B - msg->data[2], DEST_R - msg->data[0]);					   // orientation vers destination
			double thetaR = atan2(data_front_[2] - data_back_[2],data_front_[0] - data_back_[0]); // orientation dans repere
			twist.linear.set__x(0.3 * cos(thetaR - alpha));
			twist.linear.set__y(0.3 * sin(thetaR - alpha));
			twist_pub_->publish(twist);
			flagC2 = false;
		}
	}

	void rgbc2Callback(const std_msgs::msg::UInt16MultiArray::SharedPtr msg)
	{
		data_back_ = msg->data;
		flagC2 = true;
		if (flagC1)
		{
			double alpha = atan2(DEST_B - msg->data[2],DEST_R - msg->data[0]);					   // orientation vers destination
			double thetaR = atan2(data_front_[2] - data_back_[2],data_front_[0] - data_back_[0]); // orientation dans repere
			twist.linear.set__x(0.3 * cos(thetaR - alpha));
			twist.linear.set__y(0.3 * sin(thetaR - alpha));
			twist_pub_->publish(twist);
			flagC1 = false;
		}
	}

	rclcpp::Subscription<std_msgs::msg::UInt16MultiArray>::SharedPtr rgbc_sub_;
	rclcpp::Subscription<std_msgs::msg::UInt16MultiArray>::SharedPtr rgbc2_sub_;
	rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;
	rclcpp::SensorDataQoS qos;
	std::vector<uint16_t, std::allocator<uint16_t>> data_front_;
	std::vector<uint16_t, std::allocator<uint16_t>> data_back_;
	geometry_msgs::msg::Twist twist;
	bool flagC1 = false;
	bool flagC2 = false;
};

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<MapServoingHolonome>());
	rclcpp::shutdown();
	return 0;
}
