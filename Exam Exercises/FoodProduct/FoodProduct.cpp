 #include <iostream>
#include <cstring>
using namespace std;
class FoodProduct{
private:
    char name[50];
    int amount;
    int price;
public:
    FoodProduct(char *name="", int amount=0, int price=0){
        strcpy(this->name,name);
        this->amount = amount;
        this->price = price;
    }
    FoodProduct(const FoodProduct &FP){
        strcpy(this->name,FP.name);
        this->amount = FP.amount;
        this->price = FP.price;
    }
    ~FoodProduct(){}
   int getAmount(){
       return amount;
    }
    int getPrice(){
        return price;
    }
    void setAmount(int amount){
        this->amount = amount;
    }
    void setPrice(int price){
        this->price=price;
    }
    void print(){
        cout<<"Name: "<<name<<endl;
        cout<<"Amount available: "<<amount<<endl;
        cout<<"Price: "<<price<<endl;
    }
};
class Menu{
private:
    char name[50];
    int count;
    FoodProduct products[50];
public:
    Menu(char *name=""){
        strcpy(this->name,name);
        this->count = 0;
    }
    Menu (const Menu &m){
        strcpy(this->name,m.name);
        this->count = m.count;
        for(int i=0; i<count;i++){
            products[i] = m.products[i];
        }
    }
    void setName(char *name){
        strcpy(this->name, name);
    }
    void setProducts(int count){
        this->count = count;
    }
    char *getName(){
        return name;
    }
    int getNumberOfProducts(){
        return count;
    }
    void print(){
        cout<<"Name: "<<name<<endl;
        cout<<"Products:"<<endl;
        for (int i = 0; i < count; i++) {
            products[i].print();
            cout<<endl;
        }
    }
    void addProduct(FoodProduct & product){
        products[count++] = product;
    }
    int totalIncome(){
        int income = 0;
        for(int i=0;i<count;i++){
            income += (products[i].getAmount()*products[i].getPrice());
        }
        return income;
    }
};
void printWorstMenu(Menu *menus, int n){
    int flag=1, min, index;
    for (int i = 0; i < n; i++) {
        if(flag){
            min = menus[i].totalIncome();
            index =i;
            flag=0;
        }
        else if(!flag){
            if(menus[i].totalIncome() < min){
                min = menus[i].totalIncome();
                index = i;
            }
        }
    }
    menus[index].print();
}
int main() {
    int n;
    cin >> n;

    /// BASIC INPUT & ADD PRODUCT![](../AppData/Local/Temp/image.png)
    Menu menus[n];

    for(int i = 0; i < n; i++) {
        int m;
        char name[50];

        cin >> name >> m;
        menus[i] = Menu(name);

        for(int j = 0; j < m; j++) {
            char itemName[50];
            int amount, price;

            cin >> itemName >> amount >> price;

            FoodProduct product(itemName, amount, price);
            menus[i].addProduct(product);
        }
    }
/*
    /// TESTING ADD PRODUCT

    cout << "-- Testing add product & getNumberOfProducts() --\n\n";

    char tempName[50] = "test";
    Menu temp(tempName);

    cout << "Number of products before adding: " << temp.getNumberOfProducts() << '\n';

    temp.addProduct(FoodProduct(tempName, 0, 0));

    cout << "Number of products after adding: " << temp.getNumberOfProducts() << '\n';
    temp.print();

    /// TESTING COPY CONSTRUCTOR

    Menu tester(menus[0]);
    std::strcpy(tempName, "Tester Name");
    tester.setName(tempName);

    cout << "\n-- Testing copy constructor & setName() --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    menus[0].print();

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    tester.print();

    /// TESTING WORST PRODUCT

  */
    cout << "\n-- Testing printWorstMenu() --\n";
    printWorstMenu(menus, n);

    return 0;
}

