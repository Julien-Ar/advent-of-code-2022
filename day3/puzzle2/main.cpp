#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <set>

char unique_duplicate_item(const std::string & first_line, const std::string & second_line, 
                           const std::string & third_line ){

    // it = iterator

    std::set<char> set_line1 = std::set(first_line.begin(), first_line.end());
    std::set<char> set_line2 = std::set(second_line.begin(), second_line.end());
    std::set<char> set_line3 = std::set(third_line.begin(), third_line.end());


    char duplicated_item = '-';
    for( auto it1 = set_line1.begin(); it1 != set_line1.end(); ++it1){
        
        for( auto it2 = set_line2.begin(); it2 != set_line2.end(); ++it2){
            for( auto it3 = set_line3.begin(); it3 != set_line3.end(); ++it3){
                
                if( (*it1 == *it2 ) && (*it2 == *it3) ){
                    duplicated_item = *it1;
                    return duplicated_item;
                }
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
    std::vector<std::string> vec_3_lines;
    int total_priorities= 0;
    char duplicate_item;
    int count = 1;
    while(input_file.is_open()){
        if(input_file.eof()){
            // End of file reached
            duplicate_item = unique_duplicate_item(vec_3_lines[0],vec_3_lines[1], vec_3_lines[2]);
            std::cout << "duplicate item : " << duplicate_item << " | group : " << count << std::endl;
            total_priorities += lookup_priority[duplicate_item];
            input_file.close();
        }
        else {
            std::string current_line;
            int line_read = 1; // to enter the while loop one line is read
            
            while(getline(input_file, current_line)){

                if(line_read <= 3){
                    vec_3_lines.push_back(current_line);
                    line_read++;
                }
                else{
                    line_read = 2; // one line is read to enter this 'else' and another is read to enter the 'if' condition
                    duplicate_item = unique_duplicate_item(vec_3_lines[0],vec_3_lines[1], vec_3_lines[2]);
                    std::cout << "duplicate item : " << duplicate_item << " | group : " << count << std::endl;
                    ++count;

                    vec_3_lines = {current_line}; // line read to enter this 'else'

                    total_priorities += lookup_priority[duplicate_item];
                }            
            }
        }
    }
    std::cout << "Total sum of priorities : " << total_priorities << std::endl;

    return 0;
}