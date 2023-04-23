#pragma once
#pragma region "Includes"        //{
#define _CRT_SECURE_NO_WARNINGS  //On permet d'utiliser les fonctions de copies
                                 //de chaînes qui sont considérées non
                                 //sécuritaires.

#include "ClasseListeFilms.hpp"
#include "bibliotheque_cours.hpp"
#include "cppitertools/range.hpp"
#include "debogage_memoire.hpp"  // Ajout des numéros de ligne des "new" dans le rapport de fuites.  Doit être après les include du système, qui peuvent utiliser des "placement new" (non supporté par notre ajout de numéros de lignes).
#include "gsl/span"
#include "structures.hpp"  // Structures de données pour la collection de films en mémoire.
#include "verification_allocation.hpp"  // Nos fonctions pour le rapport de fuites de mémoire.

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using namespace std;
using namespace iter;
using namespace gsl;

#pragma endregion  //}

typedef uint8_t  UInt8;
typedef uint16_t UInt16;

#pragma region "Fonctions de base pour lire le fichier binaire"  //{

UInt8 lireUint8(istream& fichier)
{
    UInt8 valeur = 0;
    fichier.read((char*)&valeur, sizeof(valeur));
    return valeur;
}

UInt16 lireUint16(istream& fichier)
{
    UInt16 valeur = 0;
    fichier.read((char*)&valeur, sizeof(valeur));
    return valeur;
}

string lireString(istream& fichier)
{
    string texte;
    texte.resize(lireUint16(fichier));
    fichier.read((char*)&texte[0],
                 streamsize(sizeof(texte[0])) * texte.length());
    return texte;
}

#pragma endregion  //}

class ListeFilms
{
public:
    ListeFilms();
    ListeFilms(int capacite, int nElements, Film** elements);
    void    ajouterFilm(Film& film);
    void    enleverFilm(Film& film);
    Acteur* trouverActeur(const std::string nom);
    Acteur* lireActeur(istream& fichier);
    Film*   lireFilm(istream& fichier);
    void    creerListe(string nomFichier);
    void    detruireListeFilms();

private:
    int    capacite_;
    int    nElements_;
    Film** elements_;
};

ListeFilms::ListeFilms()
{
    capacite_        = 0;
    nElements_       = 0;
    Film** elements_ = nullptr;
}

ListeFilms::ListeFilms(int capacite, int nElements, Film** elements)
{
    capacite_  = capacite;
    nElements_ = nElements;
    elements_  = elements;
}

void ListeFilms::ajouterFilm(Film& film)
{
    if (nElements_ == 0)
    {
        capacite_++;
        capacite_             *= 2;
        elements_             = new Film*[capacite_];
        elements_[nElements_] = &film;
        nElements_++;
    }
    else if (capacite_ == nElements_)
    {
        capacite_++;
        capacite_                 *= 2;
        Film** nouvelleListeFilms = new Film*[capacite_];
        for (int i : range(nElements_))
        {
            nouvelleListeFilms[i] = elements_[i];
        }
        nouvelleListeFilms[nElements_] = &film;
        nElements_++;
        delete[] elements_;
        elements_ = nouvelleListeFilms;
    }
    else
    {
        elements_[nElements_] = &film;
        nElements_++;
    }
}

void ListeFilms::enleverFilm(Film& film)
{
    for (int i : range(nElements_))
    {
        if (elements_[i] == &film)
        {
            elements_[i]              = elements_[nElements_ - 1];
            elements_[nElements_ - 1] = nullptr;
            nElements_--;
        }
    }
}

Acteur* ListeFilms::trouverActeur(const std::string nom)
{
    span< Film* > spanFilms = span(elements_, nElements_);
    for (Film* film : spanFilms)
    {
        ListeActeurs listeActeurs = (*film).acteurs;
        for (int j : range(listeActeurs.nElements))
        {
            Acteur* ptrActeur = listeActeurs.elements[j];
            if ((*ptrActeur).nom == nom)
            {
                return ptrActeur;
            }
        }
    }
    return nullptr;
}

Acteur* ListeFilms::lireActeur(istream& fichier)
{
    Acteur acteur         = {};
    acteur.nom            = lireString(fichier);
    acteur.anneeNaissance = lireUint16(fichier);
    acteur.sexe           = lireUint8(fichier);

    if (trouverActeur(acteur.nom))
    {
        return trouverActeur(acteur.nom);
    }
    else
    {
        Acteur* ptrActeur           = new Acteur();
        (*ptrActeur).nom            = acteur.nom;
        (*ptrActeur).anneeNaissance = acteur.anneeNaissance;
        (*ptrActeur).sexe           = acteur.sexe;
        cout << acteur.nom << "\n";
        return ptrActeur;
    }
}

Film* ListeFilms::lireFilm(istream& fichier)
{
    Film film              = {};
    film.titre             = lireString(fichier);
    film.realisateur       = lireString(fichier);
    film.anneeSortie       = lireUint16(fichier);
    film.recette           = lireUint16(fichier);
    film.acteurs.nElements = lireUint8(
        fichier);  //NOTE: Vous avez le droit d'allouer d'un coup le tableau
                   //pour les acteurs, sans faire de réallocation comme pour
                   //ListeFilms.  Vous pouvez aussi copier-coller les fonctions
                   //d'allocation de ListeFilms ci-dessus dans des nouvelles
                   //fonctions et faire un remplacement de Film par Acteur, pour
                   //réutiliser cette réallocation.

    Film* ptrFilm                = new Film();
    (*ptrFilm).titre             = film.titre;
    (*ptrFilm).realisateur       = film.realisateur;
    (*ptrFilm).anneeSortie       = film.anneeSortie;
    (*ptrFilm).recette           = film.recette;
    (*ptrFilm).acteurs.nElements = film.acteurs.nElements;

    int capacite                = film.acteurs.nElements;
    film.acteurs.capacite       = capacite;
    (*ptrFilm).acteurs.elements = new Acteur*[capacite];
    Acteur**& elements          = (*ptrFilm).acteurs.elements;

    for (int i : range(capacite))
    {
        elements[i] = lireActeur(fichier);  //TODO: Placer l'acteur au bon
                                            //endroit dans les acteurs du film.
        ListeFilms& filmsJoueDans = (*elements[i]).joueDans;
        ajouterFilm(*ptrFilm);  //TODO: Ajouter le film à la liste des films
                                //dans lesquels l'acteur joue.
    }
    return ptrFilm;  //TODO: Retourner le pointeur vers le nouveau film.
}

void ListeFilms::creerListe(string nomFichier)
{
    ifstream fichier(nomFichier, ios::binary);
    fichier.exceptions(ios::failbit);

    int nElements = lireUint16(fichier);

    //TODO: Créer une liste de films vide.
    capacite_ = 0;
    nElements = 0;
    elements_ = nullptr;
    for (int i : range(nElements))
    {
        Film& film = *(lireFilm(fichier));
        ajouterFilm(film);  //TODO: Ajouter le film à la liste.
    }
}

void ListeFilms::detruireListeFilms()
{
    int     nFilms             = nElements_;
    Film**& elementsListeFilms = elements_;
    for (int i : range(nFilms))
    {
        Film*& film = elementsListeFilms[i];
        detruireFilm(*film);
    }
    delete[] elementsListeFilms;
}