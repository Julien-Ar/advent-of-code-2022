#include <iostream> 
#include <string>
#include <fstream>
#include <regex>
#include <vector>
#include <typeinfo>

int main(int argc, char* argv[]){

    std::string file_name = argv[1];
    std::cout << "File name given : " << file_name << std::endl;

    std::fstream input_file(file_name);

    while(input_file.is_open()){
        if(input_file.eof()){
            input_file.close();
        }
        else{
            std::string line, line_search;
            std::regex rgx(R"(\d+)"); // regex that recognizes a digit or number
            std::smatch match;
            std::vector<int> section_IDs;
            int pair_nb = 0;
            int line_nb = 1;
            while(getline(input_file, line)){
                line_search = line;
                while (std::regex_search(line_search, match, rgx)){
                    // get the first match, then search among the rest of the line
                    section_IDs.push_back(std::stoi(match[0]));
                    line_search = match.suffix();
                }
                //  a < d and b > c
                if ( ((section_IDs[0] <= section_IDs[3]) && (section_IDs[1] >= section_IDs[2])) ) { 
                    ++pair_nb;
                    std::cout << line <<" | line nb : " << line_nb << std::endl;
                    ++line_nb;
                    section_IDs.clear();

                }
                else {
                    std::cout << " ---- OK line : " << line << " | line nb : " <<line_nb << std::endl; 
                    ++line_nb;
                    section_IDs.clear();
                }

            }
        std::cout << "Pair number : " << pair_nb << std::endl;
        }
    }
}