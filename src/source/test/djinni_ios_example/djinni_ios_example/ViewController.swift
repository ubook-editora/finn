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
                              test9: Rc.init(a: 1),
                              test10: nil, test101: [],
                              test11: MyEnum.a,
                              test12: [:], test13: nil,
                              test14: 1,
                              test15: [MyEnum.a],
                              test16: [MyEnum.b],
                              test17: [
                                MyEnum.a : 1
                              ])
        
        let rc = Hello.create()!.print(r)
        print("\(rc == r)")
        
        
    }
}

