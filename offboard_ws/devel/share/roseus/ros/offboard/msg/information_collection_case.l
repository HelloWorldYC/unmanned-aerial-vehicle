;; Auto-generated. Do not edit!


(when (boundp 'offboard::information_collection_case)
  (if (not (find-package "OFFBOARD"))
    (make-package "OFFBOARD"))
  (shadow 'information_collection_case (find-package "OFFBOARD")))
(unless (find-package "OFFBOARD::INFORMATION_COLLECTION_CASE")
  (make-package "OFFBOARD::INFORMATION_COLLECTION_CASE"))

(in-package "ROS")
;;//! \htmlinclude information_collection_case.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass offboard::information_collection_case
  :super ros::object
  :slots (_collection_flag _point_n _arrive_flag ))

(defmethod offboard::information_collection_case
  (:init
   (&key
    ((:collection_flag __collection_flag) (instance std_msgs::String :init))
    ((:point_n __point_n) 0)
    ((:arrive_flag __arrive_flag) nil)
    )
   (send-super :init)
   (setq _collection_flag __collection_flag)
   (setq _point_n (round __point_n))
   (setq _arrive_flag __arrive_flag)
   self)
  (:collection_flag
   (&rest __collection_flag)
   (if (keywordp (car __collection_flag))
       (send* _collection_flag __collection_flag)
     (progn
       (if __collection_flag (setq _collection_flag (car __collection_flag)))
       _collection_flag)))
  (:point_n
   (&optional __point_n)
   (if __point_n (setq _point_n __point_n)) _point_n)
  (:arrive_flag
   (&optional __arrive_flag)
   (if __arrive_flag (setq _arrive_flag __arrive_flag)) _arrive_flag)
  (:serialization-length
   ()
   (+
    ;; std_msgs/String _collection_flag
    (send _collection_flag :serialization-length)
    ;; uint8 _point_n
    1
    ;; bool _arrive_flag
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/String _collection_flag
       (send _collection_flag :serialize s)
     ;; uint8 _point_n
       (write-byte _point_n s)
     ;; bool _arrive_flag
       (if _arrive_flag (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/String _collection_flag
     (send _collection_flag :deserialize buf ptr-) (incf ptr- (send _collection_flag :serialization-length))
   ;; uint8 _point_n
     (setq _point_n (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; bool _arrive_flag
     (setq _arrive_flag (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get offboard::information_collection_case :md5sum-) "79acd54d777973b93b9b56ccf8677846")
(setf (get offboard::information_collection_case :datatype-) "offboard/information_collection_case")
(setf (get offboard::information_collection_case :definition-)
      "##信息传输完成的标志位
std_msgs/String collection_flag  
uint8 point_n
##目标点到达的标志位
bool arrive_flag
================================================================================
MSG: std_msgs/String
string data

")



(provide :offboard/information_collection_case "79acd54d777973b93b9b56ccf8677846")


