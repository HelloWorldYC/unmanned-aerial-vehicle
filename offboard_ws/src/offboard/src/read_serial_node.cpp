#include <sstream>
#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <offboard/information_collection_case.h>

serial::Serial ser; //声明串口对象 
offboard::information_collection_case information_collection;                   //定义一个信息收集的具体消息
int i = 0;
int k = 0;
uint8_t receive_data[5];                                                        //串口收集的信息
uint16_t Voltage_data;                                                          //采集的ADC电压数据
float Voltage_V;                                                                //进行处理后的电压数据
size_t j;

//订阅目标点到达的回调函数
void arrive_point_cb(offboard::information_collection_case arrive_case)
{
    information_collection.arrive_flag = arrive_case.arrive_flag ;              
    information_collection.point_n = arrive_case.point_n;                       //当前到达的目标点的序号
    if(information_collection.arrive_flag == 1 && i == 0)                       //限制次数避免重复打印目标点到达信息
    {
        ROS_INFO_STREAM("Arrive message have received\n");
        i++;
    }

}

int main(int argc, char **argv)
{
   ros::init(argc,argv,"read_serial_node");
  
   ros::NodeHandle n;
 
   //发布信息收集回传的结果
   ros::Publisher serial_read_pub = n.advertise<offboard::information_collection_case>("serial_read",100);
   //订阅目标点到达的情况
   ros::Subscriber arrive_point_sub = n.subscribe("arrive_message", 10, arrive_point_cb);

   ros::Rate loop_rate(10);                                                         //设置循环的频率


    try 
    { 
        //设置串口属性，并打开串口 
        ser.setPort("/dev/ttyUSB0"); 
        ser.setBaudrate(115200); 
        serial::Timeout to = serial::Timeout::simpleTimeout(1000); 
        ser.setTimeout(to); 
        ser.open(); 
    } 
    catch(serial::IOException& e) 
    { 
        ROS_ERROR_STREAM("Unable to open port "); 
        return -1; 
    } 

    //检测串口是否已经打开，并给出提示信息 
    if(ser.isOpen()) 
    { 
        ROS_INFO_STREAM("Serial Port initialized"); 
    } 
    else 
    { 
        return -1; 
    } 

   while(ros::ok())
  {
            if(ser.available() && information_collection.arrive_flag == 1)          //到达目标点时开始读取串口数据
            {
                j = ser.available();
                ROS_INFO_STREAM("Reading from serial port"); 
                j = ser.read(receive_data , j);                                     //读取串口传输的数据
                ROS_INFO_STREAM("Read: " << j <<"  "<< receive_data[0]<<"  "<<receive_data[1]<<"  "<<receive_data[2]); 
                Voltage_data = (receive_data[0]<<8)+receive_data[1];                //将读取的电压数据的高八位和低八位整合
                Voltage_V = (Voltage_data*1.2)/1024*3;                              //对电压ADC数据进行处理得到直观的电压数据值
                ROS_INFO("The Voltage data of point %d is %f V",information_collection.point_n,Voltage_V);
                information_collection.collection_flag.data = receive_data[2];      
                serial_read_pub.publish(information_collection);                    //发布信息收集完成情况给控制节点，控制无人机继续飞行
                information_collection.arrive_flag == 0;                            //清零目标点到达标志位
                i = 0;
            }
    ros::spinOnce();                                                               //处理回调函数
    loop_rate.sleep();                                                             //使节点休眠
  }
  return 0;
}
