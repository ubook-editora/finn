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

namespace demo {

class HelloImpl: public Hello {
    
public:
    HelloImpl();
    
    my_enum say_hi() override;
    
    MyRecord print(const MyRecord & rc) override;
    
};
}
#endif /* hello_impl_hpp */
