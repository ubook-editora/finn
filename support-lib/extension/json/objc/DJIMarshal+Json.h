#import <Foundation/Foundation.h>
#import <Djinni/json.hpp>

namespace djinni {
    // For C++ <-> Objective-C
    struct Json
    {
        using json = nlohmann::json;

        using CppType = json;
        using ObjcType = NSDictionary *;

        using Boxed = Json;
        
        static CppType toCpp(ObjcType dict) {
            NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dict options:0 error:nil];
            NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
            return json::parse([jsonString UTF8String]);
        }

        static ObjcType fromCpp(CppType json) {
            std::string jsonString = json.dump();
            std::vector<uint8_t> bytes(jsonString.begin(), jsonString.end());
            
            NSData *data = [NSData dataWithBytes:bytes.data() length:static_cast<NSUInteger>(bytes.size())];
            return [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableLeaves error:nil];
        }
    };
}
