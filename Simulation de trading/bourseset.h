#ifndef BOURSESET_H_INCLUDED
#define BOURSESET_H_INCLUDED
#include <set>
#include <algorithm>
#include <iostream>
#include <vector>
class BourseSet:public Bourse
{
private:
    set<PrixJournalier> historique;
public:
    BourseSet(vector<PrixJournalier>& h)
    {
        for(unsigned int i=0;i<h.size();i++)
        {
            historique.insert(h.at(i));
        }
    };
    ~BourseSet(){};
    vector<string> getActionsDisponiblesParDate(date d) const
    {


        vector<string> actions;
        auto it = historique.lower_bound(PrixJournalier(d,"", 0));
        while(!(it==historique.end())&& (it->getdate()==d))
        {
            actions.push_back(it->getaction());
            it++;
        }
        return actions;
    }
    vector<PrixJournalier> PrixJournaliersParDate(date d) const
    {

        vector<PrixJournalier> pjd;
        auto it = historique.lower_bound(PrixJournalier(d,"", 0));
        while(!(it==historique.end())&& (it->getdate()==d))
        {
            pjd.push_back(*it);
            it++;
        }
        return pjd;
    }
    double dernierprix(string action)const
    {
        double x;
        for (auto it = historique.begin(); it != historique.end(); ++it)
        {
            if((it->getaction()==action)&&(it->getdate()<=aujourdhui))
                x=it->getprix();
            if((aujourdhui <= it->getdate())&& !(aujourdhui == it->getdate()))
                break;
        }
        return x;
    }


};



#endif // BOURSESET_H_INCLUDED
