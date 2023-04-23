/**
 * Programme qui détermine la hauteur atteinte
 * par une balle en tenant compte de la hauteur
 * initiale et du nombre de rebonds. Les données
 * à demander et à lire du clavier sont donc :
 * la hauteur initiale, le nombre de rebonds
 * au bout duquel on souhaite connaître
 * la hauteur de la balle, ainsi que le coefficient de rebond.
 * \file   hauteur_de_rebond.cpp
 * \author Hoang et Ibarissen
 * \date   29 janvier 2023
 * Créé le 24 janvier 2023
 */

#include <cmath>
#include <iostream>

const double LOWER_BOUND             = 0.0;
const double UPPER_BOUND             = INFINITY;
const double COEFFICIENT_UPPER_BOUND = 1.0;
const double GRAVITY                 = 9.81;

bool isValid(double height, int numberBounce, double bounceCoefficient);

int main()
{
    double height            = 0.0;
    int    numberBounce      = 0.0;
    double bounceCoefficient = 0.0;

    do
    {
        if (!isValid(height, numberBounce, bounceCoefficient))
        {
            std::cout << "Entrée(s) NON-VALIDE(s)\n";
        }
        std::cout << "Entrer la hauteur : ";
        std::cin >> height;
        std::cout << "Entrer le nombre de rebonds : ";
        std::cin >> numberBounce;
        std::cout << "Entrer le coefficient de rebond : ";
        std::cin >> bounceCoefficient;
    }
    while (!isValid(height, numberBounce, bounceCoefficient));

    double speed = 0.0;

    for (int i = 0; i < numberBounce; i++)
    {
        speed  = sqrt(2 * GRAVITY * height);
        speed  = bounceCoefficient * speed;
        height = (pow(speed, 2)) / (2 * GRAVITY);
    }

    std::cout << "La hauteur atteinte apres " << numberBounce
              << " rebonds est de " << height;

    return 0;
}

bool isValid(double height, int numberBounce, double bounceCoefficient)
{
    return (LOWER_BOUND <= height) && (height <= UPPER_BOUND)
        && (LOWER_BOUND <= numberBounce) && (numberBounce <= UPPER_BOUND)
        && (LOWER_BOUND <= bounceCoefficient)
        && (bounceCoefficient <= COEFFICIENT_UPPER_BOUND);
}