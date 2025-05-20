#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <algorithm>

bool do_or_dont( std::string str, bool do_ )
{
    auto last_do{ str.rfind( "do()" , str.size()) };
    auto last_dont{ str.rfind( "don't()", str.size()) };
    
    // No 'do' or 'dont' in the string -> leave boolean unchanged
    if ( last_do == std::string::npos && last_dont == std::string::npos )
    {
        return do_;
    }

    // No 'do', but at least one 'dont' in the string
    if ( last_do == std::string::npos && last_dont != std::string::npos )
    {
        return false;
    }

    // No 'dont', but at least one 'do' in the string
    else if ( last_do != std::string::npos && last_dont == std::string::npos )
    {
        return true;
    }

    // Both 'do' and 'dont' in the string
    // Check which one is the last one
    if ( last_do > last_dont )
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string input_to_single_string( std::string const& fileName )
{
    std::string input{};
    std::ifstream inFile{ fileName };
    for( std::string line; std::getline( inFile, line ); )
    {
        input += line;
    }
    return input;
}

std::vector<std::string> split_string_at_mul( std::string const& str, bool& do_ )
{
    std::vector<std::string> result;
    std::string delimiter{ "mul(" };

    auto first{ str.find( delimiter ) };
    auto last{ str.rfind( delimiter ) - (delimiter.size()-1) };

    // Check whether the string has a do/dont before the first mul(
    do_ = do_or_dont( str.substr( 0, first ), do_ );

    // Sorting the strings of the form 'mul(....' into the vector
    while ( first < str.size()-1 )
    {
        auto next{ str.find( delimiter, first + 1 ) };
        if ( next == std::string::npos )
        {
            next = str.size();
        }
        result.push_back( str.substr( first, next - first ) );
        first = next;
    }

    return result;
}

bool is_form_valid( std::string const& str )
{
    // Print string for debugging
    // std::cout << str << std::endl;

    // Needs at least 8 characters to be valid: mul(a,b)
    if ( str.size() < 8 ) return false;
    
    // Check whether the string even has a ',' and a ')' after the ','
    auto comma{ str.find( ',' ) };
    if ( comma == std::string::npos ) return false;
    auto parenthesis{ str.find( ')', comma+1 ) };
    if ( parenthesis == std::string::npos ) return false;

    // Extracting the two substrings for the arguments
    std::string substr_a{ str.substr( 4, comma - 4 ) };
    std::string substr_b{ str.substr( comma+1, parenthesis - (comma+1) ) };
    
    if ( substr_a.empty() || substr_b.empty() ) return false;
    
    return true;
}

std::vector<std::string> get_arguments( std::string const& str )
{
    std::vector<std::string> result;
    auto comma{ str.find( ',' ) };
    auto parenthesis{ str.find( ')', comma+1 ) };
    std::string substr_a{ str.substr( 4, comma - 4 ) };
    std::string substr_b{ str.substr( comma+1, parenthesis - (comma+1) ) };
    result.push_back( substr_a );
    result.push_back( substr_b );
    return result;
}

bool is_valid_argument( std::vector<std::string> const& str )
{
    for ( auto const& s : str )
    {
        // Check whether the string is a number
        if ( !std::all_of( s.begin(), s.end(), ::isdigit ) )
        {
            return false;
        }
    }
    return true;
}

std::vector<int> args_to_int( std::vector<std::string> const& str )
{
    std::vector<int> result;
    for ( auto const& s : str )
    {
        std::string::size_type sz;
        int i{ std::stoi( s, &sz ) };
        result.push_back( i );
    }
    return result;
}

int main() 
{
    std::string fileName{ "input.txt" };
    std::string input{ input_to_single_string(fileName) };
    
    bool do_{ true };
    std::vector<std::string> split_input{ split_string_at_mul(input, do_) };

    int sum{ 0 };
    std::cout << do_ << std::endl;
    for (auto const& s : split_input)
    {
        std::cout << "string: " << s << std::endl;
        if ( is_form_valid(s) && do_ )
        {
            std::vector<std::string> args{ get_arguments(s) };
            if ( is_valid_argument( args ) )
            {
                std::vector<int> args_int{ args_to_int(args) };
                sum += args_int[0] * args_int[1];
            }
        }
        do_ = do_or_dont( s, do_ );
        std::cout << do_ << std::endl;
    }
    
    std::cout << "Sum: " << sum << std::endl;
    return EXIT_SUCCESS;
}