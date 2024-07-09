#include<iostream>
#include<string.h>
using namespace std;
class OutOfBoundException{
public:
    void showMessage(){
        cout<<"Brojot na pin kodovi ne moze da go nadmine dozvolenoto"<<endl;
    }
};
class Karticka{
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
public:
    Karticka(){}
    Karticka(char* smetka,int pin){
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
    }
    virtual int presmetajTezina()
    {
        int temp = pin ,counter = 0;
        while(temp){
            counter++;
            temp/=10;
        }
        return counter;
    }
    bool getDopolnitelenPin(){
        return povekjePin;
    }
   virtual ~Karticka(){}

   friend ostream& operator<<(ostream &out, Karticka &K){
       return out<<K.smetka<<": "<<K.presmetajTezina()<<endl;
    }
    char *getNaziv(){
        return smetka;
    }
};
class SpecijalnaKarticka : public Karticka{
private:
    int *dopolnitelniKodovi;
    int count;
    const static int p;
public:
    SpecijalnaKarticka(char *smetka="", int pin=123)
    :Karticka(smetka,pin){
        dopolnitelniKodovi = nullptr;
        this->count = count;
        povekjePin = true;
    }
    int presmetajTezina(){
        return Karticka::presmetajTezina() + count;
    }
  //Nema potreba! (ima gi istite infos)
    friend ostream& operator<<(ostream &out, SpecijalnaKarticka &K){
        Karticka k(K);
        cout<<k;
    }
    ~SpecijalnaKarticka(){
        delete[] dopolnitelniKodovi;
    }
    SpecijalnaKarticka & operator+=(int Dpin){
        for(int i=0;i<count;i++){
            if(count==p){
                throw OutOfBoundException();
            }
        }
        //Ako se frli exception ne prodolzuva programata!!!
        int *temp = new int[count+1];
        for(int i=0;i<count;i++){
            temp[i] = dopolnitelniKodovi[i];
        }
        temp[count++] = Dpin;
        delete [] dopolnitelniKodovi;
        dopolnitelniKodovi = temp;
        return *this;
    }
};
const int SpecijalnaKarticka::p = 4;  //MAX num of ADDpincodes;
class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
        }
        this->broj=broj;
    }
    ~Banka(){
        for (int i=0;i<broj;i++)
            delete karticki[i];
    }
    static void setLIMIT(int limit){
        LIMIT = limit;
    }
    void pecatiKarticki(){
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite: "<<endl;
        for(int i=0;i<broj;i++){
            if(karticki[i]->presmetajTezina()<=LIMIT)
                cout<<*karticki[i];
        }
    }
   Banka &dodadiDopolnitelenPin(char *smetka, int novPin) {
       for (int i = 0; i < broj; i++) {
           if (!strcmp(karticki[i]->getNaziv(), smetka)) {
               SpecijalnaKarticka *casted = dynamic_cast<SpecijalnaKarticka *>(karticki[i]);
               if (casted) {
                       *casted += novPin;
               }
           }
       }
   }
};
int Banka::LIMIT = 7;
int main(){

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;
    try {
        komercijalna.dodadiDopolnitelenPin(smetka, pin);
    }
    catch (OutOfBoundException e){
        e.showMessage();
    }

    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}
