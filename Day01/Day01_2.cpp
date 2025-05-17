#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>

int const get_number_of_lines ( const std::string& file_name )
{
    int counter{ 0 };
    std::string x;
    std::ifstream inFile;
    inFile.open(file_name);
    if (!inFile) {
        std::cerr << "Unable to open file: " << file_name << "\n";
        exit(1); // call system to stop
    }

    while ( inFile >> x )
    {
        counter++;
    }
    inFile.close();

    return counter;
}

std::tuple<std::vector<int>, std::vector<int>> transform_input ( const std::string& fileName ) 
{
    int x;
    std::ifstream inFile;
    inFile.open(fileName);
    if (!inFile) {
        std::cerr << "Unable to open file input.txt";
        exit(1); // call system to stop
    }

    int no_lines = get_number_of_lines(fileName);
    std::vector<int> list_1{ std::vector<int>(no_lines/2) };
    std::vector<int> list_2{ std::vector<int>(no_lines/2) };

    int ind{ 0 };
    bool is_list_1{ true };

    while ( inFile >> x )
    {
        if ( is_list_1)
        {
            list_1[ind] = x;
            is_list_1 = false;
        }
        else
        {
            list_2[ind] = x;
            is_list_1 = true;
            ind++;
        }
    }

    inFile.close();

    return { list_1, list_2};
} 

int const compute_total_distance ( const std::vector<int>& list_1, const std::vector<int>& list_2 )
{
    int total_distance{ 0 };
    for ( int i = 0; i < list_1.size(); i++ )
    {
        total_distance += abs(list_1[i] - list_2[i]);
    }
    return total_distance;
}

int const compute_similarity_score  ( const std::vector<int>& list_1, const std::vector<int>& list_2 )
{
    int score{ 0 };

    // Option 1: Using a for loop
    for ( int i = 0; i < list_1.size(); i++ )
    {
        score += list_1[i] * std::count(list_2.begin(), list_2.end(), list_1[i]);
    }

    // Option 2: Using std::accumulate
    score = std::accumulate(list_1.begin(), list_1.end(), 0, [&list_2](int s, int x){ return s + x * std::count(list_2.begin(), list_2.end(), x); });

    return score;
}

int main() {
    std::string fileName= "input.txt";
    // std::string fileName= "test_input.txt";
    
    std::tuple<std::vector<int>, std::vector<int>> lists = transform_input( fileName );
    std::vector<int> list_1{ std::get<0>(lists) };
    std::vector<int> list_2{ std::get<1>(lists) };
    
    std::sort(list_1.begin(), list_1.end());
    std::sort(list_2.begin(), list_2.end());

    std::cout << "Total distance: " << compute_total_distance(list_1, list_2) << std::endl;
    std::cout << "Similarity score: " << compute_similarity_score(list_1, list_2) << std::endl;
    return 0;
}