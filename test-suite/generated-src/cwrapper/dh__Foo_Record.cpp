// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from foo_duplicate_file_creation.djinni

#include <iostream> // for debugging
#include <cassert>
#include "wrapper_marshal.hpp"
#include "Foo_Record.hpp"

#include "dh__Foo_Record.hpp"

static void(*s_py_callback_Foo_Record___delete)(DjinniRecordHandle * );
void Foo_Record_add_callback___delete(void(* ptr)(DjinniRecordHandle * )) {
    s_py_callback_Foo_Record___delete = ptr;
}

void Foo_Record___delete(DjinniRecordHandle * drh) {
    s_py_callback_Foo_Record___delete(drh);
}
void optional_Foo_Record___delete(DjinniOptionalRecordHandle * drh) {
    s_py_callback_Foo_Record___delete((DjinniRecordHandle *) drh); // can't static cast, find better way
}
static DjinniString * ( * s_py_callback_Foo_Record_get_Foo_Record_f1)(DjinniRecordHandle *);

void Foo_Record_add_callback_get_Foo_Record_f1(DjinniString *( * ptr)(DjinniRecordHandle *)) {
    s_py_callback_Foo_Record_get_Foo_Record_f1 = ptr;
}

static DjinniRecordHandle * ( * s_py_callback_Foo_Record_python_create_Foo_Record)(DjinniString *);

void Foo_Record_add_callback_python_create_Foo_Record(DjinniRecordHandle *( * ptr)(DjinniString *)) {
    s_py_callback_Foo_Record_python_create_Foo_Record = ptr;
}

djinni::Handle<DjinniRecordHandle> DjinniFooRecord::fromCpp(const ::testsuite::FooRecord& dr) {
    auto  _field_a = DjinniString::fromCpp(dr.a);

    djinni::Handle<DjinniRecordHandle> _aux(
        s_py_callback_Foo_Record_python_create_Foo_Record(
            _field_a.release()),
        Foo_Record___delete);
    return _aux;
}

::testsuite::FooRecord DjinniFooRecord::toCpp(djinni::Handle<DjinniRecordHandle> dh) {
    std::unique_ptr<DjinniString> _field_a(s_py_callback_Foo_Record_get_Foo_Record_f1(dh.get()));

    auto _aux = ::testsuite::FooRecord(
        DjinniString::toCpp(std::move( _field_a)));
    return _aux;
}

djinni::Handle<DjinniOptionalRecordHandle> DjinniFooRecord::fromCpp(std::experimental::optional<::testsuite::FooRecord> dc) {
    if (dc == std::experimental::nullopt) {
        return nullptr;
    }
    return djinni::optionals::toOptionalHandle(DjinniFooRecord::fromCpp(std::move(* dc)), optional_Foo_Record___delete);
}

std::experimental::optional<::testsuite::FooRecord>DjinniFooRecord::toCpp(djinni::Handle<DjinniOptionalRecordHandle> dh) {
     if (dh) {
        return std::experimental::optional<::testsuite::FooRecord>(DjinniFooRecord::toCpp(djinni::optionals::fromOptionalHandle(std::move(dh), Foo_Record___delete)));
    }
    return std::experimental::nullopt;
}
