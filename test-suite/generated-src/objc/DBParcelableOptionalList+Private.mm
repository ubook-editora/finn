// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from parcelable.djinni

#import "DBParcelableOptionalList+Private.h"
#import "DJIMarshal+Private.h"
#include <cassert>

namespace djinni_generated {

auto ParcelableOptionalList::toCpp(ObjcType obj) -> CppType
{
    assert(obj);
    return {::djinni::Optional<std::experimental::optional, ::djinni::List<::djinni::String>>::toCpp(obj.optionalSet)};
}

auto ParcelableOptionalList::fromCpp(const CppType& cpp) -> ObjcType
{
    return [[DBParcelableOptionalList alloc] initWithOptionalSet:(::djinni::Optional<std::experimental::optional, ::djinni::List<::djinni::String>>::fromCpp(cpp.optional_set))];
}

}  // namespace djinni_generated
