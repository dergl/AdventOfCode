#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <algorithm>

std::string input_to_single_string( std::string const& fileName )
{
    std::string input{};
    std::ifstream inFile{ fileName };
    for( std::string line; std::getline( inFile, line ); )
    {
        // std::cout << "\n    !!New line!!    \n";
        input += line;
    }
    return input;
}

std::vector<std::string> split_string_at_mul( std::string const& str )
{
    std::vector<std::string> result;
    std::string delimiter{ "mul(" };
}


int main() 
{
    std::string fileName{ "input.txt" };
    std::string input{ input_to_single_string(fileName) };
    
    std::cout << "Input: " << input << std::endl;
    return 0;
}