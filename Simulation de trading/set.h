#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED
#include <set>
#include "prixjournalier.h"
using namespace std;

class SetPrixJournaliers{
public:
    static set<PrixJournalier> lirePrixJournaliersDUnFichier(string chemin)
    {
        set<PrixJournalier> historique;
        ifstream f(chemin);
        int nbLignes= 0;
        string entete;
        if(f.is_open())
        {
            f>>entete;
            while(!f.eof())
            {
                PrixJournalier pj;
                f>>pj;
                historique.insert(pj);
                nbLignes++;
            }
        }
        return historique;
    }





};


#endif // SET_H_INCLUDED
