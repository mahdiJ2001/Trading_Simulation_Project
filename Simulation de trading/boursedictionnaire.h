#ifndef BOURSEDICTIONNAIRE_H_INCLUDED
#define BOURSEDICTIONNAIRE_H_INCLUDED
#include "prixjournalier.h"
#include <map>
#include <vector>
#include <string>
#include "prixjournalier.h"
#include "date.h"


class BourseDictionnaire:public Bourse
{
  private:
      map<date,vector<PrixJournalier>> historique;
  public:
      BourseDictionnaire(vector<PrixJournalier>& h)
      {      /*
          date D(1,1,2010);
          PrixJournalier pj(D,"",0);
          date d;
          d=h.at(0).getdate();
          vector<PrixJournalier> pjs;
          historique[date(9,1,2010)].push_back(pj);

          for(date d=h.at(0).getdate();d<=h.at(h.size()-1).getdate();d++)
          {
              historique[d].push_back(pj);
          } */
          for(unsigned int i=0;i<h.size()-1;i++)
          {
              historique[h.at(i).getdate()].push_back(h.at(i));
              date d=h.at(i).getdate();
              d++;

                  while(d<h.at(i+1).getdate())
                  {
                      historique[d]=vector<PrixJournalier> {};
                      d++;
                  }
          }
      }
      ~BourseDictionnaire(){};
      vector<string> getActionsDisponiblesParDate(date d)const
      {
          vector<string> actions;
          for(unsigned int i=0;i<historique.at(d).size();i++)
          {
              actions.push_back(historique.at(d).at(i).getaction());
          }
          return actions;
          }
      vector<PrixJournalier> PrixJournaliersParDate(date d)const
      {
          vector<PrixJournalier> pjs;
          for(unsigned int i=0;i<historique.at(d).size();i++)
          {
              pjs.push_back(historique.at(d).at(i));
          }
          return pjs;
      }

      double dernierprix(string action)const
      {
          double x;
          int r;
          auto it=historique.begin();
          date d=it->first;
          while(d<=aujourdhui)
          {
              r=PrixJournalier(d,action,0).existe(historique.at(d));
              if(r>=0)
              {
                x=this->PrixJournaliersParDate(d).at(r).getprix();
              }
              d++;
          }
          /*for(auto it=historique.rend(); it!=historique.rbegin();it++)
          {
              for(unsigned int i=it->second.size()-1;i>=0;i--)
              {
                  if((it->second.at(i).getaction()==action)&&(it->second.at(i).getdate()<=aujourdhui))
                  {
                      cout<<"le dernier prix de "<<it->second.at(i).getaction()<<" est "<<it->second.at(i).getprix()<<endl;
                      return it->second.at(i).getprix();
                  }

              }*/

          return x;
          }
};

#endif // BOURSEDICTIONNAIRE_H_INCLUDED
