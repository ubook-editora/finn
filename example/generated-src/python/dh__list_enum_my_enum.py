# AUTOGENERATED FILE - DO NOT MODIFY!
# This file generated by Djinni from example.djinni

from djinni.support import MultiSet # default imported in all files
from djinni.exception import CPyException # default imported in all files
from djinni.pycffi_marshal import CPyEnum, CPyObject

from my_enum import MyEnum
from PyCFFIlib_cffi import ffi, lib

from djinni import exception # this forces run of __init__.py which gives cpp option to call back into py to create exception

class ListEnumMyEnumHelper:
    c_data_set = MultiSet()

    @staticmethod
    def check_c_data_set_empty():
        assert len(ListEnumMyEnumHelper.c_data_set) == 0
        MyEnum.check_c_data_set_empty()

    @ffi.callback("int(struct DjinniObjectHandle *, size_t)")
    def __get_elem(cself, index):
        try:
            _ret = CPyEnum.fromPy(CPyObject.toPy(None, cself)[index])
            assert _ret != -1
            return _ret
        except Exception as _djinni_py_e:
            CPyException.setExceptionFromPy(_djinni_py_e)
            return ffi.NULL

    @ffi.callback("size_t(struct DjinniObjectHandle *)")
    def __get_size(cself):
        return len(CPyObject.toPy(None, cself))

    @ffi.callback("struct DjinniObjectHandle *()")
    def __python_create():
        c_ptr = ffi.new_handle(list())
        ListEnumMyEnumHelper.c_data_set.add(c_ptr)
        return ffi.cast("struct DjinniObjectHandle *", c_ptr)

    @ffi.callback("void(struct DjinniObjectHandle *, int)")
    def __python_add(cself, el):
        CPyObject.toPy(None, cself).append(CPyEnum.toPy(MyEnum, el))

    @ffi.callback("void(struct DjinniObjectHandle * )")
    def __delete(c_ptr):
        assert c_ptr in ListEnumMyEnumHelper.c_data_set
        ListEnumMyEnumHelper.c_data_set.remove(c_ptr)

    @staticmethod
    def _add_callbacks():
        lib.list_enum_my_enum_add_callback__get_elem(ListEnumMyEnumHelper.__get_elem)
        lib.list_enum_my_enum_add_callback___delete(ListEnumMyEnumHelper.__delete)
        lib.list_enum_my_enum_add_callback__get_size(ListEnumMyEnumHelper.__get_size)
        lib.list_enum_my_enum_add_callback__python_create(ListEnumMyEnumHelper.__python_create)
        lib.list_enum_my_enum_add_callback__python_add(ListEnumMyEnumHelper.__python_add)

ListEnumMyEnumHelper._add_callbacks()

