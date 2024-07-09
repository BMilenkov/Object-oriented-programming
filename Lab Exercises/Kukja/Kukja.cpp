
#include <iostream>
#include <cstring>
using namespace std;
class Masa{
private:
    int dolzina;
    int sirina;
public:
    //2in1 Constructor
    Masa(int dolzina = 1, int sirina = 1){
        this->dolzina = dolzina;
        this->sirina = sirina;
    }
    void pecatiM(){
        cout<<"Dolzinata na masata e: "<<dolzina<<endl<<"Sirinata na masata e: "<<sirina<<endl;
    }
};
class Soba{
private:
    Masa masa;
    int dolzina_soba;
    int sirina_soba;
public:
    Soba(){
        dolzina_soba = 1;
        sirina_soba = 1;
    }
    Soba(int dolzina_soba, int sirina_soba, Masa masa){
        this->dolzina_soba= dolzina_soba;
        this->sirina_soba = sirina_soba;
        this->masa= masa;
    }
    void pecatiS(){
        cout<<"Dolzinata na sobata e: "<<dolzina_soba<<endl<<"Sirinata na sobata e: "<<sirina_soba<<endl;
        masa.pecatiM();
    }
};
class Kukja{
private:
    Soba soba;
    char adresa[50];
public:
    Kukja(){
        //default
    }
    Kukja(Soba soba,char *adresa){
        this->soba=soba;
        strcpy(this->adresa,adresa);
    }
    ~Kukja(){
        //destruktor
    }
    void pecati() {
        cout << "Adresa: " << this->adresa << " ";
        this->soba.pecatiS();
    }
};
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int masaSirina,masaDolzina;
        cin>>masaSirina;
        cin>>masaDolzina;
        Masa m(masaSirina,masaDolzina);
        int sobaSirina,sobaDolzina;
        cin>>sobaSirina;
        cin>>sobaDolzina;
        Soba s(sobaSirina,sobaDolzina,m);
        char adresa[30];
        cin>>adresa;
        Kukja k(s,adresa);
        k.pecati();
    }
    return 0;
}
