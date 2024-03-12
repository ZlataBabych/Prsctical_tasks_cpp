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





