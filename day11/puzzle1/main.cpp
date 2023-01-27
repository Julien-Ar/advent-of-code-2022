#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <math.h>
#include <algorithm>

class Monkey{
    
    public:
        std::queue<int> item_list;
        std::vector<Monkey*> monkey_friends; // to whom to pass items based on the divible test
        std::string op; // operator (+ * )
        std::string operande; // what to add or multiply
        int divisible_test;
        int nb_inspected_items = 0; // each time an item is inspected, increment by 1

        Monkey(){
            item_list = {};
            monkey_friends = {};
            op = "";
            operande = "";
            divisible_test = 0;
        }

        Monkey(std::vector<int> item_lst, const std::vector<Monkey*> & monkey_friend,std::string ope, std::string operand, int divisible_tst){
            for(auto elem : item_lst){
                item_list.push(elem);
            }
            monkey_friends = monkey_friend;
            op = ope;
            operande = operand;
            divisible_test = divisible_tst;
        }

        void display_item(){
            std::queue<int> item_list_copy = item_list;
            while(item_list_copy.size() != 0){
                std::cout << item_list_copy.front() << " ";
                item_list_copy.pop();
            }
        }


        void process_items(){
            if(item_list.size() != 0){    
                while(item_list.size() != 0){
                    ++nb_inspected_items; 
                    int item = item_list.front();
                    item_list.pop();
                    if(operande != "old"){
                        int operande_value = std::stoi(operande);
                        if(op == "+"){
                            item = item + operande_value;
                        }
                        else{
                            item = item * operande_value;
                        }
                    }
                    else{
                       if(op == "+"){
                            item = item + item;
                        }
                        else{
                            item = item * item;
                        } 
                    }
                    item = std::floor(item / 3);
                    if(item%divisible_test == 0){
                        Monkey & friend1 = *(monkey_friends[0]);
                        friend1.item_list.push(item);
                    }
                    else{
                        Monkey & friend2 = *(monkey_friends[1]);
                        friend2.item_list.push(item); 
                    }
                } 
            }
            
        }
};



int main(int argc, char *argv[]){

    Monkey monkey0;
    Monkey monkey1;
    Monkey monkey2;   
    Monkey monkey3;
    Monkey monkey4;
    Monkey monkey5;
    Monkey monkey6;
    Monkey monkey7;

    monkey0 = Monkey(std::vector<int>{56, 52, 58, 96, 70, 75, 72}, 
                                    std::vector<Monkey *>{&monkey2, &monkey3},
                                    "*",
                                    "17",
                                    11);

    monkey1 = Monkey(std::vector<int>{75, 58, 86, 80, 55, 81}, 
                                    std::vector<Monkey *>{&monkey6, &monkey5},
                                    "+",
                                    "7",
                                    3);


    monkey2 = Monkey(std::vector<int>{73, 68, 73, 90}, 
                                    std::vector<Monkey *>{&monkey1, &monkey7},
                                    "*",
                                    "old",
                                    5);

    monkey3 = Monkey(std::vector<int>{72, 89, 55, 51, 59}, 
                                    std::vector<Monkey *>{&monkey2, &monkey7},
                                    "+",
                                    "1",
                                    7);

    monkey4 = Monkey(std::vector<int>{76, 76, 91}, 
                                    std::vector<Monkey *>{&monkey0, &monkey3},
                                    "*",
                                    "3",
                                    19);

    monkey5 = Monkey(std::vector<int>{88}, 
                                    std::vector<Monkey *>{&monkey6, &monkey4},
                                    "+",
                                    "4",
                                    2);

    monkey6 = Monkey(std::vector<int>{64, 63, 56, 50, 77, 55, 55, 86}, 
                                    std::vector<Monkey *>{&monkey4, &monkey0},
                                    "+",
                                    "8",
                                    13);

    monkey7 = Monkey(std::vector<int>{79, 58}, 
                                    std::vector<Monkey *>{&monkey1, &monkey5},
                                    "+",
                                    "6",
                                    17);                                   

    std::vector<Monkey * > monkey_family = {&monkey0, &monkey1, &monkey2, &monkey3,
                                            &monkey4, &monkey5, &monkey6, &monkey7};

    int nb_rounds = 20;

    for(int i = 0; i < nb_rounds; ++i){
        int monkey_number = 0;
        for(auto monkey : monkey_family){
            monkey->process_items();
            ++monkey_number;
        }
    }
    int monkey_number = 0;
    std::vector<int> worry_levels;
    std::cout << "\nWorry levels after "<< nb_rounds<< " rounds are for each monkey : \n";
    for(auto monkey : monkey_family){                               
        std::cout << "Monkey " << monkey_number << " : " << monkey->nb_inspected_items << std::endl;
        worry_levels.push_back(monkey->nb_inspected_items);
        ++monkey_number;
    }
    int max1 = *std::max_element(worry_levels.begin(), worry_levels.end());
    worry_levels.erase(std::remove(worry_levels.begin(), worry_levels.end(), max1), worry_levels.end());
    int max2 = *std::max_element(worry_levels.begin(), worry_levels.end());
    std::cout <<"\nLevel of monkey business is : " << max1*max2 << std::endl;
}