//#pragma once
#ifndef PRACTICAL_TASKS_H // Prevents the header from being included multiple times
#define PRACTICAL_TASKS_H

#include<list>
#include<vector>
#include<map>

//169. Calculate the number of units in any number.
int count_units(int number);

//171. Write the implementation of the function int atoi(const char* str); string to number conversion.
int atoi_(const char* str);

//177. Implement the reverse of lines.
void reverse_of_lines(char* str);

//179. Count the words in a sentence.
int count_words_in_sentence(const char* str);

//180. Implement the calculation of factorial numbers.
int factorial(int k);

//180. Implement the calculation of Fibonacci numbers.
int fibonacci(int k);

//181. Find such elements of two arrays that occur only in each of them. It is preferable to use STL.
std::list<int> unique_for_two_arrays(std::vector<int> const& v1, std::vector<int> const& v2);



#endif