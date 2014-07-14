#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
// Por base_link no Fixed_Frame



visualization_msgs::Marker func(int x, int y, int z, int id);


int main( int argc, char** argv )
 {
   ros::init(argc, argv, "marca_minas");
   ros::NodeHandle n;
   ros::Rate r(1);
   ros::Publisher marker_pub = n.advertise<visualization_msgs::MarkerArray>("visualization_marker_array", 10);

   visualization_msgs::Marker marker;
   visualization_msgs::MarkerArray lista;

   int x, y, z, id;
   x = 0;
   y = 0;
   z = 0;

   id = 0;

  while (ros::ok())
{

      if(x < 3){
       marker = func(x,y,z, id);

       lista.markers.push_back(marker);

       // Publish the marker
       marker_pub.publish(lista);
       x++;

       id++;
      }

      r.sleep();
    }
  return 0;
  }


visualization_msgs::Marker func(int x, int y, int z, int id){


    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
     marker.header.frame_id = "base_link";
     marker.header.stamp = ros::Time::now();

       // Set the namespace and id for this marker.  This serves to create a unique ID
       // Any marker sent with the same namespace and id will overwrite the old one
       marker.ns = "basic_shapes";
       marker.id = id;

       // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
       marker.type = visualization_msgs::Marker::CUBE;

       // Set the marker action.  Options are ADD and DELETE
       marker.action = visualization_msgs::Marker::ADD;

       // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
       marker.pose.position.x = x;
       marker.pose.position.y = 1;
       marker.pose.position.z = 0;
       marker.pose.orientation.x = 0.0;
       marker.pose.orientation.y = 0.0;
       marker.pose.orientation.z = 0.0;
       marker.pose.orientation.w = 1.0;

       // Set the scale of the marker -- 1x1x1 here means 1m on a side
       marker.scale.x = 0.1;
       marker.scale.y = 0.1;
       marker.scale.z = 0.1;

       // Set the color -- be sure to set alpha to something non-zero!
       marker.color.r = 0.0f;
       marker.color.g = 1.0f;
       marker.color.b = 0.0f;
       marker.color.a = 1.0;

    return marker;


}

