#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int main(int argc, char *argv[]){

    std::string file_name = argv[1];
    std::cout << "file name : " << file_name << std::endl;

    std::ifstream input_file(file_name); // create a stream object and open the file

    std::vector<double> calories_each; 

    std::string line;

    double totalCurrentCalories = 0.0;
    double currentCaloriesRead;
    int i = 0;
    while ( input_file.is_open()){
        if (input_file.eof()){
            input_file.close();
        }
        else{
            while(getline(input_file, line)){
                
                if(line.length() == 0) {
                    //std::cout << "Elf " << i << " : "<< totalCurrentCalories << std::endl;
                    calories_each.push_back(totalCurrentCalories);
                    totalCurrentCalories = 0;
                    ++i;
                }
                else{
                    
                    currentCaloriesRead = stod(line);
                    totalCurrentCalories += currentCaloriesRead;
                }
            } 
        }
    }
    double max1 = 0.0;
    double max2 = 0.0;
    double max3 = 0.0;
    int elf_nb = 0;

    for(int j = 0;  j< calories_each.size(); j++){
        
        if(calories_each[j] > max1){
            max1 = calories_each[j];
            elf_nb = j;
        }
    }

    std::cout << "Max 1 : "<< max1 << std::endl;
    calories_each.erase(calories_each.begin()+elf_nb);


    elf_nb = 0;
    
    for(int j = 0;  j< calories_each.size(); j++){
        
        if(calories_each[j] > max2){
            max2 = calories_each[j];
            elf_nb = j;
        }
    }
    std::cout << "Max 2 : "<< max2 << std::endl;
    calories_each.erase(calories_each.begin()+elf_nb);

    elf_nb = 0;
    
    for(int j = 0;  j< calories_each.size(); j++){
        
        if(calories_each[j] > max3){
            max3 = calories_each[j];
            elf_nb = j;
        }
    }

    std::cout << "Max 3 : "<< max3 << std::endl;

    std::cout << "Max1 + max2 + max3 : " << max1 + max2 + max3 << std::endl;

    return 0; 
}













