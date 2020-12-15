//
//  ViewController.swift
//  djinni_ios_example
//
//  Created by Mr Hien Nguyen Le Hien on 3/4/20.
//  Copyright © 2020 Fossil. All rights reserved.
//

import UIKit
import DjinniExample

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        
        let r = MyRecord.init(test: 1, test1: 1, test2: [1], test3: "a", test31: "a",
                              test4: Date(),
                              test41: Date(),
                              test5: Data.init(),
                              test6: [],
                              test7: [],
                              test8: [:],
                              test9: Rc.init(a: 1, b: 2, c: 3, d: MyEnum.workout, e: "Bob".data(using: .utf8)!),
                              test10: nil,
                              test101: [
                                Rc.init(a: 1, b: 2, c: 3, d: MyEnum.workout, e: Data()),
                                Rc.init(a: 10, b: 20, c: 30, d: MyEnum.workout, e: Data())
                              ],
                              test11: MyEnum.hien,
                              test13: nil,
                              test14: 1,
                              test15: [MyEnum.workout],
                              test16: [MyEnum.workout],
                              test17: [
                                MyEnum.workout : 1
                              ])
        
        let rc = Hello.create()!.print(r)
        print("\(rc == r)")
        
        
    }
}

