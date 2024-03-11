; Auto-generated. Do not edit!


(cl:in-package offboard-msg)


;//! \htmlinclude information_collection_case.msg.html

(cl:defclass <information_collection_case> (roslisp-msg-protocol:ros-message)
  ((collection_flag
    :reader collection_flag
    :initarg :collection_flag
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String))
   (point_n
    :reader point_n
    :initarg :point_n
    :type cl:fixnum
    :initform 0)
   (arrive_flag
    :reader arrive_flag
    :initarg :arrive_flag
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass information_collection_case (<information_collection_case>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <information_collection_case>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'information_collection_case)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard-msg:<information_collection_case> is deprecated: use offboard-msg:information_collection_case instead.")))

(cl:ensure-generic-function 'collection_flag-val :lambda-list '(m))
(cl:defmethod collection_flag-val ((m <information_collection_case>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard-msg:collection_flag-val is deprecated.  Use offboard-msg:collection_flag instead.")
  (collection_flag m))

(cl:ensure-generic-function 'point_n-val :lambda-list '(m))
(cl:defmethod point_n-val ((m <information_collection_case>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard-msg:point_n-val is deprecated.  Use offboard-msg:point_n instead.")
  (point_n m))

(cl:ensure-generic-function 'arrive_flag-val :lambda-list '(m))
(cl:defmethod arrive_flag-val ((m <information_collection_case>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard-msg:arrive_flag-val is deprecated.  Use offboard-msg:arrive_flag instead.")
  (arrive_flag m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <information_collection_case>) ostream)
  "Serializes a message object of type '<information_collection_case>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'collection_flag) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'point_n)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'arrive_flag) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <information_collection_case>) istream)
  "Deserializes a message object of type '<information_collection_case>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'collection_flag) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'point_n)) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'arrive_flag) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<information_collection_case>)))
  "Returns string type for a message object of type '<information_collection_case>"
  "offboard/information_collection_case")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'information_collection_case)))
  "Returns string type for a message object of type 'information_collection_case"
  "offboard/information_collection_case")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<information_collection_case>)))
  "Returns md5sum for a message object of type '<information_collection_case>"
  "79acd54d777973b93b9b56ccf8677846")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'information_collection_case)))
  "Returns md5sum for a message object of type 'information_collection_case"
  "79acd54d777973b93b9b56ccf8677846")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<information_collection_case>)))
  "Returns full string definition for message of type '<information_collection_case>"
  (cl:format cl:nil "##信息传输完成的标志位~%std_msgs/String collection_flag  ~%uint8 point_n~%##目标点到达的标志位~%bool arrive_flag~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'information_collection_case)))
  "Returns full string definition for message of type 'information_collection_case"
  (cl:format cl:nil "##信息传输完成的标志位~%std_msgs/String collection_flag  ~%uint8 point_n~%##目标点到达的标志位~%bool arrive_flag~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <information_collection_case>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'collection_flag))
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <information_collection_case>))
  "Converts a ROS message object to a list"
  (cl:list 'information_collection_case
    (cl:cons ':collection_flag (collection_flag msg))
    (cl:cons ':point_n (point_n msg))
    (cl:cons ':arrive_flag (arrive_flag msg))
))
