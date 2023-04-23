#pragma once
//Structures mémoires pour une collection de films.

#include <string>

struct Film;
struct Acteur;  //Permet d'utiliser les types alors qu'ils seront défini après.

struct ListeFilms
{
    int    capacite, nElements;
    Film** elements;  //Pointeur vers un tableau de Film*, chaque Film* pointant
                      //vers un Film.
};

//class ListeFilms
//{
//public:
//	ListeFilms();
//	ListeFilms(int capacite, int nElements, Film** elements);
//	ListeFilms(std::string nomFichier);
//	int nFilms() const;
//	Film** films() const;
//	void ajouterFilm(Film& film);
//	void enleverFilm(Film& film);
//	Acteur* trouverActeur(const std::string nom) const;
//	void detruireListeFilms();
//	void afficherListeFilms() const;
//
//private:
//	int capacite_;
//	int nElements_;
//	Film** elements_;
//};

struct ListeActeurs
{
    int      capacite, nElements;
    Acteur** elements;  //Pointeur vers un tableau de Acteur*, chaque Acteur*
                        //pointant vers un Acteur.
};

struct Film
{
    std::string titre, realisateur;  //Titre et nom du réalisateur (on suppose
                                     //qu'il n'y a qu'un réalisateur).
    int anneeSortie, recette;  //Année de sortie et recette globale du film en
                               //millions de dollars
    ListeActeurs acteurs;
};

struct Acteur
{
    std::string nom;
    int         anneeNaissance;
    char        sexe;
    ListeFilms  joueDans;
};
