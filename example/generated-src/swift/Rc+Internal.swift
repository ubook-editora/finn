// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from example.djinni

import DjinniSwift
import Foundation

extension Rc  {
    @available(swift, obsoleted: 1.0)
    @objc public var __djinni__objc_a: Int32 {
        get {
            return a
        }
    }
    @available(swift, obsoleted: 1.0)
    @objc public var __djinni__objc_b: Int32 {
        get {
            return b
        }
    }
    @available(swift, obsoleted: 1.0)
    @objc public var __djinni__objc_c: NSNumber? {
        get {
            return DjinniSwift.I32.toObjc(e: c)
        }
    }
    @available(swift, obsoleted: 1.0)
    @objc public var __djinni__objc_d: MyEnum {
        get {
            return d
        }
    }
    @available(swift, obsoleted: 1.0)
    @objc public var __djinni__objc_e: Data {
        get {
            return e
        }
    }
    @available(swift, obsoleted: 1.0)
    @objc public static func `init`(a: Int32,
                                    b: Int32,
                                    c: NSNumber?,
                                    d: MyEnum,
                                    e: Data) -> Rc {
        return Rc.init(a: a,
                       b: b,
                       c: DjinniSwift.I32.fromObjc(e: c),
                       d: d,
                       e: e)}
}
