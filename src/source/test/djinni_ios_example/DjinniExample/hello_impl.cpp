//
//  hello_impl.cpp
//  djinni_ios_example
//
//  Created by Mr Hien Nguyen Le Hien on 3/4/20.
//  Copyright © 2020 Fossil. All rights reserved.
//

#include "hello_impl.hpp"
#include "my_record.hpp"
#include <optional>
//--cpp-namespace "demo"

namespace demo {

HelloImpl::HelloImpl() {
}

std::shared_ptr<Hello> Hello::create() {
    return std::make_shared<HelloImpl>();
}

my_enum HelloImpl::say_hi() {
    return (my_enum)0;
}

MyRecord HelloImpl::print(const MyRecord & rc) {
    
    
    return rc;
}


}
