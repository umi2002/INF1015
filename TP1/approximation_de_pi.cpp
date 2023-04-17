/**
* Programme qui permet de calculer
* une valeur approchée de pi par la
* méthode de Monte‐Carlo basée sur les probabilités.
* \file   approximation_de_pi.cpp
* \author Hoang et Ibarissen
* \date   29 janvier 2023
* Créé le 24 janvier 2023
*/ 
#include <iostream>
#include <cmath>
#include <iomanip>
#include <random> 

double randomNumber();
bool isInCircle(double x, double y);

int main()
{
    int iterations = 0;
    
    std::cout << "Entrer le nombre d'iterations : ";
    std::cin >> iterations;
    
    double x = 0.0;
    double y = 0.0;
    int pointsInCircle = 0;
    
    for (int i=0; i < iterations; i++){
        x = randomNumber();
        y = randomNumber();
        
        if (isInCircle(x,y)){
            pointsInCircle++;
        }
    }
    
    double piApproximation = (double(pointsInCircle)/double(iterations)) * 4;
    
    std::cout << std::fixed;
    std::cout << std::setprecision(6);
    std::cout << piApproximation;
    
    
    return 0;
}


double randomNumber(){
    std::random_device myRandomDevice;
    unsigned seed = myRandomDevice();
    
    std::default_random_engine myRandomEngine(seed);
    
    std::uniform_real_distribution<double> rangeSquare(-1.0,1.0);
    
    return rangeSquare(myRandomEngine);

}

bool isInCircle(double x, double y){
    return (pow(x,2) + pow(y,2)) < 1;
}


