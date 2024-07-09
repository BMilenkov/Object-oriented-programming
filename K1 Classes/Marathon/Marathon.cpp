#include <iostream>
#include <cstring>
using namespace std;
class Ucesnik{
private:
    char *name;
    bool pol;
    int vozrast;
    void Copy(const Ucesnik &U){
        this->name = new char [strlen(U.name)+1];
        strcpy(this->name,U.name);
        this->pol = U.pol;
        this->vozrast = U.vozrast;
    }
public:
    Ucesnik(char *name="", bool pol= false, int vozrast = 1){
        this->name = new char [strlen(name)+1];
        strcpy(this->name,name);
        this->pol = pol;
        this->vozrast = vozrast;
    }
    Ucesnik(const Ucesnik &U){
        Copy(U);
    }
    Ucesnik & operator=(const Ucesnik & U){
        if(this!=&U){
            delete[] name;
            Copy(U);
        }
        return *this;
    }
    ~ Ucesnik(){
        delete [] name;
    }
     bool operator > (const Ucesnik &U) const{
        if(this->vozrast > U.vozrast)
            return true;
         return false;
    }
    friend ostream & operator <<(ostream  &out,const Ucesnik &U){
        out<<U.name<<endl;
        if(U.pol==0)
            out<<"zhenski"<<endl;
        else
            out<<"mashki"<<endl;
        out<<U.vozrast;
        return out;
    }
    int getVozrast() const{
        return vozrast;
    }
};
class Maraton{
private:
    char location[100];
    Ucesnik *ucesnici;
    int n;
    void Copy(const Maraton &M){
        strcpy(this->location,M.location);
        this->ucesnici = new Ucesnik[M.n];
        this->n = M.n;
        for(int i=0; i<this->n;i++){
            this->ucesnici[i] = M.ucesnici [i];
        }
    }
public:
    Maraton(char *location=""){
        strcpy(this->location,location);
        ucesnici = nullptr;
        this->n = 0;
    }
    Maraton (const Maraton &M){
        Copy(M);
    }
    Maraton & operator=(const Maraton & M){
        if(this!=&M){
            delete[] ucesnici;
            Copy(M);
        }
        return *this;
    }
   ~Maraton(){
        delete [] ucesnici;
    }
    Maraton & operator +=(const Ucesnik &U){
        Ucesnik *temp = new Ucesnik[n+1];
        for(int i=0; i<n;i++){
            temp[i] = ucesnici[i];
        }
        temp[n++] = U;
        delete [] ucesnici;
        ucesnici = temp;
        return *this;
    }
    double prosecnoVozrast(){
        int sum=0;
        for(int i=0; i<n;i++){
            sum+= ucesnici[i].getVozrast();
        }
        return (double)sum/n;
    }
    void pecatiPomladi(Ucesnik &u){
        for(int i=0; i<n;i++){
         if( u > ucesnici[i]){
             cout<<ucesnici[i]<<endl;
             }
        }
    }
};
int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
    return 0;
}