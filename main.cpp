#include <map>
#include <iostream>
#include "worstallocator.h"
#include "worstvector.h"


int factorial(int n)
{
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

int main(int, char *[]) {
    std::ios_base::sync_with_stdio(false);
    // Standart Allocator
    std::map<int, int> standart_map;
    for(size_t i=0; i<=9; i++){
        standart_map[i] = factorial(i);
    }

    std::map<int,int ,std::less<>,
            worst_allocator<std::pair<const int, int>, 10>> custom_map;
    for(size_t i=0; i<=9; i++){
        custom_map[i] = factorial(i);
    }

    for(const auto& [key,value] : custom_map){
        std::cout << key << " " << value << "\n";
    }
    auto v =WorstVector<int, worst_allocator<int, 4>>{};


    WorstVector<int> custom_vector;
    for(int i = 0; i <= 9; i++) {
        custom_vector.PushBack(i);
    }


    WorstVector<int, worst_allocator<int, 20>> custom_vector_with_worst_allocator;
    for(int i = 0; i <= 9; i++) {
        custom_vector_with_worst_allocator.PushBack(i);
    }

    for(const auto& elem: custom_vector_with_worst_allocator) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;


    return 0;
}
