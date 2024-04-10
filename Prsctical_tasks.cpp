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



int main(void) {
    
    std::vector<std::vector<int>> matrix 
    {   {0, 1, 2, 3, 4},
        {5, 6, 7, 8, 9},
        {3, 1, 7, 3, 4},
        {4, 5, 5, 9, 0},
        {7, 7, 2, 1, 8}   };

    
    
    std::vector<std::vector<int>> matrix2 = rotateTransform(matrix, -2);

            for (auto i : matrix2) {
                for (auto j : i)
                    cout << j << " ";
                cout << endl;
            }
     
    return 0;
}





		



