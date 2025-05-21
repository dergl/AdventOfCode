#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <algorithm>


std::vector<std::vector<char>> const input_to_array( std::string const& fileName )
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

int check_X( std::vector<std::vector<char>> const& arr, int i, int j )
{
    // Check top left to down right
    if ( (arr[i-1][j-1] != 'M' || arr[i+1][j+1] != 'S') && (arr[i-1][j-1] != 'S' || arr[i+1][j+1] != 'M') )
    {
        return 0;
    }
    
    // Check down left to top right
    if ( (arr[i+1][j-1] != 'M' || arr[i-1][j+1] != 'S') && (arr[i+1][j-1] != 'S' || arr[i-1][j+1] != 'M') )
    {
        return 0;
    }

    return 1;
}

int check_X_MAS( std::vector<std::vector<char>> const& arr )
{
    int counter{ 0 };
    size_t n{ arr.size() };
    for ( int i = 1; i < n-1; i++ )
    {
        for ( int j = 1; j < n-1; j++)
        {
            if ( arr[i][j] == 'A' )
            {
                counter += check_X( arr, i, j );
            }
        }
    }
    return counter;
}

int main() 
{
    std::string fileName{ "input.txt" };
    std::vector<std::vector<char>> input{ input_to_array(fileName) };
    
    int counter{ check_X_MAS( input ) };
    
    std::cout << "Sum: " << counter <<  std::endl;
    return EXIT_SUCCESS;
}