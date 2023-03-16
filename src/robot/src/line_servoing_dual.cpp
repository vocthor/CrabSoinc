#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/u_int16_multi_array.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class LineServoingDual : public rclcpp::Node
{
public:
	LineServoingDual()
		: Node("line_servoing_dual")
	{
		rgbc_sub_ = this->create_subscription<std_msgs::msg::UInt16MultiArray>("RoverC/rgbc", qos, std::bind(&LineServoingDual::rgbcCallback, this, _1));
		rgbc2_sub_ = this->create_subscription<std_msgs::msg::UInt16MultiArray>("RoverC/rgbc2", qos, std::bind(&LineServoingDual::rgbc2Callback, this, _1));
		twist_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("RoverC/cmd_vel", qos);
		this->declare_parameter<int>("couleur", 600);
		this->get_parameter("couleur", couleur_);
		this->declare_parameter<double>("lambdaKp", 0.008);
		this->get_parameter("lambdaKp", lambda_Kp_);
		this->declare_parameter<double>("lambdaKd", 0.01);
		this->get_parameter("lambdaKd", lambda_Kd_);
		this->declare_parameter<double>("lambdaKi", 0.0001);
		this->get_parameter("lambdaKi", lambda_Ki_);
	}

private:
	void rgbcCallback(const std_msgs::msg::UInt16MultiArray::SharedPtr msg)
	{
		int error = 1 * (msg->data[3] - couleur_);
		sumError_ += error;
		twist.angular.set__z(1.0 * (error * lambda_Kp_ + sumError_ * lambda_Ki_ + (error - previousError_) * lambda_Kd_));
		twist.linear.set__y(0.035 * twist.angular.z);
		flagC1 = true;
		twist.linear.set__x(0.75 / (1 + 0.5 * abs(twist.angular.z)));
		if (flagC2)
		{
			publish();
			flagC2 = false;
		}
		previousError_ = error;
		// RCLCPP_INFO(this->get_logger(), "Rgbc: [%f]", msg->data);
	}

	void rgbc2Callback(const std_msgs::msg::UInt16MultiArray::SharedPtr msg)
	{
		int error = 1 * (msg->data[3] - (couleur_ - 80));
		sumError2_ += error;
		twist2.angular.set__z(-1 * (error * lambda_Kp_ + sumError2_ * lambda_Ki_ + (error - previousError2_) * lambda_Kd_));
		twist2.linear.set__y(-0.035 * twist2.angular.z);
		flagC2 = true;
		twist.linear.set__x(0.75 / (1 + 0.5 * abs(twist.angular.z)));

		if (flagC1)
		{
			publish();
			flagC1 = false;
		}
		previousError2_ = error;
	}

	void publish()
	{
		geometry_msgs::msg::Twist twistTot;
		double lx = twist.linear.x + twist2.linear.x;
		double ly = twist.linear.y + twist2.linear.y;
		double wz = twist.angular.z + twist2.angular.z;
		twistTot.linear.set__x(lx);
		twistTot.linear.set__y(ly);
		twistTot.angular.set__z(wz);
		twist_pub_->publish(twistTot);
	}

	rclcpp::Subscription<std_msgs::msg::UInt16MultiArray>::SharedPtr rgbc_sub_;
	rclcpp::Subscription<std_msgs::msg::UInt16MultiArray>::SharedPtr rgbc2_sub_;
	rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;
	rclcpp::SensorDataQoS qos;
	int couleur_;
	double lambda_Kp_;
	double lambda_Kd_;
	double lambda_Ki_;
	int previousError_ = 0;
	int previousError2_ = 0;
	int sumError_ = 0;
	int sumError2_ = 0;
	geometry_msgs::msg::Twist twist;
	geometry_msgs::msg::Twist twist2;
	bool flagC1 = true;
	bool flagC2 = false;
};

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<LineServoingDual>());
	rclcpp::shutdown();
	return 0;
}
