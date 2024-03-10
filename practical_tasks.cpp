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


list<int> unique_for_two_arrays(vector<int> const& v1, vector<int> const& v2) {
    map<int, int> all_elem;
    list<int> unique_elem;

    for (auto it : v1)
        all_elem[it]++;

    for (auto it : v2)
        all_elem[it]++;

    for (auto it : all_elem)
        if (it.second == 1)
            unique_elem.push_back(it.first);

    return unique_elem;
}

















