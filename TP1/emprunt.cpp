/**
 * Programme qui demande et lit du clavier
 * une somme d’argent qui a été prêtée, le montant
 * remboursé chaque mois, ainsi que le taux d’intérêt
 * annuel (le taux mensuel est le 1/12 du taux annuel),
 * et retourne le nombre de mois nécessaires pour rembourser
 * la dette ainsi que la somme des intérêts perçus par le prêteur.
 * \file   emprunt.cpp
 * \author Hoang et Ibarissen
 * \date   29 janvier 2023
 * Créé le 17 janvier 2023
 */

#include <cmath>
#include <iostream>

const double LOWER_BOUND      = 0.0;
const double SUM_UPPER_BOUND  = INFINITY;
const double RATE_UPPER_BOUND = 100.0;
const double RATIO_YEAR_MONTH = 1.0 / 12.0;
const double RATIO_PERCENTAGE = 1.0 / 100.0;

bool isValid(double borrowedMoney,
             double annualInterest,
             double monthlyDeposit);

int main()
{
    double borrowedMoney  = 0.0;
    double annualInterest = 0.0;
    double monthlyDeposit = 0.0;

    do
    {
        if (!isValid(borrowedMoney, annualInterest, monthlyDeposit))
        {
            std::cout << "Entrée(s) NON-VALIDE(s)\n";
        }
        std::cout << "Entrer la somme d'argent empruntée : ";
        std::cin >> borrowedMoney;
        std::cout << "Entrer le taux d'intérêt annuel : ";
        std::cin >> annualInterest;
        std::cout << "Entrer le dépot mensuel : ";
        std::cin >> monthlyDeposit;
    }
    while (!isValid(borrowedMoney, annualInterest, monthlyDeposit));

    int    monthCount    = 0;
    double totalInterest = 0.0;

    while (borrowedMoney > 0)
    {
        double currentInterest = borrowedMoney * annualInterest;
        currentInterest        *= RATIO_PERCENTAGE * RATIO_YEAR_MONTH;
        totalInterest          += currentInterest;
        borrowedMoney          -= monthlyDeposit;
        monthCount++;
    }

    std::cout << "Nombre de mois necessaires pour repayer la dette : "
              << monthCount << "\n";
    std::cout << "Interet total accumulé : " << totalInterest << "\n";
}

bool isValid(double borrowedMoney, double annualInterest, double monthlyDeposit)
{
    return (LOWER_BOUND <= borrowedMoney) && (borrowedMoney <= SUM_UPPER_BOUND)
        && (LOWER_BOUND <= annualInterest)
        && (annualInterest <= RATE_UPPER_BOUND)
        && (LOWER_BOUND <= monthlyDeposit)
        && (monthlyDeposit <= SUM_UPPER_BOUND);
}