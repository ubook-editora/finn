//
//  hello_impl.hpp
//  djinni_ios_example
//
//  Created by Mr Hien Nguyen Le Hien on 3/4/20.
//  Copyright © 2020 Fossil. All rights reserved.
//

#ifndef hello_impl_hpp
#define hello_impl_hpp

#include <stdio.h>
#include "hello.hpp"
#include "my_enum.hpp"

class HelloImpl: public textsort::Hello {
    
public:
    HelloImpl();
    
    textsort::my_enum say_hi() override;
    
    textsort::MyRecord print(const textsort::MyRecord & rc) override;
    
};
#endif /* hello_impl_hpp */
