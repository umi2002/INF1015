/* Programme qui lit d'un fichier des films et des acteurs et les
 * convertit dans des structures
 * \file td2.cpp
 * \author Hoang et Ibarissen
 * \date 10 février 2023
 * Créé le 31 janvier 2023
 */

#pragma region "Includes"//{
#define _CRT_SECURE_NO_WARNINGS // On permet d'utiliser les fonctions de copies de chaînes qui sont considérées non sécuritaires.

#include "structures.hpp"      // Structures de données pour la collection de films en mémoire.

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>

#include "cppitertools/range.hpp"
#include "gsl/span"

#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp" // Nos fonctions pour le rapport de fuites de mémoire.
#include "debogage_memoire.hpp"        // Ajout des numéros de ligne des "new" dans le rapport de fuites.  Doit être après les include du système, qui peuvent utiliser des "placement new" (non supporté par notre ajout de numéros de lignes).

using namespace std;
using namespace iter;
using namespace gsl;

#pragma endregion//}

typedef uint8_t UInt8;
typedef uint16_t UInt16;

#pragma region "Fonctions de base pour lire le fichier binaire"//{

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
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}

#pragma endregion//}

void detruireFilm(Film& film);
Film* lireFilm(istream& fichier, ListeFilms& listeFilms);

//Version de la partie 2 du code en utilisant une classe ListeFilm.

ListeFilms::ListeFilms()
{
	capacite_ = 0;
	nElements_ = 0;
	elements_ = nullptr;
}

ListeFilms::ListeFilms(int capacite, int nElements, Film** elements)
{
	capacite_ = capacite;
	nElements_ = nElements;
	elements_ = elements;
}

ListeFilms::ListeFilms(string nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);

	int nElements = lireUint16(fichier);

	//TODO: Créer une liste de films vide.
	capacite_ = 0;
	nElements_ = 0;
	elements_ = nullptr;
	for (int i = 0; i < nElements; i++)
	{
		Film& film = *(lireFilm(fichier, *this));
		ajouterFilm(film); //TODO: Ajouter le film à la liste.
	}
}

int ListeFilms::nFilms() const
{
	return nElements_;
}

Film** ListeFilms::films() const
{
	return elements_;
}

void ListeFilms::ajouterFilm(Film& film)
{
	if (nElements_ == 0)
	{
		capacite_++;
		capacite_ *= 2;
		elements_ = new Film * [capacite_];
		elements_[nElements_] = &film;
		nElements_++;
	}
	else if (capacite_ == nElements_)
	{
		capacite_++;
		capacite_ *= 2;
		Film** nouvelleListeFilms = new Film * [capacite_];
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
			elements_[i] = elements_[nElements_ - 1];
			elements_[nElements_ - 1] = nullptr;
			nElements_--;
		}
	}
}

shared_ptr<Acteur> ListeFilms::trouverActeur(const string nom) const
{
	span<Film*> spanFilms = span(elements_, nElements_);
	for (Film* film : spanFilms)
	{
		const ListeActeurs& listeActeurs = (*film).acteurs;
		for (int j : range(listeActeurs.obtenirNElements()))
		{
			shared_ptr<Acteur> ptrActeur = listeActeurs[j];
			if ((*ptrActeur).nom == nom)
			{
				return ptrActeur;
			}
		}
	}
	return nullptr;
}

void ListeFilms::detruireListeFilms()
{
	for (int i : range(nElements_))
	{
		Film*& film = elements_[i];
		detruireFilm(*film);
	}
	delete[] elements_;
}

void ListeFilms::afficherListeFilms() const
{
	//TODO: Utiliser des caractères Unicode pour définir la ligne de séparation (différente des autres lignes de séparations dans ce progamme).
	static const string ligneDeSeparation = "\u0006\u0006\u0006\u0006\u0006\u0006\u0006\u0006\u0006\u0006\u0006\u0006\n";
	cout << ligneDeSeparation;
	//TODO: Changer le for pour utiliser un span.
	span<Film*> spanFilms = span(elements_, nElements_);
	for (Film* film : spanFilms)
	{
		//TODO: Afficher le film.
		cout << *film;
		cout << ligneDeSeparation;
	}
}

Film* ListeFilms::operator[] (int index) const
{
	return elements_[index];
}

Film ListeFilms::trouverFilm(const function<bool(Film)>& critere) const
{
	span<Film*> spanFilms = span(elements_, nElements_);
	for (Film* film : spanFilms)
	{
		if (critere(*film))
		{
			return *film;
		}
	}
	return Film();
}

shared_ptr<Acteur> lireActeur(istream& fichier, const ListeFilms listeFilms)
{
	Acteur acteur = {};
	acteur.nom = lireString(fichier);
	acteur.anneeNaissance = lireUint16(fichier);
	acteur.sexe = lireUint8(fichier);

	if (listeFilms.trouverActeur(acteur.nom))
	{
		return listeFilms.trouverActeur(acteur.nom);
	}
	else
	{
		shared_ptr<Acteur> ptrActeur = make_shared<Acteur>(acteur);
		cout << acteur.nom << "\n";
		return ptrActeur;
	}

	//TODO: Retourner un pointeur soit vers un acteur existant ou un nouvel acteur ayant les bonnes informations, selon si l'acteur existait déjà.  Pour fins de débogage, affichez les noms des acteurs crées; vous ne devriez pas voir le même nom d'acteur affiché deux fois pour la création.
}

Film* lireFilm(istream& fichier, ListeFilms& listeFilms)
{
	Film film = {};
	film.titre = lireString(fichier);
	film.realisateur = lireString(fichier);
	film.anneeSortie = lireUint16(fichier);
	film.recette = lireUint16(fichier);
	film.acteurs = ListeActeurs(lireUint8(fichier));  //NOTE: Vous avez le droit d'allouer d'un coup le tableau pour les acteurs, sans faire de réallocation comme pour ListeFilms.  Vous pouvez aussi copier-coller les fonctions d'allocation de ListeFilms ci-dessus dans des nouvelles fonctions et faire un remplacement de Film par Acteur, pour réutiliser cette réallocation.

	Film* ptrFilm = new Film();
	(*ptrFilm).titre = film.titre;
	(*ptrFilm).realisateur = film.realisateur;
	(*ptrFilm).anneeSortie = film.anneeSortie;
	(*ptrFilm).recette = film.recette;
	(*ptrFilm).acteurs = move(film.acteurs);

	int capacite = (*ptrFilm).acteurs.obtenirNElements();
	ListeActeurs& listeActeurs = (*ptrFilm).acteurs;

	for (int i : range(capacite))
	{
		listeActeurs[i] = lireActeur(fichier, listeFilms); //TODO: Placer l'acteur au bon endroit dans les acteurs du film.
		//ListeFilms& filmsJoueDans = listeActeurs[i].joueDans;
		//filmsJoueDans.ajouterFilm(*ptrFilm); //TODO: Ajouter le film à la liste des films dans lesquels l'acteur joue.
	}
	return ptrFilm; //TODO: Retourner le pointeur vers le nouveau film.
}

void detruireFilm(Film& film)
{
	//int nActeurs = film.acteurs.obtenirNElements();
	//ListeActeurs& listeActeurs = film.acteurs;
	//for (int i : range(nActeurs))
	//{
	//	shared_ptr<Acteur>& acteur = listeActeurs[i];
	//	ListeFilms& filmsJoueDans = (*acteur).joueDans;
	//	filmsJoueDans.enleverFilm(film);
	//
	//	int nFilmsJoueDans = filmsJoueDans.nFilms();
	//	if (nFilmsJoueDans == 0)
	//	{
	//		cout << (*acteur).nom << "\n";
	//		filmsJoueDans.detruireListeFilms();
	//		delete acteur;
	//	}
	//}
	delete& film;
}

//void afficherFilmographieActeur(const ListeFilms& listeFilms, const string& nomActeur)
//{
//	//TODO: Utiliser votre fonction pour trouver l'acteur (au lieu de le mettre à nullptr).
//	const Acteur* acteur = listeFilms.trouverActeur(nomActeur);
//	if (acteur == nullptr)
//		cout << "Aucun acteur de ce nom" << endl;
//	else
//		listeFilms.afficherListeFilms();
//}

ostream& operator<<(ostream& os, const Acteur& acteur)
{
	os << "  " << acteur.nom << ", " << acteur.anneeNaissance << " " << acteur.sexe << endl;
	return os;
}

Film::Film() {};

Film::Film(const Film& film)
{
	titre = film.titre;
	realisateur = film.realisateur;
	anneeSortie = film.anneeSortie;
	recette = film.recette;
	int nElements = film.acteurs.obtenirNElements();
	acteurs = ListeActeurs(nElements);
	for (int i = 0; i < nElements; i++)
	{
		acteurs[i] = film.acteurs[i];
	}
}

ostream& operator<<(ostream& os, const Film& film)
{
	os << "Titre: " << film.titre << "\n";
	os << "Réalisateur: " << film.realisateur << "\n";
	os << "Année de sortie: " << film.anneeSortie << "\n";
	os << "Recette: " << film.recette << "\n";
	int nActeurs = film.acteurs.obtenirNElements();
	for (int i = 0; i < nActeurs; i++)
	{
		const Acteur& acteur = *film.acteurs[i];
		cout << acteur;
	}
	return os;
}

int main()
{
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut.

	static const string ligneDeSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";

	//TODO: Chaque TODO dans cette fonction devrait se faire en 1 ou 2 lignes, en appelant les fonctions écrites.

	//TODO: La ligne suivante devrait lire le fichier binaire en allouant la mémoire nécessaire.  Devrait afficher les noms de 20 acteurs sans doublons (par l'affichage pour fins de débogage dans votre fonction lireActeur).
	ListeFilms listeFilms = ListeFilms("films.bin");

	cout << ligneDeSeparation << "Le premier film de la liste est:" << endl;
	//TODO: Afficher le premier film de la liste.  Devrait être Alien.
	cout << *(listeFilms.films()[0]);

	cout << ligneDeSeparation << "Les films sont:" << endl;
	//TODO: Afficher la liste des films.  Il devrait y en avoir 7.
	listeFilms.afficherListeFilms();

	//TODO: Modifier l'année de naissance de Benedict Cumberbatch pour être 1976 (elle était 0 dans les données lues du fichier).  Vous ne pouvez pas supposer l'ordre des films et des acteurs dans les listes, il faut y aller par son nom.
	(*listeFilms.trouverActeur("Benedict Cumberbatch")).anneeNaissance = 1976;

	//cout << ligneDeSeparation << "Liste des films où Benedict Cumberbatch joue sont:" << endl;
	//TODO: Afficher la liste des films où Benedict Cumberbatch joue.  Il devrait y avoir Le Hobbit et Le jeu de l'imitation.
	//afficherFilmographieActeur(listeFilms, "Benedict Cumberbatch");

	cout << ligneDeSeparation;

	Film skylien = *listeFilms[0];
	skylien.titre = "Skylien";
	skylien.acteurs[0] = (*listeFilms[1]).acteurs[0];
	(*skylien.acteurs[0]).nom = "Daniel Wroughton Craig";
	cout << skylien << *listeFilms[0] << *listeFilms[1];

	//TODO: Détruire et enlever le premier film de la liste (Alien).  Ceci devrait "automatiquement" (par ce que font vos fonctions) détruire les acteurs Tom Skerritt et John Hurt, mais pas Sigourney Weaver puisqu'elle joue aussi dans Avatar.
	detruireFilm(*(listeFilms.films()[0]));
	listeFilms.enleverFilm(*(listeFilms.films()[0]));

	cout << ligneDeSeparation << "Les films sont maintenant:" << endl;
	//TODO: Afficher la liste des films.
	listeFilms.afficherListeFilms();

	cout << ligneDeSeparation;

	cout << listeFilms.trouverFilm([](Film film) {return film.recette == 955;});

	//TODO: Faire les appels qui manquent pour avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.
	//afficherFilmographieActeur(listeFilms, "");

	//TODO: Détruire tout avant de terminer le programme.  La bibliothèque de verification_allocation devrait afficher "Aucune fuite detectee." a la sortie du programme; il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.
	listeFilms.detruireListeFilms();
}