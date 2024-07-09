#include <iostream>
#include <cstring>
using namespace std;

class Koncert{
private:
    char name[20];
    char location[20];
    static double discount; //20% //sezonski!
    double price;
public:
    Koncert(char *name="", char *location ="", double price =0.0){
        strcpy(this->name ,name);
        strcpy(this->location,location);
        this->price = price;
    }
    static void setSezonskiPopust(double D){
        Koncert::discount = D;
    }
    char *getNaziv(){
        return name;
    }
    virtual double cena(){
        return price-(discount*price);
    }
    static double getSezonskiPopust() {
        return discount;
    }
};
double Koncert::discount = 0.2;

class ElektronskiKoncert : public Koncert{
private:
    char *DJ;
    double duration;
    bool day_night_party; // day =true , night = false
public:

    ElektronskiKoncert(char *name="", char *location ="",
                       double price =0.0, char *DJ ="", double duartion=0.0,
                       bool day_night_party = true) : Koncert(name,location,price){
        this->DJ = new char[strlen(DJ)+1];
        strcpy(this->DJ ,DJ);
        this->duration = duartion;
        this->day_night_party = day_night_party;
    }
    double cena(){
        float tottal = Koncert::cena();
        if (duration > 7.0) {
            tottal += 360;
        } else if (duration > 5.0) {
            tottal += 150;
        }
        if (day_night_party) {
            tottal -= 50.0;
        } else {
            tottal += 100.0;
        }
        return tottal;
    }
    ~ElektronskiKoncert() {
        delete [] DJ;
    }
};
void najskapKoncert(Koncert ** koncerti, int n){
    Koncert *max = nullptr;
    int elektronski = 0;
    double maxprice=0.0;
    for(int i=0;  i < n; i++){
        if(koncerti[i]->cena() > maxprice){
            maxprice = koncerti[i]->cena();
            max = koncerti[i];
        }
        ElektronskiKoncert *casted = dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
        if(casted){
            elektronski++;
        }
    }
    cout<<"Najskap koncert: "<<max->getNaziv()<<
    " "<<max->cena()<<endl;
    cout<<"Elektronski koncerti: "<<elektronski<<" od vkupno "<<n<<endl;
}
bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski){
   if(elektronski){
    for(int i=0;i<n;i++){
        if(ElektronskiKoncert *casted = dynamic_cast<ElektronskiKoncert*>(koncerti[i])){
        if(!strcmp(naziv,casted->getNaziv())){
            cout<<casted->getNaziv()<<" "<<casted->cena()<<endl;
            return true;
                }
            }
        }
    }
   else {
       for (int i = 0; i < n; i++) {
           if (!strcmp(naziv, koncerti[i]->getNaziv())) {
               cout << koncerti[i]->getNaziv()<<" "<< koncerti[i]->cena() << endl;
               return true;
           }
       }
   }
    return false;
}
int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin>>tip;
    if (tip==1){//Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
    }
    else if (tip==2){//cena - Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
    }
    else if (tip==3){//ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
    }
    else if (tip==4){//cena - ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
    }
    else if (tip==5) {//najskapKoncert

    }
    else if (tip==6) {//prebarajKoncert
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        najskapKoncert(koncerti,5);
    }
    else if (tip==7){//prebaraj
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        bool elektronski;
        cin>>elektronski;
        if(prebarajKoncert(koncerti,5, "Area",elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

        if(prebarajKoncert(koncerti,5, "Area",!elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

    }
    else if (tip==8){//smeni cena
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[2] -> setSezonskiPopust(0.9);
        najskapKoncert(koncerti,4);
    }

    return 0;
}
