
#include <iostream>
#include <cstring>
using namespace std;
class Boy{
private:
    char name[10];
    char surname[10];
    int years;
public:
    Boy(char *_name = "Trajce", char *_surname = "Trajkov", int _years =18){
        strcpy(name,_name);
        strcpy(surname,_surname);
        years=_years;
    }
    int getAge(){
        return years;
    }
    Boy(const Boy &boy){
        cout<<"COPY- constructor is called for boy!"<<endl;
        strcpy(name,boy.name);
        strcpy(surname,boy.surname);
        years=boy.years;
    }
    void print(){
        cout<<"Name : "<<name<<" Surname "<<surname<< " YEARS: "<<years<<endl;
    }
};
class Girl{
private:
    char name[10];
    char surname[10];
    int years;
public:
    Girl(char *_name = "Trajanka", char *_surname = "Trajkova", int _years =18){
        strcpy(name,_name);
        strcpy(surname,_surname);
        years=_years;
    }
    int getAge(){
        return years;
    }
  Girl(const Girl &girl){
      cout<<"COPY- constructor is called for girl!"<<endl;
        strcpy(name,girl.name);
        strcpy(surname,girl.surname);
        years=girl.years;
    }
    void print(){
        cout<<"Name : "<<name<<" Surname "<<surname<< " YEARS: "<<years<<endl;
    }
};
class Date{
private:
    Boy boy;
    Girl girl;
public:
    Date(){
    }
    Date( Boy _boy, Girl _girl){
        boy = _boy;
        girl = _girl;
    }
    Date( const Date &d){
        cout<<"COPY- constructor is called!"<<endl;
        boy = d.boy;
        girl = d.girl;
    }
    void print(){
            cout <<"DATE BETWEEN: "<<endl;
            boy.print();
            cout<<"AND "<<endl;
            girl.print();
        }
       void match(){
        if(boy.getAge() <= girl.getAge())
            printf("Si odgovaraat !");
        else
            printf("Ne si odgovaraat");
    }
};
int main(){
    Boy b;
    Girl g;
    Date d(b,g);
    d.print();
    d.match();
    return 0;
}