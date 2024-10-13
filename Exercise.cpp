#include <iostream>   // For input and output
#include <vector>     // For std::vector
#include <map>        // For std::map
#include <algorithm>  // For algorithms
#include <numeric>    // For std::accumulate
#include <cmath>      // For sqrt()
#include <fstream>    // For std::ifstream
#include <sstream>    // For std::stringstream
#include <iterator>
#include <iostream>
using namespace std;

void logResultToFile(const std::string& result) {
    // Log to file
    std::ofstream outfile("test_results.txt", std::ios_base::app);  // Open in append mode
    if (outfile.is_open()) {
        outfile << result << std::endl;
    } else {
        std::cerr << "Error opening file to log results" << std::endl;
    }
    
    // Print to terminal
    std::cout << result << std::endl;
}


void realNums(std::vector<double>& nums){
    if (nums.empty()) {
        std::cout << "No numbers entered." << std::endl;
        return; // Exit if the vector is empty
    }
    double max = *std::max_element(nums.begin(), nums.end());
    double min = *std::min_element(nums.begin(), nums.end());
    int n = nums.size();
    double sum = std::accumulate(nums.begin(), nums.end(), 0.0);
    double mean = sum/n;
    std::cout << "Max Value: " << max << std::endl;
    std::cout << "Min Value: " << min << std::endl;
    std::cout << "Mean Value: " << mean << std::endl;
}

template <class elemType>
void reverseVector(vector<elemType> &vec)
{
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
int seqSearch(const vector<elemType> &list, const elemType& item){
    for(int i = 0; i < list.size(); i++){
        if(list[i]==item){
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

void histogram(){
    std::map<int, int> histMap;
    int num;
    while(true){
        std::cout << "Enter a number (or -1 to finish): ";
        std::cin >> num;
        if (num == -1) break;
        // Update the map (histogram)
        histMap[num]++;
    }

    std::cout << "\nHistogram:\n";
    for (const auto& input : histMap) {
        std::cout << "The number " << input.first << " occurs " << input.second << " times." << std::endl;;
    }
}

int main() {

    histogram();

    std::vector<double> nums; // Vector to store numbers from CSV
    std::ifstream file("test_data.csv");
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    // Read the CSV file, skipping the header
    std::getline(file, line); // Skip header
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

    // Call the functions to test them
    realNums(nums);
    reverseVector(nums);

    // Test seqSearch
    double seqInput;
    std::cout << "Input a number to search for: ";
    std::cin >> seqInput;
    double searchValue = 2.5;
    int index = seqSearch(nums, searchValue);
    if (index != -1) {
        std::cout << searchValue << " found at index: " << index << std::endl;
    } else {
        std::cout << searchValue << " not found in the list." << std::endl;
    }

    // Test GetStats
    stats<double> result = GetStats(nums);
    std::cout << "Mean: " << result.mean << ", SD: " << result.sd << std::endl;

    return 0;
}
