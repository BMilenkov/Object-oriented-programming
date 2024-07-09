#include <iostream>
#include <cstring>
using namespace std;
class Transport{
protected:
    char destination[20];
    int price;
    int kms;
public:
    Transport(char *destination ="", int price=0, int kms=0){
        strcpy(this->destination,destination);
        this->price = price;
        this->kms = kms;
    }
    virtual double  cenaTransport() = 0;
    //mora const da se stavi!!!
    bool operator <( Transport &T) const{
        if(this->kms < T.kms)
            return true;
        return false;
    }
    int getRastojanie(){
        return kms;
    }

    char *getDest(){
        return destination;
    }

    int getCena(){
        return price;
    }
};
class AvtomobilTransport : public Transport{
private:
    bool paidDriver;
public:
    explicit AvtomobilTransport(char *destination ="", int price=0, int kms=0,
                       bool paidDriver= false) : Transport(destination,price,kms){
        this->paidDriver = paidDriver;
    }
    double cenaTransport() override{
        if(paidDriver){
            return 1.2*price;
        }
        return price;
    }
};
class KombeTransport : public Transport{
private:
    int NumOfPeople;
public:
    explicit KombeTransport(char *destination ="", int price=0, int kms=0,
                       int NumOfPeople =0) : Transport(destination,price,kms){
        this->NumOfPeople=NumOfPeople;
    }
    double cenaTransport() override{
        return price - NumOfPeople * 200;
    }
};
void pecatiPoloshiPonudi(Transport **offers, int n, Transport &transport) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (offers[j]->getRastojanie() > offers[j + 1]->getRastojanie()) {
                Transport *tmp = offers[j+1];
                offers[j+1] = offers[j];
                offers[j] = tmp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (offers[i]->getCena() > transport.getCena())
            cout << offers[i]->getDest() << " " << offers[i]->getRastojanie() << " " << offers[i]->cenaTransport()
                 << endl;
    }
}
int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}

