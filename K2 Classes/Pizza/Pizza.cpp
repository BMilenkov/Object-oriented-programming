#include <cstring>
#include <iostream>
using namespace std;
class Pizza{
protected:
    char name[20];
    char ingredients[100];
    double price;
public:
    Pizza(char const *name= "" , char const *ingredients= "", float price =0.0){
        strcpy(this->name , name);
        strcpy(this->ingredients , ingredients);
        this->price = price;
    }
    Pizza(const Pizza &P){
        strcpy(this->name , P.name);
        strcpy(this->ingredients , P.ingredients);
        this->price =P.price;
    }
    virtual double GetPrice() = 0;
    bool operator <(Pizza &p1) {
        if (GetPrice() < p1.GetPrice())
            return true;
        else return false;
    }
    friend ostream &operator<<(ostream &out, Pizza &pizza) {
        out<<pizza.name<<": "<<pizza.ingredients<<", ";
        return out;
    }
};
enum Size{
    small=0,
    big=1,
    family=2
};
class FlatPizza : public Pizza{
private:
    Size size;
    void Copy(const FlatPizza &FP){
        this->size = FP.size;

    }
public:
    FlatPizza(char const *name= "" , char const *ingredients="",
              float price =0.0,Size size = (Size)0)
            :Pizza(name,ingredients,price)
    {
        this->size = size;
    }
    FlatPizza (const FlatPizza &FP) : Pizza(FP){
        Copy(FP);
    }
    double GetPrice(){
        if(size == small){
            return 1.1 * price;
        }
        else if(size == family){
            return 1.3 * price;
        } else if(size ==big)
            return 1.5 * price;
    }
    friend ostream &operator<<(ostream &out, FlatPizza &pizza) {
        out<<pizza.name<<": "<<pizza.ingredients<<", ";
        if(pizza.size == small)
            out<<"small ";
        else if(pizza.size == big)
            out<<"big ";
        else if(pizza.size == family)
            out<<"family ";
        out<<"- "<<pizza.GetPrice();
        out<<endl;
        return out;
    }
};
class FoldedPizza : public Pizza{
private:
    bool flour{};
    void Copy(const FoldedPizza &FOP){
        this->flour = FOP.flour;
    }
public:
    explicit FoldedPizza(char const *name= "" , char const *ingredients="",
                float price =0.0,bool flour = true):Pizza(name,ingredients,price){
        this->flour = flour;
    }
    FoldedPizza(const FoldedPizza & FOP) : Pizza(FOP){
        Copy(FOP);
    }
    void setWhiteFlour(bool flour ){
        this->flour = flour;
    }
    double GetPrice() override{
        if(flour){
            return 1.1 * price;
        } else
            return 1.3 * price;
    }
    friend ostream &operator<<(ostream &out, FoldedPizza &pizza) {
        out<<pizza.name<<": "<<pizza.ingredients<<", ";
        if(pizza.flour)
            out<<"wf - ";
        else
            out<<"nwf - ";
        out<<pizza.GetPrice()<<endl;
        return out;
    }
};
void expensivePizza(Pizza **pizas, int n){
    double MaxPrice = 0.0;
    int index;
    for(int i=1; i < n; i++){
        if(pizas[i]->GetPrice() > MaxPrice){
            MaxPrice = pizas[i]->GetPrice();
            index = i;
        }
    }
    //MORA dynamic cast
    auto * p1 = dynamic_cast<FlatPizza *>(pizas[index]);
    if(p1 != nullptr)
        cout<<*p1;
    auto *p2 = dynamic_cast<FoldedPizza * >(pizas[index]);
    if(p2 != nullptr)
        cout<<*p2;
}
int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->GetPrice()<<endl;
        else cout<<fp2->GetPrice()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->GetPrice()<<endl;
        else cout<<fp3->GetPrice()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->GetPrice()<<endl;
        else cout<<fp2->GetPrice()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->GetPrice()<<endl;
        else cout<<fp4->GetPrice()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}
