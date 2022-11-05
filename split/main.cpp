#include <iostream>
#include <string>
#include <vector>

using namespace std;

// TODO: Implement split function here
// Do not change main function

vector<string> split(string line,char separator,bool empty = false) {
    vector<string> splited;
    int pos_separator = 0;
    for (string::size_type i = 0; i <= line.length()-1; i++) {
        if (line.at(i) == separator) {
            string sub_string = line.substr(pos_separator,i-pos_separator);
            pos_separator = i+1;
            if (empty == true) {
                if (sub_string != "") {
                    splited.push_back(sub_string);
                }
             } else
                splited.push_back(sub_string);
        }
    }
    splited.push_back(line.substr(pos_separator));
    return splited;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto& part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto& part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
