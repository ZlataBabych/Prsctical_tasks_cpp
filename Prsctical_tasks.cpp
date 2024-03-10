// Prsctical_tasks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>
using namespace std;


//169.Порахуйте кількість одиниць у довільному числі.
int count_units(int number) {
    int count = 0;
    int i = 0;

    string str = to_string(number);

    char ch = str[0];

   while (ch != '\0') {
        ch = str[i];
        cout << ch << " ";
        if (ch == '1')
            ++count;
        ++i;
    }

    return count;
}

int main()
{
    //
    int number = 0;
    cin >> number;
    cout << endl << count_units(number) << endl;

    return 0;
}
