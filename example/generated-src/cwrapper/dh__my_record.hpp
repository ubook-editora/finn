// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from example.djinni

#pragma once

#include <atomic>
#include <optional>
#include "my_record.hpp"
#ifdef __cplusplus
extern "C" {
#endif

#include "dh__my_record.h"

#ifdef __cplusplus
}
#endif
struct DjinniMyRecord {
    static djinni::Handle<DjinniRecordHandle> fromCpp(const ::textsort::MyRecord& dr);
    static ::textsort::MyRecord toCpp(djinni::Handle<DjinniRecordHandle> dh);
    static djinni::Handle<DjinniOptionalRecordHandle> fromCpp(std::optional<::textsort::MyRecord> dc);
    static std::optional<::textsort::MyRecord> toCpp(djinni::Handle<DjinniOptionalRecordHandle> dh);
};
