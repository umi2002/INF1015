/**
 * Programme qui saisit un tableau d’entiers
 * de taille 10 et qui l’affiche de
 * telle sorte que tous les entiers pairs
 * se retrouvent avant les entiers impairs.
 * \file   tableau_pair_impair.cpp
 * \author Hoang et Ibarissen
 * \date   29 janvier 2023
 * Créé le 26 janvier 2023
 */

#include <cmath>
#include <iostream>

bool isEven(int number);

const int TABLE_SIZE = 10;

int main()
{
    int numbers[TABLE_SIZE] = {};

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        std::cout << "Entrer un nombre entier : ";
        std::cin >> numbers[i];
    }

    int evenNumbers[TABLE_SIZE] = {};
    int oddNumbers[TABLE_SIZE]  = {};
    int countEvenNumbers        = 0;
    int countOddNumbers         = 0;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (isEven(numbers[i]))
        {
            evenNumbers[countEvenNumbers] = numbers[i];
            countEvenNumbers++;
        }
        else
        {
            oddNumbers[countOddNumbers] = numbers[i];
            countOddNumbers++;
        }
    }

    int firstOddNumberIndex = TABLE_SIZE - countEvenNumbers;

    for (int i = 0; i < countEvenNumbers; i++)
    {
        numbers[i] = evenNumbers[i];
    }

    for (int i = 0; i < countOddNumbers; i++)
    {
        numbers[i + firstOddNumberIndex] = oddNumbers[i];
    }

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        std::cout << numbers[i] << " ";
    }

    return 0;
}

bool isEven(int number)
{
    return number % 2 == 0;
}
