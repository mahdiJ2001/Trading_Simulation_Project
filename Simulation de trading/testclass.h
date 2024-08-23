#ifndef TESTCLASS_H_INCLUDED
#define TESTCLASS_H_INCLUDED
#include "Date.h"
#include<iostream>


class Test {
    public :
    void verifierDate(date valeur,date valeurvraie);
    void verifierBool(bool valeur,bool valeurvraie);
};

void Test::verifierDate(date valeur,date valeurvraie){
    if (valeur==valeurvraie)
        cout<<"ok"<<endl;
    else
        cout<<"erreur"<<endl;
    }
void Test::verifierBool(bool valeur,bool valeurvraie){

    if (valeur==valeurvraie)
        cout<<"ok"<<endl;
    else
        cout<<"erreur"<<endl;
}



#endif // TESTCLASS_H_INCLUDED
