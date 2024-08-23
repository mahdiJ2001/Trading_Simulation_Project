#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED
#include<iostream>
using namespace std ;

class date {
	private:
		int jour;
		int mois;
		int annee;
	public:
	    date(){};
		date(int jj,int mm,int aaaa){annee=aaaa;
	                                 mois=mm;
                                     jour=jj;};
        ~date(){};
		int getjour() const{return jour;};
		int getmois() const{return mois;};
		int getannee() const{return annee;};
		date& operator=(const date& other) {
        if (this != &other) {
            // Copie des valeurs de other dans this
            jour = other.jour;
            mois= other.mois;
            annee = other.annee;
        }
        return *this;
    }
		bool bisextile(int a)
		{
		     if (a%4==0)
             return true ;
             else
             return false ;
		};
		int nbjoursmois(int mm,int aa )
		{
		      switch(mm){
        case 1 :
        case 3 :
        case 5 :
        case 7 :
        case 8 :
        case 10:
        case 12:
            return 31;
            break ;
        case 2 :
            if(bisextile(aa))
                return 29;
            else
                return 28;
            break ;
        case 4 :
        case 6 :
        case 9 :
        case 11:
            return 30;
            break ;
        default:
            return 0;
    }

		};
		void incrementerdate()
		{
		   if(jour==nbjoursmois(mois,annee)){
            if(mois==12){
                jour=1;
                mois=1;
                annee++;
            }
            else{
                jour=1;
                mois++;
            }
	}
	else
        jour++;
		};
		friend void operator++(date &d1,int )
		{
		   d1.incrementerdate();
		};
		bool datevalide()
		{
		    bool b=false ;

            if((1<=jour)&&(jour<=nbjoursmois(mois,annee))&&(1<=mois)&&(mois<=12))
            b=true;
            return b ;
		};
		friend ostream& operator<<(ostream& flux , const date& d)
		{
		    flux<<d.jour<<"/"<<d.mois<<"/"<<d.annee ;
	        return flux ;
		};
		friend istream& operator>>(istream& flux,date&d)
		{
            int jj,mm,aa;
            char tab[12];

            flux.getline(tab,12,'/');
            jj=atoi(tab);
            flux.getline(tab,12,'/');
            mm=atoi(tab);
            flux.getline(tab,12,';');
            aa=atoi(tab);

            d.jour=jj;
            d.mois=mm;
            d.annee=aa;
            return flux;
		}; //instructions unclear
		friend bool operator==(const date d1,const date d2)
		{
		    bool b=false;
            if(d1.jour==d2.jour && d1.mois==d2.mois && d1.annee==d2.annee)
            b=true;
            return b ;
		};
		friend bool operator<=(const date d1,const date d2){

		bool b=false ;

        if( (d1.annee)<(d2.annee))
        b=true;
        else if( (d1.annee==d2.annee) && (d1.mois<d2.mois) )
        b=true;
        else if( (d1.annee==d2.annee) && (d1.mois==d2.mois) && (d1.jour<=d2.jour) )
        b=true;
        return b ;


		};
		friend bool operator<(const date d1,const date d2){

		bool b=false ;

        if( (d1.annee)<(d2.annee))
        b=true;
        else if( (d1.annee==d2.annee) && (d1.mois<d2.mois) )
        b=true;
        else if( (d1.annee==d2.annee) && (d1.mois==d2.mois) && (d1.jour<d2.jour) )
        b=true;
        return b ;


		};
		date datesuivante()
		{
		    date x=*this;
		    x++;
		    return x;
		}

};


#endif // DATE_H_INCLUDED
