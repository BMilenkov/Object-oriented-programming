
#include <iostream>
#include <cstring>
using namespace std;
class Rabotnik{
private:
    char name[50];
    char surname[30];
    int salary;
public:
    Rabotnik(){}
    Rabotnik(char *name, char *surname, int salary){
        strcpy(this->name,name);
        strcpy(this->surname,surname);
        this->salary= salary;
    }
    int getPlata(){
        return salary;
    }
    void pecati(){
        cout<<"Ime: "<<name<<endl<<"Prezime: "<<surname<<endl;
        cout<<"Plata: "<<salary<<endl;
    }
    friend class Fabrika;
};
class Fabrika{
private:
    Rabotnik employess[100]; //employess = vraboteni!
    int number;
public:
    Fabrika(){}
    Fabrika(Rabotnik *employees, int number){
        this->number = number;
        for(int i=0 ;i < number ;i++)
            this->employess[i] = employees[i];
    }
    void pecatiVraboteni(){
        for(int i=0 ;i<number;i++)
            employess[i].pecati();
        cout<<endl;
    }
    void pecatiSoPlata(int Plata) {
        for (int i = 0; i < number; i++) {
            if (employess[i].salary >= Plata) {
                employess[i].pecati();
            }
        }
    }
};
int main(){
    int n, minSalary;
    cin>>n;
    int salary;
    char name[30], surname[30];
    Rabotnik *workers = new Rabotnik[n]; //Dinamiclly allocated memory!
    for(int i=0 ;i<n; i++){
        cin>>name>>surname>>salary;
        workers[i] = Rabotnik(name,surname,salary);
    }
    cin>>minSalary;
    Fabrika factory(workers,n);
    cout<<"Site vraboteni:"<<endl;
    factory.pecatiVraboteni();
    cout<<"Vraboteni so pogolema ili ednakva plata od:"<<minSalary<<endl;
    factory.pecatiSoPlata(minSalary);
    return 0;
}
