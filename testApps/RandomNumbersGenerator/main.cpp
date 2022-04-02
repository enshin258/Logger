#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include "windows.h" 

int main() 
{ 
    srand((unsigned)time(0)); 

    while(true) {
        int i = (rand()%20)+1;

        if (i < 10) {
            std::cout << "Generated digit: " << i << std::endl;
        } else {
            std::cerr << "Generated number!: " << i << std::endl;
        }

        Sleep(100);
    }

}
