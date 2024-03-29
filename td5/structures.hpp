#pragma once
//Structures mémoires pour une collection de films.

#include "cppitertools/itertools.hpp"

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
    class iterator
    {
    public:
        iterator(Liste< T >& liste, int position = 0);

        shared_ptr< T >& operator*();
        iterator&        operator++();
        iterator&        operator--();

        bool operator==(const iterator& autre) const;
        bool operator!=(const iterator& autre) const;

    private:
        Liste< T >& liste_;
        int         position_;
    };

    Liste(int nElements);
    Liste(const Liste< T >& liste);
    Liste< T >&            operator=(const Liste< T >& liste);
    int                    obtenirNElements() const;
    int                    obtenirCapacite() const;
    shared_ptr< T >&       operator[](int index);
    const shared_ptr< T >& operator[](int index) const;

    bool operator==(const Liste< T >& autre) const;
    bool operator!=(const Liste< T >& autre) const;

    iterator begin();
    iterator end();

private:
    int                             capacite_ = 0, nElements_ = 0;
    unique_ptr< shared_ptr< T >[] > elements_ =
        make_unique< shared_ptr< T >[] >(capacite_);
};

template< typename T >
Liste< T >::iterator::iterator(Liste< T >& liste, int position) :
    liste_(liste),
    position_(position)
{ }

template< typename T >
shared_ptr< T >& Liste< T >::iterator::operator*()
{
    return liste_.elements_[position_];
}

template< typename T >
typename Liste< T >::iterator& Liste< T >::iterator::operator++()
{
    position_++;
    return *this;
}

template< typename T >
typename Liste< T >::iterator& Liste< T >::iterator::operator--()
{
    position_--;
    return *this;
}

template< typename T >
bool Liste< T >::iterator::operator==(const iterator& autre) const
{
    return (liste_ == autre.liste_ && position_ == autre.position_);
}

template< typename T >
bool Liste< T >::iterator::operator!=(const iterator& autre) const
{
    return !(*this == autre);
}

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

template< typename T >
typename Liste< T >::iterator Liste< T >::begin()
{
    return iterator(*this, 0);
}

template< typename T >
typename Liste< T >::iterator Liste< T >::end()
{
    return iterator(*this, nElements_);
}

template< typename T >
bool Liste< T >::operator==(const Liste< T >& autre) const
{
    if (nElements_ != autre.nElements_)
    {
        return false;
    }
    for (int i = 0; i < nElements_; i++)
    {
        if (elements_[i] != autre.elements_[i])
        {
            return false;
        }
    }
    return true;
}

template< typename T >
bool Liste< T >::operator!=(const Liste< T >& autre) const
{
    return !(*this == autre);
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
    virtual void afficher() const = 0;
    virtual ~Affichable()         = default;
};

class Item : public Affichable
{
public:
    Item();
    Item(string titre, int annee);
    Item(const Film& film);
    Item& operator=(const Item& item);
    bool  operator<(const Item& autre) const;

    friend Film* lireFilm(istream& fichier, ListeFilms& listeFilms);
    friend shared_ptr< Acteur >
                 ListeFilms::trouverActeur(const std::string nom) const;
    virtual void afficher() const override;

    string titre_;

private:
    int annee_;
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
    virtual void afficher() const override;

    ListeActeurs acteurs_     = ListeActeurs(0);
    string       realisateur_ = "";
    int          recette_     = 0;

private:
};

class Livre : virtual public Item
{
public:
    Livre();
    Livre(string titre, int annee, string auteur, int copiesVendus, int nPages);
    virtual void afficher() const override;

private:
    string auteur_;
    int    copiesVendus_;
    int    nPages_;
};

class FilmLivre : public Film, public Livre
{
public:
    FilmLivre(Film film, Livre livre);
    virtual void afficher() const override;

private:
};
