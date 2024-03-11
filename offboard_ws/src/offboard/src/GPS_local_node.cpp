#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Twist.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <sensor_msgs/NavSatFix.h>
#include <mavros_msgs/GlobalPositionTarget.h>
#include <sstream>
#include <fstream>
#include <offboard/LLA.h>
#include <iostream>
#include <math.h>
#include <offboard/information_collection_case.h>

#define  Earth_radius            6378137                        //地球半径，此处是米
#define  Pi                      3.1415926535
#define  Flight_height           7.0                              //默认飞行高度
#define  HoldOn_height           3.0                              //默认悬停高度
#define  altitude_error          0.3                            //飞行高度允许误差
#define  point_num               4
#define  local_x_error           0.3
#define  local_y_error           0.3
#define  local_z_error           0.3

//定义全局变量
 mavros_msgs::State current_state;                              //定义订阅当前的状态的变量
 sensor_msgs::NavSatFix current_GPS_position;                   //定义订阅当前的GPS位置信息的变量
 geometry_msgs::PoseStamped current_local_position;             //定义订阅当前位置的变量
 geometry_msgs::TwistStamped  current_velocity;                 //定义订阅当前速度的变量
 mavros_msgs::SetMode offb_set_mode;                            //定义SetMode消息类型的变量
 mavros_msgs::CommandBool arm_cmd;                              //设置CommandBool类型的变量arm_cmd  
 geometry_msgs::PoseStamped target_local_position;              //设置目标点的位置信息                                      
 geometry_msgs::Twist target_velocity;                          //设置前往目标点的速度信息
 ros::Subscriber current_GPS_pos_sub;                           //订阅无人机当前的GPS信息
 ros::Subscriber position_sub;                                  //订阅无人机当前的位置信息,机体系
 ros::Subscriber velocity_sub;                                  //订阅无人机当前的速度信息
 ros::Subscriber state_sub;                                     //订阅无人机状态消息
 ros::Subscriber information_collection_sub;                     //订阅串口信息收集的结果
 ros::Publisher velocity_pub;                                   //发布目标点的速度信息
 ros::Publisher local_pos_pub;                                  //发布目标点的local位置消息，机体系
 ros::Publisher arrive_pos_pub;                                 //发布到达目标点的信息给串口开启节点
 ros::ServiceClient arming_client;                              //创建一个客户端向服务器发送请求服务
 ros::ServiceClient set_mode_client;                            //创建一个客户端向服务器发送请求服务，用于设置无人机的模式
 ros::Time last_request;                                        //获取时间
 float start_height;                                            //初始GPS高度
 int   count = 0;
 float targetPoint_latitude;
 float targetPoint_longitude;
 float targetPoint_altitude;
 double target_point_x;
 double target_point_y;
 int   task_finish = 0;
 int point_number = 0;
 int GPS_transform_first_flag = 0;
 double point_data[point_num*3];
 offboard::LLA point_GPS[point_num];
 offboard::LLA start_GPS;
 offboard::information_collection_case information_collection;//信息收集情况标志,0为收集未完成，1为收集完成
 offboard::information_collection_case arrive_point;           //到达目标点的情况，0为未到达，1为到达



//回调函数，将传回来的无人机的当前的状态赋给变量
void state_cb(const mavros_msgs::State::ConstPtr& msg)
{
  current_state = *msg;
}

//回调函数，将传回来的无人机的当前的位置信息赋给变量
void GPS_position_cb(const sensor_msgs::NavSatFix::ConstPtr& current_GPS)
{
  current_GPS_position = *current_GPS;
}

//回调函数，将传回来的无人机的当前的位置信息赋给变量
void local_position_cb(const geometry_msgs::PoseStamped::ConstPtr &current_pose)
{
  current_local_position= *current_pose;
}

//回调函数，将传回来的无人机的当前的速度信息赋给变量
void velocity_cb(const geometry_msgs::TwistStamped::ConstPtr &current_vel)
{
  current_velocity= *current_vel;
}

//回调函数，将传回来的信息收集的结果赋给变量
void information_collection_cb(offboard::information_collection_case information_case)
{
  information_collection = information_case;
}

//设置目标点的local位置信息
void target_local_position_set(float target_pose_x, float target_pose_y, float target_pose_z)
{
   target_local_position.pose.position.x = target_pose_x;
   target_local_position.pose.position.y = target_pose_y;
   target_local_position.pose.position.z = target_pose_z;
}


//打印当前GPS位置信息
void current_GPS_position_info(void)
{
   ROS_INFO("current GPS position \n latitude:%.19f\n longitude:%.19f\n altitude:%.19f", current_GPS_position.latitude,
                                                                                         current_GPS_position.longitude,
                                                                                         current_GPS_position.altitude);
}

//打印当前local位置信息
void current_local_position_info(void)
{
   ROS_INFO("current position \n x:%.2f\n y:%.2f\n z:%.2f", current_local_position.pose.position.x,
                                                            current_local_position.pose.position.y,
                                                            current_local_position.pose.position.z );
}

//打印当前的速度信息
void current_velocity_info(void)
{
     ROS_INFO("current velocity \n x:%f\n y:%f\n z:%f", current_velocity.twist.linear.x,
                                                        current_velocity.twist.linear.y,
                                                        current_velocity.twist.linear.z);
}

//打印GPS转换成local的位置信息
void GPS_transform_result(void)
{
    ROS_INFO("GPS transform result \n x:%f\n y:%f\n", target_point_x,target_point_y);
}

//读取txt文件中的目标点GPS位置数据
void txt_read(void)
{
    std::ifstream fin("./src/offboard/src/GPS.txt");
    int i,j;
    for(i=0; i<point_num; i++)
    {
        for(j=0; j<3; j++)
        {
            fin >> *(point_data+i*3+j);
            //ROS_INFO("The data is %.11f\n",*(point_data+i*3+j));
        }
        point_GPS[i].latitude  = *(point_data+i*3);
        point_GPS[i].longitude = *(point_data+i*3+1);
        point_GPS[i].altitude  = *(point_data+i*3+2);
        ROS_INFO("The GPS of point %d is :\n latitude:%.19f\n longitude:%.19f\n altitude:%.19f",i,point_GPS[i].latitude,
                                                                                                  point_GPS[i].longitude,
                                                                                                  point_GPS[i].altitude);
    }
    fin.close();
}

//根据两个点的GPS数据得到两点之间的距离
double GetDistance(double lat1, double lng1, double lat2, double lng2)
{
    double radlat1 = lat1*Pi/180.0;
    double radlat2 = lat2*Pi/180.0;
    double radlng1 = lng1*Pi/180.0;
    double radlng2 = lng2*Pi/180.0;
    double a = radlat1 - radlat2;
    double b = radlng1 - radlng2;
    double s = 2*asin(sqrt(pow(sin(a/2),2) + cos(radlat1)*cos(radlat2)*pow(sin(b/2),2)));
    s = s*Earth_radius;
    s = round(s*10000)/10000;
    return s;
}

//x轴为经度，y轴为纬度
void GPS_transform(offboard::LLA current_point, offboard::LLA next_point)
{
    double distance_x;
    double distance_y;
    //在同一纬度下经度不同得到东向距离
    distance_x = GetDistance(current_point.latitude,current_point.longitude,current_point.latitude,next_point.longitude);
    //将得到的东向距离加到当前点的ENU坐标下得到目标点的x坐标
    if(next_point.longitude - current_point.longitude > 0)
    {
        target_point_x = current_local_position.pose.position.x + distance_x;
    }
    else
    {
        target_point_x = current_local_position.pose.position.x - distance_x;
    }
    //在同一经度下纬度不同得到北向距离
    distance_y = GetDistance(current_point.latitude,next_point.longitude,next_point.latitude,next_point.longitude);
    //将得到的北向距离加到当前点的ENU坐标下得到目标点的y坐标
    if(next_point.latitude - current_point.latitude > 0)
    {
        target_point_y = current_local_position.pose.position.y + distance_y;
    }
    else
    {
        target_point_y = current_local_position.pose.position.y - distance_y;
    }
}


//设置节点的发布和订阅
void subscriber_and_publisher(ros::NodeHandle &n)
{
    current_GPS_pos_sub = n.subscribe<sensor_msgs::NavSatFix>     //订阅无人机当前的GPS位置信息
    ("mavros/global_position/global",10,GPS_position_cb);

    position_sub = n.subscribe<geometry_msgs::PoseStamped>        //订阅无人机当前的local位置信息
    ("mavros/local_position/pose",10,local_position_cb);

    velocity_sub = n.subscribe<geometry_msgs::TwistStamped>       //订阅无人机当前的速度信息
    ("mavros/local_position/velocity",10,velocity_cb);

    state_sub = n.subscribe<mavros_msgs::State>                   //订阅无人机状态消息，并注册回调函数state_cb
	("mavros/state", 10, state_cb); 

   information_collection_sub = n.subscribe<offboard::information_collection_case> //订阅信息收集回传的结果
   ("serial_read",10,information_collection_cb);

    velocity_pub = n.advertise<geometry_msgs::Twist>                    //发布目标点的速度信息
    ("mavros/setpoint_velocity/velocity_local", 10);         

    local_pos_pub = n.advertise<geometry_msgs::PoseStamped>             //发布目标点的local位置消息，机体系
	 ("mavros/setpoint_position/local", 10); 

    arrive_pos_pub = n.advertise<offboard::information_collection_case> //发布目标点到达的信息
    ("arrive_message",10);

    arming_client = n.serviceClient<mavros_msgs::CommandBool>     //创建一个客户端向服务器发送请求服务
	("mavros/cmd/arming"); 

    set_mode_client = n.serviceClient<mavros_msgs::SetMode>       //创建一个客户端向服务器发送请求服务，用于设置无人机的模式
	("mavros/set_mode");
}

//对无人机的状态进行判断，做起飞前的准备
void preflight_judge(void)
{
   if( current_state.mode != "OFFBOARD" &&                       //当目前状态不为OFFBOARD模式且与上一次的
      (ros::Time::now() - last_request > ros::Duration(3.0)))    //时间大于3s时满足条件
        {
	        if( set_mode_client.call(offb_set_mode)                //发布"Offboard"模式的请求，并且回传消息
              && offb_set_mode.response.mode_sent)               //证明已经设置成功则进入条件语句
               {
		                ROS_INFO("Offboard enabled");                //打印消息
                        ROS_INFO_STREAM("current state is " << current_state.mode); 
		       }
	        last_request = ros::Time::now();                       //获取当前的时间
        }
     else 
        {
	        if( !current_state.armed &&(ros::Time::now() - last_request > ros::Duration(3.0)))
              {
		              if( arming_client.call(arm_cmd) && arm_cmd.response.success)
                     {
			                   ROS_INFO("Vehicle armed");             //打印消息
			        }
			            last_request = ros::Time::now();              //获取当前时间
	  	        }
		     }
}



//根据local信息从当前点到另外一个点的飞行过程，以折线方式飞行：先飞到指定高度，再飞到目标点上方，最后降落到目标点
void point_point_local(float target_x, float target_y, float target_z)
{
    if(current_local_position.pose.position.x < (target_x - local_x_error) || current_local_position.pose.position.x > (target_x + local_x_error) ||
       current_local_position.pose.position.y < (target_y - local_y_error) || current_local_position.pose.position.y > (target_y + local_y_error))
        {
            if(count == 0)
            {
                target_local_position_set(current_local_position.pose.position.x,current_local_position.pose.position.y,Flight_height);
                count++;
                current_GPS_position_info();
                current_local_position_info();
            }
        }
    if((current_local_position.pose.position.x < (target_x - local_x_error) || current_local_position.pose.position.x > (target_x + local_x_error) ||
       current_local_position.pose.position.y < (target_y - local_y_error) || current_local_position.pose.position.y > (target_y + local_y_error)) &&
       (current_local_position.pose.position.z > (Flight_height - local_z_error) && current_local_position.pose.position.z < (Flight_height + local_z_error)) )
        {
            if(count == 1)
            {
                current_GPS_position_info();
                current_local_position_info();
                target_local_position_set(target_x, target_y, Flight_height);
                count++;
            }
        }
    if(current_local_position.pose.position.x > (target_x - local_x_error) && current_local_position.pose.position.x < (target_x + local_x_error) &&
       current_local_position.pose.position.y > (target_y - local_y_error) && current_local_position.pose.position.y < (target_y + local_y_error) &&
       current_local_position.pose.position.z > (Flight_height - local_z_error) && current_local_position.pose.position.z < (Flight_height + local_z_error))
        {
            if(count == 2)
            {
                current_GPS_position_info();
                current_local_position_info();
                target_local_position_set(target_x,target_y,target_z);
                count++;
            }
        }
    if(current_local_position.pose.position.x > (target_x - local_x_error) && current_local_position.pose.position.x < (target_x + local_x_error) &&
       current_local_position.pose.position.y > (target_y - local_y_error) && current_local_position.pose.position.y < (target_y + local_y_error) &&
       current_local_position.pose.position.z > (target_z - local_z_error) && current_local_position.pose.position.z < (target_z + local_z_error))
       {
           if(count == 3)
           {
                current_GPS_position_info();
                current_local_position_info();
                arrive_point.arrive_flag = 1;                       //将目标点到达标志位置位
                ROS_INFO("The vehicle have arrived the target point\n");
                count++ ;
           }
           if(information_collection.collection_flag.data == "1")   //信息收集完成进入这段程序
           {
                start_GPS.latitude = current_GPS_position.latitude; 
                start_GPS.longitude = current_GPS_position.longitude;
                start_GPS.altitude = current_GPS_position.altitude;
                //  task_finish = 1;
                point_number++;
                GPS_transform(start_GPS,point_GPS[point_number]);   //对下一个目标点进行坐标计算
                GPS_transform_result();                             //打印坐标计算结果
                count = 0;
                information_collection.collection_flag.data = "0";  //信息收集完成标志位清零
                arrive_point.arrive_flag = 0;                       //目标点到达标志位清零
                ROS_INFO("task finished!");
           }
       }
}




//主函数
int main(int argc, char **argv)
{
   ros::init(argc, argv, "GPS_local_node");          //初始化节点
   ros::NodeHandle nh;                                        //nh为节点句柄
   subscriber_and_publisher(nh);                              //调用节点的发布和订阅函数，对无人机信息进行发布和订阅
   ros::Rate rate(20.0);                                      //目标点发布的速率必须大于20Hz
   txt_read();
   arrive_point.arrive_flag = 0;
   


   // 等待FMU连接，连接成功，current_state.connected值为0
   while(ros::ok() && !current_state.connected)
  {
	    ros::spinOnce();                                        //用来处理节点订阅话题的所有回调函数
	    rate.sleep();                                           //调用休眠函数使节点进入休眠状态，休眠时间为1/20秒
	}

   offb_set_mode.request.custom_mode = "OFFBOARD";            //客户端的变量custom_mode赋值，申请无人机的模式为"OFFBOARD
   arm_cmd.request.value = true;                              //设置arm_cmd的类型为true，请求无人机飞行准备
   last_request = ros::Time::now();                           //获得ros::Time::now实例化的当前时间


//当ros没问题时一直循环执行下列代码
   while(ros::ok())
   {
	    preflight_judge();                                      //对无人机的状态进行判断
        if(current_GPS_position.latitude > 20 && target_point_x < 100)
        {
            switch(point_number)//根据目标点的序号来执行不同的程序
            {
                case 0:
                    if(GPS_transform_first_flag == 0)
                    {
                        start_GPS.latitude = current_GPS_position.latitude;
                        start_GPS.longitude = current_GPS_position.longitude;
                        start_GPS.altitude = current_GPS_position.altitude;
                        current_GPS_position_info();            //打印当前的GPS位置
                        current_local_position_info();          //打印当前的ENU位置
                        GPS_transform(start_GPS,point_GPS[0]);  //进行第一个目标点的坐标计算
                        GPS_transform_result();                 //打印坐标计算的结果
                        GPS_transform_first_flag = 1;           //将第一次坐标转换标志位置位，之后不会重复进行坐标计算
                    }
                    point_point_local(target_point_x,target_point_y,HoldOn_height);//飞往第一个目标点
                    break;
                case 1:
                    point_point_local(target_point_x,target_point_y,HoldOn_height);//飞往第二个目标点
                    break;
                case 2:
                    point_point_local(target_point_x,target_point_y,HoldOn_height);//飞往第三个目标点
                    break;
                case 3:
                    point_point_local(target_point_x,target_point_y,HoldOn_height);//飞往第四个目标点
            }
            arrive_point.point_n = point_number;                    //将到达的目标点的序号一起发送给串口节点
            local_pos_pub.publish(target_local_position);           //发送目标位置信息
            arrive_pos_pub.publish(arrive_point);                   //发送到达目标的信息
        }
		ros::spinOnce();                                        //处理回调函数
		rate.sleep();                                           //让节点休息
	 }
	 return 0;
}
