#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>

template <typename T>
class NumberArray {
private:
    
    T* aPtr;         
    int arraySize;   
    void deepCopy(const T* sourcePtr) {
        if (sourcePtr != nullptr) {
            aPtr = new T[arraySize];
            for (int i = 0; i < arraySize; ++i) {
                aPtr[i] = sourcePtr[i];
            }
        } else {
            aPtr = nullptr;
        }
    }

public:
    
    NumberArray(int size) : aPtr(nullptr), arraySize(size) {
        if (size <= 0) {
            throw std::invalid_argument("Array size must be positive.");
        }
        deepCopy(nullptr); 
        if (aPtr == nullptr) { 
             aPtr = new T[arraySize](); 
        }
    }

    
    NumberArray(std::initializer_list<T> list) : aPtr(nullptr), arraySize(static_cast<int>(list.size())) {
        if (arraySize == 0) {
            throw std::invalid_argument("Initializer list cannot be empty.");
        }

        aPtr = new T[arraySize];
        int i = 0;
        for (const T& val : list) {
            aPtr[i++] = val;
        }
    }

    
    NumberArray(const NumberArray<T>& other) : aPtr(nullptr), arraySize(other.arraySize) {
        std::cout << "  (Deep Copy Constructor invoked.)\n";
        deepCopy(other.aPtr);
    }

    ~NumberArray() {
        if (aPtr != nullptr) {
            delete[] aPtr;
            aPtr = nullptr;
            arraySize = 0;
           
        }
    }

    
    void setElement(int index, T value) {
        if (index < 0 || index >= arraySize) {
            throw std::out_of_range("Index out of bounds in setElement.");
        }
        aPtr[index] = value;
    }

    
    T getElement(int index) const {
        if (index < 0 || index >= arraySize) {
            throw std::out_of_range("Index out of bounds in getElement.");
        }
        return aPtr[index];
    }

    
    NumberArray<T>& operator=(const NumberArray<T>& right) {
        std::cout << "  (Deep Assignment Operator invoked.)\n";

       
        if (this != &right) {
            
            if (aPtr != nullptr) {
                delete[] aPtr;
            }

            
            arraySize = right.arraySize;
            deepCopy(right.aPtr);
        }
        return *this;
    }

    T& operator[](int index) {
        if (index < 0 || index >= arraySize) {
            throw std::out_of_range("Index out of bounds using [].");
        }
        return aPtr[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= arraySize) {
            throw std::out_of_range("Index out of bounds using [].");
        }
        return aPtr[index];
    }


    T getSum() const {
        T sum = 0; 
        for (int i = 0; i < arraySize; ++i) {
            sum += aPtr[i];
        }
        return sum;
    }
   
    double getAverage() const {
        if (arraySize == 0) return 0.0;
        return static_cast<double>(getSum()) / arraySize;
    }

    
    T getHighest() const {
        if (arraySize == 0) {
            throw std::runtime_error("Cannot find highest element in empty array.");
        }
        T maxVal = aPtr[0];
        for (int i = 1; i < arraySize; ++i) {
            if (aPtr[i] > maxVal) {
                maxVal = aPtr[i];
            }
        }
        return maxVal;
    }

    T getLowest() const {
        if (arraySize == 0) {
            throw std::runtime_error("Cannot find lowest element in empty array.");
        }
        T minVal = aPtr[0];
        for (int i = 1; i < arraySize; ++i) {
            if (aPtr[i] < minVal) {
                minVal = aPtr[i];
            }
        }
        return minVal;
    }


    void display(const std::string& description) const {
        std::cout << "\n--- " << description << " (Size: " << arraySize << ") ---\n";
        std::cout << "Data: [";
        for (int i = 0; i < arraySize; ++i) {
            std::cout << aPtr[i] << (i < arraySize - 1 ? ", " : "");
        }
        std::cout << "]\n";
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Sum: " << getSum() << "\n";
        std::cout << "Average: " << getAverage() << "\n";
        std::cout << "Highest: " << getHighest() << "\n";
        std::cout << "Lowest: " << getLowest() << "\n";
    }
};


int main() {
    std::cout << "--- NumberArray Template Class Demonstration ---\n";

    try {
       
        std::cout << "\n[1. Testing Integer Array (int)]\n";

        NumberArray<int> intArray = {10, 20, 5, 45, 12, 1};
        intArray.display("Initial Integer Array"); 
    
        intArray.setElement(2, 50); 
        intArray[5] = 100;        
        intArray.display("After Changes (int)"); 
        
        std::cout << "\n[2. Testing Deep Copy Constructor]\n";
        NumberArray<int> copiedIntArray = intArray; 
        copiedIntArray[0] = 999; 
        intArray.display("Original Array (after copy modification)");
        copiedIntArray.display("Copied Array (modified)");
        
        std::cout << "\n[3. Testing Deep Assignment Operator]\n";
        NumberArray<int> assignedIntArray(4); 
        assignedIntArray = intArray; 
        assignedIntArray.display("Assigned Array");

        std::cout << "\n[4. Testing Floating Point Array (double)]\n";
        NumberArray<double> doubleArray(5);
        doubleArray.setElement(0, 1.5);
        doubleArray.setElement(1, 2.7);
        doubleArray.setElement(2, 3.1);
        doubleArray.setElement(3, 4.0);
        doubleArray.setElement(4, 5.2);
        doubleArray.display("Initial Double Array");

       
        std::cout << "\n[5. Testing Exceptions]\n";
        try {
            doubleArray.setElement(5, 99.9); 
        } catch (const std::out_of_range& e) {
            std::cerr << "!!! EXCEPTION CAUGHT (Out of Range): " << e.what() << "\n";
        }

        try {
            NumberArray<int> zeroArray(0); 
        } catch (const std::invalid_argument& e) {
            std::cerr << "!!! EXCEPTION CAUGHT (Invalid Argument): " << e.what() << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "\n!!! UNEXPECTED GLOBAL EXCEPTION: " << e.what() << "\n";
    }

    std::cout << "\n--- Program complete. All dynamic memory should be freed via destructors. ---\n";
    return 0;
}