#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>

// To solve this puzzle, the Dijkstra algorithm is used

int get_number_name(int i, int j, int nb_cols){
    // get the name of the node at position (i,j), starting from 0
    return(i*nb_cols + j);
}

int get_min_dist_node(const std::vector<int> & Q, const std::vector<double> & dist){
    int node;
    double min = std::numeric_limits<double>::infinity();
    for(auto node_tmp : Q  ){
        if(dist[node_tmp] < min){
            min = dist[node_tmp];
            node = node_tmp;
        }
    }
    return(node);
}

std::vector<int>  get_neighbors(const std::vector<std::vector<int>> & adjacency_mat, int node){
    std::vector<int> neighbors;
    std::vector<int> vec_line_adj_matrix = adjacency_mat[node];
    for(int i = 0; i < vec_line_adj_matrix.size(); ++i){
        if(vec_line_adj_matrix[i] != 0){
            neighbors.push_back(i);
        }
    }
    return(neighbors);
}

int min_dist_dijkstra(const std::vector<std::vector<int>> & adjacency_mat, 
                      int start,
                      int end ,
                      int total_nb_nodes) {
    // Implement Dijkstra algorithm in order to find the minimum distance
    // from start to end, using the graph's adjacency matrix
    std::vector<double> vec_distance;
    std::vector<int> previous;
    std::vector<int> Q; // set of all nodes
    double inf = std::numeric_limits<double>::infinity();
    for(int i = 0; i < total_nb_nodes; ++i){
        if(i != start){
            vec_distance.push_back(inf);
        }
        else{
            vec_distance.push_back(0.);
        }
        Q.push_back(i);
        previous.push_back(-1);
    }
    int limit = 0;
    while(Q.size() != 0 && limit < total_nb_nodes){
        //std::cout << "Q not empty : " << cpt << std::endl;
        ++limit;
        int u = get_min_dist_node(Q, vec_distance);
        if(u == end){
            std::vector<int> sequence_of_nodes;
            int u_copy = u;
            while(previous[u_copy] && (u_copy!=start)){
                sequence_of_nodes.insert(sequence_of_nodes.begin(), u_copy);
                if(previous[u_copy] != -1){
                    u_copy = previous[u_copy];
                }
                else{
                    std::cout << "No path \n";
                    return 100000000;
                }
                
            }
            std::cout << "Length of shortest path from " << start << " to " << end << " : " 
                        << sequence_of_nodes.size() <<std::endl;
            // To print full path, add starting node at the beginning
            // sequence_of_nodes.insert(sequence_of_nodes.begin(), start);
            // std::cout << "\nPath is : \n";
            // for(auto node : sequence_of_nodes){
            //     std::cout << node << " ";
            // }
            // std::cout<<"\n";
            return sequence_of_nodes.size();
        }
        Q.erase(std::remove(Q.begin(), Q.end(), u), Q.end());
        std::vector<int> neighbors = get_neighbors(adjacency_mat, u);
        for(auto neighbor : neighbors){
            if(vec_distance[neighbor]>(vec_distance[u] + adjacency_mat[u][neighbor])){
                vec_distance[neighbor] = vec_distance[u] + adjacency_mat[u][neighbor];
                previous[neighbor] = u;
            }
        }
    }   
    std::cout << "No path\n";
    return 100000000;
}

int main(int argc, char*argv[]){
    std::string file_name;
    std::fstream input_file;

    if( argv[1] != nullptr){
        file_name = argv[1];
        input_file = std::fstream(file_name);
    }
    else{
        std::cout << "No input file given !" << std::endl;
        return 0;
    }
    while (input_file.is_open()){
        if(input_file.eof()){
            input_file.close();
        }
        else{
            std::string line;
            std::vector<std::vector<int>> height_map;
            std::vector<int> vec_starting_loc;
            int arriving_loc;
            int count = 0; // name every node starting from topleft as a number, as a unoriented graph
            int nb_elem_line; // count nb of element on a line from input.txt
            int nb_row = 0; 
            while(getline(input_file, line)){
                ++nb_row;
                std::vector<int> height_map_line;
                nb_elem_line = 0;
                for(auto character : line){
                    ++nb_elem_line;
                    if(character=='E'){
                        character = 'z';
                        arriving_loc = count;
                    }
                    else if( character=='S' || character=='a'){
                        character = 'a';
                        vec_starting_loc.push_back(count);
                    }
                    int height = int(character)-97; // convert to ascii code
                    height_map_line.push_back(height);
                    ++count;
                }
                height_map.push_back(height_map_line);
            }
            std::vector<std::vector<int>> adjacency_matrix;
            for(int i = 0; i < count; ++i){
                std::vector<int> vec_tmp = {};
                for(int j = 0; j < count; ++j){
                    vec_tmp.push_back(0);
                }
                adjacency_matrix.push_back(vec_tmp);
            }
            
            std::cout << "Arriving loc number node : " << arriving_loc << std::endl;
            std::cout << "nb_elem_line  : " << nb_elem_line<<std::endl;
            std::cout << "nb_row : " << nb_row << std::endl;
            int i = 0;
            for(auto height_map_line : height_map){
                int j = 0;
                for(auto height : height_map_line){
                    int current_number_name = get_number_name(i, j, nb_elem_line);
                    int nb_name_above = get_number_name(i-1, j, nb_elem_line);
                    int nb_name_below = get_number_name(i+1, j, nb_elem_line);
                    int nb_name_right = get_number_name(i, j+1, nb_elem_line);
                    int nb_name_left = get_number_name(i, j-1, nb_elem_line);
                    // check 4 position
                    if(i>=1){
                        // above : 
                        if((height - height_map[i-1][j]) == -1 ){
                            adjacency_matrix[current_number_name][nb_name_above] = 1;
                        }
                        else if(height >= height_map[i-1][j]){
                            adjacency_matrix[current_number_name][nb_name_above] = 1;
                        }
                        else{
                            adjacency_matrix[current_number_name][nb_name_above] = 0;
                        }
                    }
                    if(i < (nb_row-1)){
                        // below : 
                        if((height - height_map[i+1][j]) == -1 ){
                            adjacency_matrix[current_number_name][nb_name_below] = 1;
                        }
                        else if(height >= height_map[i+1][j]){
                            adjacency_matrix[current_number_name][nb_name_below] = 1;
                        }
                        else{
                            adjacency_matrix[current_number_name][nb_name_below] = 0;
                        }
                    }
                    if(j < (nb_elem_line-1)){
                        // right : 
                        if((height - height_map[i][j+1]) == -1 ){
                            adjacency_matrix[current_number_name][nb_name_right] = 1;
                        }
                        else if(height >= height_map[i][j+1]){
                            adjacency_matrix[current_number_name][nb_name_right] = 1;
                        }
                        else{
                            adjacency_matrix[current_number_name][nb_name_right] = 0;
                        }
                    }
                    if(j >= 1){
                        // left : 
                        if((height - height_map[i][j-1]) == -1 ){
                            adjacency_matrix[current_number_name][nb_name_left] = 1;
                        }
                        else if(height >= height_map[i][j-1]){
                            adjacency_matrix[current_number_name][nb_name_left] = 1;
                        }
                        else{
                            adjacency_matrix[current_number_name][nb_name_left] = 0;
                        }
                    }
                    ++j;
                }
                ++i;
            }
            // Print the height map (input.txt map as numbers)
            // for(auto vec_line : height_map){
            //     std::cout<<"\n";
            //     for(auto elem : vec_line){
            //         std::cout<<elem <<"  ";
            //     }
            // }
            // Print the adjacency matrix of the graph 
            // std::cout << "\n\n == Adjacency matrix == \n";
            // for(auto vec_line : adjacency_matrix){
            //     std::cout<<"\n";
            //     for(auto elem : vec_line){
            //         std::cout<<elem <<" ";
            //     }
            // }      
            std::vector<int> min_dist;
           
            for(auto starting_loc : vec_starting_loc){
                std::cout << "\n-----------------------------" << std::endl;
                std::cout << "Starting_loc number node : " << starting_loc<<std::endl;
                std::cout << "Arrival_loc number node : " << arriving_loc<<std::endl;
                int dist = min_dist_dijkstra(adjacency_matrix, starting_loc, arriving_loc, count);
                std::cout << "-----------------------------\n" << std::endl;
                min_dist.push_back(dist);
            }
            int minimum = *std::min_element(min_dist.begin(), min_dist.end());
            std::cout << "Fewest steps required to move starting from any square with \n" 
                     <<"elevation a to the location that should get the best signal is :\n"<<minimum << std::endl;
        }
    }
    return(0);
}





