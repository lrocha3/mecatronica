#include <ros/ros.h>
#include <geometry_msgs/Vector3Stamped.h>


// Cout
#include <iostream>

// Open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Write e Sleep
#include <unistd.h>



// Perror
#include <stdio.h>
#include <cerrno>


// Memset
#include <string.h>


// Strtol
#include <stdlib.h>



int main(int argc, char ** argv)
{

 int threshold;
  

  if(argc == 2){
    threshold = atoi(argv[1]);
    
  }
  else
  {
    ROS_FATAL("Não especificou um threshold!");
    exit(0);
  }
printf("\n\nThreshold: %d",threshold);

  ros::init(argc, argv, "sensor");


  ros::NodeHandle n;


  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Vector3Stamped>("dados_sensor",1000);

  ros::Rate loop_rate(10);  // 10 hz o ciclo cada vez


   geometry_msgs::Vector3Stamped msg;





  int USB;
  int ultimo;
  char buf[16];
  char proximidade[4];
  char frequencia[4];
  
  int prox_int;
  int freq_int;

  memset(buf,0,sizeof(buf));


  const char *portname = "/dev/ttyACM0";

  USB = open (portname, O_RDWR | O_NOCTTY);


  if (USB < 0)
  {
      ROS_FATAL("Nao conseguiu abrir a porta!");
  }
  else
  {


  
  
  memset(buf,0,sizeof(buf));
	

  ultimo = write(USB,"3",1);
  ultimo = read(USB,buf,sizeof(buf));  // a primeira stream é "stream start"


  ROS_INFO("Loop a ler os valores!");

  while(ros::ok())
  {


  
    ultimo = read(USB,buf , sizeof(buf));
    buf[ultimo] = '\0';
    
    proximidade[0] = buf[2];
    proximidade[1] = buf[3];
    proximidade[2] = buf[4];
    proximidade[3] = buf[5];
    proximidade[4] = '\0';
    
    frequencia[0] = buf[9];
    frequencia[1] = buf[10];
    frequencia[2] = buf[11];
    frequencia[3] = buf[12];
    frequencia[4] = '\0';
    
    prox_int = (int) strtol(proximidade, NULL, 16);  // Converte hexadecimal para inteiro
    freq_int = (int) strtol(frequencia, NULL, 16);
   

    msg.vector.x = prox_int;
    msg.vector.y = freq_int;
	
    if( prox_int > threshold)
      msg.vector.z = 1;
    else
      msg.vector.z = 0;

    msg.header.stamp=ros::Time::now();
    msg.header.frame_id="sensor";

    chatter_pub.publish(msg);

    ros::spinOnce();

    
  }



}



return 0;

}








