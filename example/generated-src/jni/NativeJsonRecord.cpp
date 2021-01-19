// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from example.djinni

#include "NativeJsonRecord.hpp"  // my header
#include "JNIMarshal+Json.h"
#include "Marshal.hpp"
#include "NativeRc.hpp"

namespace djinni_generated {

NativeJsonRecord::NativeJsonRecord() = default;

NativeJsonRecord::~NativeJsonRecord() = default;

auto NativeJsonRecord::fromCpp(JNIEnv* jniEnv, const CppType& c) -> ::djinni::LocalRef<JniType> {
    const auto& data = ::djinni::JniClass<NativeJsonRecord>::get();
    auto r = ::djinni::LocalRef<JniType>{jniEnv->NewObject(data.clazz.get(), data.jconstructor,
                                                           ::djinni::get(::djinni::Optional<std::optional, ::djinni_generated::NativeRc>::fromCpp(jniEnv, c.optional_rc)))};
    ::djinni::jniExceptionCheck(jniEnv);
    return r;
}

auto NativeJsonRecord::toCpp(JNIEnv* jniEnv, JniType j) -> CppType {
    ::djinni::JniLocalScope jscope(jniEnv, 2);
    assert(j != nullptr);
    const auto& data = ::djinni::JniClass<NativeJsonRecord>::get();
    return {::djinni::Optional<std::optional, ::djinni_generated::NativeRc>::toCpp(jniEnv, jniEnv->GetObjectField(j, data.field_mOptionalRc))};
}

}  // namespace djinni_generated