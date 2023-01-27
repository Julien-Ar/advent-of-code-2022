#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <typeinfo>
#include <algorithm>
#include "directory.h"


std::vector<Directory *> search_for_directorie_sizes(   std::vector<Directory *>  & list_dir_ok_size, 
                                                        Directory * root_directory,
                                                        int min_size_required){
    if(root_directory->total_size >= min_size_required){
        list_dir_ok_size.push_back(root_directory);
        //std::cout << "Dir : "<< root_directory->directory_name << " | Size : " << root_directory->total_size << std::endl; 
    }
    
    for(auto dir : root_directory->directory_list){
        search_for_directorie_sizes(list_dir_ok_size, dir, min_size_required);
    }
    return(list_dir_ok_size);
}

void min_dir_size_to_delete(std::vector<Directory*> list){

    std::vector<int> sizes;
    for(auto elem : list){
        sizes.push_back(elem->total_size);
    };
    std::cout << "Min size directory to delete :" << *min_element(sizes.begin(), sizes.end())  << std::endl;

}




int main(int argc, char * argv[]){

    std::string file_name = argv[1];
    std::cout << "file given : " << file_name << std::endl;

    std::fstream input_file(file_name);

    while(input_file.is_open()){
        if(input_file.eof()){
            input_file.close();
        }
        else{
            
            std::regex dir_present("(dir)\\s[a-zA-Z]+");
            std::regex file_present("(\\d)+\\s[a-zA-Z]+");
            std::smatch match;
            std::regex rgx_number("(\\d)+");
            std::regex rgx_file_name("[a-zA-Z]+(\\.)?[a-zA-Z]*");
            std::regex rgx_cd_dir("(\\$)(\\s)(cd)(\\s)[a-zA-Z]+");
            std::regex rgx_cd_parent("(\\$)\\s(cd)\\s(\\.\\.)");

            std::string line;
            
            Directory root_dir("root_dir", nullptr);
            Directory * current_dir = &root_dir;

            Directory * dir_tmp_ptr;

            while(getline(input_file, line)){
                
                if (std::regex_search(line, dir_present)){
                    //std::cout<< "line dir present: " << line << std::endl;
                    std::string dir_tmp_name = line.substr(4); // 4 because "dir " at the start of line
                    //std::cout << "     dir name : " << dir_tmp_name << " | length(name) : "<< dir_tmp_name.size() << std::endl;
                    dir_tmp_ptr = new Directory(dir_tmp_name, current_dir);
                    current_dir->insert_directory(dir_tmp_ptr);
                    //std::cout << "dir_tmp name : " << dir_tmp_ptr->directory_name <<" | parent : "<< dir_tmp_ptr->parent_directory->directory_name <<  std::endl;

                    
                    
                }
                else if(std::regex_search(line, file_present)){
                    //std::cout<< "line file_present: " << line << std::endl;
                    int file_size_tmp;
                    std::string file_name_tmp;
                    if(std::regex_search(line, match, rgx_number)){
                        file_size_tmp = std::stoi(match[0]);
                    }
                    if(std::regex_search(line, match, rgx_file_name)){
                        file_name_tmp = match[0];
                    }
                    std::pair<std::string, int> file_tmp = {file_name_tmp, file_size_tmp};
                    current_dir->insert_file(file_tmp);
                }
                else if(std::regex_search(line, rgx_cd_dir)){
                    //std::cout<< "line rgxcd_dir : " << line << std::endl;
                    std::string name_dir_to_go = line.substr(5); // 5 because "$ cd " at the start of line
                    //std::cout<< "      dir to go : " << name_dir_to_go << std::endl;
                    //std::cout << "total size : " << current_dir->total_size << std::endl;  
                    //std::cout << "current dir : " << current_dir->directory_name << " ";  
                    //for(auto dir : current_dir->directory_list){
                    //    std::cout << "| subdir : " << dir->directory_name << " ";
                    //}
                    //std::cout << "\n";
                    //if(current_dir->parent_directory != nullptr){
                    //    std::cout << " 1 parent of new current dir : " << current_dir->parent_directory->directory_name  << " | name current dir : " << current_dir->directory_name << std::endl;
                    //}
                    current_dir = current_dir->search_for_subdirectory_name(name_dir_to_go);
                    //std::cout << " 2 parent of new current dir : " << current_dir->parent_directory->directory_name  << " | name current dir : " << current_dir->directory_name << std::endl;
                }

                else if (line == "$ cd .."){
                    //std::cout<< "line cd .. : " << line << std::endl;
                    //std::cout << "current directory : "<< current_dir->directory_name << " | parent : " << current_dir->parent_directory->directory_name << std::endl;
                    current_dir = current_dir->parent_directory;
                }


            }
            std::cout <<"--------------------" << std::endl;
            std::vector<Directory *> list_dir_ok_size;
            int unused_space = 70000000 - root_dir.total_size;
            int min_size_required = 30000000 - unused_space;
            list_dir_ok_size = search_for_directorie_sizes(list_dir_ok_size, &root_dir, min_size_required);
            int s = 0;
            for(auto elem : list_dir_ok_size){
                s += elem->total_size; 
                std::cout << "Dir name : " << elem->directory_name << " | Size : " << elem->total_size << std::endl;
            }
            min_dir_size_to_delete(list_dir_ok_size);
        }
    }
    return 0;
}
