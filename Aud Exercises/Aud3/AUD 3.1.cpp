
#include <iostream>
using namespace std;
class Array{
private:
    int *arr;
    int capacity;
    int n;
public:
    Array(int capacity = 5){ //Constructor
        arr = new int [capacity];
        n = 0;
        this->capacity = capacity;
    }
    Array(const Array &a){ //Copy-contructor
        n = a.n;
        capacity = a.capacity;
        arr = new int[capacity];
        for(int i=0; i < n; i++){
            arr[i] = a.arr[i];
        }
    }
    //Assigment operator =
    Array &operator=(const Array &a) {
        if (this != &a) { //Prevention od self-assigment!
            n = a.n;
            capacity = a.capacity;
            delete[] arr;
            arr = new int[capacity];
            for (int i = 0; i < n; i++) {
                arr[i] = a.arr[i];
            }
        }
        return *this;
    }
    ~Array(){
        delete [] arr;
    }
    void print(){
        for (int i = 0; i < n; i++) {
            cout<<arr[i]<<" ";
        }
        for(int i = n; i < capacity;i++){
            cout<<" - ";
        }
        cout<<endl;
    }
    void change(int a, int b){
        for(int i=0; i < n; i++){
        if(arr[i]==a){
            arr[i] = b;
            }
        }
    }
    void deleteAll(int a) {
        int newSize = 0;
        for (int i = 0, j = 0; i < n; i++)
            if (arr[i] != n) {
                arr[j++] = arr[i];
                newSize++;
            }
        n = newSize;
    }
    void add(int a) {
        if (capacity == n) {
            int *y = new int[2 * capacity];
            for (int i = 0; i < n; ++i) {
                y[i] = arr[i];
            }
            delete [] arr;
            arr = y;
            capacity = capacity * 2;
        }
        arr[n++] = a;
    }
};
int main() {
    Array arr;
    for(int i = 6; i >=1; i--){
        arr.add(i);
    }
    Array b(arr);
    Array c;
    c = arr;
    b.add(2);
    b.change(2,6);
    c.deleteAll(6);
    cout<<"Array: ";
    arr.print();
    cout<<"B: ";
    b.print();
    cout<<"C: ";
    c.print();
    return 0;
}