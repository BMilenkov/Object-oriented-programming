#include <iostream>
#include <cstring>
using namespace std;
class Gitara{
private:
    char seriski[25];
    float nabavna;
    int godina;
    char tip[40];
    void Copy(const Gitara &gt){
        strcpy(this->tip,gt.tip);
        strcpy(this->seriski,gt.seriski);
        this->godina = gt.godina;
        this->nabavna = gt.nabavna;
    }
public:
    Gitara(char *tip="", char *seriski="", int godina=0,float nabavna=0.0){
        strcpy(this->tip,tip);
        strcpy(this->seriski,seriski);
        this->godina =godina;
        this->nabavna = nabavna;
    }
    Gitara (const Gitara & gt){
        Copy(gt);
    }
    Gitara &operator=(const Gitara &gt){
        Copy(gt);
        return *this;
    }
    ~Gitara(){}
    int getGodina(){return godina;}
    float getNabavna(){return nabavna;}
    char *getSeriski(){return seriski;}
    char *getTip(){return tip;}
    bool daliIsti(Gitara &gt){
        return strcmp(this->seriski,gt.seriski)==0;
    }
    void pecati(){
        cout<<seriski<<" "<<tip<<" "<<nabavna<<endl;
    }
};
class Magacin{
private:
    char ime[30];
    char lokacija[60];
    Gitara *gitari;
    int broj_na_gitari;
    int godina_na_otvoranje;
    void Copy(const Magacin &mg){
        strcpy(this->ime,mg.ime);
        strcpy(this->lokacija,mg.lokacija);
        this->godina_na_otvoranje = mg.godina_na_otvoranje;
        this->broj_na_gitari = mg.broj_na_gitari;
        for(int i=0 ; i<broj_na_gitari;i++){
            this->gitari[i] = mg.gitari[i];
        }
    }
public:
    Magacin(char *ime="", char *lokacija="", int godina_na_otvoranje=0){
        strcpy(this->ime,ime);
        strcpy(this->lokacija,lokacija);
        this->godina_na_otvoranje = godina_na_otvoranje;
        this->broj_na_gitari = 0;
        this->gitari = new Gitara[0];
    }
    Magacin(const Magacin *mg){
        Copy(mg);
    }
    Magacin &operator=(const Magacin &mg){
        delete [] gitari;
        Copy(mg);
        return *this;
    }
    ~Magacin(){delete [] gitari;}
    double vrednost(){
        double suma=0.0;
        for(int i=0;i<broj_na_gitari;i++){
            suma+= gitari[i].getNabavna();
        }
    }
    void dodadi(Gitara &gt){
        Gitara *temp = new Gitara[broj_na_gitari+1];
        for(int i=0;i<broj_na_gitari;i++){
            temp[i] = gitari[i];
        }
        temp[broj_na_gitari++] = gt;
        delete [] gitari;
        gitari = temp;
    }
    void prodadi(Gitara &g)
    {
        int br=0;
        for(int i=0; i<broj_na_gitari;i++)
        {
            if(gitari[i].daliIsti(g)==false)
            {
                br++;
            }
        }
        Gitara * temp = new Gitara[br];
        int j=0;
        for(int i=0;i<broj_na_gitari;i++)
        {
            if(gitari[i].daliIsti(g)==false)
            {
                temp[j++] = gitari[i];
            }
        }
        delete [] gitari;
        gitari = temp;
        broj_na_gitari = br;
    }
    void pecati(bool daliNovi) {
        cout << ime << " " << lokacija << endl;
        if (daliNovi == true) {
            for (int i = 0; i < broj_na_gitari; i++) {
                if (gitari[i].getGodina() > godina_na_otvoranje)
                    gitari[i].pecati();
            }
        } else {
            for (int i = 0; i < broj_na_gitari; i++) {
                gitari[i].pecati();
            }
        }
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50],tip[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
        cout<<g.getTip()<<endl;
        cout<<g.getSeriski()<<endl;
        cout<<g.getGodina()<<endl;
        cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
        cin>>n;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip,seriski, godina,cena);
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
    else if(testCase ==6)
    {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            kb.dodadi(g);
        }
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
    }
    return 0;
}

