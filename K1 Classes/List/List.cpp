
#include <iostream>
using namespace std;
class List{
private:
    int *broevi;
    int n;
    void Copy(const List &L) {
        this->broevi = new int(L.n);
        this->n = L.n;
        for (int i = 0; i < L.n; i++) {
            this->broevi[i] = L.broevi[i];
        }
    }
public:
    List(){}
    List(int *broevi , int n){
        this->broevi = new int(n);
        this->n = n;
        for(int i=0;i< this->n;i++){
            this->broevi[i] = broevi[i];
        }
    }
    List(const List &L){
        Copy(L);
    }
    List &operator=(const List &L){
        if(this!=&L){
            delete [] broevi;
            Copy(L);
        }
        return *this;
    }
    int getN(){
        return n;
    }
    int sum(){
        int sum= 0;
        for(int i=0;i <n;i++)
            sum+=broevi[i];
        return sum;
    }
    double average(){
        return sum()*1.0/n;
    }
    void pecati(){
        cout<<n<<": ";
        for(int i=0;i <n;i++){
            cout<<broevi[i]<<" ";
        }
        cout<<"sum: "<<sum()<<" average: "<<average()<<endl;
    }
    ~List(){
        delete [] broevi;
    }
    friend class ListContainer;
};
class ListContainer{
private:
    List *lists;
    int count;
    int attempts;
    void Copy(const ListContainer &LC){
        this->count = LC.count;
        this->lists = new List[LC.count];
        this->attempts =LC.attempts;
        for(int i=0; i<LC.count ;i++){
            this->lists[i] = LC.lists[i]; //se povikkuva operator ednakvo!!
        }
    }
public:
    ListContainer(){
        this->lists = new List[0];
        this->count = 0;
        this->attempts =0;
    }
    ListContainer (const ListContainer &LC){
        Copy(LC);
    }
    ListContainer &operator=(const ListContainer &LC){
        if(this!=&LC){
            delete [] lists;
            Copy(LC);
        }
        return *this;
    }
    ~ListContainer(){
        delete [] lists;
    }
    void print() {
        if (!count) {
            cout << "The list is empty" << endl;
            return;
        } else {
            for (int i = 0; i < count; i++) {
                cout << "List number: ";
                cout << i + 1 << " List info: ";
                lists[i].pecati();
            }
            cout<<"Sum: "<<sum();
            cout<<" Average: "<<average()<<endl;
            cout<<"Successful attempts: "<<count<<" Failed attempts: "<<attempts-count<<endl;
        }
    }
    void addNewList(List l){
        attempts++;
        for(int i=0;i<count; i++){
            if(lists[i].sum()==l.sum())
                return;
        }
        List *temp = new List[count+1];
        for(int i=0;i<count; i++){
            temp[i] = lists[i];
        }
        temp[count++] = l;
        delete [] lists;
        lists = temp;
    }
    int sum(){
        int sum=0;
        for(int i=0;i<count; i++){
            sum+=lists[i].sum();
        }
        return sum;
    }
    double average(){
        double average=0.0;
        int number = 0;
        for(int i=0;i<count; i++){
            average+= lists[i].sum();
            number+=lists[i].getN();
        }
        return average/number;
    }
        };
        int main() {
            ListContainer lc;
            int N;
            cin>>N;
            for (int i=0;i<N;i++) {
                int n;
                int niza[100];
                cin>>n;
                for (int j=0;j<n;j++){
                    cin>>niza[j];
                }
                List l=List(niza,n);
                lc.addNewList(l);
            }
            int testCase;
            cin>>testCase;
            if (testCase==1) {
                cout<<"Test case for operator ="<<endl;
                ListContainer lc1;
                lc1.print();
                cout<<lc1.sum()<<" "<<lc.sum()<<endl;
                lc1=lc;
                lc1.print();
                cout<<lc1.sum()<<" "<<lc.sum()<<endl;
                lc1.sum();
                lc1.average();
            }
            else {
                lc.print();
            }
        }