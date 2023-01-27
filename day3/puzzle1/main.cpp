#include <iostream>
#include <fstream>
#include <map>
#include <string>


char unique_duplicate_item(const std::string & first_half, const std::string & second_half){

    // it = iterator
    char duplicated_item = '-';
    for(auto it1 = first_half.begin(); it1 != first_half.end(); ++it1){
        for(auto it2 = second_half.begin(); it2 != second_half.end(); ++it2){
            
            if( (*it1) == (*it2) ){
                duplicated_item = *it1;
                return duplicated_item;
            }
        }
    }
    return duplicated_item;
}


int main(int argc, char * argv[]){

    std::string file_name = argv[1];

    std::ifstream input_file(file_name);
    std::cout << "file name given : " << file_name << std::endl;
    std::map<char, int> lookup_priority;

    std::pair<char, int> letter_and_prio;

    for(int i = 0; i<52; i++){
        
        if(i<26){
            letter_and_prio = {char(97+i), i+1}; 
            lookup_priority.insert(letter_and_prio);
            
        }
        else{
            letter_and_prio = {char(39+i), i+1};
            lookup_priority.insert(letter_and_prio);

        }
        //std::cout << letter_and_prio.first << " : " << letter_and_prio.second << std::endl;
    }

    while(input_file.is_open()){
        if(input_file.eof()){
            input_file.close();
        }
        else {
            std::string line, first_half, second_half;
            int line_nb = 0;
            int total_priorities= 0;
            char duplicate_item;
            while(getline(input_file, line)){
                first_half = line.substr(0, int(line.length()/2));
                second_half = line.substr(int(line.length()/2), int(line.length()/2));
                duplicate_item = unique_duplicate_item(first_half, second_half);
                std::cout << "duplicate : " << duplicate_item <<  " | line " << line_nb<<std::endl;
                ++line_nb;

                total_priorities += lookup_priority[duplicate_item];

            }
            std::cout << "Total sum of priorities : " << total_priorities << std::endl;
        }
    }


    return 0;
}