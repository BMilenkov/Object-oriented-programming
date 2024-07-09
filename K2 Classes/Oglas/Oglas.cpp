#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;
class Oglas{
private:
    char tittle[50];
    char category[30];
    char description[100];
    double price;
    void Copy(const Oglas &O){
        strcpy(this->tittle,O.tittle);
        strcpy(this->category,O.category);
        strcpy(this->description,O.description);
        this->price = O.price;
    }
public:
    Oglas(char *tittle= "", char *category = "", char *description="", double price = 0.0){
        strcpy(this->tittle,tittle);
        strcpy(this->category,category);
        strcpy(this->description,description);
        this->price = price;
    }
    bool operator > (Oglas &O){
        return this->price > O.price;
    }
    friend ostream& operator<<(ostream &out, Oglas &O){
        out<<O.tittle<<endl;
        out<<O.description<<endl;
        out<<O.price<<" evra"<<endl;
        return out;
    }
    Oglas(const Oglas &O){
        Copy(O);
    }
    Oglas &operator=(const Oglas &O){
        if(this!=&O){
            Copy(O);
        }
        return *this;
    }
    double GetPrice(){
        return price;
    }
    char *getCategory(){
        return category;
    }
};
class NegativnaVrednost{
public:
    void showMessage(){
        cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
    }
};
class Oglasnik{
private:
    char name[20];
    Oglas *oglasi;
    int count;
public:
    Oglasnik(char *name = ""){
        strcpy(this->name,name);
        this->count = 0;
        oglasi = nullptr;
    }
    Oglasnik &operator+=(Oglas &O) {
        if (O.GetPrice() < 0)
            throw NegativnaVrednost();
            Oglas *temp = new Oglas[count + 1];
            for (int i = 0; i < count; i++) {
                temp[i] = oglasi[i];
            }
            temp[count++] = O;
            delete[] oglasi;
            oglasi = temp;
            return *this;
    }
       friend ostream & operator <<(ostream &out, Oglasnik &O){
        out<<O.name<<endl;
        for(int i=0; i < O.count;i++){
            out<<O.oglasi[i]<<endl;
             }
           return out;
        }
    void oglasOdKategorija(const char *k){
        for(int i=0;i<count;i++){
            if(strcmp(oglasi[i].getCategory(),k)==0){
                cout<<oglasi[i]<<endl;
            }
        }
    }
    void najniskaCena(){
        double minPrice= 2222222222;
        int index;
        for(int i=0;i<count;i++){
            if(oglasi[i].GetPrice() < minPrice){
            minPrice = oglasi[i].GetPrice();
            index = i;
            }
        }
        cout<<oglasi[index];
    }
};
int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            }
            catch (NegativnaVrednost e){
                e.showMessage();
            }
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            }
            catch (NegativnaVrednost e){
                e.showMessage();
            }
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            }
            catch (NegativnaVrednost e){
                e.showMessage();
            }
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){

            try {
                cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
            catch (NegativnaVrednost e) {
                e.showMessage();
            }
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            }
            catch (NegativnaVrednost e){
                e.showMessage();
            }
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}
