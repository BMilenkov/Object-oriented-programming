#include <iostream>
#include <cstring>
using namespace std;

enum Tip{
    LINUX, UNIX, WINDOWS
};
class OperativenSistem{
private:
    char *name;
    float version;
    Tip type;
    float size;
    void Copy(const OperativenSistem &OS){
        this->name = new char [strlen(OS.name)+1];
        strcpy(this->name, OS.name);
        this->version = OS.version;
        this->type = OS.type;
        this->size = OS.size;
    }
public:
    OperativenSistem(char *name ="", float verzija=0.0, Tip type = LINUX, float size=0.0){
        this->name = new char [strlen(name)+1];
        strcpy(this->name, name);
        this->version = verzija;
        this->type = type;
        this->size = size;
    }
    OperativenSistem(const OperativenSistem &OS){
        Copy(OS);
    }
    ~OperativenSistem(){
        delete [] name;
    }
    OperativenSistem &operator=(const OperativenSistem &OS){
        if(this!=&OS){
            delete [] name;
            Copy(OS);
        }
        return *this;
    }
    void pecati(){
    cout << "Ime: " << name << " Verzija: " << version << " Tip: " << type << " Golemina:" << size <<"GB"<< endl;
    }
    bool ednakviSe(const OperativenSistem &os){
        return !strcmp(name,os.name) && version == os.version && type == os.type && size == os.size;
    }
    int sporediVerzija(const OperativenSistem &os){
        if(version==os.version)
            return 0;
        else if(version < os.version)
            return -1;
        else
            return 1;
    }
    bool istaFamilija(const OperativenSistem &sporedba){
        return !strcmp(name,sporedba.name) && type==sporedba.type;
    }
};
class Repozitorium{
private:
    char nameREP[20];
    OperativenSistem *os;
    int number;
    void Copy(const Repozitorium &R) {
        strcpy(this->nameREP, R.nameREP);
        this->number = R.number;
        this->os = new OperativenSistem[R.number];
        for (int i = 0; i < R.number; i++) {
            os[i] = R.os[i];
        }
    }
public:
    //Repozitorium(){}
    Repozitorium(char *nameREP = ""){
            strcpy(this->nameREP, nameREP);
            this->number=0;
            os = new OperativenSistem[this->number];
        }
        Repozitorium (const Repozitorium &R){
            Copy(R);
    }
    Repozitorium & operator=(const Repozitorium &R){
            if(this!=&R){
                delete [] os;
                Copy(R);
            }
            *this;
    }
    ~Repozitorium(){
    delete [] os;
}
    void pecatiOperativniSistemi(){
        cout<<"Repozitorium: "<<nameREP<<endl;
            for(int i=0 ;i<number;i++){
                os[i].pecati();
            }
        }
    void izbrishi(const OperativenSistem &operativenSistem){
    int count=0;
    for(int i=0; i<number;i++){
        if(!os[i].ednakviSe(operativenSistem)){
            count++;
        }
      }
    OperativenSistem *temp = new OperativenSistem[count];
        count=0;
        for(int i=0; i<number;i++){
            if(!os[i].ednakviSe(operativenSistem)){
                temp[count++] = os[i];
            }
        }
        delete [] os;
        os=temp;
        number = count;
    }
    void dodadi(const OperativenSistem &nov) {
        for (int i = 0; i < number; i++) {
          if(os[i].istaFamilija(nov) && os[i].sporediVerzija(nov)==-1){
          os[i] = nov;
              return;
          }
        }
        OperativenSistem *temp = new OperativenSistem[number+1];
        for(int i=0; i< number;i++){
            temp[i] = os[i];
        }
        temp[number++] =nov;
        delete [] os;
        os = temp;
    }
};
int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }
    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}