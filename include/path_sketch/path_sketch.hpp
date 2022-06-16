#ifndef ROS2__PATH_SKETCH
#define ROS2__PATH_SKETCH

#include <rclcpp/rclcpp.hpp>
#include "nav_msgs/msg/odometry.hpp"
#include "nav_msgs/msg/path.hpp"

namespace filter {

    class PathSketch : public rclcpp::Node {
        public:
        
        PathSketch(const rclcpp::NodeOptions & options);
        
        ~PathSketch(){};

        private:
        rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_subs_;
        rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_pub_;

        void odom_callback(const nav_msgs::msg::Odometry::SharedPtr odom_msg);
        
    	std::shared_ptr<nav_msgs::msg::Path> path_msg;

        std::string source_topic_odom;
        std::string path_topic_;
        double old_x;
        double old_y;
        
    };
} //namespace filter

#include "rclcpp_components/register_node_macro.hpp"

// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
RCLCPP_COMPONENTS_REGISTER_NODE(filter::PathSketch)

#endif //ROS2__PATH_SKETCH