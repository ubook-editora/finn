//
//  DJIMarshal+Swift.swift
//  DjinniExample
//
//  Created by Hien Nguyen on 25/08/2020.
//  Copyright © 2020 Fossil. All rights reserved.
//

import Foundation

public protocol DjinniRepresentable {
    associatedtype Swift : Hashable
    associatedtype Objc : Hashable
    
    static func toObjc(e: Swift) -> Objc
    
    static func toObjc(e: Swift?) -> Objc?
    
    static func fromObjc(e: Objc) -> Swift
    
    static func fromObjc(e: Objc?) -> Swift?
}

public struct Enum <T : RawRepresentable>: DjinniRepresentable, Hashable where T: Hashable {
    public typealias Swift = T
    public typealias Objc = NSNumber
    
    public static func toObjc(e: Swift) -> Objc {
        return Objc.init(value: e.rawValue as! NSInteger)
    }
    
    public static func toObjc(e: Swift?) -> Objc? {
        if let unwrapped = e {
            return Objc.init(value: unwrapped.rawValue as! NSInteger)
        }
        
        return nil
    }
    
    public static func fromObjc(e: Objc) -> Swift {
        return Swift.init(rawValue: e.intValue as! Swift.RawValue)!
    }
    
    public static func fromObjc(e: Objc?) -> Swift? {
        if let unwrapped = e {
            return Swift.init(rawValue: unwrapped.intValue as! Swift.RawValue)!
        }
        return nil
    }
}

public struct I8 : DjinniRepresentable {
    public typealias Swift = Int8
    public typealias Objc = NSNumber // uint_8
    
    public static func toObjc(e: Swift) -> NSNumber {
        return NSNumber.init(value: e)
    }
    
    public static func toObjc(e: Swift?) -> NSNumber? {
        if let unwrapped = e {
            return NSNumber.init(value: unwrapped)
        }
        
        return nil
    }
    
    public static func fromObjc(e: NSNumber) -> Swift {
        return Swift.init(e.int8Value)
    }
    
    public static func fromObjc(e: NSNumber?) -> Swift? {
        if let unwrapped = e {
            return Swift.init(unwrapped.int8Value)
        }
        return nil
    }
}

public struct I16 : DjinniRepresentable {
    public typealias Swift = Int16
    public typealias Objc = NSNumber
    
    public static func toSwift(e: Objc) -> Swift {
        return Swift.init(e.int16Value)
    }
    
    public static func toObjc(e: Swift) -> NSNumber {
        return NSNumber.init(value: e)
    }
    
    public static func toObjc(e: Swift?) -> NSNumber? {
        if let unwrapped = e {
            return NSNumber.init(value: unwrapped)
        }
        
        return nil
    }
    
    public static func fromObjc(e: NSNumber) -> Swift {
        return Swift.init(e.int16Value)
    }
    
    public static func fromObjc(e: NSNumber?) -> Swift? {
        if let unwrapped = e {
            return Swift.init(unwrapped.int16Value)
        }
        return nil
    }
}

public class I32 : NSObject, DjinniRepresentable {
    public typealias Swift = Int32
    public typealias Objc = NSNumber
    
    public static func toObjc(e: Swift) -> NSNumber {
        return NSNumber.init(value: e)
    }
    
    public static func toObjc(e: Swift?) -> NSNumber? {
        if let unwrapped = e {
            return NSNumber.init(value: unwrapped)
        }
        
        return nil
    }
    
    public static func fromObjc(e: NSNumber) -> Swift {
        return Swift.init(e.int32Value)
    }
    
    public static func fromObjc(e: NSNumber?) -> Swift? {
        if let unwrapped = e {
            return Swift.init(unwrapped.int32Value)
        }
        return nil
    }
}

public struct I64 : DjinniRepresentable {
    public typealias Swift = Int64
    public typealias Objc = NSNumber
    
    public static func toObjc(e: Swift) -> NSNumber {
        return NSNumber.init(value: e)
    }
    
    public static func toObjc(e: Swift?) -> NSNumber? {
        if let unwrapped = e {
            return NSNumber.init(value: unwrapped)
        }
        
        return nil
    }
    
    public static func fromObjc(e: NSNumber) -> Swift {
        return Swift.init(e.int64Value)
    }
    
    public static func fromObjc(e: NSNumber?) -> Swift? {
        if let unwrapped = e {
            return Swift.init(unwrapped.int64Value)
        }
        return nil
    }
}

public struct List<T : DjinniRepresentable> {
    public typealias ObjcType = T.Objc
    public typealias SwiftType = T.Swift
    
    
    public typealias Swift = Array<SwiftType>
    public typealias Objc = Array<ObjcType>
    
    public static func toObjc(e: Swift) -> Objc {
        return e.map { T.toObjc(e: $0) }
    }
    
    public static func fromObjc(e: Objc) -> Swift {
        return e.map { T.fromObjc(e: $0) }
    }
}

public struct SetHelper<T : DjinniRepresentable> {
    public typealias ObjcType = T.Objc
    public typealias SwiftType = T.Swift
    
    public typealias Swift = Set<SwiftType>
    public typealias Objc = Set<ObjcType>
    
    public static func toObjc(e: Swift) -> Objc {
        var result = Objc.init()
        e.forEach { (v: SwiftType) in
            result.insert(T.toObjc(e: v))
        }
        
        return result
    }
    
    public static func fromObjc(e: Objc) -> Swift {
        var result = Swift.init()
        e.forEach { (v: ObjcType) in
            result.insert(T.fromObjc(e: v))
        }
        return result
    }
}

public struct Map<K: DjinniRepresentable, V: DjinniRepresentable> {
    public typealias KeyObjcType = K.Objc
    public typealias KeySwiftType = K.Swift
    
    public typealias ValueObjcType = V.Objc
    public typealias ValueSwiftType = V.Swift
    
    public typealias Swift = Dictionary<KeySwiftType, ValueSwiftType>
    public typealias Objc = Dictionary<KeyObjcType, ValueSwiftType>
    
    public static func toObjc(e: Swift) -> Objc {
        var result = Objc.init()
        
        e.forEach { (key: KeySwiftType, value: ValueSwiftType) in
            result[K.toObjc(e: key)] = value
        }
        
        return result
    }
    
    public static func fromObjc(e: Objc) -> Swift {
        var result = Swift.init()
        e.forEach { (key: KeyObjcType, value: ValueSwiftType) in
            result[K.fromObjc(e: key)] = value
        }
        return result
    }
}
