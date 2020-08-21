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
//        let hello = Hello.create()
//
//        let a: MyEnum = (hello?.sayHi())!
//
//        print("\(a.rawValue)")
        
        
        
        let r = MyRecord.init(bo: [MyEnum.A, MyEnum.B])
        
        
    }
}

