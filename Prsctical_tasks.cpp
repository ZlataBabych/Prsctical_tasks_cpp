#include "practical_tasks.h"
#include <iostream>
#include<list>
#include<vector>
#include<map>
using namespace std;



int main()
{
    vector<int> v1{ 1, -2, 3, 1, 5, -1, 3, 3, 1};
    vector<int> v2{ 1, 2, 3, 1, 15, -1 };
    list<int> unique_elem = unique_for_two_arrays(v1, v2);
    for (auto it : unique_elem) {
        cout << it << " " ;
    }
    return 0;
}
