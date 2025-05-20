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
        for ( int j = 0; j < n-3; j++)
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
    for ( int i = 0; i < n-3; i++ )
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

int check_top_left_to_down_right( std::vector<std::vector<char>> arr )
{
    int counter{ 0 };
    size_t n{ arr.size() };
    for ( int i = 0; i < n-3; i++ )
    {
        for ( int j = 0; j < n-3; j++)
        {
            std::string str{};
            str.push_back( arr[i][j] );
            str.push_back( arr[i+1][j+1] );
            str.push_back( arr[i+2][j+2] );
            str.push_back( arr[i+3][j+3] );
            if ( str == "XMAS" || str == "SAMX" )
            {
                counter++;
            }
        }
    }
    return counter;
}

int check_down_left_to_top_right( std::vector<std::vector<char>> arr )
{
    int counter{ 0 };
    size_t n{ arr.size() };
    for ( int i = 3; i < n; i++ )
    {
        for ( int j = 0; j < n-3; j++)
        {
            std::string str{};
            str.push_back( arr[i][j] );
            str.push_back( arr[i-1][j+1] );
            str.push_back( arr[i-2][j+2] );
            str.push_back( arr[i-3][j+3] );
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
    std::string fileName{ "input.txt" };
    std::vector<std::vector<char>> input{ input_to_array(fileName) };
    
    int counter{ 0 };
    counter += check_horizontal( input );
    counter += check_vertical( input );
    counter += check_top_left_to_down_right( input );
    counter += check_down_left_to_top_right( input );
    
    // std::cout << "Horizontal: " << check_horizontal( input ) << std::endl;
    // std::cout << "Vertical: " << check_vertical( input ) << std::endl;
    // std::cout << "Top left to down right: " << check_top_left_to_down_right( input ) << std::endl;
    // std::cout << "Down left to top right: " << check_down_left_to_top_right( input ) << std::endl;
    std::cout << "Sum: " << counter <<  std::endl;
    return EXIT_SUCCESS;
}