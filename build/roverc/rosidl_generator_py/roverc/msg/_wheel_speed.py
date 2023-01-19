# generated from rosidl_generator_py/resource/_idl.py.em
# with input from roverc:msg/WheelSpeed.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_WheelSpeed(type):
    """Metaclass of message 'WheelSpeed'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('roverc')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'roverc.msg.WheelSpeed')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__wheel_speed
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__wheel_speed
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__wheel_speed
            cls._TYPE_SUPPORT = module.type_support_msg__msg__wheel_speed
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__wheel_speed

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class WheelSpeed(metaclass=Metaclass_WheelSpeed):
    """Message class 'WheelSpeed'."""

    __slots__ = [
        '_front_right',
        '_front_left',
        '_rear_right',
        '_rear_left',
    ]

    _fields_and_field_types = {
        'front_right': 'int8',
        'front_left': 'int8',
        'rear_right': 'int8',
        'rear_left': 'int8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.front_right = kwargs.get('front_right', int())
        self.front_left = kwargs.get('front_left', int())
        self.rear_right = kwargs.get('rear_right', int())
        self.rear_left = kwargs.get('rear_left', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.front_right != other.front_right:
            return False
        if self.front_left != other.front_left:
            return False
        if self.rear_right != other.rear_right:
            return False
        if self.rear_left != other.rear_left:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def front_right(self):
        """Message field 'front_right'."""
        return self._front_right

    @front_right.setter
    def front_right(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'front_right' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'front_right' field must be an integer in [-128, 127]"
        self._front_right = value

    @builtins.property
    def front_left(self):
        """Message field 'front_left'."""
        return self._front_left

    @front_left.setter
    def front_left(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'front_left' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'front_left' field must be an integer in [-128, 127]"
        self._front_left = value

    @builtins.property
    def rear_right(self):
        """Message field 'rear_right'."""
        return self._rear_right

    @rear_right.setter
    def rear_right(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'rear_right' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'rear_right' field must be an integer in [-128, 127]"
        self._rear_right = value

    @builtins.property
    def rear_left(self):
        """Message field 'rear_left'."""
        return self._rear_left

    @rear_left.setter
    def rear_left(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'rear_left' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'rear_left' field must be an integer in [-128, 127]"
        self._rear_left = value
