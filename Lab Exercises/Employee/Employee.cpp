
#include <iostream>
#include <cstring>
using namespace std;
class Employee{
protected:
    char name[50];
    int age;
public:
    Employee(char *name = "", int age= 20){
        strcpy(this->name, name);
        this->age = age;
    }
    virtual void displayInfo(){
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
    }
};
class Payable{
protected:
    double salary;
public:
    virtual double calculateSalary()=0;
};
class Developer : public Employee , public Payable{
private:
    char PL[30];
public:
    Developer(char *name = "", int age= 20,double salary=0.0, char *PL = "")
    : Employee(name,age) {
        strcpy(this->PL,PL);
        this->salary = salary;
    }
    void displayInfo(){
        cout<<"-- Developer Information --"<<endl;
        Employee::displayInfo();
        cout<<"Salary: $"<<calculateSalary()<<endl;
        cout<<"Programming Language: "<<PL<<endl;
    }
    double calculateSalary(){
        return 0.9*salary;
    }
};
class Manager: public Employee , public Payable{
private:
    int departments;
public:
    Manager(char *name = "", int age= 20,double salary=0.0,int departments=0)
            : Employee(name,age) {
        this->departments = departments;
        this->salary = salary;
    }
    double calculateSalary(){
        return 1.15*salary;
    }
    void displayInfo(){
        cout<<"-- Manager Information --"<<endl;
        Employee::displayInfo();
        cout<<"Salary: $"<<calculateSalary()<<endl;
        cout<<"Number of Departments: "<<departments<<endl;
    }
};
double biggestSalary(Payable **p, int n){
    double BS = 0.0;
    for(int i =0;i<n;i++){
       if(p[i]->calculateSalary() > BS){
           BS = p[i]->calculateSalary();
       }
    }
    return BS;
}
int main()
{
    Payable* payable[5];
    Developer developers[5];
    Manager managers[5];
    int j=0, k=0;
    for(int i=0; i<5; i++)
    {
        char name[50];
        int age;
        double salary;
        cin>>name>>age>>salary;
        if(i%2==0)
        {
            char programmingLanguage[50];
            cin>>programmingLanguage;
            developers[j]=Developer(name, age, salary, programmingLanguage);
            developers[j].displayInfo();
            payable[i]=&developers[j];
            j++;
        }
        else {
            int numberOfDepartments;
            cin>>numberOfDepartments;
            managers[k]=Manager(name, age, salary, numberOfDepartments);
            managers[k].displayInfo();
            payable[i]=&managers[k];
            k++;
        }
    }
    cout<<endl<<"Biggest Salary: "<<biggestSalary(payable, 5);
    return 0;
}
