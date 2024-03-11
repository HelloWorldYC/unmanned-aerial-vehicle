# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "offboard: 2 messages, 0 services")

set(MSG_I_FLAGS "-Ioffboard:/home/myc/offboard_ws/src/offboard/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(offboard_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/myc/offboard_ws/src/offboard/msg/information_collection_case.msg" NAME_WE)
add_custom_target(_offboard_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "offboard" "/home/myc/offboard_ws/src/offboard/msg/information_collection_case.msg" "std_msgs/String"
)

get_filename_component(_filename "/home/myc/offboard_ws/src/offboard/msg/LLA.msg" NAME_WE)
add_custom_target(_offboard_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "offboard" "/home/myc/offboard_ws/src/offboard/msg/LLA.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(offboard
  "/home/myc/offboard_ws/src/offboard/msg/information_collection_case.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/String.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/offboard
)
_generate_msg_cpp(offboard
  "/home/myc/offboard_ws/src/offboard/msg/LLA.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/offboard
)

### Generating Services

### Generating Module File
_generate_module_cpp(offboard
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/offboard
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(offboard_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(offboard_generate_messages offboard_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/myc/offboard_ws/src/offboard/msg/information_collection_case.msg" NAME_WE)
add_dependencies(offboard_generate_messages_cpp _offboard_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/myc/offboard_ws/src/offboard/msg/LLA.msg" NAME_WE)
add_dependencies(offboard_generate_messages_cpp _offboard_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(offboard_gencpp)
add_dependencies(offboard_gencpp offboard_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS offboard_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(offboard
  "/home/myc/offboard_ws/src/offboard/msg/information_collection_case.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/String.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/offboard
)
_generate_msg_eus(offboard
  "/home/myc/offboard_ws/src/offboard/msg/LLA.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/offboard
)

### Generating Services

### Generating Module File
_generate_module_eus(offboard
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/offboard
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(offboard_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(offboard_generate_messages offboard_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/myc/offboard_ws/src/offboard/msg/information_collection_case.msg" NAME_WE)
add_dependencies(offboard_generate_messages_eus _offboard_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/myc/offboard_ws/src/offboard/msg/LLA.msg" NAME_WE)
add_dependencies(offboard_generate_messages_eus _offboard_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(offboard_geneus)
add_dependencies(offboard_geneus offboard_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS offboard_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(offboard
  "/home/myc/offboard_ws/src/offboard/msg/information_collection_case.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/String.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/offboard
)
_generate_msg_lisp(offboard
  "/home/myc/offboard_ws/src/offboard/msg/LLA.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/offboard
)

### Generating Services

### Generating Module File
_generate_module_lisp(offboard
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/offboard
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(offboard_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(offboard_generate_messages offboard_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/myc/offboard_ws/src/offboard/msg/information_collection_case.msg" NAME_WE)
add_dependencies(offboard_generate_messages_lisp _offboard_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/myc/offboard_ws/src/offboard/msg/LLA.msg" NAME_WE)
add_dependencies(offboard_generate_messages_lisp _offboard_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(offboard_genlisp)
add_dependencies(offboard_genlisp offboard_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS offboard_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(offboard
  "/home/myc/offboard_ws/src/offboard/msg/information_collection_case.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/String.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/offboard
)
_generate_msg_nodejs(offboard
  "/home/myc/offboard_ws/src/offboard/msg/LLA.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/offboard
)

### Generating Services

### Generating Module File
_generate_module_nodejs(offboard
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/offboard
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(offboard_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(offboard_generate_messages offboard_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/myc/offboard_ws/src/offboard/msg/information_collection_case.msg" NAME_WE)
add_dependencies(offboard_generate_messages_nodejs _offboard_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/myc/offboard_ws/src/offboard/msg/LLA.msg" NAME_WE)
add_dependencies(offboard_generate_messages_nodejs _offboard_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(offboard_gennodejs)
add_dependencies(offboard_gennodejs offboard_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS offboard_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(offboard
  "/home/myc/offboard_ws/src/offboard/msg/information_collection_case.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/String.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/offboard
)
_generate_msg_py(offboard
  "/home/myc/offboard_ws/src/offboard/msg/LLA.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/offboard
)

### Generating Services

### Generating Module File
_generate_module_py(offboard
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/offboard
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(offboard_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(offboard_generate_messages offboard_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/myc/offboard_ws/src/offboard/msg/information_collection_case.msg" NAME_WE)
add_dependencies(offboard_generate_messages_py _offboard_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/myc/offboard_ws/src/offboard/msg/LLA.msg" NAME_WE)
add_dependencies(offboard_generate_messages_py _offboard_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(offboard_genpy)
add_dependencies(offboard_genpy offboard_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS offboard_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/offboard)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/offboard
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(offboard_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/offboard)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/offboard
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(offboard_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/offboard)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/offboard
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(offboard_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/offboard)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/offboard
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(offboard_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/offboard)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/offboard\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/offboard
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(offboard_generate_messages_py std_msgs_generate_messages_py)
endif()
