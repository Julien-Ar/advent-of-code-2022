#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>



class CPU{

    public:

        int registerX = 1;
        int cycle = 0;
        std::vector< std::pair<int , int >> memory;
        std::queue < std::string > instructions;

        void get_cycle_register(){
            if( (cycle-20)%40 == 0 ) {
                memory.push_back(std::pair<int, int >(cycle, registerX));
            }
        }
        
        void add_instruction(const std::string & instru){
            instructions.push(instru);
        }
    
        void process_instruction(){
            std::string instru = instructions.front();

            if (instru == "noop"){
                instructions.pop();
                ++cycle;
                get_cycle_register();
            }
            else{       
                int value = std::stoi(instru.substr(5));
                int cycle_tmp = cycle;
                while(cycle != cycle_tmp + 2){
                    ++cycle;
                    get_cycle_register();
                }
                registerX += value;
                instructions.pop();
            }
        }
};

int main(int argc, char* argv[]){
    
    std::string file_name;
    if(argv[1] != nullptr){
        file_name = argv[1];
    }
    else{
        std::cout << "No input file" << std::endl;
        return 0;
    }
    std::fstream input_file(file_name);
    
    while(input_file.is_open()){
        if(input_file.eof()){
            input_file.close();
        }
        else{
            std::string line;
            CPU cpu;
            while(getline(input_file, line)){
                cpu.add_instruction(line);
                cpu.process_instruction();
            }
            int s = 0;
            for(auto elem : cpu.memory){
                std::cout << "Cycle : " << elem.first << " | Register : " << elem.second << std::endl;
                s += elem.first*elem.second;
            }
            std::cout << "Sum of signal strength for these cycles :  " << s << std::endl;
        }
    }
}