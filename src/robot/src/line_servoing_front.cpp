#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/u_int16_multi_array.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class LineServoingFront : public rclcpp::Node
{
public:
	LineServoingFront()
		: Node("line_servoing_front")
	{
		rgbc_sub_ = this->create_subscription<std_msgs::msg::UInt16MultiArray>("RoverC/rgbc", qos, std::bind(&LineServoingFront::rgbcCallback, this, _1));
		twist_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("RoverC/cmd_vel", qos);
		this->declare_parameter<int>("clair", 1200);
		this->get_parameter("clair", clair_);
		this->declare_parameter<int>("fonce", 120);
		this->get_parameter("fonce", fonce_);
		this->declare_parameter<int>("couleur", 600);
		this->get_parameter("couleur", couleur_);
		this->declare_parameter<double>("lambdaKp", 0.04);
		this->get_parameter("lambdaKp", lambda_Kp_);
		this->declare_parameter<double>("lambdaKd", 0.04);
		this->get_parameter("lambdaKd", lambda_Kd_);
		previousError_ = 0;
	}

private:
	void rgbcCallback(const std_msgs::msg::UInt16MultiArray::SharedPtr msg)
	{
		geometry_msgs::msg::Twist twist;

		// if (msg->data[2] > clair_)
		// {
		// 	// Sur du blanc
		// 	twist.angular.set__z((clair_ - msg->data[2]) * lambda_Kp_ );
		// }
		// else if (msg->data[2] < fonce_)
		// {
		// 	// Sur du noir
		// 	twist.angular.set__z((fonce_ - msg->data[2]) * lambda_Kp_);
		// }
		// else
		// {
		// 	twist.angular.set__z(0.0);
		// }

		int error = msg->data[3] - couleur_;
		twist.angular.set__z(error * lambda_Kp_ / 10 + (error - previousError_) * lambda_Kd_);
		twist.linear.set__x(0.5 / (1 + 0.7 * abs(twist.angular.z)));
		previousError_ = error;
		RCLCPP_INFO(this->get_logger(), "Twist: [lx: %f, ly: %f, wz: %f]", twist.linear.x, twist.linear.y, twist.angular.z);
		twist_pub_->publish(twist);
		// RCLCPP_INFO(this->get_logger(), "Rgbc: [%f]", msg->data);
	}

	/*
	noir 34 42 52 | 35 43 35 | 35 44 54 | 36 46 57; 127

	blanc 293 445 558 | 271 425 544 | 298 454 568; 1120

		271 333 182 | 180 219 121 | 238 295 164 743; 600

	bleu;
*/
	rclcpp::Subscription<std_msgs::msg::UInt16MultiArray>::SharedPtr rgbc_sub_;
	rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;
	rclcpp::SensorDataQoS qos;
	int clair_;
	int fonce_;
	int couleur_;
	double lambda_Kp_;
	double lambda_Kd_;
	int previousError_;
};

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<LineServoingFront>());
	rclcpp::shutdown();
	return 0;
}
