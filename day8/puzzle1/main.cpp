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

            int nb_edge_trees = 2*forest.size() + 2*(forest[0].size()) - 4;
            int nb_tree_visible = nb_edge_trees;
            int height_tree_ij;
            std::cout << "Nb edge trees : " << nb_edge_trees << std::endl;
            for(int i = 1; i < forest.size()-1; ++i){
                for(int j = 1; j < forest[0].size()-1; ++j){
            
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


                    if( ( *max_element(left_side_tree_ij.begin(), left_side_tree_ij.end()) ) < height_tree_ij){
                        //std::cout << "      visible from left " << std::endl;
                        nb_tree_visible += 1;
                    }
                    else if( ( *max_element(right_side_tree_ij.begin(), right_side_tree_ij.end()) ) < height_tree_ij){
                        //std::cout << "      visible from right" << std::endl;
                        nb_tree_visible += 1;
                    }
                    else if( ( *max_element(up_side_tree_ij.begin(), up_side_tree_ij.end()) ) < height_tree_ij){
                        //std::cout << "      visible from up" << std::endl;
                        nb_tree_visible += 1;
                    }
                    else if( ( *max_element(down_side_tree_ij.begin(), down_side_tree_ij.end()) ) < height_tree_ij){
                        //std::cout << "      visible from down" << std::endl;
                        nb_tree_visible += 1;
                    } 

                }
            }
            std::cout << "----------- \n"<< std::endl;
            std::cout << "Total number of trees visible : " << nb_tree_visible << std::endl;
        }
    }
    
    
    
    return 0;
}