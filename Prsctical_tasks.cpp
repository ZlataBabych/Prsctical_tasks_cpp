#include "practical_tasks.h"
#include <iostream>
#include <fstream>
#include <memory>
#include<list>
#include<vector>
#include<map>
#include <string>
using namespace std;



int main() {
   /* LoggerToConsole consoleLogger;
    consoleLogger.log_mess("Logging to the console.");

    LoggerToFile fileLogger("D:/Zlata/WORK/С++/Prsctical_tasks/log.txt");
    fileLogger.log_mess("Logging to a file.");*/

    cout << is_palindrome("teiilpiiet") << "  " <<
        is_palindrome("") << "  " <<
        is_palindrome("kereek") << "  " << is_palindrome("teret");

    return 0;
}

