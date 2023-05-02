/**
 * Programme qui permet de jouer au jeu d'échecs.
 * \file board.cpp
 * \author Hoang et Ibarissen
 * \date 20 avril 2023
 * Créé le 12 avril 2023
 */

#include "libraries.hpp"
#include "view/maingui.hpp"

//#if __has_include("gtest/gtest.h")
//#include "gtest/gtest.h"
//#endif

#if __has_include("bibliotheque_cours.hpp")
#    include "bibliotheque_cours.hpp"
#    define BIBLIOTHEQUE_COURS_INCLUS
using bibliotheque_cours::cdbg;
#else
auto& cdbg = clog;
#endif

#if __has_include("verification_allocation.hpp")
#    include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
#    include "verification_allocation.hpp"
#endif

void initialiserBibliothequeCours([[maybe_unused]] int   argc,
                                  [[maybe_unused]] char* argv[])
{
#ifdef BIBLIOTHEQUE_COURS_INCLUS
    bibliotheque_cours::
        activerCouleursAnsi();  //Permet sous Windows les "ANSI escape code"
                                //pour changer de couleurs
                                //https://en.wikipedia.org/wiki/ANSI_escape_code
                                //; les consoles Linux/Mac les supportent
                                //normalement par défaut.

    //cdbg.setTee(&clog);  // Décommenter cette ligne pour que cdbg affiche sur
    //la console en plus de la "Sortie" du débogueur.

    bibliotheque_cours::executerGoogleTest(argc, argv);  //Attention de ne rien
//afficher avant cette ligne, sinon l'Explorateur de tests va tenter de lire
//votre affichage comme un résultat de test.
#endif
}

int main(int argc, char* argv[])
{
    initialiserBibliothequeCours(argc, argv);

    QApplication app(argc, argv);
    MainGui      window;
    return app.exec();
}
