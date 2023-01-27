#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

int main(int argc, char *argv[]){

    std::string file_name = argv[1];
    std::cout << "file name : " << file_name << std::endl;

    std::ifstream input_file(file_name); // create a stream object and open the file

    std::map<std::string, int> lookup_scores = {{"A Z", 6}, {"B Z", 6}, {"C Z", 6}, 
                                                {"A X", 0}, {"B X", 0}, {"C X", 0},
                                                {"A Y", 3}, {"B Y", 3}, {"C Y", 3},
                                                {"X", 1}, {"Y", 2}, {"Z", 3}};
    
    std::map<std::string, std::string> lookup_shapes = {{"A Z", "Y"}, {"B Z", "Z"}, {"C Z", "X"}, 
                                                        {"A X", "Z"}, {"B X", "X"}, {"C X", "Y"},
                                                        {"A Y", "X"}, {"B Y", "Y"}, {"C Y", "Z"}};

    std::string line;
    std::string shape;
    int total_score = 0;
    int round_score;
    int shape_score;

    int i = 0;
    while ( input_file.is_open()){
        if (input_file.eof()){
            input_file.close();
        }
        else{
            while(getline(input_file, line)){
                
                shape = lookup_shapes[line];
                shape_score = lookup_scores[shape];
                round_score = lookup_scores[line];
                //std::cout << "final round score : " << shape_score << "( " << shape << " )" << " + "  << round_score << std::endl;
                total_score += shape_score + round_score;
            } 
        }
    }
    std::cout << "Total score : " << total_score << std::endl;
    return 0; 
}













