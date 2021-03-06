# AUTOGENERATED FILE - DO NOT MODIFY!
# This file generated by Djinni from foo_interface.djinni

from djinni.support import MultiSet # default imported in all files
from djinni.exception import CPyException # default imported in all files
from djinni.pycffi_marshal import CPyPrimitive, CPyString

from abc import ABCMeta, abstractmethod
from foo_primitives import FooPrimitives
from foo_primitives import FooPrimitivesHelper
from future.utils import with_metaclass
from PyCFFIlib_cffi import ffi, lib

from djinni import exception # this forces run of __init__.py which gives cpp option to call back into py to create exception

class FooInterface(with_metaclass(ABCMeta)):
    @abstractmethod
    def int32_inverse(self, x):
        raise NotImplementedError

    @abstractmethod
    def set_private_int32(self, private_int):
        raise NotImplementedError

    @abstractmethod
    def get_private_int32(self):
        raise NotImplementedError

    @abstractmethod
    def set_private_string(self, private_string):
        raise NotImplementedError

    @abstractmethod
    def get_private_string(self):
        raise NotImplementedError

    @abstractmethod
    def get_set_strings(self, ps1, ps2):
        raise NotImplementedError

    @abstractmethod
    def get_foo_primitives(self):
        raise NotImplementedError

    @staticmethod
    def create():
        return FooInterfaceCppProxy.create()

class FooInterfaceCppProxy(FooInterface):
    def __init__(self, proxy):
        self._is_cpp_proxy = True
        self._cpp_impl = proxy
    def __del__(self):
        if not lib:
            return
        lib.foo_interface___wrapper_dec_ref(self._cpp_impl)

    def int32_inverse(self, x):
        _ret_c = lib.cw__foo_interface_int32_inverse(self._cpp_impl, CPyPrimitive.fromPy(x))
        CPyException.toPyCheckAndRaise(_ret_c)
        _ret = CPyPrimitive.toPy(_ret_c)
        assert _ret is not None
        return _ret

    def set_private_int32(self, private_int):
        lib.cw__foo_interface_set_private_int32(self._cpp_impl, CPyPrimitive.fromPy(private_int))
        CPyException.toPyCheckAndRaise(ffi.NULL)

    def get_private_int32(self):
        _ret_c = lib.cw__foo_interface_get_private_int32(self._cpp_impl)
        CPyException.toPyCheckAndRaise(_ret_c)
        _ret = CPyPrimitive.toPy(_ret_c)
        assert _ret is not None
        return _ret

    def set_private_string(self, private_string):
        with CPyString.fromPy(private_string) as pys_private_string:
            lib.cw__foo_interface_set_private_string(self._cpp_impl, pys_private_string.release_djinni_string())
            CPyException.toPyCheckAndRaise(ffi.NULL)

    def get_private_string(self):
        _ret_c = lib.cw__foo_interface_get_private_string(self._cpp_impl)
        CPyException.toPyCheckAndRaise(_ret_c)
        _ret = CPyString.toPy(_ret_c)
        assert _ret is not None
        return _ret

    def get_set_strings(self, ps1, ps2):
        with CPyString.fromPy(ps1) as pys_ps1,\
                CPyString.fromPy(ps2) as pys_ps2:
            _ret_c = lib.cw__foo_interface_get_set_strings(self._cpp_impl, pys_ps1.release_djinni_string(), pys_ps2.release_djinni_string())
            CPyException.toPyCheckAndRaise(_ret_c)
            _ret = CPyString.toPy(_ret_c)
            assert _ret is not None
            return _ret

    @staticmethod
    def create():
        _ret_c = lib.cw__foo_interface_create()
        CPyException.toPyCheckAndRaise(_ret_c)
        _ret = FooInterfaceHelper.toPy(_ret_c)
        assert _ret is not None
        return _ret

    def get_foo_primitives(self):
        _ret_c = lib.cw__foo_interface_get_foo_primitives(self._cpp_impl)
        CPyException.toPyCheckAndRaise(_ret_c)
        _ret = FooPrimitivesHelper.toPy(_ret_c)
        assert _ret is not None
        return _ret

class FooInterfaceHelper:
    c_data_set = MultiSet()
    @staticmethod
    def toPy(obj):
        if obj == ffi.NULL:
            return None
        return FooInterfaceCppProxy(obj)

