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


HelloImpl::HelloImpl() {
}

std::shared_ptr<cpp_generated::Hello> cpp_generated::Hello::create() {
    return std::make_shared<HelloImpl>();
}

cpp_generated::MyEnum HelloImpl::say_hi() {
    return cpp_generated::MyEnum::A;
}

cpp_generated::MyRecord HelloImpl::print(const cpp_generated::MyRecord & rc) {
    return rc;
}
