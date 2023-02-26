#pragma once
// Structures mémoires pour une collection de films.

#include <string>
#include <memory>
#include <iostream>
#include <functional>

using namespace std;

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront défini après.

//struct ListeFilms {
//	int capacite = 0, nElements = 0;
//	Film** elements = nullptr; // Pointeur vers un tableau de Film*, chaque Film* pointant vers un Film.
//};

class ListeFilms
{
public:
	ListeFilms();
	ListeFilms(int capacite, int nElements, Film** elements);
	ListeFilms(std::string nomFichier);
	int nFilms() const;
	Film** films() const;
	void ajouterFilm(Film& film);
	void enleverFilm(Film& film);
	shared_ptr<Acteur> trouverActeur(const std::string nom) const;
	void detruireListeFilms();
	void afficherListeFilms() const;
	Film* operator[](int index) const;
	Film trouverFilm(const function<bool(Film)>& critere) const;

private:
	int capacite_;
	int nElements_;
	Film** elements_;
};

class ListeActeurs {
public:
	ListeActeurs(int nElements);
	int obtenirNElements() const;
	int obtenirCapacite() const;
	shared_ptr<Acteur>& operator[](int index);
	const shared_ptr<Acteur>& operator[](int index) const;
private:
	int capacite_ = 0, nElements_ = 0;
	unique_ptr<shared_ptr<Acteur>[]> elements_ = make_unique<shared_ptr<Acteur>[]>(capacite_); // Pointeur vers un tableau de Acteur*, chaque Acteur* pointant vers un Acteur.
};

ListeActeurs::ListeActeurs(int nElements)
{
	nElements_ = nElements;
	capacite_ = nElements_;
	elements_ = make_unique<shared_ptr<Acteur>[]>(capacite_);
}

int ListeActeurs::obtenirNElements() const
{
	return nElements_;
}

int ListeActeurs::obtenirCapacite() const
{
	return capacite_;
}

shared_ptr<Acteur>& ListeActeurs::operator[](int index)
{
	return elements_[index];
}

const shared_ptr<Acteur>& ListeActeurs::operator[](int index) const
{
	return elements_[index];
}

struct Acteur
{
	string nom = ""; int anneeNaissance = 0; char sexe = '\0';
	friend ostream& operator<<(ostream& os, const Acteur& acteur);
	//ListeFilms joueDans{};
};

struct Film
{
	Film();
	Film(const Film& film);
	string titre = "", realisateur = ""; // Titre et nom du réalisateur (on suppose qu'il n'y a qu'un réalisateur).
	int anneeSortie = 0, recette = 0; // Année de sortie et recette globale du film en millions de dollars
	ListeActeurs acteurs = ListeActeurs(0);
	friend ostream& operator<<(ostream& os, const Film& film);
};
