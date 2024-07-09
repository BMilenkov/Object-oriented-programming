#include<iostream>
#include<string.h>
using namespace std;

class BadInputException{
public:
    void showMessage(){
        cout<<"Greshna opisna ocenka"<<endl;
    }
};
class StudentKurs{
protected:
    char ime[30];
    int ocenka; //pismen del
    bool daliUsno;
    static int MAX;
    const static int MINOCENKA;
public:
    StudentKurs(char* ime="",int finalenIspit=0){
        strcpy(this->ime,ime);
        this->ocenka=finalenIspit;
        this->daliUsno=false;
    }
   static void setMAX(int mark){
        MAX = mark;
    }
    bool getDaliUsno(){
        return daliUsno;
    }
    virtual int Ocenka(){
        return ocenka;
    }
    friend ostream &operator<<(ostream &out, StudentKurs &sk){
        out << sk.ime << " --- " << sk.Ocenka()<< endl;
        return out;
    }
    static int getMINOCENKA(){
        return MINOCENKA;
    }
    char *getName(){
        return ime;
    }
    virtual ~StudentKurs(){}
};
int StudentKurs::MAX=10;
const int StudentKurs::MINOCENKA = 6;

class StudentKursUsno:public  StudentKurs{
private:
    char *opisna;
public:
    StudentKursUsno(char* ime="",int finalenIspit=0): StudentKurs(ime,finalenIspit){
        this->daliUsno = true;
        this->opisna= nullptr;
    }
    int Ocenka(){
        if(!strcmp(opisna,"odlicen")) {
            if ((ocenka + 2) < MAX)
                return ocenka + 2;
        }
        else if(!strcmp(opisna,"dobro")) {
            if ((ocenka + 1) < MAX)
                return ocenka + 1;
        }
        else if(!strcmp(opisna,"losho")) {
            if ((ocenka - 1) < MAX)
                return ocenka - 1;
        }
        else
            return ocenka;
    }
    friend ostream &operator<<(ostream &out, StudentKursUsno &sk){
        out << sk.ime << " --- " << sk.Ocenka()<< endl;
        return out;
    }
    StudentKursUsno & operator +=(char *OPISNA){
        for(int i=0; i < strlen(OPISNA); i++){
            if(!isalpha(OPISNA[i]))
                throw BadInputException();
        }
        delete [] opisna;
        opisna = new char [strlen(OPISNA)+1];
        strcpy(opisna,OPISNA);
        return *this;
    }
};

class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno()){
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            }
            else this->studenti[i]=new StudentKurs(*studenti[i]);
        }
        this->broj=broj;
    }
    ~KursFakultet(){
        for (int i=0;i<broj;i++)
            delete studenti[i];
    }
    void pecatiStudenti(){
        cout<<"Kursot "<<naziv<<" go polozile: "<<endl;
        for(int i=0;i < broj;i++){
            if(studenti[i]->Ocenka()>=StudentKurs::getMINOCENKA())
                cout<<*studenti[i];
        }
    }
    void postaviOpisnaOcenka(char * ime, char* opisnaOcenka){
        for(int i=0;i < broj;i++){
            if(!strcmp(studenti[i]->getName(),ime)){
            auto *casted = dynamic_cast<StudentKursUsno*>(studenti[i]);
            if(casted){
                *casted+=opisnaOcenka;
                 }
            }
        }
    }
};

int main(){

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0;i<n;i++){
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>ime>>opisna;
        try {
            programiranje.postaviOpisnaOcenka(ime, opisna);
        }
        catch (BadInputException e){
            e.showMessage();
            int j = 0;
            for(int i=0;i < strlen(opisna);i++){
                if(isalpha(opisna[i]))
                    opisna[j++] = opisna[i];
            }
            opisna[j]='\0';
            programiranje.postaviOpisnaOcenka(ime, opisna);
        }
    }
    StudentKurs::setMAX(9);
    programiranje.pecatiStudenti();
}
