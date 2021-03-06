// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from example.djinni

#include "NativeHello.hpp"  // my header
#include "NativeMyEnum.hpp"
#include "NativeMyRecord.hpp"

namespace djinni_generated {

NativeHello::NativeHello() : ::djinni::JniInterface<::textsort::Hello, NativeHello>("com/dropbox/textsort/Hello$CppProxy") {}

NativeHello::~NativeHello() = default;


CJNIEXPORT void JNICALL Java_com_dropbox_textsort_Hello_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::textsort::Hello>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_com_dropbox_textsort_Hello_00024CppProxy_create(JNIEnv* jniEnv, jobject /*this*/)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        auto r = ::textsort::Hello::create();
        return ::djinni::release(::djinni_generated::NativeHello::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jobject JNICALL Java_com_dropbox_textsort_Hello_00024CppProxy_native_1sayHi(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::textsort::Hello>(nativeRef);
        auto r = ref->say_hi();
        return ::djinni::release(::djinni_generated::NativeMyEnum::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jobject JNICALL Java_com_dropbox_textsort_Hello_00024CppProxy_native_1print(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_rc)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::textsort::Hello>(nativeRef);
        auto r = ref->print(::djinni_generated::NativeMyRecord::toCpp(jniEnv, j_rc));
        return ::djinni::release(::djinni_generated::NativeMyRecord::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

}  // namespace djinni_generated
