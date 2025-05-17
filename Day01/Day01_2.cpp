#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>

int get_number_of_lines ( std::string file_name )
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

std::tuple<std::vector<int>, std::vector<int>> transform_input ( std::string fileName ) 
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



int main() {
    std::string fileName= "input.txt";
    std::tuple<std::vector<int>, std::vector<int>> lists = transform_input( fileName );
    std::vector<int> list_1{ std::get<0>(lists) };
    std::vector<int> list_2{ std::get<1>(lists) };
    
    std::sort(list_1.begin(), list_1.end());
    std::sort(list_2.begin(), list_2.end());


    std::vector<int> list_difference;
    for ( int i = 0; i < list_1.size(); i++ )
    {
        list_difference.push_back( abs(list_1[i] - list_2[i]) );
    }
    
    int diff;
    diff = std::accumulate(list_difference.begin(), list_difference.end(), 0);

    std::cout << "Final difference: " << diff << std::endl;
    return 0;
}