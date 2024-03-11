
(cl:in-package :asdf)

(defsystem "offboard-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "LLA" :depends-on ("_package_LLA"))
    (:file "_package_LLA" :depends-on ("_package"))
    (:file "information_collection_case" :depends-on ("_package_information_collection_case"))
    (:file "_package_information_collection_case" :depends-on ("_package"))
  ))