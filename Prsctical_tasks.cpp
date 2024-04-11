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

const float PI_F = 3.14f;

class Circle {
public:
    Circle(float r) {
        if (r < 0)
            throw std::exception("Radius < 0");
        R = r;
    }
    float getArea() { return PI_F * R * R; };
    float getPerimeter() { return PI_F * R * 2; };
private:
    float R;
};



int main(void) {


	return 0;
}




		



