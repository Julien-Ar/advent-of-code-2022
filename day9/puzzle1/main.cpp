#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <vector>


bool is_adjacent(const std::pair<double, double> & Tail, const std::pair<double, double> & Head){
    // if Tail and Head are at distance 1 of each other return true
    if( (abs(Tail.first - Head.first) <= 1 ) && (abs(Tail.second - Head.second) <= 1) ){
        return true;
    }
    else{
        return false; 
    }
}

void update_tail_pos(std::pair<double, double> & Tail, const std::pair<double, double> & Head){
    // DOESNT WORK IN PUZZLE2
    std::pair <double, double> distance = {Head.first - Tail.first, Head.second - Tail.second};

    if(abs(distance.first) == 2){
        distance.first = distance.first / 2;
    }
    else{
        distance.second = distance.second / 2;
    }
    Tail.first +=  distance.first;
    Tail.second +=  distance.second;
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
            std::pair<double, double> Hpos = {0., 0.};
            std::pair<double, double> Tpos = {0., 0.};
            std::set< std::pair<double, double> > unique_pos_T = {Tpos};
            //std::vector < std::pair<int, int>> all_pos_T = {Tpos};
            while(getline(input_file, line)){

                char direction = line[0];
                int step = std::stoi(line.substr(2));
                 
                for(int i = 0; i< step; ++i){
                    
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

                    bool adjacent = is_adjacent(Tpos, Hpos);

                    if(!adjacent){
                        update_tail_pos(Tpos, Hpos);
                    }
                    unique_pos_T.insert(Tpos);
                    //std::cout << direction << " " << step << " T (" << Tpos.first << "," << Tpos.second << ") | H (" << Hpos.first << "," << Hpos.second << ")" << std::endl;
                }        
            }
           // std::set<std::pair<int,int>> set_teest(all_pos_T.begin(), all_pos_T.end());
            std::cout << "Nb unique pos tail : " << unique_pos_T.size()<< std::endl;
        }       
    }
}
