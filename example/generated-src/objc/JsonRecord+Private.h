// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from example.djinni

#import <DjinniExample/DjinniExample-Swift.h>
#include "json_record.hpp"

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@class JsonRecord;

namespace djinni_generated {

struct JsonRecordHelper
{
    using CppType = ::textsort::JsonRecord;
    using ObjcType = JsonRecord*;

    using Boxed = JsonRecordHelper;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCpp(const CppType& cpp);
};

}  // namespace djinni_generated