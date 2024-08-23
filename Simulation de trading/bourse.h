#ifndef BOURSE_H_INCLUDED
#define BOURSE_H_INCLUDED
#include "date.h"


class Bourse {
    protected:
    date aujourdhui;
    public:
    Bourse(){};
    Bourse(date ajd):aujourdhui(ajd){};
    virtual ~Bourse(){};
    void setdateaujourdhui(date d){aujourdhui=d;};
    void incrementerdateaujourdhui(){aujourdhui++;};
    virtual vector<string> getActionsDisponiblesParDate(date d)const=0;
    virtual vector<PrixJournalier> PrixJournaliersParDate(date d)const=0;
    date getdateaujourdhui() const{return aujourdhui;}
    virtual double dernierprix(string action)const=0;
};


#endif // BOURSE_H_INCLUDED
