// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from foo_containers.djinni

#pragma once

#include <atomic>
#include <experimental/optional>
#include "foo_containers_record.hpp"
#ifdef __cplusplus
extern "C" {
#endif

#include "dh__map_int8_t_list_date.h"

#ifdef __cplusplus
}
#endif
struct DjinniMapInt8TListDate {
    static djinni::Handle<DjinniObjectHandle> fromCpp(const std::unordered_map<int8_t, std::vector<std::chrono::system_clock::time_point>> & dc);
    static std::unordered_map<int8_t, std::vector<std::chrono::system_clock::time_point>> toCpp(djinni::Handle<DjinniObjectHandle> dh);
    static djinni::Handle<DjinniOptionalObjectHandle>fromCpp(std::experimental::optional<std::unordered_map<int8_t, std::vector<std::chrono::system_clock::time_point>>> dc);
    static std::experimental::optional<std::unordered_map<int8_t, std::vector<std::chrono::system_clock::time_point>>> toCpp(djinni::Handle<DjinniOptionalObjectHandle> dh);
};
