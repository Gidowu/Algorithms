#include <iostream>   // For input and output
#include <vector>     // For std::vector
#include <map>        // For std::map
#include <algorithm>  // For algorithms
#include <numeric>    // For std::accumulate
#include <cmath>      // For sqrt()
#include <fstream>    // For std::ifstream
#include <sstream>    // For std::stringstream
#include <iterator>
#include <string>
using namespace std;

void realNums(std::vector<double>& nums) {
    if (nums.empty()) {
        std::cout << "No numbers entered." << std::endl;
        return; // Exit if the vector is empty
    }
    double max = *std::max_element(nums.begin(), nums.end());
    double min = *std::min_element(nums.begin(), nums.end());
    int n = nums.size();
    double sum = std::accumulate(nums.begin(), nums.end(), 0.0);
    double mean = sum / n;
    std::cout << "Max Value: " << max << std::endl;
    std::cout << "Min Value: " << min << std::endl;
    std::cout << "Mean Value: " << mean << std::endl;
}

template <class elemType>
void reverseVector(vector<elemType>& vec) {
    int n = vec.size();
    for (int i = 0; i < n / 2; ++i) {
        std::swap(vec[i], vec[n - 1 - i]);
    }
    // Print the reversed vector
    std::cout << "Reversed Vector: ";
    for (const auto& elem : vec) {
        std::cout << elem << " "; // Print each element followed by a space
    }
    std::cout << std::endl; // New line at the end
}

template <class elemType>
int seqSearch(const vector<elemType>& list, const elemType& item) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i] == item) {
            return i;
        }
    }
    return -1;
}

template <class elemType>
struct stats {
    elemType mean;
    elemType sd;
};

template <class elemType>
stats<elemType> GetStats(std::vector<elemType>& nums) {
    stats<elemType> result;
    int n = nums.size();
    if (n == 0) {
        result.mean = 0;
        result.sd = 0;
        return result;
    }
    elemType sum = std::accumulate(nums.begin(), nums.end(), static_cast<elemType>(0));
    result.mean = sum / n;
    elemType sum2 = 0;
    for (int i = 0; i < n; i++) {
        sum2 += std::pow(nums[i] - result.mean, 2);
    }
    result.sd = std::sqrt(sum2 / n);
    return result;
}

// Updated histogram function with multiple sets and only positive numbers
void histogram() {
    while (true) {
        std::map<int, int> histMap;
        int num;

        std::cout << "Enter numbers for this set (or -1 to finish): \n";

        while (true) {
            std::cout << "Enter a positive number (or -1 to finish this set): ";
            std::cin >> num;
            if (num == -1) break;
            if (num <= 0) {
                std::cout << "Only positive numbers are allowed. Try again.\n";
                continue;
            }
            histMap[num]++;
        }

        std::cout << "\nHistogram for this set:\n";
        for (const auto& input : histMap) {
            std::cout << "The number " << input.first << " occurs " << input.second << " times.\n";
        }

        char choice;
        std::cout << "Do you want to enter another set? (y/n): ";
        std::cin >> choice;

        if (choice != 'y' && choice != 'Y') {
            break;
        }
    }
}

int main() {

    // Test histogram function
    // histogram();

    // Vector to store numbers from CSV
    while(true){
        int inputSwitch1;
        std::cout << "Select 1 to input a vector, 2 to input a histogram, or 3 to quit: ";
        std::cin >> inputSwitch1;
        std::vector<double> nums;
        std::string inputCase1;
        switch(inputSwitch1){
            case 1:
                while (true) {
                    std::cout << "Enter a numbers for your vector (or q to finish): ";
                    std::getline(std::cin, inputCase1);
                    if (inputCase1 == "q") {
                        break; // Stop processing if 's' is encountered
                    }
                    try {
                        double value = std::stod(inputCase1);
                        nums.push_back(value); // Add input to the vector
                    } catch (const std::invalid_argument&) {
                        std::cout << "Invalid input: " << inputCase1 << std::endl;
                    }
                }
                int inputSwitch2;
                std::cout << "Select 1 to get vector statistics, 2 to reverse the vector, 3 to do a sequence search, or 4 to quit: ";
                std::cin >> inputSwitch2;
                switch(inputSwitch2){
                    case 1:{
                        realNums(nums);
                        break;
                    }
                    case 2:{
                        reverseVector(nums);
                        break;
                    }
                    case 3:{
                        double searchValue;
                        std::cout << "Input a number to search for: ";
                        std::cin >> searchValue;
                        int index;
                        index = seqSearch(nums, searchValue);
                        if (index != -1) {
                            std::cout << searchValue << " found at index: " << index << std::endl;
                        } else {
                            std::cout << searchValue << " not found in the list." << std::endl;
                        }
                        break;
                    }
                    case 4: {break;}
                }
            case 2: {
                histogram();
                break;
                }
            case 3: {break;}
        }
}




    //std::ifstream file("test_data.csv");
    //std::string line;

    /*if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }*/

    // Read the CSV file, skipping the header
    /*std::getline(file, line); // Skip header
    while (getline(file, line)) {
        if (line == "s") {
            break; // Stop processing if 's' is encountered
        }
        try {
            double value = std::stod(line);
            nums.push_back(value); // Add input to the vector
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input: " << line << std::endl;
        }
    }
    */

    // Test other functions
    // realNums(nums);
    // reverseVector(nums);

    // Test seqSearch
    /*double searchValue;
    std::cout << "Input a number to search for: ";
    std::cin >> searchValue;
    int index = seqSearch(nums, searchValue);
    if (index != -1) {
        std::cout << searchValue << " found at index: " << index << std::endl;
    } else {
        std::cout << searchValue << " not found in the list." << std::endl;
    }*/

    // Test GetStats
    // stats<double> result = GetStats(nums);
    // std::cout << "Mean: " << result.mean << ", SD: " << result.sd << std::endl;

    return 0;
}
