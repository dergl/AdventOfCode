#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <algorithm>

class Report
{
    private:
        std::vector<int> report_data;

    public:
        Report( std::vector<int> const& v );
        bool is_data_safe();
        friend std::ostream& operator<<( std::ostream& os, const Report& report );
};

Report::Report( std::vector<int> const& v )
: report_data{ v }
{}

bool Report::is_data_safe()
{
    if( report_data.size() == 1)
    {
        std::cout << "Data only contains one element!" << std::endl;
        return true;
    }

    if( report_data[0] < report_data[1] )
    {
        return std::is_sorted( report_data.begin(), report_data.end(), 
                [](int a, int b){ return (a <= b) || (a-b > 3); } );       
    }
    else
    {
        return std::is_sorted(report_data.begin(), report_data.end(), 
                [](int a, int b){ return (a >= b) || (b-a > 3); } );
    }
}

std::ostream& operator<<( std::ostream& os, const Report& report )
{
    os << "Report: ";
    for ( auto& data : report.report_data )
    {
        os << data << " ";
    }
    return os;
}

std::vector<Report> input_to_reports( std::string const& fileName )
{
    std::vector<Report> reports;
    std::ifstream inFile{ fileName };
    
    for( std::string line; std::getline( inFile, line ); )
    {
        // split line by space and save to vector
        std::istringstream iss(line);
        std::vector<std::string> v_str;
        boost::split(v_str, line, boost::is_any_of(" "));
        
        // cast string vector to int vector
        std::vector<int> v(v_str.size());
        std::transform(v_str.begin(), v_str.end(), v.begin(), [](std::string& s) {
            return std::stoi(s);
        });

        Report report{ v };
        reports.push_back(report);
    }
    return reports;
}



int main() 
{
    std::string fileName{ "input.txt" };
    std::vector<Report> reports;
    reports = input_to_reports(fileName);
    int counter{ 0 };
    for ( auto& report : reports )
    {
        std::cout << report << ": ";
        if( report.is_data_safe() )
        {
            counter++;
            // std::cout << "safe" << std::endl;
        }
        // else
        // {
        //     std::cout << "unsafe" << std::endl;
        // }
    }
    std::cout << "Number of safe reports: " << counter << std::endl;
    return 0;
}