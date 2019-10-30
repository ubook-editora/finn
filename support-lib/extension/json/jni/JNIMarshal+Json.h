#include <jni.h>
#include "nlohmann/json.hpp"

namespace djinni {
    // For C++ <-> Objective-C
    struct Json
    {
        using json = nlohmann::json;
        using CppType =  json;
        using JniType = jobject;
        using Boxed = Json;

        static CppType toCpp(JNIEnv* env, JniType json_object) {
            jclass jsonObjectClass = env->FindClass("org/json/JSONObject");
            jmethodID toStringMethod = env->GetMethodID(jsonObjectClass, "toString", "()Ljava/lang/String;");
            auto stringValue_ = (jstring) env->CallObjectMethod(json_object, toStringMethod);
            const char *stringValueUTF = (env)->GetStringUTFChars(stringValue_, nullptr);

            std::string strVal_copy(stringValueUTF);
            
            json js = json(strVal_copy);

            env->ReleaseStringUTFChars(stringValue_, stringValueUTF);

            return js;
        }

        static LocalRef<JniType> fromCpp(JNIEnv *env, CppType src) {

            const char * jsonString = src.dump().c_str();

            jclass jsonObjectClass = env->FindClass("org/json/JSONObject");
            jmethodID constructorID = env->GetMethodID(jsonObjectClass,"<init>","(Ljava/lang/String;)V");

            jstring jsonJString = (env)->NewStringUTF(jsonString);

            jobject obj = (env)->NewObject(jsonObjectClass, constructorID, jsonJString);

            return {env, obj};
        }
    };
}