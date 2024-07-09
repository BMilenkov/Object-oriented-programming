#include <iostream>
#include <cstring>
using namespace std;
class IceCream{
private:
    char *name;
    char ingredient[100];
    float price;
    int discount;
    void Copy(const IceCream &IC){
        this->name = new char [strlen(IC.name)+1];
        strcpy(this->name, IC.name);
        strcpy(this->ingredient,IC.ingredient);
        this->price = IC.price;
        this->discount = IC.discount;
    }
public:
    IceCream(char *name="", char *ingredient="", float price=0.0)
    {
        this->name = new char [strlen(name)+1];
        strcpy(this->name, name);
        strcpy(this->ingredient,ingredient);
        this->price = price;
        this->discount = 0;
    }
    IceCream(const IceCream &IC){
        Copy(IC);
    }
    IceCream &operator=(const IceCream &IC){
        if(this!=&IC){
            delete [] name;
            Copy(IC);
        }
        return *this;
    }
    ~IceCream(){
        delete[] name;
    }
    friend ostream & operator<<(ostream &out,const IceCream &IC){
        out<<IC.name<<": "<<IC.ingredient<<" "<<IC.price;
        if(IC.discount > 0)
            out << " (" << IC.price * (100 - IC.discount) / 100 << ")";
        return out;
    }
     IceCream & operator++(){
        discount+=5;
         return *this;
    }
    IceCream &operator +(const char *extra){
       char* newName = new char[strlen(name) + strlen(extra) + 4];
        strcpy(newName, name);
        strcat(newName, " + ");
        strcat(newName, extra);
        delete [] name;
        name = newName;
        price+=10;
        return *this;
    }
    void setDiscount(int d) {
        if(d>=0 && d<=100)
            discount = d;
    }
    void setName(const char* n) {
        delete [] name;
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }
};
class IceCreamShop{
private:
    char name[50];
    IceCream *icecreams;
    int count;
    void Copy(const IceCreamShop &ICS){
        strcpy(this->name,ICS.name);
        icecreams = new IceCream [ICS.count] ;
        this->count = ICS.count;
        for(int i=0;i<ICS.count;i++){
            this->icecreams[i] = ICS.icecreams[i];
        }
    }
public:
    IceCreamShop(char *name =""){
        strcpy(this->name,name);
        icecreams= nullptr;
        this->count = 0;
    }
    ~IceCreamShop(){
        delete [] icecreams;
    }
    IceCreamShop(const IceCreamShop&ICS){
        Copy(ICS);
    }
    IceCreamShop & operator +=(const IceCream &IC){
        IceCream *temp = new IceCream[count+1];
        for(int i=0 ;i<count;i++){
            temp[i] = icecreams[i];
        }
        temp[count++] = IC;
        delete [] icecreams;
        icecreams = temp;
        return *this;
    }
    IceCreamShop& operator=(const IceCreamShop &ics) {
        if (this != &ics) {
            delete[] icecreams;
            Copy(ics);
        }
        return *this;
    }
   friend ostream &operator <<(ostream &out,const IceCreamShop &ICS){
       cout << ICS.name << endl;
       for (int i = 0; i < ICS.count; ++i) {
           out << ICS.icecreams[i] << endl;
       }
       return out;
   }
};
int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        //cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }
    return 0;
}

