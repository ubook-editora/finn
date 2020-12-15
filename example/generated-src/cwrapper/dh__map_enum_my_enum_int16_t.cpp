// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from example.djinni

#include <iostream> // for debugging
#include <cassert>
#include "wrapper_marshal.hpp"
#include "my_record.hpp"

#include "dh__list_binary.hpp"
#include "dh__list_enum_my_enum.hpp"
#include "dh__list_int32_t.hpp"
#include "dh__list_record_rc.hpp"
#include "dh__map_enum_my_enum_int16_t.hpp"
#include "dh__map_int32_t_string.hpp"
#include "dh__my_enum.hpp"
#include "dh__my_record.hpp"
#include "dh__rc.hpp"
#include "dh__set_enum_my_enum.hpp"
#include "dh__set_int32_t.hpp"
#include "my_enum.hpp"
#include <chrono>
#include <optional>
#include <vector>

static void(*s_py_callback_map_enum_my_enum_int16_t___delete)(DjinniObjectHandle *);
void map_enum_my_enum_int16_t_add_callback___delete(void(* ptr)(DjinniObjectHandle *)) {
    s_py_callback_map_enum_my_enum_int16_t___delete = ptr;
}

void map_enum_my_enum_int16_t___delete(DjinniObjectHandle * drh) {
    s_py_callback_map_enum_my_enum_int16_t___delete(drh);
}
void optional_map_enum_my_enum_int16_t___delete(DjinniOptionalObjectHandle *  drh) {
    s_py_callback_map_enum_my_enum_int16_t___delete((DjinniObjectHandle *) drh);
}
static int16_t ( * s_py_callback_map_enum_my_enum_int16_t__get_value)(DjinniObjectHandle *, int);

void map_enum_my_enum_int16_t_add_callback__get_value(int16_t( * ptr)(DjinniObjectHandle *, int)) {
    s_py_callback_map_enum_my_enum_int16_t__get_value = ptr;
}

static size_t ( * s_py_callback_map_enum_my_enum_int16_t__get_size)(DjinniObjectHandle *);

void map_enum_my_enum_int16_t_add_callback__get_size(size_t( * ptr)(DjinniObjectHandle *)) {
    s_py_callback_map_enum_my_enum_int16_t__get_size = ptr;
}

static DjinniObjectHandle * ( * s_py_callback_map_enum_my_enum_int16_t__python_create)(void);

void map_enum_my_enum_int16_t_add_callback__python_create(DjinniObjectHandle *( * ptr)(void)) {
    s_py_callback_map_enum_my_enum_int16_t__python_create = ptr;
}

static void ( * s_py_callback_map_enum_my_enum_int16_t__python_add)(DjinniObjectHandle *, int, int16_t);

void map_enum_my_enum_int16_t_add_callback__python_add(void( * ptr)(DjinniObjectHandle *, int, int16_t)) {
    s_py_callback_map_enum_my_enum_int16_t__python_add = ptr;
}

static int ( * s_py_callback_map_enum_my_enum_int16_t__python_next)(DjinniObjectHandle *);

void map_enum_my_enum_int16_t_add_callback__python_next(int( * ptr)(DjinniObjectHandle *)) {
    s_py_callback_map_enum_my_enum_int16_t__python_next = ptr;
}

djinni::Handle<DjinniObjectHandle> DjinniMapEnumMyEnumInt16T::fromCpp(const std::unordered_map<::textsort::my_enum, int16_t> & dc) {
    djinni::Handle<DjinniObjectHandle> _handle(s_py_callback_map_enum_my_enum_int16_t__python_create(), & map_enum_my_enum_int16_t___delete);
    for (const auto & it : dc) {
        s_py_callback_map_enum_my_enum_int16_t__python_add(_handle.get(), int32_from_enum_my_enum(it.first), it.second);
    }

    return _handle;
}

std::unordered_map<::textsort::my_enum, int16_t> DjinniMapEnumMyEnumInt16T::toCpp(djinni::Handle<DjinniObjectHandle> dh) {
    std::unordered_map<::textsort::my_enum, int16_t>_ret;
    size_t size = s_py_callback_map_enum_my_enum_int16_t__get_size(dh.get());

    for (int i = 0; i < size; i++) {
        auto _key_c = s_py_callback_map_enum_my_enum_int16_t__python_next(dh.get()); // key that would potentially be surrounded by unique pointer
        auto _val = s_py_callback_map_enum_my_enum_int16_t__get_value(dh.get(), _key_c);

        auto _key = static_cast<::textsort::my_enum>(_key_c);
        _ret.emplace(std::move(_key), std::move(_val));
    }

    return _ret;
}

djinni::Handle<DjinniOptionalObjectHandle> DjinniMapEnumMyEnumInt16T::fromCpp(std::optional<std::unordered_map<::textsort::my_enum, int16_t>> dc) {
    if (dc == std::nullopt) {
        return nullptr;
    }
    return djinni::optionals::toOptionalHandle(DjinniMapEnumMyEnumInt16T::fromCpp(std::move(* dc)), optional_map_enum_my_enum_int16_t___delete);
}

std::optional<std::unordered_map<::textsort::my_enum, int16_t>>DjinniMapEnumMyEnumInt16T::toCpp(djinni::Handle<DjinniOptionalObjectHandle> dh) {
     if (dh) {
        return std::optional<std::unordered_map<::textsort::my_enum, int16_t>>(DjinniMapEnumMyEnumInt16T::toCpp(djinni::optionals::fromOptionalHandle(std::move(dh), map_enum_my_enum_int16_t___delete)));
    }
    return std::nullopt;
}

