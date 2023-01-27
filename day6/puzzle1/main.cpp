#include <iostream>
#include <stdio.h>
#include <cassert>
#include <string>
#include <fstream>
#include <set>


void read_input(std::string file_name){

    assert(!(file_name.empty()));
    std::fstream input_file(file_name);

    while(input_file.is_open()){
        if(input_file.eof()){
            input_file.close();
        }
        else {
            std::string line;
            std::string substr_line_len4;
            std::set<char> set_substr;
            int i;
            while(getline(input_file, line)){
                substr_line_len4 = line.substr(0, 4);
                i = 1;
                for(auto elem : substr_line_len4) {
                    set_substr.insert(elem);
                }
                while(set_substr.size() != 4){
                    //std::cout << set_substr.size() << std::endl;
                    substr_line_len4 = line.substr(i, 4);
                    set_substr.clear();
                    for(auto elem : substr_line_len4) {
                        set_substr.insert(elem);
                    }
                    //std::cout << substr_line_len4 << " | set size : " <<set_substr.size()<< std::endl;
                    ++i;
                }
            }
            std::cout << " chaine : " << substr_line_len4 << " | nb letters : " << i+3 << std::endl;
        }
    }
}

int main(int argc, char* argv[]){
    std::string file_name = argv[1];
    read_input(file_name);
    return 0;
}