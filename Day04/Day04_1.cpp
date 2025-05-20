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

int check_horizontal( std::vector<std::vector<char>> arr )
{
    int counter{ 0 };
    size_t n{ arr.size() };
    for ( int i = 0; i < n; i++ )
    {
        for ( int j = 0; j < n-4; j++)
        {
            std::string str{};
            str.push_back( arr[i][j] );
            str.push_back( arr[i][j+1] );
            str.push_back( arr[i][j+2] );
            str.push_back( arr[i][j+3] );
            // std::cout << str << std::endl;
            if ( str == "XMAS" || str == "SAMX" )
            {
                counter++;
                // std::cout << "Found: " << str << std::endl;
            }
        }
    }
    return counter;
}

int check_vertical( std::vector<std::vector<char>> arr )
{
    int counter{ 0 };
    size_t n{ arr.size() };
    for ( int i = 0; i < n-4; i++ )
    {
        for ( int j = 0; j < n; j++)
        {
            std::string str{};
            str.push_back( arr[i][j] );
            str.push_back( arr[i+1][j] );
            str.push_back( arr[i+2][j] );
            str.push_back( arr[i+3][j] );
            if ( str == "XMAS" || str == "SAMX" )
            {
                counter++;
            }
        }
    }
    return counter;
}


int main() 
{
    std::string fileName{ "test_input.txt" };
    std::vector<std::vector<char>> input{ input_to_array(fileName) };
    
    int counter{ 0 };
    counter += check_horizontal( input );
    // for( auto const& row : input )
    // {
    //     for( auto const& c : row )
    //     {
    //         std::cout << c;
    //     }
    //     std::cout << std::endl;
    // }
    
    std::cout << "Sum: " <<  std::endl;
    return EXIT_SUCCESS;
}