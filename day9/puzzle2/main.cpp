#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <vector>
#include <math.h>


void update_tail_pos(std::pair<double, double> & Tail, const std::pair<double, double> & Head){
    // called if Tail and Head not adjacent

    // same row
    if(Tail.second == Head.second){
        if(Tail.first < Head.first ){
            ++Tail.first;
        }
        else {
            --Tail.first;
        }
    }
    // same column
    else if (Tail.first == Head.first){
        if(Tail.second < Head.second ){
            ++Tail.second;
        }
        else {
            --Tail.second;
        }      
    }
    else {
        if(Tail.second < Head.second){
            if(Tail.first < Head.first){
                ++Tail.first;
                ++Tail.second;
            }
            else{
                --Tail.first;
                ++Tail.second;
            }
        }
        else{
            if(Tail.first < Head.first){
                ++Tail.first;
                --Tail.second;
            }
            else{
                --Tail.first;
                --Tail.second;
            } 
        }
    }
}

bool is_adjacent(const std::pair<double, double> & Tail, const std::pair<double, double> & Head){
    // if Tail and Head are at distance 1 of each other return true
    if( (abs(Tail.first - Head.first) <= 1 ) && (abs(Tail.second - Head.second) <= 1) ){
        return true;
    }
    else{
        return false; 
    }
}


int main (int argc, char* argv[]){

    std::string file_name;
    std::fstream input_file;

    if ( argv[1] != nullptr){
        file_name = argv[1];
        input_file = std::fstream(file_name);
    }
    else{
        std::cout << "No input file given !!" << std::endl;
        return 0;
    }

    while(input_file.is_open()){
        if(input_file.eof()){
            input_file.close();
        }
        else{
            std::string line;

            std::vector<std::pair<double, double>> rope; // first element = Head | last = tail
            
            int rope_length = 10;
            for(int i = 0; i < rope_length; ++i){
                rope.push_back( std::pair<double, double>{0, 0} );
            }
            std::pair<double, double> & Hpos = rope[0];

            std::set< std::pair<double, double> > unique_pos_T;

            while(getline(input_file, line)){

                char direction = line[0];
                int step = std::stoi(line.substr(2));
                
                for(int i = 0; i < step; ++i){
                             
                    switch ( direction ) { 
                        case 'R' :
                            ++Hpos.first; // x
                            break;
                        case 'U' :
                            ++Hpos.second; // y
                            break;
                        case 'L' :
                            --Hpos.first; // x
                            break;
                        case 'D' :
                            --Hpos.second; // y
                            break;
                    }
                    for(int j = 1; j < rope.size(); ++j){
                        std::pair<double, double> & Hpos_tmp = rope[j-1];
                        std::pair<double, double> & Tpos_tmp = rope[j];
                        bool adjacent = is_adjacent(Tpos_tmp, Hpos_tmp);

                        if(!adjacent){
                            update_tail_pos(Tpos_tmp, Hpos_tmp);
                        }
                    }
                    unique_pos_T.insert(rope.back());
                }
                    

                    //std::cout << direction << " " << step << " T (" << Tpos.first << "," << Tpos.second << ") | H (" << Hpos.first << "," << Hpos.second << ")" << std::endl;        
            }
            std::cout << "Nb unique pos tail : " << unique_pos_T.size()<< std::endl;
        }       
    }
}
