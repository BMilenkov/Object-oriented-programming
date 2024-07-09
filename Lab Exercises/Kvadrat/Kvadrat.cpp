#include <iostream>
using namespace std;
class Kvadrat{
protected:
    double a;
public:
    Kvadrat(double a=0.0){
        this->a = a;
    }
    Kvadrat(const Kvadrat &K){
        this->a = K.a;
    }
    double perimetar(){
        return 4*a;
    }
    double plostina(){
        return a*a;
    }
    void pecati(){
        cout<<"Kvadrat so dolzina a="<<a<<" ima plostina P="<<plostina()<<" i perimetar L="<<perimetar()<<endl;
    }
};
class Pravoagolnik: public Kvadrat{
    double x;
    double y;
public:
    Pravoagolnik(double a=0.0, double x=0.0,double y=0.0) : Kvadrat(a){
        this->x=x;
        this->y =y;
    }
    Pravoagolnik(const Kvadrat &k, double x,double y): Kvadrat(k){
        this->x=x;
        this->y =y;
    }
    Pravoagolnik(const Pravoagolnik& p) : Kvadrat(p){
        this->x = p.x;
        this->y = p.y;
    }
    double perimetar(){
        if(x==y) {
            a = a + x;
            return Kvadrat::perimetar();
        }
        else
            return (2*(a+x) + 2*(a+y));
    }
    double plostina(){
        if(x==y) {
            a = a + x;
            return Kvadrat::plostina();
        }
        else
            return ((a+x)*(a+y));

    }
    void pecati(){
        if(x==y)
        {
            a=a+x;
            Kvadrat::pecati();
        }
        else
        {
            cout<<"Pravoagolnik so strani: "<<a+x<<" i "<<a+y<<" ima plostina P="<<plostina()<<" i perimetar L="<<perimetar()<<endl;
        }
    }
};
int main ()
{
    int n;
    double a,x,y;
    Kvadrat * kvadrati;
    Pravoagolnik * pravoagolnici;

    cin>>n;

    kvadrati = new Kvadrat [n];
    pravoagolnici = new Pravoagolnik [n];

    for (int i=0;i<n;i++){
        cin>>a;

        kvadrati[i] = Kvadrat(a);
    }

    for (int i=0;i<n;i++){
        cin>>x>>y;

        pravoagolnici[i]=Pravoagolnik(kvadrati[i],x,y);
    }

    int testCase;
    cin>>testCase;

    if (testCase==1){
        cout<<"===Testiranje na klasata Kvadrat==="<<endl;
        for (int i=0;i<n;i++)
            kvadrati[i].pecati();
    }
    else {
        cout<<"===Testiranje na klasata Pravoagolnik==="<<endl;
        for (int i=0;i<n;i++)
            pravoagolnici[i].pecati();
    }
}