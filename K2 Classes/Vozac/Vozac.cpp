#include <iostream>
#include <cstring>
using namespace std;
class Vozac{
protected:
    char name[100];
    int age;
    int NumOfRaces;
    bool veteran;
public:
    Vozac(char *name, int age, int NumOfRaces, bool veteran){
        strcpy(this->name ,name);
        this->age = age;
        this->NumOfRaces = NumOfRaces;
        this->veteran = veteran;
    }
    friend ostream &operator <<(ostream &out, const Vozac &V){
        out<<V.name<<endl<<V.age<<endl<<V.NumOfRaces<<endl;
        if(V.veteran)
            out<<"VETERAN"<<endl;
        return out;
    }
    virtual float earning()=0;
    virtual double danok() =0;
    friend bool operator==(Vozac &a, Vozac &b)
    {
        return a.earning()==b.earning();
    }
    ~Vozac(){}
};
class Avtomobilist :public Vozac{
private:
    float price;
public:
    explicit Avtomobilist(char *name, int age, int NumOfRaces ,
                 bool veteran, float price )
                 :Vozac(name, age, NumOfRaces, veteran){
        this->price = price;
    }
    float earning() override{
        return price/5;
    }
   double danok(){
        if(NumOfRaces>10)
            return 0.15*earning();
        return 0.10*earning();
    }
    ~Avtomobilist(){}
};
class Motociklist : public Vozac{
private:
    int power;
public:
    explicit Motociklist(char *name, int age, int NumOfRaces,
                 bool veteran, float power)
            :Vozac(name, age, NumOfRaces, veteran){
        this->power = power;
    }
    float earning() override{
        return power*20;
    }
    double danok(){
        if(veteran)
            return 0.25*earning();
        return 0.20*earning();
    }
    ~Motociklist(){}
};
int soIstaZarabotuvachka(Vozac **drivers,int count, Vozac *V){
    int counter= 0;
    for(int i=0;i < count; i++)
    {
        if(drivers[i]->earning()==V->earning())
            counter++;
    }
    return counter;
}
int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}