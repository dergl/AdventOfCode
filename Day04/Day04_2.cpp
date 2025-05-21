#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <algorithm>


std::vector<std::vector<char>> input_to_array( std::string const& fileName )
{
    std::vector<std::vector<char>> arr{};
    std::ifstream inFile{ fileName };
    for( std::string line; std::getline( inFile, line ); )
    {
        std::vector<char> row{};
        for( char c : line )
        {
            row.push_back( c );
        }
        arr.push_back( row );
    }
    return arr;
}




int main() 
{
    std::string fileName{ "input.txt" };
    std::vector<std::vector<char>> input{ input_to_array(fileName) };
    
    int counter{ /* TODO */ };
    
    std::cout << "Sum: " << counter <<  std::endl;
    return EXIT_SUCCESS;
}