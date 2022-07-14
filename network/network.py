# This file was automatically generated by SWIG (http://www.swig.org).
# Version 4.0.2
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info
if _swig_python_version_info < (2, 7, 0):
    raise RuntimeError("Python 2.7 or later required")

# Import the low-level C/C++ module
if __package__ or "." in __name__:
    from . import _network
else:
    import _network

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__

def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)


def _swig_setattr_nondynamic_instance_variable(set):
    def set_instance_attr(self, name, value):
        if name == "thisown":
            self.this.own(value)
        elif name == "this":
            set(self, name, value)
        elif hasattr(self, name) and isinstance(getattr(type(self), name), property):
            set(self, name, value)
        else:
            raise AttributeError("You cannot add instance attributes to %s" % self)
    return set_instance_attr


def _swig_setattr_nondynamic_class_variable(set):
    def set_class_attr(cls, name, value):
        if hasattr(cls, name) and not isinstance(getattr(cls, name), property):
            set(cls, name, value)
        else:
            raise AttributeError("You cannot add class attributes to %s" % cls)
    return set_class_attr


def _swig_add_metaclass(metaclass):
    """Class decorator for adding a metaclass to a SWIG wrapped class - a slimmed down version of six.add_metaclass"""
    def wrapper(cls):
        return metaclass(cls.__name__, cls.__bases__, cls.__dict__.copy())
    return wrapper


class _SwigNonDynamicMeta(type):
    """Meta class to enforce nondynamic attributes (no new attributes) for a class"""
    __setattr__ = _swig_setattr_nondynamic_class_variable(type.__setattr__)


value_types_null_value = _network.value_types_null_value
value_types_bool_value = _network.value_types_bool_value
value_types_short_value = _network.value_types_short_value
value_types_ushort_value = _network.value_types_ushort_value
value_types_int_value = _network.value_types_int_value
value_types_uint_value = _network.value_types_uint_value
value_types_long_value = _network.value_types_long_value
value_types_ulong_value = _network.value_types_ulong_value
value_types_llong_value = _network.value_types_llong_value
value_types_ullong_value = _network.value_types_ullong_value
value_types_float_value = _network.value_types_float_value
value_types_double_value = _network.value_types_double_value
value_types_bytes_value = _network.value_types_bytes_value
value_types_string_value = _network.value_types_string_value
value_types_container_value = _network.value_types_container_value

def convert_value_type(*args):
    return _network.convert_value_type(*args)
class value(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, *args):
        _network.value_swiginit(self, _network.new_value(*args))
    __swig_destroy__ = _network.delete_value

    def get_ptr(self):
        return _network.value_get_ptr(self)

    def set_parent(self, parent):
        return _network.value_set_parent(self, parent)

    def set_data(self, *args):
        return _network.value_set_data(self, *args)

    def name(self):
        return _network.value_name(self)

    def type(self):
        return _network.value_type(self)

    def data(self):
        return _network.value_data(self)

    def size(self):
        return _network.value_size(self)

    def parent(self):
        return _network.value_parent(self)

    def child_count(self):
        return _network.value_child_count(self)

    def children(self, only_container=False):
        return _network.value_children(self, only_container)

    def add(self, *args):
        return _network.value_add(self, *args)

    def remove(self, *args):
        return _network.value_remove(self, *args)

    def remove_all(self):
        return _network.value_remove_all(self)

    def value_array(self, key):
        return _network.value_value_array(self, key)

    def to_bytes(self):
        return _network.value_to_bytes(self)

    def is_null(self):
        return _network.value_is_null(self)

    def is_bytes(self):
        return _network.value_is_bytes(self)

    def is_boolean(self):
        return _network.value_is_boolean(self)

    def is_numeric(self):
        return _network.value_is_numeric(self)

    def is_string(self):
        return _network.value_is_string(self)

    def is_container(self):
        return _network.value_is_container(self)

    def to_xml(self):
        return _network.value_to_xml(self)

    def to_json(self):
        return _network.value_to_json(self)

    def serialize(self):
        return _network.value_serialize(self)

    def to_boolean(self):
        return _network.value_to_boolean(self)

    def to_short(self):
        return _network.value_to_short(self)

    def to_ushort(self):
        return _network.value_to_ushort(self)

    def to_int(self):
        return _network.value_to_int(self)

    def to_uint(self):
        return _network.value_to_uint(self)

    def to_long(self):
        return _network.value_to_long(self)

    def to_ulong(self):
        return _network.value_to_ulong(self)

    def to_llong(self):
        return _network.value_to_llong(self)

    def to_ullong(self):
        return _network.value_to_ullong(self)

    def to_float(self):
        return _network.value_to_float(self)

    def to_double(self):
        return _network.value_to_double(self)

    def to_string(self, original=True):
        return _network.value_to_string(self, original)

# Register value in _network:
_network.value_swigregister(value)

class value_container(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, *args):
        _network.value_container_swiginit(self, _network.new_value_container(*args))
    __swig_destroy__ = _network.delete_value_container

    def get_ptr(self):
        return _network.value_container_get_ptr(self)

    def set_source(self, source_id, source_sub_id):
        return _network.value_container_set_source(self, source_id, source_sub_id)

    def set_target(self, *args):
        return _network.value_container_set_target(self, *args)

    def set_message_type(self, message_type):
        return _network.value_container_set_message_type(self, message_type)

    def set_units(self, target_values):
        return _network.value_container_set_units(self, target_values)

    def swap_header(self):
        return _network.value_container_swap_header(self)

    def clear_value(self):
        return _network.value_container_clear_value(self)

    def copy(self, containing_values=True):
        return _network.value_container_copy(self, containing_values)

    def source_id(self):
        return _network.value_container_source_id(self)

    def source_sub_id(self):
        return _network.value_container_source_sub_id(self)

    def target_id(self):
        return _network.value_container_target_id(self)

    def target_sub_id(self):
        return _network.value_container_target_sub_id(self)

    def message_type(self):
        return _network.value_container_message_type(self)

    def add(self, *args):
        return _network.value_container_add(self, *args)

    def remove(self, *args):
        return _network.value_container_remove(self, *args)

    def value_array(self, target_name):
        return _network.value_container_value_array(self, target_name)

    def get_value(self, target_name, index=0):
        return _network.value_container_get_value(self, target_name, index)

    def initialize(self):
        return _network.value_container_initialize(self)

    def serialize(self):
        return _network.value_container_serialize(self)

    def serialize_array(self):
        return _network.value_container_serialize_array(self)

    def deserialize(self, *args):
        return _network.value_container_deserialize(self, *args)

    def to_xml(self):
        return _network.value_container_to_xml(self)

    def to_json(self):
        return _network.value_container_to_json(self)

    def datas(self):
        return _network.value_container_datas(self)

    def load_packet(self, file_path):
        return _network.value_container_load_packet(self, file_path)

    def save_packet(self, file_path):
        return _network.value_container_save_packet(self, file_path)

# Register value_container in _network:
_network.value_container_swigregister(value_container)

session_types_message_line = _network.session_types_message_line
session_types_file_line = _network.session_types_file_line
session_types_binary_line = _network.session_types_binary_line
connection_conditions_waiting = _network.connection_conditions_waiting
connection_conditions_expired = _network.connection_conditions_expired
connection_conditions_confirmed = _network.connection_conditions_confirmed
class data_handling(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _network.delete_data_handling

# Register data_handling in _network:
_network.data_handling_swigregister(data_handling)

class messaging_client(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, source_id, start_code_value=231, end_code_value=67):
        _network.messaging_client_swiginit(self, _network.new_messaging_client(source_id, start_code_value, end_code_value))
    __swig_destroy__ = _network.delete_messaging_client

    def get_ptr(self):
        return _network.messaging_client_get_ptr(self)

    def source_id(self):
        return _network.messaging_client_source_id(self)

    def source_sub_id(self):
        return _network.messaging_client_source_sub_id(self)

    def set_auto_echo(self, auto_echo, echo_interval):
        return _network.messaging_client_set_auto_echo(self, auto_echo, echo_interval)

    def set_bridge_line(self, bridge_line):
        return _network.messaging_client_set_bridge_line(self, bridge_line)

    def set_encrypt_mode(self, encrypt_mode):
        return _network.messaging_client_set_encrypt_mode(self, encrypt_mode)

    def set_compress_mode(self, compress_mode):
        return _network.messaging_client_set_compress_mode(self, compress_mode)

    def set_compress_block_size(self, compress_block_size):
        return _network.messaging_client_set_compress_block_size(self, compress_block_size)

    def set_session_types(self, session_type):
        return _network.messaging_client_set_session_types(self, session_type)

    def set_connection_key(self, connection_key):
        return _network.messaging_client_set_connection_key(self, connection_key)

    def set_snipping_targets(self, snipping_targets):
        return _network.messaging_client_set_snipping_targets(self, snipping_targets)

    def set_connection_notification(self, notification):
        return _network.messaging_client_set_connection_notification(self, notification)

    def set_message_notification(self, notification):
        return _network.messaging_client_set_message_notification(self, notification)

    def set_file_notification(self, notification):
        return _network.messaging_client_set_file_notification(self, notification)

    def set_binary_notification(self, notification):
        return _network.messaging_client_set_binary_notification(self, notification)

    def get_confirm_status(self):
        return _network.messaging_client_get_confirm_status(self)

    def start(self, ip, port, high_priority=8, normal_priority=8, low_priority=8):
        return _network.messaging_client_start(self, ip, port, high_priority, normal_priority, low_priority)

    def stop(self):
        return _network.messaging_client_stop(self)

    def echo(self):
        return _network.messaging_client_echo(self)

    def send(self, *args):
        return _network.messaging_client_send(self, *args)

    def send_files(self, *args):
        return _network.messaging_client_send_files(self, *args)

    def send_binary(self, target_id, target_sub_id, data):
        return _network.messaging_client_send_binary(self, target_id, target_sub_id, data)

# Register messaging_client in _network:
_network.messaging_client_swigregister(messaging_client)

class messaging_server(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, source_id, start_code_value=231, end_code_value=67):
        _network.messaging_server_swiginit(self, _network.new_messaging_server(source_id, start_code_value, end_code_value))
    __swig_destroy__ = _network.delete_messaging_server

    def get_ptr(self):
        return _network.messaging_server_get_ptr(self)

    def set_encrypt_mode(self, encrypt_mode):
        return _network.messaging_server_set_encrypt_mode(self, encrypt_mode)

    def set_compress_mode(self, compress_mode):
        return _network.messaging_server_set_compress_mode(self, compress_mode)

    def set_compress_block_size(self, compress_block_size):
        return _network.messaging_server_set_compress_block_size(self, compress_block_size)

    def set_drop_connection_time(self, drop_connection_time):
        return _network.messaging_server_set_drop_connection_time(self, drop_connection_time)

    def set_connection_key(self, connection_key):
        return _network.messaging_server_set_connection_key(self, connection_key)

    def set_acceptable_target_ids(self, acceptable_target_ids):
        return _network.messaging_server_set_acceptable_target_ids(self, acceptable_target_ids)

    def set_ignore_target_ids(self, ignore_target_ids):
        return _network.messaging_server_set_ignore_target_ids(self, ignore_target_ids)

    def set_ignore_snipping_targets(self, ignore_snipping_targets):
        return _network.messaging_server_set_ignore_snipping_targets(self, ignore_snipping_targets)

    def set_possible_session_types(self, possible_session_types):
        return _network.messaging_server_set_possible_session_types(self, possible_session_types)

    def set_session_limit_count(self, session_limit_count):
        return _network.messaging_server_set_session_limit_count(self, session_limit_count)

    def set_connection_notification(self, notification):
        return _network.messaging_server_set_connection_notification(self, notification)

    def set_message_notification(self, notification):
        return _network.messaging_server_set_message_notification(self, notification)

    def set_file_notification(self, notification):
        return _network.messaging_server_set_file_notification(self, notification)

    def set_binary_notification(self, notification):
        return _network.messaging_server_set_binary_notification(self, notification)

    def start(self, port, high_priority=8, normal_priority=8, low_priority=8):
        return _network.messaging_server_start(self, port, high_priority, normal_priority, low_priority)

    def wait_stop(self, seconds=0):
        return _network.messaging_server_wait_stop(self, seconds)

    def stop(self):
        return _network.messaging_server_stop(self)

    def disconnect(self, target_id, target_sub_id):
        return _network.messaging_server_disconnect(self, target_id, target_sub_id)

    def echo(self):
        return _network.messaging_server_echo(self)

    def send(self, *args):
        return _network.messaging_server_send(self, *args)

    def send_files(self, *args):
        return _network.messaging_server_send_files(self, *args)

    def send_binary(self, *args):
        return _network.messaging_server_send_binary(self, *args)

# Register messaging_server in _network:
_network.messaging_server_swigregister(messaging_server)



