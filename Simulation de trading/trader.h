#ifndef TRADER_H_INCLUDED
#define TRADER_H_INCLUDED
#include"boursevecteur.h"
#include"portefeuille.h"
#include"prixjournalier.h"
#include "triplet.h"
#include<vector>
#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;
class Trader {
    public :
        virtual Transaction prendreDecision( const Bourse& bourse, const Portefeuille& portefeuille)=0;
        Trader(){};
};

class TraderAleatoire : public Trader {
    public :
        TraderAleatoire(){};
        Transaction prendreDecision(const Bourse& bourse, const Portefeuille& portefeuille)
        {
            int choix=rand()%3;
            int x;
            int r;
            date date=bourse.getdateaujourdhui();
            if(choix==0)
            {
                 cout<<"ACHAT:"<<endl;
                 int taille=bourse.PrixJournaliersParDate(date).size();
                 if(taille>0)
                 {
                     int r=rand()%taille;
                     int a=floor(portefeuille.getSolde()/bourse.PrixJournaliersParDate(date).at(r).getprix());
                     if(a>=1)
                     {
                         int x=rand()%a+1;
                         Transaction t(ACHAT,x,bourse.getActionsDisponiblesParDate(date).at(r));
                         return t;
                     }
                     else
                     {
                         Transaction t(ACHAT,0,"N/A");
                         return t;
                     }
                 }
                else
                {
                    Transaction t(ACHAT,0,"N/A");
                    cout<<"  bourse fermee ---->";
                    return t;
                }

            }
            if(choix==1)
            {
                cout<<"VENTE:"<<endl;
                if(portefeuille.Titres.size()==0)
                {
                    x=0;
                    Transaction t(VENTE,x,"N/A");
                    cout<<"  le portefeuille est vide ---->";
                    return t;
                }
                else
                {
                    int taille=portefeuille.Titres.size();
                    r=rand()%taille;
                    int qte=portefeuille.Titres.at(r).getQuantite();
                    x=rand()%qte+1;
                    Transaction t(VENTE,x,portefeuille.Titres.at(r).getAction());
                    return t;
                }

            }
            else
            {

                Transaction t(RIEN,0,"N/A");
                return t;
            }
        }
} ;

class TraderSemiAleatoire:public Trader{
    Transaction prendreDecision(const Bourse& bourse, const Portefeuille& portefeuille)
    {
        int choix;
        choix=rand()%3;
        date date=bourse.getdateaujourdhui();
        if(choix==0)
        {
            if(bourse.PrixJournaliersParDate(date).size()>0)
            {
            PrixJournalier pj=bourse.PrixJournaliersParDate(date).at(0);
            for(unsigned int i=0;i<bourse.PrixJournaliersParDate(date).size();i++)
            {
                if(bourse.PrixJournaliersParDate(date).at(i).getprix()<pj.getprix())
                    pj=bourse.PrixJournaliersParDate(date).at(i);
            }
            if(portefeuille.getSolde()<pj.getprix())
            {
                Transaction t(ACHAT,0,"N/A");
                return t;
            }
            else
            {
                Transaction t(ACHAT,1,pj.getaction());
                return t;
            }
            }
            else
            {
                Transaction t(ACHAT,0,"N/A");
                return t;
            }
        }
        else if(choix==1)
        {
            cout<<"VENTE"<<endl;
            if(portefeuille.Titres.size()!=0)
            {
            Titre tre=portefeuille.Titres.at(0);
            for(unsigned int i=0;i<portefeuille.Titres.size();i++)
            {
                //cout<<"le dernier prix est"<<bourse.dernierprix(tre.getAction())<<endl;
                if(bourse.dernierprix(portefeuille.Titres.at(i).getAction())<bourse.dernierprix(tre.getAction()))
                    tre=portefeuille.Titres.at(i);
            }
            Transaction t(VENTE,tre.getQuantite(),tre.getAction());
            return t;
            }
            else
            {
                Transaction t(VENTE,0,"N/A");
                return t;
            }
        }
        else
        {
            Transaction t(RIEN,0,"N/A");
            return t;
        }
    }
};

class TraderHumain : public Trader{
public:
    TraderHumain(){};
    Transaction prendreDecision(const Bourse& bourse, const Portefeuille& portefeuille)
    {
        int choix;
        int x;
        string action;
        date date=bourse.getdateaujourdhui();
        do
        {
          cout<<"quelle action vous voulez effectuer"<<endl;
          cout<<"Tapez(0) si Vous voulez Acheter"<<endl;
          cout<<"Tapez(1) si vous voulez vendre"<<endl;
          cout<<"Tapez(2) si vous ne voulez rien faire"<<endl;
          cout<<"Tapez(3) si vous voulez voir les actions disponibles aujourd'hui"<<endl;
           cin>>choix;
           if(choix>=3)
           {
               if(bourse.getActionsDisponiblesParDate(date).size()==0)
               cout<<" pas d'actions disponibles aujourdhui "<<endl;
               else
               {
                   cout<<" voici les actions disponibles aujourdhui :  "<<endl;
                   cout<<"| ";
                   for(unsigned int i=0;i<bourse.PrixJournaliersParDate(date).size()-1;i++)
                   {
                       cout<<"| "<<bourse.PrixJournaliersParDate(date).at(i).getaction()<<" prix: "<<bourse.PrixJournaliersParDate(date).at(i).getprix()<<endl;
                   }
                cout<<bourse.PrixJournaliersParDate(date).at(bourse.PrixJournaliersParDate(date).size()-1).getaction()<<" prix: "<<bourse.PrixJournaliersParDate(date).at(bourse.PrixJournaliersParDate(date).size()-1).getprix()<<" |"<<endl;
               }

           }
        }while((choix<0)||(choix>2));

        if(choix==0)
        {
            cout<<" vous avez "<<portefeuille.getSolde()<<" comme budget dans le portefeuille "<<endl;
            cout<<" tapez le nom de l'action que vous voulez acheter "<<endl;
            cin>>action;
            int r=PrixJournalier(date,action,0).existe(bourse.PrixJournaliersParDate(date));
            if(r>=0)
            {
                cout<<"le prix de cette action"<<bourse.PrixJournaliersParDate(date).at(r).getprix()<<endl;
                cout<<"Tapez la quantité que vous voulez achetez "<<endl;
                do
                {
                    cin>>x;
                    if(bourse.PrixJournaliersParDate(date).at(r).getprix()*x>portefeuille.getSolde())
                        cout<<"quantite invalide, entrer une quantite valide : "<<endl;
                }while(bourse.PrixJournaliersParDate(date).at(r).getprix()*x>portefeuille.getSolde());
                Transaction t(ACHAT,x,action);
                return t;
            }
            else
            {
                cout<<"cette action n'est pas disponible aujourdhui"<<endl;
                Transaction t(ACHAT,0,"N/A");
                return t;
            }
        }
        else if(choix==1)
        {
            if(portefeuille.Titres.size()==0)
            {
              cout<<" le portefeuille est vide vous ne pouvez rien vendre  "<<endl;
              Transaction t(VENTE,0,"N/A");
              return t ;
            }
            else
            {
                cout<<"________________"<<endl;
                cout<<"|"<<"action"<<"|"<<"quantite"<<"|"<<endl;
                cout<<"________________"<<endl;
                for(unsigned int i=0;i<portefeuille.Titres.size();i++)
                {
                    cout<<"|"<<portefeuille.Titres.at(i).getAction()<<"|"<<portefeuille.Titres.at(i).getQuantite()<<"|"<<endl;
                    cout<<"________________"<<endl;
                }
                do
                {
                    cout<<" tapez le nom de l'action que vous voulez choisir "<<endl;
                    cin>>action;
                }while(portefeuille.existe(action)==-1);
                do
                {
                    cout<<" tapez la quantite que vous voulez vendre de l'action "<<action<<endl;
                    cin>>x;
                }while(x>portefeuille.Titres.at(portefeuille.existe(action)).getQuantite());
                Transaction t(VENTE,x,action);
                return t;
            }
        }
        else
        {
            Transaction t(RIEN,0,"N/A");
            return t;
        }

    }
};

class TraderIntelligent : public Trader {
public:
    TraderIntelligent() {};

    Transaction prendreDecision(const Bourse& bourse, const Portefeuille& portefeuille) {
        int choix = rand() % 6;
        int x;
        int r;
        date date = bourse.getdateaujourdhui();

        if(choix==4)
        {
            Transaction t(RIEN, 0, "N/A");
            return t;
        }
        else if (choix < 4) {
            cout << "ACHAT:" << endl;
            int taille = bourse.PrixJournaliersParDate(date).size();

            if (taille > 0) {
                int r = rand() % taille;
                int a = floor(portefeuille.getSolde() / bourse.PrixJournaliersParDate(date).at(r).getprix());

                if (a >= 1) {
                    int x = rand() % a + 1;
                    Transaction t(ACHAT, x, bourse.getActionsDisponiblesParDate(date).at(r));
                    return t;
                } else {
                    Transaction t(ACHAT, 0, "N/A");
                    return t;
                }
            } else {
                Transaction t(ACHAT, 0, "N/A");
                cout << "  bourse fermee ---->";
                return t;
            }
        } else {
            cout << "VENTE:" << endl;

            if (portefeuille.Titres.size() == 0) {
                x = 0;
                Transaction t(VENTE, x, "N/A");
                cout << "  le portefeuille est vide ---->";
                return t;
            } else {
                int taille = portefeuille.Titres.size();
                r = rand() % taille;
                int qte = portefeuille.Titres.at(r).getQuantite();
                x = rand() % qte + 1;
                Transaction t(VENTE, x, portefeuille.Titres.at(r).getAction());
                return t;
            }
        }
    }
};






#endif // TRADER_H_INCLUDED
