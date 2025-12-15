#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>

class InvalidEmployeeNumber : public std::logic_error {
public:
    
    InvalidEmployeeNumber()
        : std::logic_error("Error: Invalid Employee Number. Format must be XXX-L (e.g., 123-A).") {}
};

class InvalidHireDate : public std::logic_error {
public:
    
    InvalidHireDate()
        : std::logic_error("Error: Invalid Hire Date Year. Year must be between 2000 and 2025.") {}
};

class EmployeeInfo {
private:
    std::string name;
    std::string employeeNumber;
    std::string hireDate; 

    static const int MIN_YEAR = 2000;
    static const int MAX_YEAR = 2025;

    void validateEmployeeNumber(const std::string& num) const {
        if (num.length() != 5) {
            throw InvalidEmployeeNumber();
        }

        for (int i = 0; i < 3; ++i) {
            if (!isdigit(num[i])) {
                throw InvalidEmployeeNumber();
            }
        }

        if (num[3] != '-') {
            throw InvalidEmployeeNumber();
        }

        char lastChar = toupper(num[4]);
        if (lastChar < 'A' || lastChar > 'M') {
            throw InvalidEmployeeNumber();
        }
    }

    void validateHireDate(const std::string& date) const {
        if (date.length() < 4) {
            
            return; 
        }

        try {
            int year = std::stoi(date.substr(0, 4));
            if (year < MIN_YEAR || year > MAX_YEAR) {
                throw InvalidHireDate();
            }
        } catch (const std::invalid_argument&) {
            
            std::cerr << "Warning: Date string format is unreadable.\n";
        }
    }

public:
    
    EmployeeInfo(const std::string& n, const std::string& num, const std::string& date)
        : name(n) {
        setEmployeeNumber(num); 
        setHireDate(date);       
    }

    EmployeeInfo() : name(""), employeeNumber(""), hireDate("") {}

    void setEmployeeNumber(const std::string& num) {
        validateEmployeeNumber(num);
        employeeNumber = num;
    }

    void setHireDate(const std::string& date) {
        validateHireDate(date);
        hireDate = date;
    }

    void setName(const std::string& n) {
        name = n;
    }


    std::string getName() const { return name; }
    std::string getEmployeeNumber() const { return employeeNumber; }
    std::string getHireDate() const { return hireDate; }


    void displayInfo() const {
        std::cout << "\n[Employee Details]\n";
        std::cout << "  Name: " << name << "\n";
        std::cout << "  Number: " << employeeNumber << "\n";
        std::cout << "  Hire Date: " << hireDate << "\n";
    }
};

void runTest(const std::string& testName, const std::string& employeeName, 
             const std::string& empNum, const std::string& date) {
    std::cout << "\n==================================================\n";
    std::cout << "TEST SCENARIO: " << testName << "\n";
    std::cout << "  Attempting to create: " << employeeName 
              << ", Number: " << empNum << ", Date: " << date << "\n";
    std::cout << "--------------------------------------------------\n";

    try {
        EmployeeInfo employee(employeeName, empNum, date);
        employee.displayInfo();

    } catch (const InvalidEmployeeNumber& e) {
      
        std::cerr << "!!! EXCEPTION CAUGHT (Employee Number): " << e.what() << "\n";

    } catch (const InvalidHireDate& e) {
        
        std::cerr << "!!! EXCEPTION CAUGHT (Hire Date): " << e.what() << "\n";

    } catch (const std::exception& e) {
        
        std::cerr << "!!! UNEXPECTED EXCEPTION: " << e.what() << "\n";
    }

    std::cout << "==================================================\n";
}

int main() {
    std::cout << "--- Encapsulated Exception Handling Demo ---\n";
  
    runTest("Valid Employee Creation", "Alice Wonder", "987-M", "2020-07-01");


    runTest("Invalid Number (Too Short)", "Bob Smith", "12-A", "2023-01-01");

 
    runTest("Invalid Number (Non-Digit)", "Charlie Brown", "A12-B", "2019-05-01");


    runTest("Invalid Number (Letter N)", "David Lee", "000-N", "2022-12-15");


    runTest("Invalid Hire Date (Too Early)", "Eve Adams", "111-C", "1999-01-01");


    runTest("Invalid Hire Date (Too Late)", "Frank Jones", "222-D", "2026-10-31");


    runTest("Both Invalid (Number First)", "Grace Kelly", "5-G", "2030-01-01");

    return 0;
}