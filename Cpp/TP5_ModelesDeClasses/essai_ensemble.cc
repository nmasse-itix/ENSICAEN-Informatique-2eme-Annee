/**
 * @file   essai_ensemble.cc
 * @author Sebastien Fourey
 * @date   Thu Nov 18 20:38:47 2004
 * 
 * @brief  Programme de test du modele de classe "Ensemble"
 *         defini dans Ensemble.hh
 */

/*
 * Ici, toute la definition du modele de classe "Ensemble"
 * est dans un unique fichier .hh
 * On ne fait plus de compilation separee.
 *
 */

#include <ios>
#include <iostream>
#include <iomanip>

#include "Ensemble.hh"

using namespace std;

/**
 * Fonction principale du programme.
 * 
 * @param argc le nombre d'arguments sur la ligne de commande.
 * @param argv le tableau des arguments de la ligne de commande.
 * 
 * @return 0 (SUCCESS)
 */
int main(int argc, char * argv[]) {

    typedef Ensemble<double> EnsembleDouble;
    EnsembleDouble e;
    Ensemble<double> f;
    Ensemble<double> g;

    for (int i = 1; i <= 10 ; i++)
        e.ajoute(i);

    for (int i = 6; i <= 15 ; i++)
        f.ajoute(i);

    for (int i = 11; i < 20 ; i++)
        g.ajoute(i);

    cout << setiosflags(ios_base::boolalpha); // <iomanip>

    // Alternative :  cout.setf(ios_base::boolalpha); // <ios>

    cout << e.contient(5) << endl;

    cout << f.contient(5) << endl;

    cout << g.contient(5) << endl;

    cout << "e = " << e << endl;

    cout << "f = " << f << endl;

    cout << "g = " << g << endl;

    /*
      e.retire(0);
      cout << "e - 0 = " << e << endl;
      e.retire(3);
      cout << "e - 3 = " << e << endl;
      e.retire(1);
      cout << "e - 1 = " << e << endl;
      e.retire(10);
      cout << "e - 10 = " << e << endl;
      e.retire(6);
      cout << "e - 6 = " << e << endl;
    */

    cout << " e U f = " << (e + f) << endl;

    cout << " e inter f = " << (e & f) << endl;

    cout << " e - f = " << (e - f) << endl;

    cout << " e inter g = " << (e & g) << endl;

    cout << " e diffSym f = " << (e ^ f) << endl;

    cout << " e diffSym g = " << (e ^ g) << endl;

    cout << " e - e = " << (e - e) << endl;

    cout << " e - {40.0} = " << (e - Ensemble<double>::singleton(40.0)) << endl;

    cout << " e U {40} U {50} = " << e + Ensemble<double>::singleton(40.0) + Ensemble<double>::singleton(50.0) << endl;

    cout << endl;

    cout << " e = " << e << endl;

    cout << " f = " << f << endl;

    cout << " (e U f) - f " << (e + f) - f << endl;

    cout << " (e U f) - f == e ?   " << (((e + f) - f) == e) << endl;

    cout << " En effet, car e inter f = " << (e & f) << endl;

    cout << endl;

    cout << " e == e U {} ? " << ((e + Ensemble<double>()) == e) << endl;

    Foncteur<double> fct(3);

    cout << "e.appliquerAuxElements(Foncteur fct(3)) = " << e.appliquerAuxElements(fct) << endl;


    //  cout << " e - {5} < e ? " << ((e - Ensemble<double>(5.0)) < e) << endl;

    Ensemble<bool> a, b;

    a.ajoute(true);

    b.ajoute(false);

    cout << endl;

    cout << " a = " << a << endl;

    cout << " b = " << b << endl;

    cout << " a + b = " << (a + b) << endl;

    cout << " a + b - {true} = " << ((a + b) - Ensemble<bool>::singleton(true)) << endl;

    return 0;
}

