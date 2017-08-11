#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include <iostream>
#include <fstream>
#define RATE 15
#define BUFFER 100

class Marker_Utility {
   public:
      static void createMarker(visualization_msgs::Marker* m1);
};
void Marker_Utility::createMarker(visualization_msgs::Marker* m1) {
   m1->header.frame_id = "map";
   m1->header.stamp = ros::Time::now();
   m1->ns = "demomarker";
   m1->id = 1;
   m1->type = visualization_msgs::Marker::SPHERE;
   m1->action = visualization_msgs::Marker::ADD;
   m1->pose.position.x = 0;
   m1->pose.position.y = 0;
   m1->pose.position.z = 0;
   m1->pose.orientation.x= 0;
   m1->pose.orientation.y = 0;
   m1->pose.orientation.z = 0;
   m1->pose.orientation.w = 1;
   m1->scale.x = 0.5;
   m1->scale.y = 0.5;
   m1->scale.z = 0.5;
   m1->color.r = 0.0f;
   m1->color.g = 1.0f;
   m1->color.b = 0.0f;
   m1->color.a = 1.0;
   m1->lifetime = ros::Duration();
}

//for now it only takes path to file as argument
int main(int argc, char* argv[]) {

   ros::init(argc, argv, "translator");
   ros::NodeHandle n;
   ros::Publisher markerpub = n.advertise<visualization_msgs::Marker>("demo_markers", BUFFER);
   ros::Rate r(RATE);
   
   std::ifstream path_file;
   path_file.open(argv[1], std::ios::in);

   while (ros::ok()) {

      while (markerpub.getNumSubscribers() < 1) {
         ROS_WARN_ONCE("Create a subscriber.");
         sleep(1);
      }

      std::string xyz [3];
      if (path_file.good()) {
         for (int i = 0; i<= 2; i++) {
            std::getline(path_file, xyz[i], '\0');
         }// gets 3 values from the file(x, y, z)
      } else {
         path_file.close();
         return 0;
      }
      visualization_msgs::Marker primarker;
      Marker_Utility::createMarker(&primarker);
      ////
      try {
         primarker.pose.position.x = std::stof(xyz[0]);
         primarker.pose.position.y = std::stof(xyz[1]);
         primarker.pose.position.z = std::stof(xyz[2]);
      } catch ( const std::exception& e ) {
         ROS_INFO("Expected exception caught: end of file");
         ROS_INFO("Ending routine...");
         ROS_INFO( e.what());
         path_file.close();
         return 0;
      }

      markerpub.publish(primarker);
      r.sleep();
   }//while (ros::ok     
//delicious imperative code
//classes suck
return 0;
}

