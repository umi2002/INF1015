/**
 * Programme de traitement de données pour un dictionnaire
 * (mot, nature/genre, définition). Le programme doit créer
 * un tableau de structures, y placer le dictionnaire en le
 * lisant d’un fichier, et ensuite afficher le mot le plus
 * long du dictionnaire dans le format suivant :
 * mot (nature/genre) : définition
 * \file   emprunt.cpp
 * \author Hoang et Ibarissen
 * \date   29 janvier 2023
 * Créé le 29 janvier 2023
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int const WORD_COUNT = 4;

int main()
{
    std::ifstream dictionnary("dictionnaire.txt");
    std::string   wordsWithDefinitions[WORD_COUNT][3] = {};

    std::string line      = "";
    int         countTabs = 0;
    while (std::getline(dictionnary, line))
    {
        std::istringstream fullDefinition(line);
        std::string        partOfDefinition = "";
        int                wordIndex        = 0;
        int                partIndex        = 0;
        while (std::getline(fullDefinition, partOfDefinition, '\t'))
        {
            wordIndex                                  = countTabs / 3;
            partIndex                                  = countTabs % 3;
            wordsWithDefinitions[wordIndex][partIndex] = partOfDefinition;
            countTabs++;
        }
    }

    int         indexOfLongestWord = 0;
    std::string longestWord        = "";

    for (int i = 0; i < WORD_COUNT; i++)
    {
        std::string currentWord = wordsWithDefinitions[i][0];
        if (currentWord.length() > longestWord.length())
        {
            indexOfLongestWord = i;
            longestWord        = currentWord;
        }
    }

    std::string genreNature = wordsWithDefinitions[indexOfLongestWord][1];
    std::string definition  = wordsWithDefinitions[indexOfLongestWord][2];

    std::cout << longestWord;
    std::cout << " (" << genreNature << ") : ";
    std::cout << definition;

    return 0;
}