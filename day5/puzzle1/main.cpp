#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <algorithm>

int main(int argc, char * argv[]){

    std::string file_name = argv[1];
    std::fstream input_file(file_name);


    while(input_file.is_open()){
        if(input_file.eof()){
            input_file.close();
        }
        else{
            std::string line;
            std::vector< std::string > lines_stacks; // store the lines referring to the stacks
            std::smatch match;
            std::regex rgx_stack ("\\[");
            std::regex rgx_letter("[A-Z]+");
            std::regex rgx_instruction("move");
            std::regex rgx_number ("(\\d)+");
            std::vector < std::vector<int> > vec_instructions; // store each instruction  in a vector
            while(getline(input_file, line)){
                //std::cout << line << std::endl;
                if(std::regex_search(line, rgx_stack)){
                    //std::cout << line << std::endl;
                    lines_stacks.push_back(line);
                }
                if (std::regex_search(line, rgx_instruction)){
                    // store the quantity, and the locations of crates departures and destinations
                    std::string suffix = line;
                    std::vector <int> current_instructions;
                    while(std::regex_search(suffix, match, rgx_number)){
                        // get the first match, then search among the rest of the line
                        current_instructions.push_back(std::stoi(match[0]));
                        suffix = match.suffix();
                    }
                    vec_instructions.push_back(current_instructions);
                }

            }
            std::cout << "------------" << std::endl;

            std::vector < std::vector<std::string> > stacks(9); // 9 stacks are present in the file
            
            for(auto elem_lines_stacks : lines_stacks){
                int i = 0;
                int stack_nb = 0; 
                for (auto elem : elem_lines_stacks){
                    // if we are in position 1, 5, 9, 13 ,.....
                    if((i-1)%4 == 0){
                        // string(1, elem) creates the string of length 1 from char elem 
                        if(std::regex_match(std::string(1, elem), rgx_letter)){
                            // put the crate in the corresponding stack
                            stacks[stack_nb].push_back(std::string(1, elem));
                        }
                        ++stack_nb;
                    };
                    ++i;
                }
            }
            // print stacks before instructions
            for (int j = 0 ; j< stacks.size(); ++j){
                std::reverse(stacks[j].begin(), stacks[j].end());
                std::cout << "Stack " << j+1 << std::endl;
                for(auto elem2 : stacks[j]){
                    std::cout << elem2 << " ";
                }
                std::cout << "\n\n";
            }

            // execute instructions
            for( auto instru : vec_instructions){
                int nb_crates = instru[0];
                int start_stack = instru[1]-1;
                int destination_stack = instru[2]-1;
                for(int i = 0; i < nb_crates; ++i){
                    std::string crate_tmp = stacks[start_stack].back();
                    stacks[start_stack].pop_back();
                    
                    stacks[destination_stack].push_back(crate_tmp);
                }
            }

            std::cout << "--------- After moving crates -------" << std::endl;

            for (int j = 0 ; j< stacks.size(); ++j){

                std::cout << "Stack " << j+1 << std::endl;
                for(auto elem2 : stacks[j]){
                    std::cout << elem2 << " ";
                }
                std::cout << "\n\n";
            }

            std::cout << "--------- Top crates in order :" << std::endl;
            for (int j = 0 ; j< stacks.size(); ++j){
                if(stacks[j].size() != 0){
                    std::cout << stacks[j].back();
                }
                
            }
            std::cout << "\n\n";


        }
        




    }
}



