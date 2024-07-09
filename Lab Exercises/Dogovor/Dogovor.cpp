#include <iostream>
#include <cstring>
using namespace std;
class Potpisuvac{
private:
    char name[20];
    char surname[20];
    char embg[14];
public:
    Potpisuvac(char *name=" ",char *surname=" ", char *embg=" "){
        strcpy(this->name,name);
        strcpy(this->surname,surname);
        strcpy(this->embg,embg);
    }
    Potpisuvac(const Potpisuvac &p){
        strcpy(this->name,p.name);
        strcpy(this->surname,p.surname);
        strcpy(this->embg,p.embg);
    }
    char *getEMBG(){
        return this->embg;
    }
    friend class Dogovor;
};
class Dogovor{
private:
    int broj_na_dogovor;
    char kategorija[50];
    Potpisuvac potpisuvaci[3];
public:
    Dogovor(int broj_na_dogovor,char *kategorija, Potpisuvac potpisuvaci[3]){
        this->broj_na_dogovor=broj_na_dogovor;
        strcpy(this->kategorija,kategorija);
        for(int i=0 ;i<3;i++){
            this->potpisuvaci[i]=potpisuvaci[i];
        }
    }
    //No need of the copy-constructor!
    bool proverka1 (){
        return (strcmp(potpisuvaci[0].embg,potpisuvaci[1].embg)==0
                || strcmp(potpisuvaci[1].embg,potpisuvaci[2].embg)==0
                || strcmp(potpisuvaci[0].embg,potpisuvaci[2].embg)==0);
    }
    bool proverka(){
        return strcmp(potpisuvaci[0].getEMBG(),potpisuvaci[1].getEMBG())==0
               || strcmp(potpisuvaci[1].getEMBG(),potpisuvaci[2].getEMBG())==0
               || strcmp(potpisuvaci[0].getEMBG(),potpisuvaci[2].getEMBG())==0;
    }
};
//ne smee da se menuva main funkcijata
int main()
{
    char embg[14], ime[20], prezime[20], kategorija[20];
    int broj, n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> embg >> ime >> prezime;
        Potpisuvac p1(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        Potpisuvac p2(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        Potpisuvac p3(ime, prezime, embg);
        cin >> broj >> kategorija;
        Potpisuvac p[3];
        p[0] = p1; p[1] = p2; p[2] = p3;
        Dogovor d(broj, kategorija, p);
        cout << "Dogovor " << broj << ":" << endl;
        if(d.proverka() == true)
            cout << "Postojat potpishuvaci so ist EMBG" << endl;
        else
            cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
    }
    return 0;
}