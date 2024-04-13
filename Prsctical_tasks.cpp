#include <iostream>
#include <string>
#include <stack>
#include <stdexcept>
#include <cstdlib>
#include <sstream>
using namespace std; 


class VersionException {
    std::string Exception;
public:
    VersionException(std::string Exception):Exception(Exception){}
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


int main(void) {

	return 0;
}




		



