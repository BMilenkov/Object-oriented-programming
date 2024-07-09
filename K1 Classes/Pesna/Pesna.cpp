#include <iostream>
#include <cstring>
using namespace std;
enum tip{
    pop,rap,rok //0,1,2
};
class Pesna{
private:
    char *name;
    int minuti;
    tip kojtip;
    void Copy(const Pesna &song){
        this->name = new char[strlen(song.name)+1];
        strcpy(this->name,song.name);
        this->minuti = song.minuti;
        this->kojtip = song.kojtip;
    }
public:
    Pesna(){}
    Pesna(char *name, int minuti, tip kojtip = tip(0)){
       this->name = new char[strlen(name)+1];
        strcpy(this->name,name);
        this->minuti = minuti;
        this->kojtip = kojtip;

        }
    Pesna(const Pesna &song){
        Copy(song);
        }
    Pesna &operator =(const Pesna &song) {
        if (this != &song) {
            delete [] name;
            Copy(song);
        }
        return *this;
    }
    ~Pesna(){
        delete[] name;
    }
    void pecati(){
        //cout<<"Ime: "<<NameFile<<" Vremetraenje:"<<minuti<<" Tip:";
            cout << "\"" << name << "\"" <<"-" << minuti << "min" << endl;
        /* if(kojtip==0){
             cout<<"pop"<<endl;
         }
            else if(kojtip==1){
                 cout<<"rap"<<endl;
             }
             else if(kojtip==2){
                 cout<<"rok"<<endl;
             }
         */}
         int getMinuti(){
             return minuti;
    }
    tip getTip(){
        return kojtip;
    }
    friend class CD;
};
class CD{
private:
    Pesna songs[10];
    int n;
    int maxDuration;
public:
    CD(){}
    CD(int maxDuration){
        this->maxDuration = maxDuration;
        this->n = 0;
    }
    CD(const CD &cd){
        this->maxDuration = cd.maxDuration;
        this->n = cd.n;
    }
    ~CD(){}
    void dodadiPesna (Pesna &p){
        if(n>=10)
            return;
        int current=0;
            for(int i=0;i<n;i++) {
                current+=songs[i].getMinuti(); // current+=songs[i].minuti;
            }
            if(current+p.getMinuti()>maxDuration)
                return;
            songs[n++]=p;
    }
    Pesna getPesna(int i){
        return songs[i];
    }
    void pecatiPesniPoTip(tip t){
        for(int i =0; i<n ;i++){
            if(songs[i].getTip()==t){
                songs[i].pecati();
            }
        }
    }
    int getBroj(){
        return n;
    }
};
int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];
    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    }
     else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
     else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);
    }
    return 0;
     }