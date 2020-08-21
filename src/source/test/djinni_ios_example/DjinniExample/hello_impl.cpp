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

//MyRecord HelloImpl::say_hello() {
//    return MyRecord(1000);
//}

//MyRecord HelloImpl::say_hello(my_enum en) {
//    return MyRecord(en);
//}

my_enum HelloImpl::say_hi() {
    return (my_enum)0;
}

//void HelloImpl::hlll() {
//    printf("Ahihi");
//}

}
