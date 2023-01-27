#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <vector>


class Directory
{
    public : 

        Directory();
        Directory(std::string, Directory *);

        int total_size;
        std::string directory_name;
        Directory * parent_directory;
        std::vector<std::pair<std::string, int>> file_list; // list of pair {name, size}
        std::vector<Directory * > directory_list; // 

        void insert_directory( Directory * );
        void insert_file(std::pair<std::string, int>);


        Directory * search_for_subdirectory_name(std::string);
        

};


#endif