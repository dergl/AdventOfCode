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

    auto first{ str.find( delimiter ) };
    auto last{ str.find_last_of( delimiter ) - (delimiter.size()-1) };

    while ( first < last )
    {
        auto next{ str.find( delimiter, first + 1 ) };
        result.push_back( str.substr( first, next - first ) );
        first = next;
    }
    result.push_back( str.substr( last, str.size()-1 ) );

    // for ( auto const& s : result )
    // {
    //     std::cout << "substring: " << s << std::endl;
    // }
    return result;
}


int main() 
{
    std::string fileName{ "test_input.txt" };
    std::string input{ input_to_single_string(fileName) };
    
    std::cout << "Input: " << input << std::endl;
    std::vector<std::string> split_input{ split_string_at_mul(input) };
    
    return 0;
}