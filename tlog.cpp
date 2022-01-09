#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "color.h"

int main(int argc, char *argv[]) {

    const char* file("/Users/jack/tlog/.tlog");
    
    // Read file
    if (argc == 1) {
        std::ifstream infile(file);
        std::string line;
        while (std::getline(infile, line)) {            
            bool is_date(true);
            bool is_time(true);
            std::string word;
            std::istringstream iss(line, std::istringstream::in);
            while( iss >> word ) {
                if (is_date) {
                    std::cout << KYEL << word << RST << ' ';
                    is_date = false;
                } else if (is_time) {
                    std::cout << KCYN << word << RST << ' ';
                    is_time = false;
                } else {
                    std::cout << word << ' ';
                }
            }
            std::cout << std::endl;
        }
        return 0;
    }

    // Write file
    std::ofstream outfile;
    outfile.open(file, std::ios_base::app); // Append instead of overwrite
    time_t now = time(0);
    tm* ltm = localtime(&now);
    outfile << 1900 + ltm->tm_year << '/';
    outfile << std::setfill('0') << std::setw(2) << 1 + ltm->tm_mon << '/';
    outfile << std::setfill('0') << std::setw(2) << ltm->tm_mday << ' ';
    outfile << std::setfill('0') << std::setw(2) << 5+ltm->tm_hour << ':';
    outfile << std::setfill('0') << std::setw(2) << 30+ltm->tm_min << ':';
    outfile << std::setfill('0') << std::setw(2) << ltm->tm_sec << ' ';
    for (size_t idx=1; idx!=argc; ++idx) {
        outfile << argv[idx];
        if (idx!=argc-1) {
            outfile << ' ';
        }
    }
    outfile << '\n';
    return 0;
}