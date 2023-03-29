/* Programme qui lit d'un fichier des films et des acteurs_ et les
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
#include <iomanip>
#include <sstream>
#include <forward_list>

#include "cppitertools/range.hpp"
#include "cppitertools/imap.hpp"
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

Film* lireFilm(istream& fichier, ListeFilms& listeFilms);

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

	capacite_ = 0;
	nElements_ = 0;
	elements_ = nullptr;
	for (int i = 0; i < nElements; i++)
	{
		Film* film = lireFilm(fichier, *this);
		ajouterFilm(film);
	}
}

int ListeFilms::nFilms() const
{
	return nElements_;
}

void ListeFilms::changeDimensions(int nouvelleCapacite)
{
	capacite_ = nouvelleCapacite;
	Film** nouvelleListeFilms = new Film * [capacite_];
	for (int i : range(nElements_))
	{
		nouvelleListeFilms[i] = elements_[i];
	}
	delete[] elements_;
	elements_ = nouvelleListeFilms;
}

void ListeFilms::ajouterFilm(Film* film)
{
	if (capacite_ == nElements_)
	{
		changeDimensions(++capacite_);
	}
	elements_[nElements_++] = film;
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
		const ListeActeurs& listeActeurs = (*film).acteurs_;
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
	delete[] elements_;
}

const Film* ListeFilms::operator[] (int index) const
{
	return elements_[index];
}

Film*& ListeFilms::operator[] (int index)
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
}

Film* lireFilm(istream& fichier, ListeFilms& listeFilms)
{
	Film film = {};
	film.titre_ = lireString(fichier);
	film.realisateur_ = lireString(fichier);
	film.annee_ = lireUint16(fichier);
	film.recette_ = lireUint16(fichier);
	film.acteurs_ = ListeActeurs(lireUint8(fichier)); 

	Film* ptrFilm = new Film();
	(*ptrFilm).titre_ = film.titre_;
	(*ptrFilm).realisateur_ = film.realisateur_;
	(*ptrFilm).annee_ = film.annee_;
	(*ptrFilm).recette_ = film.recette_;
	(*ptrFilm).acteurs_ = film.acteurs_;

	int capacite = (*ptrFilm).acteurs_.obtenirNElements();
	ListeActeurs& listeActeurs = (*ptrFilm).acteurs_;

	for (int i : range(capacite))
	{
		listeActeurs[i] = lireActeur(fichier, listeFilms);
	}
	return ptrFilm;
}

ostream& operator<<(ostream& os, const Acteur& acteur)
{
	os << "  " << acteur.nom << ", " << acteur.anneeNaissance << " " << acteur.sexe << endl;
	return os;
}

Item::Item()
{
	titre_ = "";
	annee_ = 0;
}

Item::Item(string titre, int annee)
{
	titre_ = titre;
	annee_ = annee;
}

Item::Item(const Film& film)
{
	titre_ = film.titre_;
	annee_ = film.annee_;
}

Item& Item::operator=(const Item& item)
{
	titre_ = item.titre_;
	annee_ = item.annee_;
	return *this;
}

void Item::afficher() const
{
	string affichage = "";
	affichage += "Titre: " + titre_ + "\n";

	cout << affichage;
}

Film::Film() : Item()
{
	realisateur_ = "";
	recette_ = 0;
	acteurs_ = ListeActeurs(0);
}

Film::Film(const Film& film) : Item(film)
{
	realisateur_ = film.realisateur_;
	recette_ = film.recette_;
	acteurs_ = film.acteurs_;
}

Film::Film(string titre, int annee, string realisateur, int recette, ListeActeurs acteurs) : Item(titre, annee)
{
	realisateur_ = realisateur;
	recette_ = recette;
	acteurs_ = acteurs;
}

Film& Film::operator=(const Film& film)
{
	Item::operator=(film);
	realisateur_ = film.realisateur_;
	recette_ = film.recette_;
	acteurs_ = film.acteurs_;
	return *this;
}

void Film::afficher() const
{
	cout << "Réalisateur: " << realisateur_ << "\n";
}

Livre::Livre() : Item()
{
	auteur_ = "";
	copiesVendus_ = 0;
}

Livre::Livre(string titre, int annee, string auteur, int copiesVendus, int nPages) : Item(titre, annee)
{
	auteur_ = auteur;
	copiesVendus_ = copiesVendus;
	nPages_ = nPages;
}

void Livre::afficher() const
{
	cout << "Auteur: " << auteur_ << "\n";
}

FilmLivre::FilmLivre(Film film, Livre livre) : Item(film), Film(film), Livre(livre) { ; };

void FilmLivre::afficher() const
{
	Film::afficher();
	Livre::afficher();
}

void afficherListeFilms(vector<Item*> listeFilms)
{
	static const string ligneDeSeparation = "\u0006\u0006\u0006\u0006\u0006\u0006\u0006\u0006\u0006\u0006\u0006\u0006\n";
	cout << ligneDeSeparation;
	for (Item* item : listeFilms)
	{
		(*item).Item::afficher();
		(*item).afficher();
		cout << ligneDeSeparation;
	}
}

const int indiceHobbitFilm = 4;
const int indiceHobbitLivre = 9;

int main()
{
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut.

	static const string ligneDeSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";

	ListeFilms listeFilms = ListeFilms("films.bin");

	vector<Item*> bibliotheque;

	for (int i : range(listeFilms.nFilms()))
	{
		bibliotheque.push_back(listeFilms[i]);
	}

	ifstream fichier("livres.txt");
	string ligne = "";
	string titre = "";
	int annee = 0;
	string auteur = "";
	int copiesVendus = 0;
	int nPages = 0;
	
	while (getline(fichier, ligne))
	{
		istringstream iss(ligne);
		iss >> quoted(titre) >> annee >> quoted(auteur) >> copiesVendus >> nPages;
		bibliotheque.push_back(new Livre(titre, annee, auteur, copiesVendus, nPages));
	}

	bibliotheque.push_back(new FilmLivre(*dynamic_cast<Film*>(bibliotheque[indiceHobbitFilm]), *dynamic_cast<Livre*>(bibliotheque[indiceHobbitLivre])));

	afficherListeFilms(bibliotheque);

	forward_list<Item*> listeLiee;
	forward_list<Item*> listeLiee2;
	forward_list<Item*> listeLieeRenversee;
	vector<Item*> bibliotheque2;

	for (Item* item : bibliotheque)
	{
		listeLiee.push_front(item);
	}

	for (Item* item : bibliotheque)
	{
		listeLieeRenversee.insert_after(listeLieeRenversee.before_begin(), item);
	}

	for (Item* item : listeLiee)
	{
		listeLiee2.push_front(item);
	}

	for (Item* item : listeLiee) // O(n)
	{
		bibliotheque2.insert(bibliotheque2.begin(), item); // O(n)
	} // Total = O(n^2)

	Film* alien = dynamic_cast<Film*>(bibliotheque[0]);
	ListeActeurs listeActeurs = move(alien->acteurs_);

	for (auto&& acteur : listeActeurs)
	{
		cout << acteur << "\n";
	}

	for (Item* item : bibliotheque)
	{
		delete item;
		item = nullptr;
	}

	listeFilms.detruireListeFilms();

	return 0;
}