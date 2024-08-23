#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED
#include "boursevecteur.h"
#include "bourse.h"
#include "trader.h"
#include "date.h"
#include "portefeuille.h"
#include "triplet.h"
#include <chrono>
#include <map>
#include <fstream>



class Simulation{
    date datedebut;
    date datefin;
    date datecourante;
    double budget;
public:
    Simulation(date d1,date d2,date d,double x):datedebut(d1),datefin(d2),datecourante(d),budget(x){};
    static map<string,long long> executer(Bourse& bourse,Trader& trader,date datedebut,date datefin,double budget)
    {
       map<string,long long> stats={
       {"NB_ACHAT",0},
       {"NB_VENTE",0},
       {"NB_TX",0},
       {"TEMPS_GET_ACTIONS_TOTAL_NANO_SEC",0},
       {"TEMPS_GET_ACTIONS_MOYEN_NANO_SEC",0},
       {"TEMPS_GET_PRIX_ACTION_TOTAL_NANO_SEC",0},
       {"TEMPS_GET_PRIX_ACTION_MOYEN_NANO_SEC",0},
       {"TEMPS_TRANSACTION_NANO_SEC",0},
       {"TEMPS_SIMULATION_NANO_SEC",0},
       };
       date d=datedebut;
       int nbtotaljourdispo=0;
       int totalgetprixaction=0;
       int nbgetactions=0;
       vector<string> actions;
       bourse.setdateaujourdhui(datedebut);
       auto start_simulation = chrono::high_resolution_clock::now();
       vector<Titre> Titres;
       Portefeuille portefeuille(budget,Titres);
       while(d<=datefin)
       {
           if(bourse.getActionsDisponiblesParDate(d).size()!=0)
       {
          auto start = chrono::high_resolution_clock::now();
          auto actionsAujourdhui = bourse.getActionsDisponiblesParDate(d);
          auto stop = chrono::high_resolution_clock::now();
          auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
          stats["TEMPS_GET_ACTIONS_TOTAL_NANO_SEC"]+=duration.count();
          nbtotaljourdispo++;
       }
           cout<<"*****le jour: ";
           cout<<d ;
           cout<<" *****"<<endl;
           for(int i=0;i<100;i++)
           {
               Transaction tx;
               auto start = chrono::high_resolution_clock::now();
               tx=trader.prendreDecision(bourse,portefeuille);
               auto stop = chrono::high_resolution_clock::now();
               auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
               stats["TEMPS_TRANSACTION_NANO_SEC"]+=duration.count();
               TypeTransaction choix=tx.getchoix();
               int x=tx.getquantite();
               string action=tx.getaction();
               double prix;
               if(choix==ACHAT)
               {
                   if(action!="N/A")
                   {
                       nbgetactions++;
                       date dd(4,1,2010);
                       PrixJournalier pj(dd,action,0);
                       auto startprixachat = chrono::high_resolution_clock::now();
                       int r=pj.existe(bourse.PrixJournaliersParDate(d));
                       if(r>=0)
                       prix=bourse.PrixJournaliersParDate(d).at(r).getprix();
                       auto stopprixachat = chrono::high_resolution_clock::now();
                       auto durationprixachat= chrono::duration_cast<chrono::microseconds>(stopprixachat - startprixachat);
                       stats["TEMPS_GET_PRIX_ACTION_TOTAL_NANO_SEC"]+=durationprixachat.count();
                       totalgetprixaction++;
                       portefeuille.retirermontant(bourse.PrixJournaliersParDate(d).at(r).getprix()*x);
                       if(portefeuille.existe(action)==-1)
                       {
                           Titre t(action,x);
                           portefeuille.ajoutertitre(t);
                       }
                       else
                       {
                           portefeuille.Titres.at(portefeuille.existe(action)).ajouterQuantite(x);
                       }
                       cout<<"   Le traideur a achete l'action   ";
                       cout<<bourse.getActionsDisponiblesParDate(d).at(r);
                       cout<<" d'une quantite ";
                       cout<<x;
                       cout<<"   Le montant retire est donc   ";
                       cout<<bourse.PrixJournaliersParDate(d).at(r).getprix()*x<<endl;
                       stats["NB_ACHAT"]++;
                   }
                   else
                   {
                       cout<<"  achat impossible"<<endl;
                   }
               }
               if(choix==VENTE)
               {
                   if(action!="N/A")
                   {
                       nbgetactions++;
                       int r=portefeuille.existe(action);
                       PrixJournalier px(d,action,0);
                       int p=px.existe(bourse.PrixJournaliersParDate(d));
                       date dd(4,1,2010);
                       PrixJournalier pj(dd,action,0);
                       if(bourse.PrixJournaliersParDate(d).size()!=0)
                       {
                       auto startprixvente = chrono::high_resolution_clock::now();
                       int ex=pj.existe(bourse.PrixJournaliersParDate(d));
                       if(ex>=0)
                       prix=bourse.PrixJournaliersParDate(d).at(ex).getprix();
                       auto stopprixvente = chrono::high_resolution_clock::now();
                       auto durationprixvente= chrono::duration_cast<chrono::microseconds>(stopprixvente - startprixvente);
                       stats["TEMPS_GET_PRIX_ACTION_TOTAL_NANO_SEC"]+=durationprixvente.count();
                       totalgetprixaction++;
                       if(ex>=0)
                       {
                       portefeuille.Titres.at(r).retirerQuantite(x);
                       portefeuille.deposermontant(bourse.PrixJournaliersParDate(d).at(p).getprix()*x);
                       cout<<"  Le Traideur a vendu l'action ";
                       cout<<portefeuille.Titres.at(r).getAction();
                       cout<<" d'une quantite ";
                       cout<<x;
                       cout<<" Le montant depose est  ";
                       cout<<(bourse.PrixJournaliersParDate(d).at(p).getprix())*x<<endl;
                       stats["NB_VENTE"]++;
                       if(portefeuille.Titres.at(r).getQuantite()==0)
                       portefeuille.retirertitre(r);
                       }
                       else
                       {
                           cout<<"l'action "<<action<<" n'est pas disponible dans ce jour la"<<endl;
                       }
                       }
                       else
                       {
                           cout<<"  pas d'actions disponibles aujourdhui"<<endl;
                       }
                   }
                   else
                        cout<<"  vente impossible"<<endl;
               }
               if(choix==RIEN)
               {
                   cout<<"RIEN:"<<endl;
                   cout<<"________________"<<endl;
                   cout<<"|"<<"action"<<"|"<<"quantite"<<"|"<<endl;
                   cout<<"________________"<<endl;
                   for(unsigned int i=0;i<portefeuille.Titres.size();i++)
                    {
                    cout<<"|"<<portefeuille.Titres.at(i).getAction()<<"|"<<portefeuille.Titres.at(i).getQuantite()<<"|"<<endl;
                    cout<<"________________"<<endl;
                    }

                   /* int qte1=0;
                    double x1=0;
                    double tot1=0;
                    for(unsigned int i=0;i<portefeuille.Titres.size();i++)
                    {
                    qte1=portefeuille.Titres.at(i).getQuantite();
                    x1=bourse.dernierprix(portefeuille.Titres.at(i).getAction());
                    tot1+=qte1*x1;
                    }
                    cout<<"valeur du portefeuille : "<<portefeuille.getSolde()+tot1<<endl;*/

                   break;
               }
           }
           cout<<"---LE BUDGET ACTUEL EST :  "<<portefeuille.getSolde()<<"---"<<endl;
           d++;
           bourse.setdateaujourdhui(d);
           }
        int qte;
        double x;
        double tot;
        for(unsigned int i=0;i<portefeuille.Titres.size();i++)
        {
            qte=portefeuille.Titres.at(i).getQuantite();
            x=bourse.dernierprix(portefeuille.Titres.at(i).getAction());
            tot+=qte*x;
        }
        cout<<endl;
        cout<<endl;
        cout<<"LES STATISTIQUES:"<<endl;
        double GAINP;
        if(budget!=0){
        GAINP=((portefeuille.getSolde()+tot-budget)/budget)*100;
        cout<<"GAIN %  "<<GAINP<<endl;
        cout<<"GAIN    "<<(portefeuille.getSolde()+tot-budget)<<endl;
        }
        stats["TEMPS_GET_ACTIONS_MOYEN_NANO_SEC"]=stats["TEMPS_GET_ACTIONS_TOTAL_NANO_SEC"]/nbgetactions;
        stats["TEMPS_GET_PRIX_ACTION_MOYEN_NANO_SEC"]=stats["TEMPS_GET_PRIX_ACTION_TOTAL_NANO_SEC"]/totalgetprixaction;
        auto stop_simulation = chrono::high_resolution_clock::now();
        auto duration_simulation = chrono::duration_cast<chrono::microseconds>(stop_simulation - start_simulation);
        stats["TEMPS_SIMULATION_NANO_SEC"]+=duration_simulation.count();
        cout<<"le budget final est "<<portefeuille.getSolde()+tot<<endl;
        cout<<"le budget initial est "<<budget<<endl;
        stats["NB_TX"]=stats["NB_VENTE"]+stats["NB_ACHAT"];
        cout<<"NB GET_ACTIONS  "<<nbgetactions<<endl;
        cout<<"NB GET_PRIX_ACTION_JOUR  "<<totalgetprixaction<<endl;

        ofstream fichier("BDSimulation.txt",std::ios::app);
        if (fichier.is_open()) {
        fichier<<"Date Debut: "<<datedebut<<endl;
        fichier<<"Date Fin: "<<datefin<<endl;
        fichier<<"GAIN %  "<<GAINP<<endl;
        fichier<<"GAIN    "<<portefeuille.getSolde()+tot-budget<<endl;
        fichier<<"le budget final est "<<portefeuille.getSolde()+tot<<endl;
        fichier<<"le budget initial est "<<budget<<endl;
        fichier<<"NB GET_ACTIONS  "<<nbgetactions<<endl;
        fichier<<"NB GET_PRIX_ACTION_JOUR  "<<totalgetprixaction<<endl;
        fichier<<endl;
        fichier<<endl;
        fichier.close();
        }   else {
        cout<<"Erreur lors de l'ouverture du fichier."<<endl;
        }
        return stats;



       }
    };



#endif // SIMULATION_H_INCLUDED
