// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from test.djinni

#include <iostream> // for debugging
#include <cassert>
#include "wrapper_marshal.hpp"
#include "conflict_user.hpp"

#include "cw__Conflict.hpp"
#include "dh__set_interface_Conflict.hpp"

static void(*s_py_callback_set_interface_Conflict___delete)(DjinniObjectHandle *);
void set_interface_Conflict_add_callback___delete(void(* ptr)(DjinniObjectHandle *)) {
    s_py_callback_set_interface_Conflict___delete = ptr;
}

void set_interface_Conflict___delete(DjinniObjectHandle * drh) {
    s_py_callback_set_interface_Conflict___delete(drh);
}
void optional_set_interface_Conflict___delete(DjinniOptionalObjectHandle *  drh) {
    s_py_callback_set_interface_Conflict___delete((DjinniObjectHandle *) drh);
}
static size_t ( * s_py_callback_set_interface_Conflict__get_size)(DjinniObjectHandle *);

void set_interface_Conflict_add_callback__get_size(size_t( * ptr)(DjinniObjectHandle *)) {
    s_py_callback_set_interface_Conflict__get_size = ptr;
}

static DjinniObjectHandle * ( * s_py_callback_set_interface_Conflict__python_create)(void);

void set_interface_Conflict_add_callback__python_create(DjinniObjectHandle *( * ptr)(void)) {
    s_py_callback_set_interface_Conflict__python_create = ptr;
}

static void ( * s_py_callback_set_interface_Conflict__python_add)(DjinniObjectHandle *, DjinniWrapperConflict *);

void set_interface_Conflict_add_callback__python_add(void( * ptr)(DjinniObjectHandle *, DjinniWrapperConflict *)) {
    s_py_callback_set_interface_Conflict__python_add = ptr;
}

static DjinniWrapperConflict * ( * s_py_callback_set_interface_Conflict__python_next)(DjinniObjectHandle *);

void set_interface_Conflict_add_callback__python_next(DjinniWrapperConflict *( * ptr)(DjinniObjectHandle *)) {
    s_py_callback_set_interface_Conflict__python_next = ptr;
}

djinni::Handle<DjinniObjectHandle> DjinniSetInterfaceConflict::fromCpp(const std::unordered_set<std::shared_ptr<::testsuite::Conflict>> & dc) {
    djinni::Handle<DjinniObjectHandle> _handle(s_py_callback_set_interface_Conflict__python_create(), & set_interface_Conflict___delete);
    for (const auto & it : dc) {
        auto _key_val = DjinniWrapperConflict::wrap(std::move(it));
        s_py_callback_set_interface_Conflict__python_add(_handle.get(), _key_val.release());
    }

    return _handle;
}

std::unordered_set<std::shared_ptr<::testsuite::Conflict>> DjinniSetInterfaceConflict::toCpp(djinni::Handle<DjinniObjectHandle> dh) {
    std::unordered_set<std::shared_ptr<::testsuite::Conflict>>_ret;
    size_t size = s_py_callback_set_interface_Conflict__get_size(dh.get());

    for (int i = 0; i < size; i++) {
        auto _el = DjinniWrapperConflict::get(djinni::Handle<DjinniWrapperConflict>(s_py_callback_set_interface_Conflict__python_next(dh.get()), Conflict___wrapper_dec_ref));
        _ret.insert(std::move(_el));
    }

    return _ret;
}

djinni::Handle<DjinniOptionalObjectHandle> DjinniSetInterfaceConflict::fromCpp(std::experimental::optional<std::unordered_set<std::shared_ptr<::testsuite::Conflict>>> dc) {
    if (dc == std::experimental::nullopt) {
        return nullptr;
    }
    return djinni::optionals::toOptionalHandle(DjinniSetInterfaceConflict::fromCpp(std::move(* dc)), optional_set_interface_Conflict___delete);
}

std::experimental::optional<std::unordered_set<std::shared_ptr<::testsuite::Conflict>>>DjinniSetInterfaceConflict::toCpp(djinni::Handle<DjinniOptionalObjectHandle> dh) {
     if (dh) {
        return std::experimental::optional<std::unordered_set<std::shared_ptr<::testsuite::Conflict>>>(DjinniSetInterfaceConflict::toCpp(djinni::optionals::fromOptionalHandle(std::move(dh), set_interface_Conflict___delete)));
    }
    return std::experimental::nullopt;
}

