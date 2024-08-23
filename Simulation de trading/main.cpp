#include <iostream>
#include <random>
#include <fstream>
#include "PrixJournalier.h"
#include "boursevecteur.h"
#include "PersistancePrixJournaliers.h"
#include "simulation.h"
#include "boursedictionnaire.h"
#include "set.h"
#include "bourseset.h"
using namespace std;

int main()
{
 PersistancePrixJournaliers extract ;
    vector<PrixJournalier> historique ;
    historique=extract.lirePrixJournaliersDUnFichier("prices_simple.csv");
    date d1,d2;
    string typetrader;
    srand(time(NULL));
    cout<<"          ##########SIMULATION DE TRADING##########"<<endl;
    cout<<endl;
    cout<<"Les Dates doivent etre entre 04/01/2010 et 30/12/2016"<<endl;
    cout<<endl;
    do{
    cout<<"donner la date de debut au format : jj/mm/aaaa;  ";
    cin>>d1;
    }while(!d1.datevalide());
    do{
    cout<<"donner la date de fin au format : jj/mm/aaaa;  ";
    cin>>d2;
    }while(!d2.datevalide());

    double budget;
    do{
    cout<<"donner le budget"<<endl;
    cin>>budget;
    }while(!(budget>=0));

    int choixTrader;
    int choixBourse;
    cout<<"Quel Type de Trader vous voulez choisir"<<endl;
    cout<<"1-Trader Aleatoire"<<endl;
    cout<<"2-Trader SemiAleatoire"<<endl;
    cout<<"3-Trader Humain"<<endl;
    cout<<"4-Trader Intelligent"<<endl;
    do
    {
        cin>>choixTrader;
    }while ((choixTrader<1) || (choixTrader>4));
    if(choixTrader==1)
        {typetrader="Trader Aleatoire";}
    else if(choixTrader==2)
        {typetrader="Trader SemiAleatoire";}
    else if(choixTrader==3)
        {typetrader="Trader Humain";}
    else
        {typetrader="Trader Intelligent";}

    cout<<"Quel Type de Bourse vous voulez choisir"<<endl;
    cout<<"1-Bourse Vecteur"<<endl;
    cout<<"2-Bourse Set"<<endl;
    cout<<"3-Bourse map"<<endl;
    do
    {
        cin>>choixBourse;
    }while ((choixBourse<1) || (choixBourse>3));

    ofstream fichier("BDSimulation.txt",std::ios::app);
    if (fichier.is_open()) {
        fichier<<"****"<<endl;
        fichier <<"Type du Trader : "<<typetrader<<endl;
        fichier.close();
    } else {
        cout << "Erreur lors de l'ouverture du fichier." <<endl;
    }

    if((choixTrader==1)&&(choixBourse==1))
    {
        TraderAleatoire* Tr=new TraderAleatoire();
        BourseVecteur b(historique);
        Simulation S(d1,d2,d1,budget);
        auto stats=S.executer(b,*Tr,d1,d2,budget);
        for(auto it:stats)
        {
        cout<<it.first<<" : "<<it.second<<endl;
        }

    }
    if((choixTrader==1)&&(choixBourse==2))
    {
        TraderAleatoire* Tr=new TraderAleatoire();
        BourseSet b(historique);
        Simulation S(d1,d2,d1,budget);
        auto stats=S.executer(b,*Tr,d1,d2,budget);
        for(auto it:stats)
        {
        cout<<it.first<<" : "<<it.second<<endl;
        }
    }
    if((choixTrader==1)&&(choixBourse==3))
    {
        TraderAleatoire* Tr=new TraderAleatoire();
        BourseDictionnaire b(historique);
        Simulation S(d1,d2,d1,budget);
        auto stats=S.executer(b,*Tr,d1,d2,budget);
        for(auto it:stats)
        {
        cout<<it.first<<" : "<<it.second<<endl;
        }
    }
    if((choixTrader==2)&&(choixBourse==1))
    {
        TraderSemiAleatoire* Tr=new TraderSemiAleatoire();
        BourseVecteur b(historique);
        Simulation S(d1,d2,d1,budget);
        auto stats=S.executer(b,*Tr,d1,d2,budget);
        for(auto it:stats)
        {
        cout<<it.first<<" : "<<it.second<<endl;
        }
    }
    if((choixTrader==2)&&(choixBourse==2))
    {
        TraderSemiAleatoire* Tr=new TraderSemiAleatoire();
        BourseSet b(historique);
        Simulation S(d1,d2,d1,budget);
        auto stats=S.executer(b,*Tr,d1,d2,budget);
        for(auto it:stats)
        {
        cout<<it.first<<" : "<<it.second<<endl;
        }
    }
    if((choixTrader==2)&&(choixBourse==3))
    {
        TraderSemiAleatoire* Tr=new TraderSemiAleatoire();
        BourseDictionnaire b(historique);
        Simulation S(d1,d2,d1,budget);
        auto stats=S.executer(b,*Tr,d1,d2,budget);
        for(auto it:stats)
        {
        cout<<it.first<<" : "<<it.second<<endl;
        }
    }
    if((choixTrader==3)&&(choixBourse==1))
    {
        TraderHumain* Tr=new TraderHumain();
        BourseVecteur b(historique);
        Simulation S(d1,d2,d1,budget);
        auto stats=S.executer(b,*Tr,d1,d2,budget);
        for(auto it:stats)
        {
        cout<<it.first<<" : "<<it.second<<endl;
        }
    }
    if((choixTrader==3)&&(choixBourse==2))
    {
        TraderHumain* Tr=new TraderHumain();
        BourseSet b(historique);
        Simulation S(d1,d2,d1,budget);
        auto stats=S.executer(b,*Tr,d1,d2,budget);
        for(auto it:stats)
        {
        cout<<it.first<<" : "<<it.second<<endl;
        }
    }
    if((choixTrader==3)&&(choixBourse==3))
    {
        TraderHumain* Tr=new TraderHumain();
        BourseDictionnaire b(historique);
        Simulation S(d1,d2,d1,budget);
        auto stats=S.executer(b,*Tr,d1,d2,budget);
        for(auto it:stats)
        {
        cout<<it.first<<" : "<<it.second<<endl;
        }
    }
    if((choixTrader==4)&&(choixBourse==1))
    {
        TraderIntelligent* Tr=new TraderIntelligent();
        BourseVecteur b(historique);
        Simulation S(d1,d2,d1,budget);
        auto stats=S.executer(b,*Tr,d1,d2,budget);
        for(auto it:stats)
        {
        cout<<it.first<<" : "<<it.second<<endl;
        }
    }
    if((choixTrader==4)&&(choixBourse==2))
    {
        TraderIntelligent* Tr=new TraderIntelligent();
        BourseSet b(historique);
        Simulation S(d1,d2,d1,budget);
        auto stats=S.executer(b,*Tr,d1,d2,budget);
        for(auto it:stats)
        {
        cout<<it.first<<" : "<<it.second<<endl;
        }
    }
    if((choixTrader==4)&&(choixBourse==3))
    {
        TraderIntelligent* Tr=new TraderIntelligent();
        BourseDictionnaire b(historique);
        Simulation S(d1,d2,d1,budget);
        auto stats=S.executer(b,*Tr,d1,d2,budget);
        for(auto it:stats)
        {
        cout<<it.first<<" : "<<it.second<<endl;
        }
    }
    int nbpj=0;
    for(int i=0;i<historique.size();i++){
        if((d2<=historique.at(i).getdate())&& !(historique.at(i).getdate()==d2))
            break;
        if(d1<=historique.at(i).getdate())
            nbpj++;

    }
    cout<<"nb pj    "<<nbpj<<endl;

    return 0;}
