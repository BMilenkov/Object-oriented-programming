#include <iostream>
#include <cstring>
using namespace std;
class Course{
protected:
    char name[50];
public:
    Course(char *name= ""){
        strcpy(this->name ,name);
    }
    virtual void displayInfo(){
        cout<<"Name: "<<name<<endl;
    }
    virtual int level() =0;
};

class RegularCourse : virtual public  Course{
protected:
    int maxStudents;
public:
    RegularCourse(char *name= "", int maxStudents=0) : Course(name){
        this->maxStudents = maxStudents;
    }
    int level(){
        if (maxStudents < 10)
            return 10;
        else if(maxStudents>10 && maxStudents <30){
            return 7;
        }
        else if(maxStudents >30){
            return 5;
        }
    }
    void displayInfo(){
        Course::displayInfo();
        cout<<"Students: "<<maxStudents<<endl;
        cout<<"Level: "<<level()<<endl;
    }
};
class SpecialCourse : virtual public  Course{
protected:
    int numTeachers;
public:
    SpecialCourse(char *name= "", int numTeachers=0) : Course(name){
        this->numTeachers = numTeachers;
    }
    int level(){
        if (numTeachers < 3)
            return 6;
        else if(numTeachers>3 && numTeachers <5){
            return 8;
        }
        else{
            return 10;
        }
    }
    void displayInfo(){
        Course::displayInfo();
        cout<<"Teachers: "<<numTeachers<<endl;
        cout<<"Level: "<<level()<<endl;
    }
};

class RSCourse:public RegularCourse, public SpecialCourse{
public:
    RSCourse(char *name= "", int maxStudents=0, int numTeachers = 0): Course(name){
        this->numTeachers = numTeachers;
        this->maxStudents = maxStudents;
    }
    int level(){
        return (RegularCourse::level()+2) + (SpecialCourse::level()-1);
    }
    void displayInfo(){
        Course::displayInfo();
        cout<<"Level: "<<level()<<endl;
    }
};
Course *bestCourse(Course**courses, int n){
    int max=0 , index;
    for(int i=0;i<n;i++){
        if(courses[i]->level() > max){
            max = courses[i]->level();
            index = i;
        }
    }
    return courses[index];

}

int main()
{
    int choice;
    cin>>choice;
    if(choice==1)
    {
        char name[50];
        int maxStudents;
        cin>>name>>maxStudents;
        RegularCourse regularCourse(name, maxStudents);
        cout<<"--- Testing RegularCourse class ---"<<endl;
        regularCourse.displayInfo();
    }
    else if(choice==2)
    {
        char name[50];
        int numTeachers;
        cin>>name>>numTeachers;
        SpecialCourse specialCourse(name, numTeachers);
        cout<<"--- Testing SpecialCourse class ---"<<endl;
        specialCourse.displayInfo();
    }
    else if(choice==3)
    {
        char name[50];
        int maxStudents, numTeachers;
        cin>>name>>maxStudents>>numTeachers;
        RSCourse rsCourse(name, maxStudents, numTeachers);
        cout<<"--- Testing RSCourse class ---"<<endl;
        rsCourse.displayInfo();
    }
    else if(choice==4)
    {
        Course **c = new Course *[5];
        for(int i=0; i<5; i++)
        {
            if(i%2==0)
            {
                char name[50];
                int numTeachers;
                cin>>name>>numTeachers;
                c[i]=new SpecialCourse(name, numTeachers);
            }
            else {
                char name[50];
                int maxStudents;
                cin>>name>>maxStudents;
                c[i]=new RegularCourse(name, maxStudents);
            }
            c[i]->displayInfo();
            cout<<endl;
        }
        cout<<"Best Course:"<<endl;
        bestCourse(c, 5)->displayInfo();
    }
    return 0;
}
