#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "json.hpp"
#import "DJIMarshal+Json.h"
#import "DJICppWrapperCache+Private.h"
#import "DJIError.h"
#import "DJIMarshal+Private.h"
#import "DJIObjcWrapperCache+Private.h"
#import "proxy_cache_impl.hpp"
#import "proxy_cache_interface.hpp"

FOUNDATION_EXPORT double DjinniVersionNumber;
FOUNDATION_EXPORT const unsigned char DjinniVersionString[];

