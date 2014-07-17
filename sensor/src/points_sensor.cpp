#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/message_filter.h>
#include <message_filters/subscriber.h>
#include <geometry_msgs/Vector3Stamped.h>

// INICIO
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
// FIM

class MetalDetector
{
public:
    MetalDetector() : tf_(),  target_frame_("odom")
    {
        md_sub_.subscribe(n_, "dados_sensor", 100);
        tf_filter_ = new tf::MessageFilter<geometry_msgs::Vector3Stamped>(md_sub_, tf_, target_frame_, 10);
        tf_filter_->registerCallback( boost::bind(&MetalDetector::msgCallback, this, _1) );

        // INICIO

        marker_pub = n_.advertise<visualization_msgs::MarkerArray>("visualization_marker_array", 10);


        id = 0;
        // FIM

    }

private:
    message_filters::Subscriber<geometry_msgs::Vector3Stamped> md_sub_;
    tf::TransformListener tf_;
    tf::MessageFilter<geometry_msgs::Vector3Stamped> * tf_filter_;
    ros::NodeHandle n_;
    std::string target_frame_;

    // INICIO

    ros::Publisher marker_pub;
    visualization_msgs::Marker marker;
    visualization_msgs::MarkerArray lista;
    int id;




    visualization_msgs::Marker func(double x, double y, double z, int id){


        visualization_msgs::Marker marker;
        // Set the frame ID and timestamp.  See the TF tutorials for information on these.
         marker.header.frame_id = "odom";
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
           marker.pose.position.y = y;
           marker.pose.position.z = z;
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



    // FIM



    //  Callback to register with tf::MessageFilter to be called when transforms are available
    void msgCallback(const boost::shared_ptr<const geometry_msgs::Vector3Stamped>& coil_ptr)
    {
        geometry_msgs::PointStamped point_in;
        point_in.header.frame_id = coil_ptr->header.frame_id;
        point_in.header.stamp = coil_ptr->header.stamp;
        point_in.point.x = 0.0;
        point_in.point.y = 0.0;
        point_in.point.z = 0.0;

        geometry_msgs::PointStamped point_out;
        try
        {
            tf_.transformPoint(target_frame_, point_in, point_out);

            // Note that z is the position of the coil, not the position of the possible metal sample!
             ROS_INFO("\nFrame ID: %s \nProximidade: %f \nFrequencia: %f \nMina: %f  \nPosicao (x,y,z): (%f,%f,%f)\n",
                coil_ptr->header.frame_id.c_str(),
                coil_ptr->vector.x,
                coil_ptr->vector.y,
                coil_ptr->vector.z,
                point_out.point.x,
                point_out.point.y,
                point_out.point.z);

             if((int) coil_ptr->vector.z == 1 ){

                 marker = func(point_out.point.x,point_out.point.y,point_out.point.z, id);

                 lista.markers.push_back(marker);

                 // Publish the marker
                 marker_pub.publish(lista);

                 id++;

             }




        }
        catch (tf::TransformException &ex)
        {
            ROS_WARN("Failure %s\n", ex.what());
        }
    }
};

int main(int argc, char ** argv)
{
    ros::init(argc, argv, "read_metal_detector");

    MetalDetector md;

    ros::spin();

    return 0;
};

