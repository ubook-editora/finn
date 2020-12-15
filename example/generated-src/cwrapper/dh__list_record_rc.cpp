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

static void(*s_py_callback_list_record_rc___delete)(DjinniObjectHandle *);
void list_record_rc_add_callback___delete(void(* ptr)(DjinniObjectHandle *)) {
    s_py_callback_list_record_rc___delete = ptr;
}

void list_record_rc___delete(DjinniObjectHandle * drh) {
    s_py_callback_list_record_rc___delete(drh);
}
void optional_list_record_rc___delete(DjinniOptionalObjectHandle *  drh) {
    s_py_callback_list_record_rc___delete((DjinniObjectHandle *) drh);
}
static DjinniRecordHandle * ( * s_py_callback_list_record_rc__get_elem)(DjinniObjectHandle *, size_t);

void list_record_rc_add_callback__get_elem(DjinniRecordHandle *( * ptr)(DjinniObjectHandle *, size_t)) {
    s_py_callback_list_record_rc__get_elem = ptr;
}

static size_t ( * s_py_callback_list_record_rc__get_size)(DjinniObjectHandle *);

void list_record_rc_add_callback__get_size(size_t( * ptr)(DjinniObjectHandle *)) {
    s_py_callback_list_record_rc__get_size = ptr;
}

static DjinniObjectHandle * ( * s_py_callback_list_record_rc__python_create)(void);

void list_record_rc_add_callback__python_create(DjinniObjectHandle *( * ptr)(void)) {
    s_py_callback_list_record_rc__python_create = ptr;
}

static void ( * s_py_callback_list_record_rc__python_add)(DjinniObjectHandle *, DjinniRecordHandle *);

void list_record_rc_add_callback__python_add(void( * ptr)(DjinniObjectHandle *, DjinniRecordHandle *)) {
    s_py_callback_list_record_rc__python_add = ptr;
}

djinni::Handle<DjinniObjectHandle> DjinniListRecordRc::fromCpp(const std::vector<::textsort::Rc> & dc) {
    djinni::Handle<DjinniObjectHandle> _handle(s_py_callback_list_record_rc__python_create(), & list_record_rc___delete);
    size_t size = dc.size();
    for (int i = 0; i < size; i++) {
        auto _el = DjinniRc::fromCpp(dc[i]);
        s_py_callback_list_record_rc__python_add(_handle.get(), _el.release());
    }

    return _handle;
}

std::vector<::textsort::Rc> DjinniListRecordRc::toCpp(djinni::Handle<DjinniObjectHandle> dh) {
    std::vector<::textsort::Rc>_ret;
    size_t size = s_py_callback_list_record_rc__get_size(dh.get());
    _ret.reserve(size);

    for (int i = 0; i < size; i++) {
        _ret.push_back(DjinniRc::toCpp(djinni::Handle<DjinniRecordHandle>(s_py_callback_list_record_rc__get_elem(dh.get(), i), rc___delete)));
    }

    return _ret;
}

djinni::Handle<DjinniOptionalObjectHandle> DjinniListRecordRc::fromCpp(std::optional<std::vector<::textsort::Rc>> dc) {
    if (dc == std::nullopt) {
        return nullptr;
    }
    return djinni::optionals::toOptionalHandle(DjinniListRecordRc::fromCpp(std::move(* dc)), optional_list_record_rc___delete);
}

std::optional<std::vector<::textsort::Rc>>DjinniListRecordRc::toCpp(djinni::Handle<DjinniOptionalObjectHandle> dh) {
     if (dh) {
        return std::optional<std::vector<::textsort::Rc>>(DjinniListRecordRc::toCpp(djinni::optionals::fromOptionalHandle(std::move(dh), list_record_rc___delete)));
    }
    return std::nullopt;
}

