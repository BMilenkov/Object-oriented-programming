#include<iostream>
#include<cstring>
using namespace std;
class Team {
private:
    int foundingYear;
    char name[20];
    char city[20];
public:
    Team(int foundingYear = 0, char *name = "", char *city = "") {
        this->foundingYear = foundingYear;
        strcpy(this->name, name);
        strcpy(this->city, city);
    }
    Team(const Team &e) { foundingYear = e.foundingYear;
        strcpy(name, e.name);
        strcpy(city, e.city);
    }
    const char *getName() {
        return name;
    }
    ~Team() {}

};
class Match {
private:
    Team Home;
    Team Away;
    int HomeGoals;
    int AwayGoals;
public:
    Match( Team home, Team away, int _HomeGoals, int _AwayGoals) {
        Home = home;
        Away = away;
        HomeGoals = _HomeGoals;
        AwayGoals = _AwayGoals;
    }
    Team getHome() {
        return Home;
    }
    Team getAway() {
        return Away;
    }
    int getHomeGoals() {
        return HomeGoals;
    }
    int getAwayGoals() {
        return AwayGoals;
    }
    ~Match() {}
};
bool isRematch(Match m1, Match m2){
    return ((strcmp(m1.getHome().getName(),m2.getAway().getName())==0 && strcmp(m1.getAway().getName(),m2.getHome().getName())==0));
}
Team Duel(Match m1, Match m2){
    if(isRematch(m1,m2)){
        int Team1goals = m1.getHomeGoals() + m2.getAwayGoals();
        int Team2goals = m1.getAwayGoals() + m2.getHomeGoals();
        if(Team1goals > Team2goals)
            return m1.getHome();
        else if (Team1goals < Team2goals)
            return m2.getHome();
        else
            printf("Draw in regular 90. Lets go to penalties!");
    }
    else{
        printf("TOO MANY TEAMS!");
    }

}
int main(){
    Team t1(1899,"Barcelona","Barcelona");
    Team t2(1902,"Real Madrid", "Madrid");
    Match m1 (t1,t2,0,0);
    Match m2 (t2,t1,1,0);
    cout<<Duel(m1,m2).getName()<<endl;
    return 0;
}