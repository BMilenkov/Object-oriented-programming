#include <iostream>
#include <cstring>
#define MAX 50
using namespace std;

class UserExistsException{
public:
    void showMessage(){
        cout<<"The user already exists in the list!"<<endl;
    }
};

enum typeC{
    standard,
    loyal,VIP
};

class Customer{
private:
    char name[50];
    char email[50];
    typeC type;
    static int discount; //OSNOVEN!
    const static int AddDiscound; //DOPOLNITELEN!
    int products;
    void Copy(const Customer &C){
        strcpy(this->name,C.name);
        strcpy(this->email,C.email);
        this->type = C.type;
        this->products = C.products;
        this->discount = C.discount;
    }
public:
    Customer(const char *name="",const char *email="", typeC type = standard, int products = 0){
        strcpy(this->name,name);
        strcpy(this->email,email);
        this->type = type;
        this->products = products;
        this->discount = discount;
    }
    Customer(const Customer &C){
        Copy(C);
    }
    Customer& operator=(const Customer &C){
        if(this!=&C){
            Copy(C);
        }
        return *this;
    }
    char *getEmail() {
        return email;
    }
    int getProducts(){
        return products;
    }
    typeC getType(){
        return type;
    }
    void setType(typeC t){
        this->type = t;
    }
    ~Customer(){}

    static void setDiscount1(int setDiscount){
        discount = setDiscount;
    }
    double popust()const{
        if(type==loyal)
            return discount;
        else
            if(type==standard)
                return 0;
            else if(type==VIP)
                return AddDiscound;
    }
    friend ostream &operator<<(ostream &out, const Customer &C){
        out<<C.name<<endl<<C.email<<endl<<C.products<<endl;
        if(C.type==VIP){
            out<<"vip ";
        }
        else if(C.type ==standard){
            out<<"standard ";
        } else if(C.type ==loyal) {
            out << "loyal ";
        }
        out<<C.popust()<<endl;
        return out;
    }
};
int Customer::discount = 10; //10%
const int Customer::AddDiscound = 30; //20%

class FINKI_bookstore{
private:
    Customer *customers;
    int count;
public:
    FINKI_bookstore(){
        customers= nullptr;
        this->count = 0;
    }
   FINKI_bookstore & operator += (Customer &C) {
       bool hasFound = false;
       for (int i = 0; i < count; i++) {
           if (!strcmp(customers[i].getEmail(), C.getEmail())) {
               hasFound = true;
           }
       }
       if (hasFound) {
           throw UserExistsException();
       } else {
           Customer *temp = new Customer[count + 1];
           for (int i = 0; i < count; i++) {
               temp[i] = customers[i];
           }
           temp[count++] = C;
           delete[] customers;
           customers = temp;
       }
   }
   void setCustomers(Customer *customers, int n){
        this->count = n;
        this->customers = new Customer[count];
        for(int i=0;i < n;i++){
            this->customers[i] = customers[i];
        }
    }
    void update(){
       for(int i=0;i<count;i++){
           if(customers[i].getType()==standard && customers[i].getProducts() > 5){
               customers[i].setType(loyal);
           }
           else if(customers[i].getType()==loyal && customers[i].getProducts() > 10){
               customers[i].setType(VIP);
           }
       }
    }
   friend ostream & operator<<(ostream &out, FINKI_bookstore &FBS){
        for(int i=0;i<FBS.count;i++){
           out<<FBS.customers[i];
        }
       return out;
    }
};
int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try {
            fc += c;

        }catch (UserExistsException e){
            e.showMessage();
        }
        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);

        try {
            fc += c;
        }catch (UserExistsException e){
            e.showMessage();
        }
        cout << fc;
    }
    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
