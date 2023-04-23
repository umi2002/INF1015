#pragma once
//Structures mémoires pour une collection de films.

#include <functional>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Film;
struct Acteur;  //Permet d'utiliser les types alors qu'ils seront défini après.

class ListeFilms
{
public:
    ListeFilms();
    ListeFilms(int capacite, int nElements, Film** elements);
    ListeFilms(std::string nomFichier);
    int                  nFilms() const;
    void                 changeDimensions(int nouvelleCapacite);
    void                 ajouterFilm(Film* film);
    void                 enleverFilm(Film& film);
    shared_ptr< Acteur > trouverActeur(const std::string nom) const;
    void                 detruireListeFilms();
    const Film*          operator[](int index) const;
    Film*&               operator[](int index);
    Film trouverFilm(const function< bool(Film) >& critere) const;

private:
    int    capacite_;
    int    nElements_;
    Film** elements_;
};

template< typename T >
class Liste
{
public:
    Liste(int nElements);
    Liste(const Liste< T >& liste);
    Liste< T >&            operator=(const Liste< T >& liste);
    int                    obtenirNElements() const;
    int                    obtenirCapacite() const;
    shared_ptr< T >&       operator[](int index);
    const shared_ptr< T >& operator[](int index) const;

private:
    int                             capacite_ = 0, nElements_ = 0;
    unique_ptr< shared_ptr< T >[] > elements_ =
        make_unique< shared_ptr< T >[] >(capacite_);
};

template< typename T >
Liste< T >::Liste(int nElements)
{
    nElements_ = nElements;
    capacite_  = nElements_;
    elements_  = make_unique< shared_ptr< T >[] >(capacite_);
}

template< typename T >
Liste< T >::Liste(const Liste< T >& liste)
{
    nElements_ = liste.nElements_;
    capacite_  = liste.capacite_;
    elements_  = make_unique< shared_ptr< T >[] >(capacite_);
    for (int i = 0; i < nElements_; i++)
    {
        elements_[i] = liste.elements_[i];
    }
}

template< typename T >
Liste< T >& Liste< T >::operator=(const Liste< T >& liste)
{
    nElements_ = liste.nElements_;
    capacite_  = liste.capacite_;
    elements_  = make_unique< shared_ptr< T >[] >(capacite_);
    for (int i = 0; i < nElements_; i++)
    {
        elements_[i] = liste.elements_[i];
    }
    return *this;
}

template< typename T >
int Liste< T >::obtenirNElements() const
{
    return nElements_;
}

template< typename T >
int Liste< T >::obtenirCapacite() const
{
    return capacite_;
}

template< typename T >
shared_ptr< T >& Liste< T >::operator[](int index)
{
    return elements_[index];
}

template< typename T >
const shared_ptr< T >& Liste< T >::operator[](int index) const
{
    return elements_[index];
}

using ListeActeurs = Liste< Acteur >;

struct Acteur
{
    string          nom            = "";
    int             anneeNaissance = 0;
    char            sexe           = '\0';
    friend ostream& operator<<(ostream& os, const Acteur& acteur);
};

class Affichable
{
public:
    virtual const string afficherBase() const = 0;
    virtual const string afficher() const     = 0;
    virtual ~Affichable()                     = default;
};

class Item : public Affichable
{
public:
    Item();
    Item(string titre, int annee);
    Item(const Film& film);
    Item&        operator=(const Item& item);
    friend Film* lireFilm(istream& fichier, ListeFilms& listeFilms);
    friend shared_ptr< Acteur >
                         ListeFilms::trouverActeur(const std::string nom) const;
    virtual const string afficherBase() const override;
    virtual const string afficher() const override;

private:
    string titre_;
    int    annee_;
};

class Film : virtual public Item
{
public:
    Film();
    Film(const Film& film);
    Film& operator=(const Film& film);
    Film(string       titre,
         int          annee,
         string       realisateur,
         int          recette,
         ListeActeurs acteurs);
    friend Film* lireFilm(istream& fichier, ListeFilms& listeFilms);
    friend shared_ptr< Acteur >
                         ListeFilms::trouverActeur(const std::string nom) const;
    virtual const string afficher() const override;

private:
    string       realisateur_ = "";
    int          recette_     = 0;
    ListeActeurs acteurs_     = ListeActeurs(0);
};

class Livre : virtual public Item
{
public:
    Livre();
    Livre(string titre, int annee, string auteur, int copiesVendus, int nPages);
    virtual const string afficher() const override;

private:
    string auteur_;
    int    copiesVendus_;
    int    nPages_;
};

class FilmLivre : public Film, public Livre
{
public:
    FilmLivre(Film film, Livre livre);
    virtual const string afficher() const override;

private:
};
