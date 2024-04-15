#include "practical_tasks.h"
#include<string>
#include <iostream>
#include<list>
//#include<vector>
#include<map>

using namespace std;

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
map<string, function<int(int, int)>> funcs = {
  make_pair("0F12", [](int n1, int n2) { return n1 + n2; }),
  make_pair("B7A2", [](int n1, int n2) { return n1 - n2; }),
  make_pair("C3D9", [](int n1, int n2) { return n1 * n2; }),
};
string communicationModule(string packet)
{
    int n1 = stoi(packet.substr(8, 4));
    int n2 = stoi(packet.substr(12, 4));
    int num = funcs[packet.substr(4, 4)](n1, n2);

    if (num < 0) num = 0;
    if (num > 9999) num = 9999;

    stringstream stream;
    stream << setfill('0') << setw(4) << num;

    packet.replace(4, 4, "FFFF");
    packet.replace(8, 4, stream.str());
    packet.replace(12, 4, "0000");

    return packet;
}



std::string generateName()
{
    std::string str = "";
    char ch;
    for (int i = 0; i < 6; i++)
    {
        ch = 65 + rand() % 25;
        str += ch;
    }
    return str;
}


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

    for (auto& it : all_elem)
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


bool is_palindrome(std::string const& word) {
    int len = word.length();
    std::cout << len << "   ";

    if (len == 0)
        return false;
    
    if (len == 1)
        return true;
;
    for (int i = 0; i <= len / 2; ++i) {
        std::cout << word[i] << " " << word[len - i - 1] << std::endl;
        if (word[i] != word[len - i - 1])
            return false;
    }

    return true;
}


void sortBubble(std::vector<int>& arr) {
    if (arr.empty())
        return;

    if (arr.size() == 1)
        return;

    int size = arr.size();
    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - 1 - i; ++j) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
}


bool areParenthesesBalanced(const std::string& expression) {
    std::stack<char> stack;

    for (char c : expression) {
        switch (c) {
        case '(':
        case '{':
        case '[':
            stack.push(c);
            break;
        case ')':
            if (stack.empty() || stack.top() != '(') return false;
            stack.pop();
            break;
        case '}':
            if (stack.empty() || stack.top() != '{') return false;
            stack.pop();
            break;
        case ']':
            if (stack.empty() || stack.top() != '[') return false;
            stack.pop();
            break;
        }
    }

    // If stack is empty, all parentheses were balanced; otherwise, not balanced.
    return stack.empty();
}


void exThrowInConstructor() {
    //out of func:
    struct ExcType1 {};
    struct ExcType2 {};


    class A {
    public:
        A() { throw ExcType1(); }
    };

    //func:
    try {
        A a;
        throw ExcType2();
    }

    catch (ExcType1&) {
        printf("ExcType1 ");
    }

    catch (ExcType2&) {
        printf("ExcType2 ");
    }

    printf(". but Continue");
}


void exRvalueMoveConstructor() {
    //struct:
    struct String {

        String() {};

        String(String const& s) { std::cout << "Copy Constructor" << std::endl; };

        String& operator=(String const& a) {

            std::cout << "Copy Operator = " << std::endl;

            return *this;

        };

        ~String() {};

        String(String&& s) { std::cout << "Move Constructor" << std::endl; }

        String& operator=(String&& s) {

            std::cout << "Move Operator = " << std::endl;

            return *this;

        }

    };



    //functions:

    /*String& fun1(String & s) { return s; }

    String&& fun2(String & s) { return std::move(s); }

    String fun3(String & s) { return std::move(s); }

    String fun4(String s) { return std::move(s); }

    String fun5(String s) { return std::forward<String>(s); }

    String&& fun6(String && s) { return std::move(s); }

    String fun7(String && s) { return s; }*/



    //main:

 /*   String str, str2;

    std::cout << "fun1" << std::endl;

    str2 = fun1(str);

    std::cout << "fun2" << std::endl;

    str2 = fun2(str);

    std::cout << "fun3" << std::endl;

    str2 = fun3(str);

    std::cout << "fun4" << std::endl;

    str2 = fun4(str);

    std::cout << "fun5" << std::endl;

    str2 = fun5(str);

    std::cout << "fun6" << std::endl;

    str2 = fun6(String());

    std::cout << "fun7" << std::endl;

    str2 = fun7(String());*/

}


void productOfAllElemInArray(int* A, int* B, size_t N) {
    if (N == 1)
        B[0] = A[0];

    for (int i = 0; i < N; ++i) {
        B[i] = 1;
        for (int j = 0; j < N; ++j) {
            if (i == j)
                continue;
            B[i] *= A[j];
        }
    }
}

void productOfAllElemInArrayBest(int* A, int* B, int N) {
    // Set prod to the neutral multiplication element
    int prod = 1;

    for (int i = 0; i < N; ++i) {
        // For element "i" set B[i] to A[0] * ... * A[i - 1]
        B[i] = prod;
        // Multiply with A[i] to set prod to A[0] * ... * A[i]
        prod *= A[i];
    }

    // Reset prod and use it for the right elements
    prod = 1;

    for (int i = N - 1; i >= 0; --i) {
        // For element "i" multiply B[i] with A[i + 1] * ... * A[N - 1]
        B[i] *= prod;
        // Multiply with A[i] to set prod to A[i] * ... * A[N - 1]
        prod *= A[i];
    }
}

std::vector<int> invertArray(std::vector<int> arr) {
    for (auto& i : arr)
        i = -1 * i;

    return arr;
}




std::vector<std::vector<int>> clockwiseRotateTwoDimensionalMatrix(std::vector<std::vector<int>> matrix) {
    size_t n = matrix.size();

    std::vector<std::vector<int>> matrixRotate(matrix);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            matrixRotate[i][j] = matrix[n - j - 1][i];

    return matrixRotate;
}
std::vector<std::vector<int>> counterclockwiseRotateTwoDimensionalMatrix(std::vector<std::vector<int>> matrix) {
    size_t n = matrix.size();

    std::vector<std::vector<int>> matrixRotate(matrix);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            matrixRotate[n - j - 1][i] = matrix[i][j];

    return matrixRotate;
}
std::vector<std::vector<int>> RotateTwoDimensionalMatrix(std::vector<std::vector<int>> matrix, int num) {

    /*
    std::vector<std::vector<int>> matrix 
    {   {0, 1, 2, 3, 4},
        {5, 6, 7, 8, 9},
        {3, 1, 7, 3, 4},
        {4, 5, 5, 9, 0},
        {7, 7, 2, 1, 8}   };
    */

    if (num != 0 && num % 4 != 0) {
        std::vector<std::vector<int>> matrixRotate(matrix);
        if (num > 0)
            while (num > 0) {
                matrixRotate = clockwiseRotateTwoDimensionalMatrix(matrixRotate);
                --num;
            }
        else
            while (num < 0) {
                matrixRotate = counterclockwiseRotateTwoDimensionalMatrix(matrixRotate);
                ++num;
            }
        return matrixRotate;
    }
    return matrix;
}
//best solution
std::vector<std::vector<int>> rotateTransform(std::vector<std::vector<int>> arr, int num) {
    num %= 4;
    size_t n = arr.size();
    using Matrix = std::vector<std::vector<int>>;
    auto transpose = [&](Matrix& m) {
        for (int row = 0; row < n; ++row)
            for (int col = row + 1; col < n; ++col)
                std::swap(m[row][col], m[col][row]);
    };
    auto flip = [](Matrix& m) {
        for (auto& row : m)
            std::reverse(m.begin(), m.end());
    };
    while (num < 0) { flip(arr); transpose(arr); ++num; }
    while (num > 0) { transpose(arr); flip(arr); --num; }
    return arr;
}


int sumDigit(int positiveInteger) {
    int sum = 0;
    while (positiveInteger % 10 != 0) {
        sum += positiveInteger % 10;
        positiveInteger /= 10;
    }
    return sum;
}


std::string spaceMessageInScope(std::string str, int open, int close) {
    std::string new_str = "";


    char* mult_str = new char[close - open];
    memset(mult_str, '0', sizeof(char));

    int i = 0;
    for (int s = open + 1; s < close; ++s) {
        mult_str[i] = str[s];
        ++i;
    }

    int count = atoi(mult_str);


    for (int s = open + 1; s < close; ++s) {
        if ((str[s] < '0' || str[s] > '9') && (str[s] != '[' || str[s] != ']')) {
            new_str += str[s];
        }
    }

    std::string res = "";
    while (count > 0) {
        res += new_str;
        --count;
    }

    return res;
}
std::string spaceMessage(std::string str) {
    std::string new_str = "";

    int open = 0; // [
    int close = 0; // ]

    bool flag = true;

    for (int s = 0; s < str.length(); ++s) {
        if (str[s] == '[') {
            flag = false;
            open = s;
            continue;
        }
        if (str[s] == ']') {
            flag = true;
            close = s;
            new_str += spaceMessageInScope(str, open, close);
            continue;
        }
        if (flag == true && (str[s] != '[' || str[s] != ']'))
            new_str += str[s];
    }

    return new_str;
}


bool isWristband(vector<vector<string>> arr) {
    size_t n = arr.size();
    size_t m = arr[0].size();

    if (n == 0 || m == 0)
        return false;

    if (n == 1 || m == 1)
        return true;

    auto isHorizontal = [n, m](vector<vector<string>> arr) -> bool {

        for (int i = 0; i < n; ++i) {
            char first = arr[i][0][0];
            for (int j = 1; j < m; ++j) {
                if (arr[i][j][0] != first)
                    return false;
            }
        }

        return true;
    };

    auto isVertical = [n, m](vector<vector<string>> arr) -> bool {

        for (int i = 0; i < m; ++i) {
            char first = arr[0][i][0];
            for (int j = 1; j < n; ++j) {
                if (arr[j][i][0] != first)
                    return false;
            }
        }

        return true;
    };

    auto isDiagonalLeft = [n, m](vector<vector<string>> arr) -> bool {

        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < m - 1; ++j) {
                //cout << " arr[i][j] = " << arr[i][j] << "     arr[i+1][j+1] " << arr[i + 1][j + 1] << endl;
                if (arr[i][j] != arr[i + 1][j + 1])
                    return false;
            }
        }

        return true;
    };

    auto isDiagonalRight = [n, m](vector<vector<string>> arr) -> bool {

        for (int i = 0; i < n - 1; ++i) {
            for (int j = 1; j < m; ++j) {
                //cout << " arr[i][j] = " << arr[i][j] << "     arr[i+1][j+1] " << arr[i + 1][j + 1] << endl;
                if (arr[i][j] != arr[i + 1][j - 1])
                    return false;
            }
        }

        return true;
    };

    return (isHorizontal(arr) || isVertical(arr) || isDiagonalLeft(arr) || isDiagonalRight(arr));
}