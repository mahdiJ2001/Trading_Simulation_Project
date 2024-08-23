#ifndef PRIXJOURNALIER_H_INCLUDED
#define PRIXJOURNALIER_H_INCLUDED
#include<iostream>
#include<sstream>
#include "date.h"
#include<vector>


class PrixJournalier {
    private:
        date dateaction ;
        string action;
        double prix;
    public:
        PrixJournalier(){};
        ~PrixJournalier(){};
        PrixJournalier(date d,string na,double pj):dateaction(d),action(na),prix(pj){};
        date getdate() const {return dateaction;};
        string getaction() const {return action;};
        double getprix() const {return prix;};
        friend ostream& operator<<(ostream& flux , const PrixJournalier& pj);
        friend istream& operator>> (istream& flux, PrixJournalier& pj);
        friend bool operator <(const PrixJournalier pj1,const PrixJournalier pj2)
        {
            bool b=false;
            if(pj1.dateaction<pj2.dateaction)
                b=true;
            else if((pj1.dateaction==pj2.dateaction)&&(pj1.action<pj2.action))
                b=true;
            else if((pj1.dateaction==pj2.dateaction)&&(pj1.action==pj2.action)&&(pj1.prix<pj2.prix))
                b=true;
            return b;
        }
        int existe(vector<PrixJournalier> pjs)
        {
        int b=-1;
        for(unsigned int i=0;i<pjs.size();i++)
        {
            if(pjs.at(i).getaction()==action)
                b=i;
        }
        return b;
        }
};


ostream& operator<<(ostream& flux , const PrixJournalier& pj){

flux<<"date : "<<pj.dateaction;
flux<<"action : "<<pj.action<<endl;
flux<<"prix : "<<pj.prix<<endl;
return flux ;

}

istream& operator>> (istream& flux, PrixJournalier& pj){

flux>>pj.dateaction;
char nomaction[100];
flux.getline(nomaction,100,';');
pj.action=nomaction;
flux>>pj.prix;

return flux ;

}


#endif // PRIXJOURNALIER_H_INCLUDED
