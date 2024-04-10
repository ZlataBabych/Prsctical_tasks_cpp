#pragma once

#include <iostream>
#include<list>
#include<vector>
#include<map>
#include <fstream>
#include <memory>
#include <string>

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

//183. Write a logging class that could log to the console or a file.
class Logger {
public:
    Logger() {};
    virtual void log_mess(const std::string& str) = 0;
    virtual ~Logger() = default;
};

class LoggerToConsole : public Logger {
public:
    LoggerToConsole() {};
    void log_mess(const std::string& str) override {
        std::cout << str << std::endl; // or std::cout << str << '\n';
    }

};

class LoggerToFile : public Logger {
    std::ofstream file;
public:
    LoggerToFile(std::string const path) {
        file.open(path, std::ios::app); // Open in append mode
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file for logging.");
        }
    }

    void log_mess(const std::string& str) override {
        file << str << std::endl;
    }

    ~LoggerToFile() {
        if (file.is_open())
            file.close();
    }
};

//185. Write a function to determine whether a certain word is a palindrome.
bool is_palindrome(std::string const& word);


//186. Write an implementation of the Singleton pattern.
//class ISingleton {
//    std::string data;
//    ISingleton() { data = "I am ISingleton"; }
//
//protected:
//    static ISingleton* create() {
//        return new ISingleton;
//    }
//
//    std::string get_data() {
//        return data;
//    }
//};
//class Singleton {
//    std::string data;
//    static Singleton* obj;
//    Singleton() {
//        data = "I am a Singleton"; 
//        Singleton::obj = new Singleton;
//    }
//public:
//    
//    static Singleton* getSingleton();
//
//    std::string get_data() {
//        std::cout << "data " << data << " \n obj  " << obj << "  & " << &obj << "\n";
//        return data;
//    }
//};
//Singleton* Singleton::obj = nullptr;
//Singleton* Singleton::getSingleton() {
//    return Singleton::obj == nullptr ? new Singleton : Singleton::obj;
//}
//




//187. Write an implementation of std::vector with operations : push_back, push_front, pop_back, pop_front, size, clear.
//188. Write a recursive search for a value in a binary search tree.
//189. Write a function that checks whether a tree is balanced.
//190. Write a function to find a unique element in an array.



void sortBubble(std::vector<int>& arr);

int sumDigit(int positiveInteger);

constexpr inline const char* super_secret(void) {
    constexpr const char* STRING = "string";
    return STRING;
}


//throw an exeption in class constructow (it`s good)
void exThrowInConstructor();


/*
Implement a void function F that takes pointers
to two arrays of integers (A and B) and a size N as parameters.
It then populates B where B[i] is the product of all A[j] where j != i.

For example: If A = {2, 1, 5, 9}, then B would be {45, 90, 18, 10}.
*/

void productOfAllElemInArray(int* A, int* B, size_t N);

void productOfAllElemInArrayBest(int* A, int* B, int N);

std::vector<int> invertArray(std::vector<int> arr);


//Create a function to rotate a two-dimensional matrix of N * N integer elements num times, 
//where if num is positive, the rotation is clockwise, and if not, counterclockwise.
std::vector<std::vector<int>> clockwiseRotateTwoDimensionalMatrix(std::vector<std::vector<int>> matrix);
std::vector<std::vector<int>> counterclockwiseRotateTwoDimensionalMatrix(std::vector<std::vector<int>> matrix);
std::vector<std::vector<int>> RotateTwoDimensionalMatrix(std::vector<std::vector<int>> matrix, int num);
//best solution
std::vector<std::vector<int>> rotateTransform(std::vector<std::vector<int>> arr, int num);



//You have received an encrypted message from space.Your task is to decrypt the message with the following simple rules :
//
//Message string will consist of capital letters, numbers, and brackets only.
//When there's a block of code inside the brackets, such as [10AB], it means you need to repeat the letters AB for 10 times.
//Message can be embedded in multiple layers of blocks.
//Final decrypted message will only consist of capital letters.
//Create a function that takes encrypted message str and returns the decrypted message.
//
//Examples
//spaceMessage("ABCD") ➞ "ABCD"
//
//spaceMessage("AB[3CD]") ➞ "ABCDCDCD"
//// "AB" = "AB"
//// "[3CD]" = "CDCDCD"
//
//spaceMessage("IF[2E]LG[5O]D") ➞ "IFEELGOOOOOD"
std::string spaceMessageInScope(std::string str, int open, int close);
std::string spaceMessage(std::string str);




