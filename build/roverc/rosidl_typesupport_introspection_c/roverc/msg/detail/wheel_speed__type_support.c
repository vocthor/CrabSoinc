// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from roverc:msg/WheelSpeed.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "roverc/msg/detail/wheel_speed__rosidl_typesupport_introspection_c.h"
#include "roverc/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "roverc/msg/detail/wheel_speed__functions.h"
#include "roverc/msg/detail/wheel_speed__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void roverc__msg__WheelSpeed__rosidl_typesupport_introspection_c__WheelSpeed_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  roverc__msg__WheelSpeed__init(message_memory);
}

void roverc__msg__WheelSpeed__rosidl_typesupport_introspection_c__WheelSpeed_fini_function(void * message_memory)
{
  roverc__msg__WheelSpeed__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember roverc__msg__WheelSpeed__rosidl_typesupport_introspection_c__WheelSpeed_message_member_array[4] = {
  {
    "front_right",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(roverc__msg__WheelSpeed, front_right),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "front_left",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(roverc__msg__WheelSpeed, front_left),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "rear_right",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(roverc__msg__WheelSpeed, rear_right),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "rear_left",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(roverc__msg__WheelSpeed, rear_left),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers roverc__msg__WheelSpeed__rosidl_typesupport_introspection_c__WheelSpeed_message_members = {
  "roverc__msg",  // message namespace
  "WheelSpeed",  // message name
  4,  // number of fields
  sizeof(roverc__msg__WheelSpeed),
  roverc__msg__WheelSpeed__rosidl_typesupport_introspection_c__WheelSpeed_message_member_array,  // message members
  roverc__msg__WheelSpeed__rosidl_typesupport_introspection_c__WheelSpeed_init_function,  // function to initialize message memory (memory has to be allocated)
  roverc__msg__WheelSpeed__rosidl_typesupport_introspection_c__WheelSpeed_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t roverc__msg__WheelSpeed__rosidl_typesupport_introspection_c__WheelSpeed_message_type_support_handle = {
  0,
  &roverc__msg__WheelSpeed__rosidl_typesupport_introspection_c__WheelSpeed_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_roverc
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, roverc, msg, WheelSpeed)() {
  if (!roverc__msg__WheelSpeed__rosidl_typesupport_introspection_c__WheelSpeed_message_type_support_handle.typesupport_identifier) {
    roverc__msg__WheelSpeed__rosidl_typesupport_introspection_c__WheelSpeed_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &roverc__msg__WheelSpeed__rosidl_typesupport_introspection_c__WheelSpeed_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
