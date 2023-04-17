/**
* Programme qui lit du clavier un nombre entier, puis détermine si ce
* nombre est premier ou non. S’il n’est pas premier, le plus petit entier
* qui est un diviseur de ce nombre est affiché.
* \file   nbpremiers.cpp
* \author Hoang et Ibarissen
* \date   29 janvier 2023
* Créé le 17 janvier 2023
*/


#include <iostream>
#include <cmath>

bool isEven(int number);

int main()
{
    int numberIn = 0;
    std::cout << "Entrer un nombre entier : ";
    std::cin >> numberIn;
    if (numberIn == 1){
        std::cout << "Ce nombre n'est pas premier\n";
    }
    else if (numberIn==2){
        std::cout << "Ce nombre est premier\n";
    }
    else if(isEven(numberIn)){
        std::cout << "Ce nombre n'est pas premier car il est divisible par 2.\n";
    }
    else {
        int smallestDivisor = 3;
        const int STEP = 2;
        bool isPrime = true;
        
        //Verifie si le nombre est premier
        while (smallestDivisor <= sqrt(numberIn) && isPrime){
            
            if (numberIn%smallestDivisor == 0){
                isPrime=false;
                smallestDivisor -= STEP;
            }
            smallestDivisor += STEP;
        }
        if (isPrime){
            std::cout << "Ce nombre est premier\n";
        }
        else{
            std::cout << "Ce nombre n'est pas premier " <<
            "car il est divisible par " 
            << smallestDivisor << "\n";
        }
    }
}

bool isEven(int number) {return number%2==0;}





