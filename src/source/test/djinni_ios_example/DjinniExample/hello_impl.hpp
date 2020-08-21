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
    
//    virtual std::shared_ptr<Hello> create() override;
    
//    virtual MyRecord say_hello() override;
    
//    virtual MyRecord say_hello(my_enum en) override;
    
    virtual my_enum say_hi() override;
    
//    virtual void hlll() override;
};
}
#endif /* hello_impl_hpp */
