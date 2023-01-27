#include "directory.h"
#include <iostream>


Directory::Directory(){
    total_size = 0;
    directory_name = "";
    parent_directory = nullptr;
    file_list = {};
    directory_list = {};
}

Directory::Directory(std::string dname, Directory * prnt_directory){
    total_size = 0;
    directory_name = dname;
    parent_directory = prnt_directory;
    file_list = {};
    directory_list = {};
}

void Directory::insert_directory(Directory * directory_to_insert){
    directory_list.push_back( directory_to_insert);
}

void Directory::insert_file(std::pair<std::string, int> file){

    file_list.push_back(file);
    total_size += file.second;
    Directory * dir_parent_ptr = parent_directory;
    while(dir_parent_ptr != nullptr){
        
        dir_parent_ptr->total_size += file.second;
        dir_parent_ptr = dir_parent_ptr->parent_directory;
    }


}

Directory  * Directory::search_for_subdirectory_name(std::string name){

    bool found = false;
    //std::cout << "      Dir to find : " << name << std::endl; 
    for (auto dir : directory_list){
        //std::cout << "      subdir name : " << dir->directory_name << std::endl;
        if(dir->directory_name == name){
            found = true;
            //std::cout << "      Succesfully found dir : " << name << " | parent : " << directory_name << std::endl;
            return dir;
        }
    }
    if(!found){
        std::cout << name << "      not found | parent : " << directory_name << std::endl;
    };
}





