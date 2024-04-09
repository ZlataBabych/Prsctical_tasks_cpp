#include "practical_tasks.h"
#include <iostream>
#include <fstream>
#include <memory>
#include<list>
#include<vector>
#include<algorithm>
#include<map>
#include <string>

using namespace std;

class Base {
    virtual void method() { std::cout << "from Base" << std::endl; }
public:
    virtual ~Base() { method(); }
    void baseMethod() { method(); }
};

class A : public Base {
    void method() { std::cout << "from A" << std::endl; }
public:
    ~A() { method(); }
};

int main(void) {
    

    unsigned char half_limit = 150;

    for (unsigned char i = 0; i < 2 * half_limit; ++i)
    {
        cout << i << " ";
    }





    return 0;
}





		



