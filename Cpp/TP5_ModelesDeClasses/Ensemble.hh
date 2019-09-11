/**
 * @file   Ensemble.hh
 * @author Nicolas MASSE & Thomas LIMIN
 * @date   Thu Nov 18
 * 
 * @brief Declaration de la classe parametree Ensemble.
 * 
 */
#ifndef ENSEMBLE_H
#define ENSEMBLE_H

#include <iostream>
#include <ostream>

/* using namespace std;
 *
 * NOTE :
 * Ce fichier d'en-tete ne comporte pas de directive using, bien que la version
 * fournie en comporte. En effet, l'usage de cette directive dans un fichier
 * d'en-tete (dont la finalite est d'etre inclus dans un fichier source) peut creer
 * des conflits d'espace de noms dans les fichiers l'incluant. On preferera
 * l'utilisation des prefixe d'espace de noms
 */




/**
 * Extension (iterateur, foncteur)
 * Classe foncteur. Ses instances peuvent etre appelees
 * comme des fonctions race à la surcharge de l'opérateur ()
 * l'implémentation courante retourne le double de l'element
 * passé a cette fonction
 */

template <typename T>

class Foncteur {

public:

    /**
     * Constructeur. Permet de definir le coefficient de multiplication
     * propre au foncteur
     *
     * @param coef	le coefficient
     */
    Foncteur(double coef) : _coef(coef) {}

    /**
     * Une methode foncteur, retourne le double de l'elemet
     * passe en parametre. Ceci ne fonctionne que pour les
     * types de données qpossédant un opérateur *
     *
     * @param e	l'element a traiter
     * @return	l'element retourne
     */
    T operator() (const T & e) {
        return e * _coef;
    }

private:

    double _coef;
};



/**
 * Classe permettant de representer un ensemble d'elements
 * en utilisant uniquement la notion d'egalite entre elements
 * Aucune relation d'ordre n'est utilisee (par exemple
 * pour avoir un representation ordonnee en memoire qui accelererait
 * les recherches).<br>
 * Seul l'operateur == est utilise pour tester l'egalite de deux 
 * elements.
 */

template <typename T>

class Ensemble {

private:

    /**
     * Concept de noeud d'une liste chainée. Cette clase est définnie a l'interieur
     * de la classe ensemble, ce qui permet d'en limiter la portée a la classe
     * Ensemble
     */

    class Noeud {

    private:
        T _valeur;
        Noeud * _suivant;

    public:
        Noeud(const T & valeur, Noeud * suivant = 0) : _valeur(valeur), _suivant(suivant) { }

        Noeud(const Noeud & n) {
            _valeur = n.getValeur();

            if (n.aUnSuivant()) {
                _suivant = new Noeud(*n.getSuivant());
            } else {
                _suivant = 0;
            }
        }

        ~Noeud() {
            delete _suivant;
        }

        const T & getValeur() const {
            return _valeur;
        }

        Noeud * getSuivant() const {
            return _suivant;
        }

        void setSuivant(Noeud * suivant) {
            _suivant = suivant;
        }

        bool aUnSuivant() const {
            return _suivant != 0;
        }

        /**
         * Methode recursive de suppression d'un element dans
         * une liste chainee.
         *
         * @param liste une liste.
         * @param x un element.
         * 
         * @return le liste sans l'element.
         */
        Noeud * retire(const T & x) {

            Noeud * ret = this;

            if (this->getValeur() == x) {
                // On l'a trouve !
                ret = this->getSuivant();
                this->setSuivant(0);
                delete this;
            } else if (this->aUnSuivant()) {
                // Il y a un suivant.
                this->setSuivant(this->getSuivant()->retire(x));
            }

            return ret;
        }
    };


    /**
     * Concept d'iterateur d'une liste.
     */

    class Iterateur {

    public:
        /**
         * Constructeur d'iterateur. L'iterateur retourne permet
         * d'acceder au premier element de la l'ensemble.
         *
         * @param e	l'enemble sur lequel l'iterateur s'applique
         */
        Iterateur(const Ensemble<T> & e) : _ensemble(e) {
            _noeudSuivant = e._liste;
        }

        /**
         * Test la fin de l'ensemble itere
         *
         * @return true si il reste des element, false sinon
         */
        bool hasNext() const {
            return _noeudSuivant != 0;
        }

        /**
         * @return l'element courant et passe au suivant
         */
        const T & next() {
            const T & v = _noeudSuivant->getValeur();

            _noeudSuivant = _noeudSuivant->getSuivant();

            return v;
        }

    private:
        /**
         * l'enemble itere
         */
        const Ensemble<T> & _ensemble;

        /**
         * la position courante dans l'ensemble
         */
        Noeud * _noeudSuivant;
    };

    Noeud * _liste;


public:

    /**
     * Construit un ensemble vide.
     */
    Ensemble<T>() : _liste(0) { }

    /**
     * Construit un singleton.
     */
    Ensemble<T>(T x) {
        _liste = new Noeud(x);
    }

    /**
     * Destructeur.
     */
    ~Ensemble<T>() {
        // delete 0 fonctionne !
        delete _liste;
        _liste = 0;
    }

    /**
     * Test si l'ensemble est vide.
     *
     * @return true si l'ensemble est vide, sinon false.
     */
    bool estVide() const {
        return _liste == 0;
    }

    /**
     * Envoie tous les elements dans un flot de sortie.
     * 
     * @param out un flot de sortie.
     * 
     * @return le flot de sortie donne en parametre.
     */
    std::ostream & flush(std::ostream & out) const {
        Noeud * courant = _liste;

        out << "[ ";

        while (courant != 0) {
            out << courant->getValeur() << " ";
            courant = courant->getSuivant();
        }

        out << "]" << std::endl;

        return out;
    }

    /**
     * Test l'appartenance d'un element a l'ensemble.
     * 
     * @param x un double.
     * 
     * @return true sie est dans l'ensemble, false sinon.
     */
    bool contient(const T & x) const {
        Noeud * courant = _liste;
        bool result = false;

        while (courant != 0) {
            if (courant->getValeur() == x) {
                result = true;
                break;
            }

            courant = courant->getSuivant();
        }

        return result;
    }

    /**
     * Test l'inclusion dans un autre ensemble.
     * 
     * @param e un ensemble
     * 
     * @return true si "je" suis inclus dans e, false sinon.
     */
    bool estInclusDans(const Ensemble<T> & autre) const {
        Noeud * courant = _liste;
        bool result = true;

        while (courant != 0) {
            if (!autre.contient(courant->getValeur())) {
                result = false;
                break;
            }

            courant = courant->getSuivant();
        }

        return result;
    }

    /**
     * Ajoute un "objet" a l'ensemble.
     * 
     * @param x un element a ajouter a l'ensemble.
     */
    void ajoute(const T & x) {
        if (!this->contient(x)) {
            _liste = new Noeud(x, _liste);
        }
    }

    /**
     * Retire un element de l'esemble.
     * 
     * @param e un element a retirer.
     */
    void retire(const T & e) {
        _liste = _liste->retire(e);
    }


    /**
     * Ajoute tous les elements dans un autre ensemble.
     * 
     * @param e un ensemble
     */
    void ajouteDans(Ensemble<T> & e) const {
        Noeud * courant = _liste;

        while (courant != 0) {
            e.ajoute(courant->getValeur());

            courant = courant->getSuivant();
        }
    }

    /**
     * Retire tous les elements dans un autre ensemble.
     * Apres a.enleveDe(b), b vaut b - a (- ensembliste)
     *
     * @param e un ensemble dont il faut retirer des elements.
     */
    void retireDe(Ensemble<T> & e) const {
        Noeud * courant = _liste;

        while (courant != 0) {
            e.retire(courant->getValeur());
            courant = courant->getSuivant();
        }
    }

    /**
     * Constructeur par recopie.
     * 
     * @param e un ensemble
     */
    Ensemble(const Ensemble<T> & e) {
        if (!e.estVide()) {
            this->_liste = new Noeud(*(e._liste));
        } else {
            this->_liste = 0;
        }
    }

    /**
     * Operateur d'affectation d'un ensemble.
     * 
     * @param e un ensemble
     * 
     * @return une reference a moi-meme
     */
    Ensemble<T> & operator=(const Ensemble<T> & e) {
        if (&e != this) {
            delete this->_liste;

            // nous nous voyons ici dans l'obligation de recopier
            // le contenu du constructeur de recopie, ne pouvant
            // l'appeler directement.
            this->_liste = new Noeud(*(e._liste));
        }

    }


    /**
     * Creation d'un singleton.
     * 
     * @param x un element
     * 
     * @return le singleton {x}
     */
    static Ensemble<T> singleton(T x) {
        return Ensemble<T>(x);
    }

    /**
     * Creation d'un ensemble vide.
     * 
     * @param x un double
     * 
     * @return le singleton {x}
     */
    static Ensemble<T> ensembleVide() {
        return Ensemble<T>();
    }

    /**
     * Retourne un iterateur.
     *
     * @return un ipointeur sur un iterateur.
     */
    Iterateur * getIterateur() const {
        return new Iterateur(*this);
    }


    /**
     * Application d'une fonction a tous les elements d'un ensemble
     *
     * @param fct	le foncteur
     * @return		copie le nouvel ensemble contenant les resultat en valeur de retour
     */
    Ensemble<T> appliquerAuxElements(Foncteur<T> & fct) const {
        Ensemble<T> dest;
        Iterateur * it = this->getIterateur();

        while (it->hasNext()) {
            dest.ajoute(fct(it->next()));
        }

        delete it;

        return dest;
    }

private:

    /* Noeud * retireRec(Noeud * liste, T x);
     * 
     * NOTE :
     * Cette fonction n'utilisant, ni variable d'instance, ni methode de cette
     * classe, nous avon juge bon de deplacer cette fonction utilitaire dans la
     * classe Noeud ou elle devient une methode d'instance a part entiere.
     */


};


/**
 * Operateur << pour les ensembles.
 * 
 * @param out un flot de sortie.
 * @param e un ensemble.
 * 
 * @return le flot de sortie donne en argument.
 */
template <typename T>
std::ostream & operator<<(std::ostream & out, const Ensemble<T> & e) {
    return e.flush(out);
}


/*
 * Creation d'un singleton.
 *
 * Note :
 * Cette fonction utilitaire nous semble plus a sa place
 * en tant que méthode statique la classe Ensemble
 *
 * @param x un element
 *
 * @return le singleton {x}
 */
//template<typename T> Ensemble<T> singleton(T x);

/**
 * Creation d'un ensemble vide.
 * 
 * Note :
 * Cette fonction utilitaire nous semble plus a sa place
 * en tant que méthode statique la classe Ensemble
 *
 * @param x un double
 * 
 * @return le singleton {x}
 */ 
//template<typename T> Ensemble<T> ensembleVide();

/**
 * Teste l'egalite de deux ensembles. Cette fonction (et les suivantes )
 * serait aussi bien implemente en tant que methode membre, mais elle
 * restera ici dans un but simplement didactique (syntaxe de la surcharge
 * d'operateur hors classe et non acces a la partie privee afin d'utiliser 
 * les methodes publiques precedemment cites). On a egalite quand E1
 * inclus dans E2 et E2 inclus dans E1
 * 
 * @param a un ensemble.
 * @param b un ensemble.
 * 
 * @return true si a=b (i.e., a est inclus dans b et b est inclus dans a),
 *         sinon false.
 */
template <typename T>
bool egale(const Ensemble<T> & a, const Ensemble<T> & b) {
    return a.estInclusDans(b) && b.estInclusDans(a);
}

template <typename T>
bool operator==(const Ensemble<T> & a, const Ensemble<T> & b) {
    return egale(a, b);
}


/* ne voyons pas le sens de ces operateurs, dans le cas d'ensemble */

//template <typename T>
//bool operator<(const Ensemble<T> & a, const Ensemble<T> & b) {}
 
//template <typename T>
//bool operator>(const Ensemble<T> & a, const Ensemble<T> & b) {}


/**
 * Union de deux ensembles de doubles.
 * 
 * @param a un ensemble de doubles.
 * @param b un ensemble de doubles.
 * 
 * @return a new Ensemble c = a union b.
 */
template <typename T>
Ensemble<T> reunion(const Ensemble<T> & a, const Ensemble<T> & b) {
    Ensemble<T> c(a);
    b.ajouteDans(c);
    return c;
}

template <typename T>
Ensemble<T> operator+(const Ensemble<T> & a, const Ensemble<T> & b) {
    return reunion(a, b);
}

template <typename T>
Ensemble<T> operator|(const Ensemble<T> & a, const Ensemble<T> & b) {
    return reunion(a, b);
}


/**
 * Difference de deux ensembles.
 * 
 * @param a un ensemble de doubles.
 * @param b un ensemble de doubles.
 * 
 * @return a new Ensemble a prive de b.
 */
template <typename T>
Ensemble<T> difference(const Ensemble<T> & a, const Ensemble<T> & b) {
    Ensemble<T> c(a);
    b.retireDe(c);
    return c;
}

template <typename T>
Ensemble<T> operator-(const Ensemble<T> & a, const Ensemble<T> & b) {
    return difference(a, b);
}


/**
 * Difference symetrique entre deux ensembles.
 * 
 * @param a un ensemble.
 * @param b un ensemble.
 * 
 * @return (a prive de b) union (b prive de a)
 */
template <typename T>
Ensemble<T> diffSymetrique(const Ensemble<T> & a, const Ensemble<T> & b) {
    return (a - b) + (b - a);
}

template <typename T>
Ensemble<T> operator^(const Ensemble<T> & a, const Ensemble<T> & b) {
    return diffSymetrique(a, b);
}


/**
 * Intersection entre deux ensembles de doubles.
 * 
 * @param a un ensemble de doubles.
 * @param b un ensemble de doubles.
 * 
 * @return l'intersection de a et b.
 */
template <typename T>
Ensemble<T> intersection(const Ensemble<T> & a, const Ensemble<T> & b) {
    return (a + b) - (a ^ b);
}

template <typename T>
Ensemble<T> operator&(const Ensemble<T> & a, const Ensemble<T> & b) {
    return intersection(a, b);
}


#endif /* ENSEMBLE_H */

