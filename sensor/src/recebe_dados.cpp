#include <ros/ros.h>
#include <geometry_msgs/Vector3Stamped.h>


void chatterCallback(const geometry_msgs::Vector3Stamped msg)
{
  ROS_INFO("Proximidade: [%d] Frequencia: [%d] Mina: [%d] ",(int)msg.vector.x,(int)msg.vector.y, (int)msg.vector.z);


}



int main(int argc, char **argv)
{

  ros::init(argc, argv, "leitura");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("dados_sensor", 1000, chatterCallback);






  ros::spin(); // fica num loop a puxar callbacks --> retorna quando o ros::ok() é falso

  return 0;


}





/*


#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/message_filter.h>
#include <message_filters/subscriber.h>
#include <metal_detector_msgs/Coil.h>

class MetalDetector
{
public:
    MetalDetector() : tf_(),  target_frame_("minefield")
    {
        md_sub_.subscribe(n_, "coils", 10);
        tf_filter_ = new tf::MessageFilter<metal_detector_msgs::Coil>(md_sub_, tf_, target_frame_, 10);
        tf_filter_->registerCallback( boost::bind(&MetalDetector::msgCallback, this, _1) );
    }

private:
    message_filters::Subscriber<metal_detector_msgs::Coil> md_sub_;
    tf::TransformListener tf_;
    tf::MessageFilter<metal_detector_msgs::Coil> * tf_filter_;
    ros::NodeHandle n_;
    std::string target_frame_;

    //  Callback to register with tf::MessageFilter to be called when transforms are available
    void msgCallback(const boost::shared_ptr<const metal_detector_msgs::Coil>& coil_ptr)
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
             ROS_INFO("Coil %s with data ch0 %d ch1 %d ch2 %d at x %f y %f z %f",
                coil_ptr->header.frame_id.c_str(),
                coil_ptr->channel[0],
                coil_ptr->channel[1],
                coil_ptr->channel[2],
                point_out.point.x,
                point_out.point.y,
                point_out.point.z);
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



*/

