#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include <iostream>
#include <fstream>
#define RATE 15
#define BUFFER 100


//for now it only takes path to file as argument
int main(int argc, char* argv[]) {

   ros::init(argc, argv, "translator");
   ros::NodeHandle n;
   ros::Publisher posepub = n.advertise<geometry_msgs::Pose>("demo_pose", BUFFER);
   ros::Rate r(RATE);
   
   std::ifstream path_file;
   path_file.open(argv[1], std::ios::in);

   while (ros::ok()) {

      std::string xyz [3];
      if (path_file.good()) {
         for (int i = 0; i<= 2; i++) {
            std::getline(path_file, xyz[i], '\0');
         }// gets 3 values from the file(x, y, z)
      } else {
         path_file.close();
         return 0;
      }
      geometry_msgs::Pose pose;
      ////
      try {
         pose.position.x = std::stof(xyz[0]);
         pose.position.y = std::stof(xyz[1]);
         pose.position.z = std::stof(xyz[2]);
         pose.orientation.w = 1;
      } catch ( const std::exception& e ) {
         ROS_INFO("Expected exception caught: end of file");
         ROS_INFO("Ending routine...");
         ROS_INFO( e.what());
         path_file.close();
         return 0;
      }

      posepub.publish(pose);
      r.sleep();
   }//while (ros::ok     
//delicious imperative code
//classes suck
return 0;
}

