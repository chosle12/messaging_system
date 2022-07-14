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
    from . import _threads
else:
    import _threads

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


priorities_none = _threads.priorities_none
priorities_low = _threads.priorities_low
priorities_normal = _threads.priorities_normal
priorities_high = _threads.priorities_high
priorities_top = _threads.priorities_top
class job(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, *args):
        _threads.job_swiginit(self, _threads.new_job(*args))
    __swig_destroy__ = _threads.delete_job

    def get_ptr(self):
        return _threads.job_get_ptr(self)

    def priority(self):
        return _threads.job_priority(self)

    def set_job_pool(self, job_pool):
        return _threads.job_set_job_pool(self, job_pool)

    def work(self, worker_priority):
        return _threads.job_work(self, worker_priority)

# Register job in _threads:
_threads.job_swigregister(job)

class job_pool(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self):
        _threads.job_pool_swiginit(self, _threads.new_job_pool())
    __swig_destroy__ = _threads.delete_job_pool

    def get_ptr(self):
        return _threads.job_pool_get_ptr(self)

    def push(self, new_job):
        return _threads.job_pool_push(self, new_job)

    def pop(self, *args):
        return _threads.job_pool_pop(self, *args)

    def contain(self, *args):
        return _threads.job_pool_contain(self, *args)

    def set_push_lock(self, lock):
        return _threads.job_pool_set_push_lock(self, lock)

    def append_notification(self, id, notification):
        return _threads.job_pool_append_notification(self, id, notification)

    def remove_notification(self, id):
        return _threads.job_pool_remove_notification(self, id)

    def check_empty(self):
        return _threads.job_pool_check_empty(self)

# Register job_pool in _threads:
_threads.job_pool_swigregister(job_pool)

class thread_worker(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, *args):
        _threads.thread_worker_swiginit(self, _threads.new_thread_worker(*args))
    __swig_destroy__ = _threads.delete_thread_worker

    def set_job_pool(self, job_pool):
        return _threads.thread_worker_set_job_pool(self, job_pool)

    def set_worker_notification(self, notification):
        return _threads.thread_worker_set_worker_notification(self, notification)

    def start(self):
        return _threads.thread_worker_start(self)

    def stop(self):
        return _threads.thread_worker_stop(self)

    def guid(self):
        return _threads.thread_worker_guid(self)

    def priority(self):
        return _threads.thread_worker_priority(self)

# Register thread_worker in _threads:
_threads.thread_worker_swigregister(thread_worker)

class thread_pool(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, *args):
        _threads.thread_pool_swiginit(self, _threads.new_thread_pool(*args))
    __swig_destroy__ = _threads.delete_thread_pool

    def start(self):
        return _threads.thread_pool_start(self)

    def append(self, worker, start=False):
        return _threads.thread_pool_append(self, worker, start)

    def stop(self, stop_immediately=True, jop_pool_lock=False):
        return _threads.thread_pool_stop(self, stop_immediately, jop_pool_lock)

    def push(self, job):
        return _threads.thread_pool_push(self, job)

# Register thread_pool in _threads:
_threads.thread_pool_swigregister(thread_pool)



