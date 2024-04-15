#pragma once

#include <iostream>
#include<list>
#include<vector>
#include<map>
#include <fstream>
#include <memory>
#include <string>

// Deque from GitHub
/*
template <class T>
class deque {
private:
    T* arr;
    int front;
    int rear;
    int size;
    int curr_size;

public:

    deque()
    {
        arr = new T[1];
        front = -1;
        rear = 0;
        size = 0;
        curr_size = 0;
    }

    deque(int size, T x)
    {
        arr = new T[size];
        front = -1;
        rear = 0;
        curr_size = 0;
        this->size = size;
        for (int i = 0;i < size;i++)
            push_back(x);
    }
    bool empty()
    {
        if (front == -1)
            return true;
        else return false;
    }
    bool isFull()
    {
        if (front == 0 && rear == size - 1)
            return true;
        else if (front == rear + 1)
            return true;
        else return false;
    }
    void push_back(T data)
    {

        if (isFull())
        {
            cout << " Overflow\n " << endl;
            return;
        }
        if (rear == size - 1)
            rear = 0;
        else if (front == -1)
        {
            front = 0;
            rear = 0;
        }
        else ++rear;
        arr[rear] = data;
        ++curr_size;
    }

    void pop_back()
    {
        if (empty())
        {
            cout << " Underflow\n";
            return;
        }
        if (rear == 0)
            rear = size - 1;
        else if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else --rear;
        --curr_size;
    }

    void push_front(T data)
    {
        if (isFull())
        {
            cout << "Overflow\n" << endl;
            return;
        }
        if (front == 0)
            front = size - 1;
        else if (front == -1)
        {
            front = 0;
            rear = 0;
        }

        else --front;
        arr[front] = data;
        ++curr_size;
    }

    void pop_front()
    {
        if (empty())
        {
            cout << "Queue Underflow\n" << endl;
            return;
        }
        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else front == (front + 1) % size;
        --curr_size;
    }

    int get_size()
    {
        return ((size - front + rear) % size);
    }

    T back()
    {
        return arr[size - 1];
    }

    T get_front()
    {
        return arr[1];
    }

    void resize(int x, T d)
    {
        if (curr_size == x)
            return;
        else if (curr_size > x)
        {
            int i = curr_size - x;
            while (i--)
                pop_front();
        }

        else
        {
            int i = x - curr_size;
            while (i--)
                push_front(d);
            size = (size - front + rear) % size;
        }

    }

    T D(int n)
    {
        return arr[n];
    }

    void clear()
    {
        front = -1;
        rear = 0;
        size = 0;
        curr_size = 0;
    }



    void display()

    {
        if (front == -1)
        {
            cout << "Empty\n";
            return;
        }
        cout << "\n Elements are: ";
        if (rear >= front)
        {
            for (int i = front;i <= rear;i++)
                cout << arr[i] << endl;
        }
        else
        {
            for (int i = front;i < size;i++)
                cout << arr[i];
            for (int i = 0;i <= rear;i++)
                cout << arr[i] << endl;
        }
    }
};
*/


//Mimic a software versioning system
/*
In this kata we are going to mimic a software versioning system.

You have to implement a VersionManager class.

It should accept an optional parameter that represents the initial version. The input will be in one of the following formats: "{MAJOR}", "{MAJOR}.{MINOR}", or "{MAJOR}.{MINOR}.{PATCH}". More values may be provided after PATCH but they should be ignored. If these 3 parts are not decimal values, an exception with the message "Error occured while parsing version!" should be thrown. If the initial version is not provided or is an empty string, use "0.0.1" by default.

This class should support the following methods, all of which should be chainable (except release):

major() - increase MAJOR by 1, set MINOR and PATCH to 0
minor() - increase MINOR by 1, set PATCH to 0
patch() - increase PATCH by 1
rollback() - return the MAJOR, MINOR, and PATCH to their values before the previous major/minor/patch call, or throw an exception with the message "Cannot rollback!" if there's no version to roll back to. Multiple calls to rollback() should be possible and restore the version history
release() - return a string in the format "{MAJOR}.{MINOR}.{PATCH}"
Note: In C++, use preloaded VersionException class for throwing exceptions.

May the binary force be with you!
*/
class VersionException {
    std::string Exception;
public:
    VersionException(std::string Exception) :Exception(Exception) {}
};
class VersionManager {
public:
    VersionManager(std::string version = "0.0.1") {
        if (version.empty()) {
            version = "0.0.1";
        }
        try {
            parseVersion(version);
        }
        catch (const std::invalid_argument&) {
            throw VersionException("Error occured while parsing version!");
        }
        catch (const std::out_of_range&) {
            throw VersionException("Error occured while parsing version!");
        }
    }

    VersionManager& major() {
        saveState();
        major_++;
        minor_ = 0;
        patch_ = 0;
        return *this;
    }

    VersionManager& minor() {
        saveState();
        minor_++;
        patch_ = 0;
        return *this;
    }

    VersionManager& patch() {
        saveState();
        patch_++;
        return *this;
    }

    VersionManager& rollback() {
        if (history_.empty())
            throw VersionException("Cannot rollback!");

        std::tie(major_, minor_, patch_) = history_.top();
        history_.pop();
        return *this;
    }

    std::string release() const {
        return std::to_string(major_) + "." + std::to_string(minor_) + "." + std::to_string(patch_);
    }

private:
    int major_ = 0, minor_ = 0, patch_ = 0;
    std::stack<std::tuple<int, int, int>> history_;

    void saveState() {
        history_.push({ major_, minor_, patch_ });
    }

    void parseVersion(const std::string& version) {
        std::istringstream iss(version);
        std::string part;

        if (!std::getline(iss, part, '.') || part.empty()) throw std::invalid_argument("Invalid input");
        major_ = stoi(part);
        if (!std::getline(iss, part, '.')) return;
        minor_ = stoi(part);
        if (!std::getline(iss, part, '.')) return;
        patch_ = stoi(part);
    }
};


//Return the correct state of the TCP FSM based on the array of events given.
/*
Automatons, or Finite State Machines (FSM), are extremely useful to programmers when it comes to software design. You will be given a simplistic version of an FSM to code for a basic TCP session.

The outcome of this exercise will be to return the correct state of the TCP FSM based on the array of events given.

The input array of events will consist of one or more of the following strings:

APP_PASSIVE_OPEN, APP_ACTIVE_OPEN, APP_SEND, APP_CLOSE, APP_TIMEOUT, RCV_SYN, RCV_ACK, RCV_SYN_ACK, RCV_FIN, RCV_FIN_ACK
The states are as follows and should be returned in all capital letters as shown:

CLOSED, LISTEN, SYN_SENT, SYN_RCVD, ESTABLISHED, CLOSE_WAIT, LAST_ACK, FIN_WAIT_1, FIN_WAIT_2, CLOSING, TIME_WAIT
The input will be an array of events. The initial state is CLOSED. Your job is to traverse the FSM as determined by the events, and return the proper final state as a string, all caps, as shown above.

If an event is not applicable to the current state, your code will return "ERROR".

Action of each event upon each state:
(the format is INITIAL_STATE: EVENT -> NEW_STATE)

CLOSED: APP_PASSIVE_OPEN -> LISTEN
CLOSED: APP_ACTIVE_OPEN  -> SYN_SENT
LISTEN: RCV_SYN          -> SYN_RCVD
LISTEN: APP_SEND         -> SYN_SENT
LISTEN: APP_CLOSE        -> CLOSED
SYN_RCVD: APP_CLOSE      -> FIN_WAIT_1
SYN_RCVD: RCV_ACK        -> ESTABLISHED
SYN_SENT: RCV_SYN        -> SYN_RCVD
SYN_SENT: RCV_SYN_ACK    -> ESTABLISHED
SYN_SENT: APP_CLOSE      -> CLOSED
ESTABLISHED: APP_CLOSE   -> FIN_WAIT_1
ESTABLISHED: RCV_FIN     -> CLOSE_WAIT
FIN_WAIT_1: RCV_FIN      -> CLOSING
FIN_WAIT_1: RCV_FIN_ACK  -> TIME_WAIT
FIN_WAIT_1: RCV_ACK      -> FIN_WAIT_2
CLOSING: RCV_ACK         -> TIME_WAIT
FIN_WAIT_2: RCV_FIN      -> TIME_WAIT
TIME_WAIT: APP_TIMEOUT   -> CLOSED
CLOSE_WAIT: APP_CLOSE    -> LAST_ACK
LAST_ACK: RCV_ACK        -> CLOSED
"EFSM TCP"

Examples
["APP_PASSIVE_OPEN", "APP_SEND", "RCV_SYN_ACK"] =>  "ESTABLISHED"

["APP_ACTIVE_OPEN"] =>  "SYN_SENT"

["APP_ACTIVE_OPEN", "RCV_SYN_ACK", "APP_CLOSE", "RCV_FIN_ACK", "RCV_ACK"] =>  "ERROR"
*/
std::map<std::string, std::map<std::string, std::string>> TCP_FSM = {
        {"CLOSED",     {{"APP_PASSIVE_OPEN", "LISTEN"},{"APP_ACTIVE_OPEN", "SYN_SENT"}} },
        {"LISTEN",     {{"RCV_SYN", "SYN_RCVD"}, {"APP_SEND", "SYN_SENT"}, {"APP_CLOSE", "CLOSED"}}},
        {"SYN_RCVD",   {{"APP_CLOSE", "FIN_WAIT_1"}, {"RCV_ACK","ESTABLISHED"}}},
        {"SYN_SENT",   {{"RCV_SYN", "SYN_RCVD"}, {"RCV_SYN_ACK", "ESTABLISHED"}, {"APP_CLOSE", "CLOSED"}}},
        {"ESTABLISHED",{{"APP_CLOSE", "FIN_WAIT_1"}, {"RCV_FIN", "CLOSE_WAIT"}}},
        {"FIN_WAIT_1", {{"RCV_FIN", "CLOSING"}, {"RCV_FIN_ACK", "TIME_WAIT"}, {"RCV_ACK", "FIN_WAIT_2"}}},
        {"CLOSING",    {{"RCV_ACK", "TIME_WAIT"}}},
        {"FIN_WAIT_2", {{"RCV_FIN", "TIME_WAIT"}}},
        {"TIME_WAIT",  {{"APP_TIMEOUT", "CLOSED"}}},
        {"CLOSE_WAIT", {{"APP_CLOSE", "LAST_ACK"}}},
        {"LAST_ACK",   {{"RCV_ACK", "CLOSED"}}},
};
std::string traverse_TCP_states(const std::vector<std::string>& events) {
    std::string state = "CLOSED";
    for (const auto& i : events) {
        if (TCP_FSM[state].find(i) == TCP_FSM[state].end()) {
            return "ERROR";
        }
        state = TCP_FSM[state][i];
    }
    return state;
}


//String Packet Based Communications
//method of receiving commands over a network, processing the information and responding.
/*
We need you to implement a method of receiving commands over a network, processing the information and responding.

Our device will send a single packet to you containing data and an instruction which you must perform before returning your reply.

To keep things simple, we will be passing a single "packet" as a string. Each "byte" contained in the packet is represented by 4 chars.

One packet is structured as below:

Header  Instruction   Data1    Data2   Footer
------   ------       ------   ------  ------
 H1H1     0F12         0012     0008    F4F4
------   ------       ------   ------  ------

The string received in this case would be - "H1H10F1200120008F4F4"

Instruction: The calculation you should perform, always one of the below.
            0F12 = Addition
            B7A2 = Subtraction
            C3D9 = Multiplication
            FFFF = This instruction code should be used to identify your return value.
The Header and Footer are unique identifiers which you must use to form your reply.

Data1 and Data2 are the decimal representation of the data you should apply your instruction to. i.e 0109 = 109.

Your response must include the received header/footer, a "FFFF" instruction code, and the result of your calculation stored in Data1.

Data2 should be zero'd out to "0000".

To give a complete example:

If you receive message "H1H10F1200120008F4F4".
The correct response would be "H1H1FFFF00200000F4F4"
In the event that your calculation produces a negative result, the value returned should be "0000", similarly if the value is above 9999 you should return "9999".
*/
string communicationModule(string packet);


// Return the sum of all values in the tree, including the root
struct node;
int sumTheTreeValues(node* root);



// make sure to check the name is unique via the photoManager object
std::string generateName();


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


/*
A wristband can have 4 patterns:

horizontal: each item in a row is identical.
vertical: each item in a column is identical.
diagonal left: each item is identical to the one on its upper left or bottom right.
diagonal right: each item is identical to the one on its upper right or bottom left.
You are shown an incomplete section of a wristband.

Write a function that returns true if the section can be correctly classified into one of the 4 types, and false otherwise.

Examples
std::vector<std::vector<string>> arr1
    {	{"A", "B", "C"},
        {"B", "C", "A"},
        {"C", "A", "B"},
        {"A", "B", "A"}		};

    std::vector<std::vector<string>> arr2
    {	{"A", "B", "C"},
        {"A", "B", "C"},
        {"A", "B", "C"},
        {"A", "B", "C"} };

    std::vector<std::vector<string>> arr3
    {	{"A", "A", "A"},
        {"C", "C", "C"},
        {"C", "C", "C"},
        {"A", "A", "A"} };

    std::vector<std::vector<string>> arr4
    {	{"A", "B", "C"},
        {"B", "A", "B"},
        {"C", "B", "A"},
        {"A", "C", "B"} };
*/

bool isWristband(std::vector<std::vector<std::string>> arr);

