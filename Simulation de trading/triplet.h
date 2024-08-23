#ifndef TRIPLET_H_INCLUDED
#define TRIPLET_H_INCLUDED
#include <string>
enum TypeTransaction{ACHAT,VENTE,RIEN};
class Transaction
{
    TypeTransaction choix;
    int quantite;
    string action;
public:
    Transaction(){};
    Transaction(TypeTransaction c,int x,string action):choix(c),quantite(x),action(action){};
    ~Transaction(){};
    TypeTransaction getchoix(){return choix;};
    int getquantite(){return quantite;};
    string getaction(){return action;};
};


#endif // TRIPLET_H_INCLUDED
