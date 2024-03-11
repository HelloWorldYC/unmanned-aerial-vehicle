// Auto-generated. Do not edit!

// (in-package offboard.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class information_collection_case {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.collection_flag = null;
      this.point_n = null;
      this.arrive_flag = null;
    }
    else {
      if (initObj.hasOwnProperty('collection_flag')) {
        this.collection_flag = initObj.collection_flag
      }
      else {
        this.collection_flag = new std_msgs.msg.String();
      }
      if (initObj.hasOwnProperty('point_n')) {
        this.point_n = initObj.point_n
      }
      else {
        this.point_n = 0;
      }
      if (initObj.hasOwnProperty('arrive_flag')) {
        this.arrive_flag = initObj.arrive_flag
      }
      else {
        this.arrive_flag = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type information_collection_case
    // Serialize message field [collection_flag]
    bufferOffset = std_msgs.msg.String.serialize(obj.collection_flag, buffer, bufferOffset);
    // Serialize message field [point_n]
    bufferOffset = _serializer.uint8(obj.point_n, buffer, bufferOffset);
    // Serialize message field [arrive_flag]
    bufferOffset = _serializer.bool(obj.arrive_flag, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type information_collection_case
    let len;
    let data = new information_collection_case(null);
    // Deserialize message field [collection_flag]
    data.collection_flag = std_msgs.msg.String.deserialize(buffer, bufferOffset);
    // Deserialize message field [point_n]
    data.point_n = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [arrive_flag]
    data.arrive_flag = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.String.getMessageSize(object.collection_flag);
    return length + 2;
  }

  static datatype() {
    // Returns string type for a message object
    return 'offboard/information_collection_case';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '79acd54d777973b93b9b56ccf8677846';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    ##信息传输完成的标志位
    std_msgs/String collection_flag  
    uint8 point_n
    ##目标点到达的标志位
    bool arrive_flag
    ================================================================================
    MSG: std_msgs/String
    string data
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new information_collection_case(null);
    if (msg.collection_flag !== undefined) {
      resolved.collection_flag = std_msgs.msg.String.Resolve(msg.collection_flag)
    }
    else {
      resolved.collection_flag = new std_msgs.msg.String()
    }

    if (msg.point_n !== undefined) {
      resolved.point_n = msg.point_n;
    }
    else {
      resolved.point_n = 0
    }

    if (msg.arrive_flag !== undefined) {
      resolved.arrive_flag = msg.arrive_flag;
    }
    else {
      resolved.arrive_flag = false
    }

    return resolved;
    }
};

module.exports = information_collection_case;
