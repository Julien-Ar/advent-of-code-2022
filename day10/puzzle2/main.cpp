#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>

class Sprite{
    
    public :
        int middle_pixel = 1; // 
        int left_pixel = middle_pixel - 1;
        int right_pixel = middle_pixel + 1;

        void update_pos_sprite(int value){
            middle_pixel += value;  
            left_pixel = middle_pixel - 1;
            right_pixel = middle_pixel + 1;
        }
};


class CRT{
    
    public:
        std::vector< std::vector<char> > screen;
        int rows = 6;
        int cols = 40;

        void init_screen(){
            for(int i = 0; i < rows; ++i){
                std::vector<char> row(cols);
                for(int j = 0; j < cols; ++j){
                    row[j] = ' ';
                }
            screen.push_back(row);
            }
        };

        void update_screen(int cycle, Sprite & sprite){
            // get the row on which to draw the sprite based on the cycle value
            int current_row_pos = ((cycle - cycle%cols)/cols) ;
            std::vector<char> & current_row = screen[current_row_pos];

            // if the current pixel is on one of the sprite pixels, light the current pixel
            if( (cycle%cols <= sprite.right_pixel) && (cycle%cols >= sprite.left_pixel) ){
                current_row[cycle%cols] = ' ';
            }
        };

        void draw_screen(){
            std::cout << "---------------------------------------" << std::endl;
            for(auto screen_row : screen){
                for(auto character : screen_row){
                    std::cout << character;
                }
                std::cout << "\n";
            };
            std::cout << "---------------------------------------" << std::endl;
        };
};

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
    
        void process_instruction(Sprite & sprite, CRT & crt){
            
            std::string instru = instructions.front();

            if (instru == "noop"){
                instructions.pop();
                crt.update_screen(cycle, sprite);
                ++cycle;
            }
            else{
                // value to add to register and to sprite position
                int value = std::stoi(instru.substr(5)); 
                int cycle_tmp = cycle;
                while(cycle != cycle_tmp + 2){
                    crt.update_screen(cycle, sprite);
                    ++cycle;
                }
                registerX += value;
                sprite.update_pos_sprite(value);
                instructions.pop();
            }
        };

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
            Sprite sprite;
            CRT crt;
            
            crt.init_screen();

            while(getline(input_file, line)){
               
                cpu.add_instruction(line);
                cpu.process_instruction(sprite, crt);
            }
            crt.draw_screen();
        }
    }
}