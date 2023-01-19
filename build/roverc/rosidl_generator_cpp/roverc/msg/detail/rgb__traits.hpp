// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from roverc:msg/RGB.idl
// generated code does not contain a copyright notice

#ifndef ROVERC__MSG__DETAIL__RGB__TRAITS_HPP_
#define ROVERC__MSG__DETAIL__RGB__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "roverc/msg/detail/rgb__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace roverc
{

namespace msg
{

inline void to_flow_style_yaml(
  const RGB & msg,
  std::ostream & out)
{
  out << "{";
  // member: red
  {
    out << "red: ";
    rosidl_generator_traits::value_to_yaml(msg.red, out);
    out << ", ";
  }

  // member: green
  {
    out << "green: ";
    rosidl_generator_traits::value_to_yaml(msg.green, out);
    out << ", ";
  }

  // member: blue
  {
    out << "blue: ";
    rosidl_generator_traits::value_to_yaml(msg.blue, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RGB & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: red
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "red: ";
    rosidl_generator_traits::value_to_yaml(msg.red, out);
    out << "\n";
  }

  // member: green
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "green: ";
    rosidl_generator_traits::value_to_yaml(msg.green, out);
    out << "\n";
  }

  // member: blue
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "blue: ";
    rosidl_generator_traits::value_to_yaml(msg.blue, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RGB & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace roverc

namespace rosidl_generator_traits
{

[[deprecated("use roverc::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const roverc::msg::RGB & msg,
  std::ostream & out, size_t indentation = 0)
{
  roverc::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use roverc::msg::to_yaml() instead")]]
inline std::string to_yaml(const roverc::msg::RGB & msg)
{
  return roverc::msg::to_yaml(msg);
}

template<>
inline const char * data_type<roverc::msg::RGB>()
{
  return "roverc::msg::RGB";
}

template<>
inline const char * name<roverc::msg::RGB>()
{
  return "roverc/msg/RGB";
}

template<>
struct has_fixed_size<roverc::msg::RGB>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<roverc::msg::RGB>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<roverc::msg::RGB>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROVERC__MSG__DETAIL__RGB__TRAITS_HPP_
