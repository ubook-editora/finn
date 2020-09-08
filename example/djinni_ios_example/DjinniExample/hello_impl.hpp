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

class HelloImpl: public cpp_generated::Hello {
    
public:
    HelloImpl();
    
    cpp_generated::MyEnum say_hi() override;
    
    cpp_generated::MyRecord print(const cpp_generated::MyRecord & rc) override;
    
};
#endif /* hello_impl_hpp */
