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
    from . import _utilities
else:
    import _utilities

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


logging_level_exception = _utilities.logging_level_exception
logging_level_error = _utilities.logging_level_error
logging_level_information = _utilities.logging_level_information
logging_level_sequence = _utilities.logging_level_sequence
logging_level_parameter = _utilities.logging_level_parameter
logging_level_packet = _utilities.logging_level_packet
class logger(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined")
    __repr__ = _swig_repr
    __swig_destroy__ = _utilities.delete_logger

    def start(self, *args):
        return _utilities.logger_start(self, *args)

    def stop(self):
        return _utilities.logger_stop(self)

    def set_target_level(self, target_level):
        return _utilities.logger_set_target_level(self, target_level)

    def set_write_console(self, write_console, write_console_only=False):
        return _utilities.logger_set_write_console(self, write_console, write_console_only)

    def set_write_date(self, write_date):
        return _utilities.logger_set_write_date(self, write_date)

    def set_limit_log_file_size(self, limit_log_file_size):
        return _utilities.logger_set_limit_log_file_size(self, limit_log_file_size)

    def set_backup_notification(self, notification):
        return _utilities.logger_set_backup_notification(self, notification)

    def chrono_start(self):
        return _utilities.logger_chrono_start(self)

    def write(self, *args):
        return _utilities.logger_write(self, *args)

    @staticmethod
    def handle():
        return _utilities.logger_handle()

# Register logger in _utilities:
_utilities.logger_swigregister(logger)

def logger_handle():
    return _utilities.logger_handle()

class cryptor(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    @staticmethod
    def create_key():
        return _utilities.cryptor_create_key()

    @staticmethod
    def encryption(original_data, key, iv):
        return _utilities.cryptor_encryption(original_data, key, iv)

    @staticmethod
    def decryption(encrypted_data, key, iv):
        return _utilities.cryptor_decryption(encrypted_data, key, iv)

    def __init__(self):
        _utilities.cryptor_swiginit(self, _utilities.new_cryptor())
    __swig_destroy__ = _utilities.delete_cryptor

# Register cryptor in _utilities:
_utilities.cryptor_swigregister(cryptor)

def cryptor_create_key():
    return _utilities.cryptor_create_key()

def cryptor_encryption(original_data, key, iv):
    return _utilities.cryptor_encryption(original_data, key, iv)

def cryptor_decryption(encrypted_data, key, iv):
    return _utilities.cryptor_decryption(encrypted_data, key, iv)

class compressor(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    @staticmethod
    def compression(original_data, block_bytes=1024, hide_log=True):
        return _utilities.compressor_compression(original_data, block_bytes, hide_log)

    @staticmethod
    def decompression(compressed_data, block_bytes=1024, hide_log=True):
        return _utilities.compressor_decompression(compressed_data, block_bytes, hide_log)

    def __init__(self):
        _utilities.compressor_swiginit(self, _utilities.new_compressor())
    __swig_destroy__ = _utilities.delete_compressor

# Register compressor in _utilities:
_utilities.compressor_swigregister(compressor)

def compressor_compression(original_data, block_bytes=1024, hide_log=True):
    return _utilities.compressor_compression(original_data, block_bytes, hide_log)

def compressor_decompression(compressed_data, block_bytes=1024, hide_log=True):
    return _utilities.compressor_decompression(compressed_data, block_bytes, hide_log)

class combiner(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    @staticmethod
    def append(result, source):
        return _utilities.combiner_append(result, source)

    @staticmethod
    def divide(source, index):
        return _utilities.combiner_divide(source, index)

    def __init__(self):
        _utilities.combiner_swiginit(self, _utilities.new_combiner())
    __swig_destroy__ = _utilities.delete_combiner

# Register combiner in _utilities:
_utilities.combiner_swigregister(combiner)

def combiner_append(result, source):
    return _utilities.combiner_append(result, source)

def combiner_divide(source, index):
    return _utilities.combiner_divide(source, index)



