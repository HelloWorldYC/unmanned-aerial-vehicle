// Generated by gencpp from file offboard/information_collection_case.msg
// DO NOT EDIT!


#ifndef OFFBOARD_MESSAGE_INFORMATION_COLLECTION_CASE_H
#define OFFBOARD_MESSAGE_INFORMATION_COLLECTION_CASE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/String.h>

namespace offboard
{
template <class ContainerAllocator>
struct information_collection_case_
{
  typedef information_collection_case_<ContainerAllocator> Type;

  information_collection_case_()
    : collection_flag()
    , point_n(0)
    , arrive_flag(false)  {
    }
  information_collection_case_(const ContainerAllocator& _alloc)
    : collection_flag(_alloc)
    , point_n(0)
    , arrive_flag(false)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::String_<ContainerAllocator>  _collection_flag_type;
  _collection_flag_type collection_flag;

   typedef uint8_t _point_n_type;
  _point_n_type point_n;

   typedef uint8_t _arrive_flag_type;
  _arrive_flag_type arrive_flag;





  typedef boost::shared_ptr< ::offboard::information_collection_case_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::offboard::information_collection_case_<ContainerAllocator> const> ConstPtr;

}; // struct information_collection_case_

typedef ::offboard::information_collection_case_<std::allocator<void> > information_collection_case;

typedef boost::shared_ptr< ::offboard::information_collection_case > information_collection_casePtr;
typedef boost::shared_ptr< ::offboard::information_collection_case const> information_collection_caseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::offboard::information_collection_case_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::offboard::information_collection_case_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace offboard

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'offboard': ['/home/myc/offboard_ws/src/offboard/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::offboard::information_collection_case_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::offboard::information_collection_case_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::offboard::information_collection_case_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::offboard::information_collection_case_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::offboard::information_collection_case_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::offboard::information_collection_case_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::offboard::information_collection_case_<ContainerAllocator> >
{
  static const char* value()
  {
    return "79acd54d777973b93b9b56ccf8677846";
  }

  static const char* value(const ::offboard::information_collection_case_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x79acd54d777973b9ULL;
  static const uint64_t static_value2 = 0x3b9b56ccf8677846ULL;
};

template<class ContainerAllocator>
struct DataType< ::offboard::information_collection_case_<ContainerAllocator> >
{
  static const char* value()
  {
    return "offboard/information_collection_case";
  }

  static const char* value(const ::offboard::information_collection_case_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::offboard::information_collection_case_<ContainerAllocator> >
{
  static const char* value()
  {
    return "##信息传输完成的标志位\n\
std_msgs/String collection_flag  \n\
uint8 point_n\n\
##目标点到达的标志位\n\
bool arrive_flag\n\
================================================================================\n\
MSG: std_msgs/String\n\
string data\n\
";
  }

  static const char* value(const ::offboard::information_collection_case_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::offboard::information_collection_case_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.collection_flag);
      stream.next(m.point_n);
      stream.next(m.arrive_flag);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct information_collection_case_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::offboard::information_collection_case_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::offboard::information_collection_case_<ContainerAllocator>& v)
  {
    s << indent << "collection_flag: ";
    s << std::endl;
    Printer< ::std_msgs::String_<ContainerAllocator> >::stream(s, indent + "  ", v.collection_flag);
    s << indent << "point_n: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.point_n);
    s << indent << "arrive_flag: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.arrive_flag);
  }
};

} // namespace message_operations
} // namespace ros

#endif // OFFBOARD_MESSAGE_INFORMATION_COLLECTION_CASE_H
