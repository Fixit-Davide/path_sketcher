#include <chrono>
#include <cmath>
#include <vector>
#include "path_sketch/path_sketch.hpp"

using std::placeholders::_1;

namespace filter{    

    PathSketch::PathSketch(const rclcpp::NodeOptions & options) : Node("path_sketch", options) {

        source_topic_odom = declare_parameter<std::string>("topics.odometry", "/odometry/filtered");
        path_topic_ = declare_parameter<std::string>("topics.path_publisher", "/path"); 
        odom_subs_ = create_subscription<nav_msgs::msg::Odometry>(source_topic_odom, 1, std::bind(&PathSketch::odom_callback, this, _1));
        path_pub_ = create_publisher<nav_msgs::msg::Path>(path_topic_, 1);
        path_msg = std::make_shared<nav_msgs::msg::Path>();
    }

    void PathSketch::odom_callback(const nav_msgs::msg::Odometry::SharedPtr odom_msg)
    {
        path_msg->header = odom_msg->header;
        geometry_msgs::msg::PoseStamped ps;
        ps.header = odom_msg->header;
        ps.pose = odom_msg->pose.pose;
        path_msg->poses.push_back(std::move(ps));

        path_pub_->publish(*path_msg);
    }


  
} //namespace filter

