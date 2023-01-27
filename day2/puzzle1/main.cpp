#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

int main(int argc, char *argv[]){

    std::string file_name = argv[1];
    std::cout << "file name : " << file_name << std::endl;

    std::ifstream input_file(file_name); // create a stream object and open the file

    std::map<std::string, int> lookup_scores = {{"A Y", 6}, {"B Z", 6}, {"C X", 6}, 
                                                {"A Z", 0}, {"B X", 0}, {"C Y", 0},
                                                {"A X", 3}, {"B Y", 3}, {"C Z", 3},
                                                {"X", 1}, {"Y", 2}, {"Z", 3}};
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
                shape = line[2];
                //std::cout << shape << std::endl;
                shape_score = lookup_scores[shape];
                round_score = lookup_scores[line];
                total_score += shape_score + round_score;
            } 
        }
    }
    std::cout << "Total score : " << total_score << std::endl;
    return 0; 
}













