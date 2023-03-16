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

class MapServoingHybrid : public rclcpp::Node
{
public:
	MapServoingHybrid()
		: Node("map_servoing_hybrid")
	{
		rgbc_sub_ = this->create_subscription<std_msgs::msg::UInt16MultiArray>("RoverC/rgbc", qos, std::bind(&MapServoingHybrid::rgbcCallback, this, _1));
		rgbc2_sub_ = this->create_subscription<std_msgs::msg::UInt16MultiArray>("RoverC/rgbc2", qos, std::bind(&MapServoingHybrid::rgbc2Callback, this, _1));
		twist_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("RoverC/cmd_vel", qos);
		this->declare_parameter<double>("lambdaKp", 2.0);
		this->get_parameter("lambdaKp", lambda_Kp_);
	}

private:
	void rgbcCallback(const std_msgs::msg::UInt16MultiArray::SharedPtr msg)
	{
		data_front_ = msg->data;
		distance_ = sqrt(pow(DEST_B - msg->data[2], 2) + pow(DEST_R - msg->data[0], 2));
		flagC1 = true;
		if (flagC2)
		{
			// TODO : distance en couleur ????
			double ratioDist = 0; 
			double alpha = atan2(DEST_B - msg->data[2], DEST_R - msg->data[0]);					   // orientation vers destination
			double thetaR = atan2(data_front_[2] - data_back_[2], data_front_[0] - data_back_[0]); // orientation dans repere
			double rot = (thetaR - alpha);
			if (rot > M_PI)
				rot -= 2 * M_PI;
			else if (rot < -M_PI)
				rot += 2 * M_PI;
			double holoX = lambda_Kp_ * 0.3 * cos(thetaR - alpha);
			double holoY = lambda_Kp_ * 0.3 * sin(thetaR - alpha);
			double diffX = lambda_Kp_ * 0.3;
			double diffZ = lambda_Kp_ * rot;
			twist.linear.set__x(holoX * (1 - ratioDist) + ratioDist * diffX);
			twist.linear.set__y(holoY * (1 - ratioDist));
			twist.angular.set__z(diffZ * ratioDist);
			twist_pub_->publish(twist);
			flagC2 = false;
		}
	}

	void rgbc2Callback(const std_msgs::msg::UInt16MultiArray::SharedPtr msg)
	{
		data_back_ = msg->data;
		distance_ = sqrt(pow(DEST_B - msg->data[2], 2) + pow(DEST_R - msg->data[0], 2));
		flagC2 = true;
		if (flagC1)
		{
			double alpha = atan2(DEST_B - msg->data[2], DEST_R - msg->data[0]);					   // orientation vers destination
			double thetaR = atan2(data_front_[2] - data_back_[2], data_front_[0] - data_back_[0]); // orientation dans repere
			double rot = (thetaR - alpha);
			if (rot > M_PI)
				rot -= 2 * M_PI;
			else if (rot < -M_PI)
				rot += 2 * M_PI;
			double holoX = lambda_Kp_ *  0.3 * cos(thetaR - alpha);
			double holoY = lambda_Kp_ *  0.3 * sin(thetaR - alpha);
			double diffX = lambda_Kp_ *  0.3;
			double diffZ = lambda_Kp_ *  rot;
			twist.linear.set__x(holoX / distance_ + distance_ * diffX);
			twist.linear.set__y(holoY / distance_);
			twist.angular.set__z(diffZ);
			twist_pub_->publish(twist);
			flagC1 = false;
		}
	}

	rclcpp::Subscription<std_msgs::msg::UInt16MultiArray>::SharedPtr rgbc_sub_;
	rclcpp::Subscription<std_msgs::msg::UInt16MultiArray>::SharedPtr rgbc2_sub_;
	rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;
	rclcpp::SensorDataQoS qos;
	double lambda_Kp_;
	std::vector<uint16_t, std::allocator<uint16_t>> data_front_;
	std::vector<uint16_t, std::allocator<uint16_t>> data_back_;
	geometry_msgs::msg::Twist twist;
	bool flagC1 = false;
	bool flagC2 = false;
	double distance_;
};

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<MapServoingHybrid>());
	rclcpp::shutdown();
	return 0;
}
