#include <iostream>   // For input and output
#include <vector>     // For std::vector
#include <map>        // For std::map
#include <algorithm>  // For algorithms
#include <numeric>    // For std::accumulate
#include <cmath>      // For sqrt()
#include <fstream>    // For std::ifstream
#include <sstream>    // For std::stringstream
#include <iterator>   // For iterator usage
#include <string>     // For string manipulation
using namespace std;

// Function to calculate and print max, min, and mean of numbers in a vector
void realNums(std::vector<double>& nums) {
    if (nums.empty()) {
        std::cout << "No numbers entered." << std::endl;
        return; // Exit if the vector is empty
    }

    // Find the max and min values in the vector
    double max = *std::max_element(nums.begin(), nums.end());
    double min = *std::min_element(nums.begin(), nums.end());
    // Get the total number of elements
    int n = nums.size();
    // Calculate the sum of elements
    double sum = std::accumulate(nums.begin(), nums.end(), 0.0);
    // Calculate the mean
    double mean = sum / n;
    // Output the max, min, and mean
    std::cout << "Max Value: " << max << std::endl;
    std::cout << "Min Value: " << min << std::endl;
    std::cout << "Mean Value: " << mean << std::endl;
}

// Function template to reverse a vector of any type
template <class elemType>
void reverseVector(vector<elemType>& vec) {
    int n = vec.size();
    // Loop to swap elements from the start and end
    for (int i = 0; i < n / 2; ++i) {
        std::swap(vec[i], vec[n - 1 - i]);     // Swap the ith element with the (n-i-1)th element
    }
    // Print the reversed vector
    std::cout << "Reversed Vector: ";
    for (const auto& elem : vec) {
        std::cout << elem << " "; // Print each element followed by a space
    }
    std::cout << std::endl; // New line at the end
}

// Sequential search function template that returns the index of an element in the vector
template <class elemType>
int seqSearch(const vector<elemType>& list, const elemType& item) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i] == item) {
            return i;        // Return the index if the item is found
        }
    }
    return -1;              // Return -1 if the item is not found
}

// Structure to hold statistical data: mean and standard deviation
template <class elemType>
struct stats {
    elemType mean;
    elemType sd;            // Standard deviation
};

// Function to calculate the mean and standard deviation of a vector
template <class elemType>
stats<elemType> GetStats(std::vector<elemType>& nums) {
    stats<elemType> result;
    int n = nums.size();
    if (n == 0) {
        result.mean = 0;               // Return zero values if the vector is empty
        result.sd = 0;
        return result;
    }
    elemType sum = std::accumulate(nums.begin(), nums.end(), static_cast<elemType>(0));       // Calculate the mean
    result.mean = sum / n;
    elemType sum2 = 0;                  // Calculate the variance
    for (int i = 0; i < n; i++) {
        sum2 += std::pow(nums[i] - result.mean, 2);
    }
    result.sd = std::sqrt(sum2 / n);      // Calculate the standard deviation
    return result;                        // Return the calculated statistics
}

// Updated histogram function with multiple sets and only positive numbers
void histogram() {
    while (true) {
        std::map<int, int> histMap;        // Map to store numbers and their frequencies
        int num;

        std::cout << "Enter numbers for this set (or -1 to finish): \n";

        while (true) {
            std::cout << "Enter a positive number (or -1 to finish this set): ";
            std::cin >> num;

            if (std::cin.fail()) {
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input. Please enter a positive number.\n";
                continue; // Restart the loop
            }
            
            if (num == -1) break;     // Exit the loop if -1 is entered
            if (num <= 0) {
                std::cout << "Only positive numbers are allowed. Try again.\n";
                continue;
            }
            histMap[num]++;          // Increment the count of the entered number in the map
        }
        
        // Output the histogram
        std::cout << "\nHistogram for this set:\n";
        for (const auto& input : histMap) {
            std::cout << "The number " << input.first << " occurs " << input.second << " times.\n";
        }
         
        // Ask the user if they want to enter another set of numbers
        char choice;
        std::cout << "Do you want to enter another set? (y/n): ";
        std::cin >> choice;

        if (choice != 'y' && choice != 'Y') {
            break;                  // Exit the loop if the user chooses not to continue
        }
    }
}

int main() {

    while (true) {
        int inputSwitch1;
        std::cout << "Select 1 to input a vector, 2 to input a histogram, or 3 to quit: ";
        std::cin >> inputSwitch1;

        // Check if input failed (invalid input like letters or special characters)
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag on cin
            std::cin.ignore(10000, '\n'); // Discard the invalid input
            std::cout << "Invalid input. Please enter a number.\n";
            continue; // Prompt the user again
        }

        // Clear the input buffer to avoid issues with getline
        std::cin.ignore(10000, '\n'); // This handles the newline left over from std::cin

        std::vector<double> nums;
        std::string inputCase1;
        
        switch(inputSwitch1) {
            case 1: {
                // Input vector
                while (true) {
                    std::cout << "Enter numbers for your vector (or q to finish): ";
                    std::getline(std::cin, inputCase1);
                    if (inputCase1 == "q") {
                        break; // Stop processing if 'q' is entered
                    }
                    try {
                        double value = std::stod(inputCase1);    // Convert input to a double
                        nums.push_back(value); // Add input to the vector
                    } catch (const std::invalid_argument&) {
                        std::cout << "Invalid input: " << inputCase1 << std::endl;
                    }
                }

                int inputSwitch2;
                std::cout << "Select 1 to get vector statistics, 2 to reverse the vector, 3 to do a sequence search, or 4 to quit: ";
                std::cin >> inputSwitch2;

                switch(inputSwitch2) {
                    case 1: {
                        realNums(nums);     // Calculate and display statistics
                        break;
                    }
                    case 2: {
                        reverseVector(nums);    // Reverse the vector and display it
                        break;
                    }
                    case 3: {
                        double searchValue;
                        std::cout << "Input a number to search for: ";
                        std::cin >> searchValue;
                        int index = seqSearch(nums, searchValue);   // Search for the number in the vector
                        if (index != -1) {
                            std::cout << searchValue << " found at index: " << index << std::endl;
                        } else {
                            std::cout << searchValue << " not found in the list." << std::endl;
                        }
                        break;
                    }
                    case 4:
                        break; // Quit
                    default:
                        std::cout << "Invalid option." << std::endl;
                }
                break; // Break after handling the vector case
            }

            case 2: {
                // Input histogram
                histogram();  // Call the histogram function
                break;
            }

            case 3: {
                // Quit the program
                std::cout << "Exiting the program." << std::endl;
                return 0;
            }

            default: {
                std::cout << "Invalid input. Please select a valid option." << std::endl;
                break;
            }
        }
    }

    return 0;
}

    // This is the code we used in main to take in AI generated test data in our csv "test_data.csv".
    // The output of the code to the terminal is saved in test_output.txt to show that our tests were successful!

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
    }
    
    return 0;
    */
