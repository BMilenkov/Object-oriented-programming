#include<iostream>
#include<string.h>
using namespace std;

class Delo{
private:
    char name[50];
    int year;
    char country[50];
public:
    Delo(char *name="", int year = 1900, char *country=""){
        strcpy(this->name,name);
        this->year = year;
        strcpy(this->country,country);
    }
    bool operator==(Delo &D){
        return !strcmp(name,D.name);
    }
    int getYear(){
        return year;
    }
    char *getCountry(){
        return country;
    }
    char *getIme(){
        return name;
    }
    Delo &operator ++(){
        year++;
        return *this;
    }
    Delo operator++(int n){
        Delo d= *this;
        year++;
        return d;
    }
};

class Pretstava {
protected:
    Delo d;
    int tickets;
    char date[15];
public:
    Pretstava(){}
    Pretstava(Delo d, int tickets, char *date){
        this->d = d;
        this->tickets = tickets;
        strcpy(this->date,date);
    }
    virtual double cena(){
        int m,n;
       if(d.getYear() / 100==20 || d.getYear()/100 == 19) {
           m = 50;
       }
       else if(d.getYear()/100 == 18){
           m = 75;
       }
       else{
           m=100;
       }
       if(!strcmp(d.getCountry(),"Italija"))
           n=100;
       else if(!strcmp(d.getCountry(),"Rusija"))
           n=150;
       else n=80;
        return n+m;
    }
    Delo getDelo(){
        return d;
    }
    int getTickets(){
        return tickets;
    }
};

class Balet: public Pretstava{
private:
    static double AddPrice;
public:
    Balet(Delo d, int tickets, char *date): Pretstava(d,tickets,date){}
    double cena(){
        return Pretstava::cena() + AddPrice;
    }
    static void setCenaBalet(double cena){
        AddPrice = cena;
    }
};
double Balet::AddPrice = 150;

class Opera: public Pretstava{
public:
    Opera(Delo d, int tickets, char *date): Pretstava(d,tickets,date){}
    double cena(){
        return Pretstava::cena();
    }
};


double prihod(Pretstava **pretstavi, int n){
    double max=0.0;
    for(int i = 0; i < n; i++){
        max+=pretstavi[i]->cena()*pretstavi[i]->getTickets();
    }
    return max;
}
int brojPretstaviNaDelo(Pretstava **pretstavi ,int n, Delo &D){
    int counter=0;
    for(int i = 0; i < n; i++){
        if(pretstavi[i]->getDelo()==D){
            counter++;
        }
    }
    return counter;
}
//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}
