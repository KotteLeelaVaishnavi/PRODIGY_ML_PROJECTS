#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <map>
#include <sstream>

// Simulated food database
std::map<std::string, int> food_database = {
    {"apple", 95},
    {"banana", 105},
    {"orange", 62},
    {"chicken breast", 165},
    {"rice", 206},
    {"broccoli", 55},
    {"carrot", 41},
    {"pizza slice", 285},
    {"hamburger", 354},
    {"salad", 100}
};

// Simple function to simulate image recognition
std::vector<std::string> recognize_food(const std::string& image_description) {
    std::vector<std::string> recognized_items;
    std::string item;
    std::istringstream iss(image_description);
    
    while (iss >> item) {
        std::transform(item.begin(), item.end(), item.begin(),
            [](unsigned char c){ return std::tolower(c); });
        
        if (food_database.find(item) != food_database.end()) {
            recognized_items.push_back(item);
        }
    }
    
    return recognized_items;
}

// Function to estimate calories
int estimate_calories(const std::vector<std::string>& food_items) {
    int total_calories = 0;
    for (const auto& item : food_items) {
        total_calories += food_database[item];
    }
    return total_calories;
}

// Function to display results
void display_results(const std::vector<std::string>& recognized_items, int total_calories) {
    std::cout << "Recognized food items:" << std::endl;
    for (const auto& item : recognized_items) {
        std::cout << "- " << item << " (" << food_database[item] << " calories)" << std::endl;
    }
    std::cout << "Total estimated calories: " << total_calories << std::endl;
}

int main() {
    std::string image_description;
    std::cout << "Enter a description of the food in the image: ";
    std::getline(std::cin, image_description);

    std::vector<std::string> recognized_items = recognize_food(image_description);
    int total_calories = estimate_calories(recognized_items);

    display_results(recognized_items, total_calories);

    return 0;
}