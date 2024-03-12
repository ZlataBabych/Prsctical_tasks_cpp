#include "practical_tasks.h"
#include<string>
#include <iostream>
#include<list>
#include<vector>
#include<map>

using namespace std;




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

int atoi_(const char* str) {
   
    int res = 0;

    if (str == '\0' || str == nullptr)
        return 0;

    bool positiv = true;

    int i = 0;

    while (str[i] == ' ') 
        ++i;

    if (str[i] == '-') {
        positiv = false;
        ++i;
    }        

    while (str[i] != '\0' && str[i] >= '0' && str[i]<= '9') {
        res = res * 10 + (str[i] - '0');
        ++i;
    }

    return positiv? res : -res;
}


int count_words_in_sentence(const char* str) {
    int count = 0;

    if (str == '\0' || str == nullptr)
        return 0;

    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == ' ')
            ++count;
        ++i;
    }

    return ++count;
}


int factorial(int k) {
    if (k < 0)
        return 0;
    if (k == 0 || k == 1)
        return 1;
    if (k == 2)
        return 2;

    int i = 1;
    int sum = k;
    while (i < k) {
        sum *= i;
        cout << sum << " ";
        ++i;
    }

    return sum;
}


int fibonacci(int k) {
    if (k <= 0)
        return 0;

    if (k == 1 or k == 2)
        return 1;

    int fib = 0;
    int subprev = 1;
    int prev = 1;

    for (int i = 3; i <= k; ++i) {
        fib = subprev + prev;
        subprev = prev;
        prev = fib;
    }

    return fib;
}


list<int> unique_for_two_arrays(std::vector<int> const& v1, std::vector<int> const& v2) {
    std::map<int, int> all_elem;
    std::list<int> unique_elem;

    for (auto it : v1)
        all_elem[it]++;

    for (auto it : v2)
        all_elem[it]++;

    for (auto it : all_elem)
        if (it.second == 1)
            unique_elem.push_back(it.first);

    return unique_elem;
}

void reverse_of_lines(char* str) {
    if (str == nullptr || str[0] == '\0')
        return;

    int size = 0;
    while (str[size] != '\0')
        ++size;

    char temp = '\0';
    for (int i = 0; i < size/2; ++i) {
        temp = str[i];
        str[i] = str[size - i];
        str[size - i] = temp;
    }
}

















