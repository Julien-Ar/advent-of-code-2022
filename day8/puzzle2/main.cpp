#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>


int main(int argc, char*argv[]){
    
    
    std::string file_name;
    std::fstream input_file;
    if(argv[1] != nullptr){
        file_name = argv[1];
        input_file = std::fstream(file_name);
    }
    else{
        std::cout << "No input file given !!" << std::endl;
        return 0;
    }

    while (input_file.is_open()){
        if(input_file.eof()){
            input_file.close();
        }
        else{
            std::vector < std::vector< int > > forest;
            std::string line;

            while(getline(input_file, line)){
                std::vector< int> current_line_numbers;

                for(auto elem : line) {
                    current_line_numbers.push_back(elem - '0');
                }
                forest.push_back(current_line_numbers);                
            }

            int max_scenic_score = 0;
            int height_tree_ij;

            for(int i = 1; i < forest.size()-1; ++i){
                for(int j = 1; j < forest[0].size()-1; ++j){
                    
                    int dist_right = 0;
                    int dist_down = 0;
                    int dist_up = 0;
                    int dist_left = 0;

                    height_tree_ij = forest[i][j];
                    // ith line , jth column
                    std::vector< int> left_side_tree_ij(forest[i].begin(), forest[i].begin()+j);  
                    std::vector< int> right_side_tree_ij(forest[i].begin()+j+1, forest[i].end());

                    std::vector< int> current_column;

                    for(int k = 0; k < forest.size(); ++k){
                        current_column.push_back(forest[k][j]);
                    }
                    std::vector< int> up_side_tree_ij(current_column.begin(), current_column.begin()+i);
                    std::vector< int> down_side_tree_ij(current_column.begin()+i+1, current_column.end());

                    // reverse left and up tree positions in order to be in the current tree point of view
                    std::reverse(left_side_tree_ij.begin(), left_side_tree_ij.end());
                    std::reverse(up_side_tree_ij.begin(), up_side_tree_ij.end());

                    for(auto tree_height : left_side_tree_ij){
                        if (tree_height >= height_tree_ij){
                            ++dist_left;
                            break;
                        }
                        else{
                            ++dist_left;
                        }
                    }
                    for(auto tree_height : right_side_tree_ij){
                        if (tree_height >= height_tree_ij){
                            ++dist_right;
                            break;
                        }
                        else{
                            ++dist_right;
                        }
                    }
                    for(auto tree_height : up_side_tree_ij){
                        if (tree_height >= height_tree_ij){
                            ++dist_up;
                            break;
                        }
                        else{
                            ++dist_up;
                        }
                    }
                    for(auto tree_height : down_side_tree_ij){
                        if (tree_height >= height_tree_ij){
                            ++dist_down;
                            break;
                        }
                        else{
                            ++dist_down;
                        }
                    } 
                    int max_tmp = dist_right*dist_left*dist_up*dist_down;
                    if(max_tmp > max_scenic_score){
                        max_scenic_score = max_tmp;
                    }
                }
            }
            std::cout << "----------- \n"<< std::endl;
            std::cout << "Max scenic score possible : " << max_scenic_score << std::endl;
        }
    }
    return 0;
}