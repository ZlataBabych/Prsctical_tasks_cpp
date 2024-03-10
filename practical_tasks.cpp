#include "practical_tasks.h"
#include<string>


int count_units(int number) {
    int count = 0;
    std::string str = std::to_string(number);

    for (char ch : str) {
        if (ch == '1') {
            ++count;
        }
    }

    return count;
}