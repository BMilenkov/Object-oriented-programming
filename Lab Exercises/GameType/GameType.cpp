
#include <iostream>
#include <cstring>
using namespace std;

class Game{
protected:
    char tittle[20];
public:
    Game(char *tittle = ""){
        strcpy(this->tittle ,tittle);
    }
    virtual void displayInfo()const{
        cout<<"Game: "<<tittle<<endl;
    }
    virtual int complexity(){}
};
class BoardGame: virtual public Game{
protected:
    int maxPlayers;
public:
    BoardGame(char *tittle="", int maxPlayers=0) : Game(tittle){
        this->maxPlayers = maxPlayers;
    }
     virtual int complexity() const{
        if(maxPlayers > 6)
            return 10;
        else if (maxPlayers > 3 && maxPlayers <6)
            return 5;
        else if(maxPlayers < 3)
            return 3;
    }
     virtual void displayInfo()const{
        Game::displayInfo();
        cout<<"Max players: "<<maxPlayers<<endl;
        cout<<"Complexity: "<<complexity()<<endl;
    }
};
class CardGame: virtual public Game{
protected:
    int NumOfCards;
public:
    CardGame(char *tittle="", int NumOfCards=0) : Game(tittle){
        this->NumOfCards = NumOfCards;
    }
     virtual int complexity()const{
        if(NumOfCards >20)
            return 10;
        else if(NumOfCards > 10 && NumOfCards < 20)
            return 5;
        else if(NumOfCards < 10 )
            return 3;
    }
    virtual void displayInfo()const{
        Game::displayInfo();
        cout<<"Number of cards: "<<NumOfCards<<endl;
        cout<<"Complexity: "<<complexity()<<endl;
    }
};
class BoardCardGame : public BoardGame,public CardGame{
public:
    BoardCardGame(char *tittle="", int maxPlayers=0, int NumOfCards=0)
    : Game(tittle){
        this->maxPlayers = maxPlayers;
        this->NumOfCards = NumOfCards;
    }
    int complexity() const{
        return (CardGame::complexity() + BoardGame::complexity())/2;
    }
   void displayInfo()const{
        Game::displayInfo();
        cout<<"Complexity: "<<complexity()<<endl;
    }
};
Game *mostComplexCardGame(Game **games, int n) {
    int max = 0, index;
    for (int i = 0; i < n; i++) {
        CardGame *casted = dynamic_cast<CardGame *>(games[i]);
        if (casted) {
            if (casted->complexity() > max) {
                max = casted->complexity();
                index = i;
            }
        }
    }
    return games[index];
}
int main() {
    char title[50];
    int maxPlayers;
    int numCards;
    int n;
    int choice;

    cin>>choice;
    if(choice==1)
    {
        cin>>title;
        BoardCardGame boardCardGame(title, 8, 15);
        boardCardGame.displayInfo();
    }
    else {

        cin >> n;

        Game **g = new Game *[n];
        for (int i = 0; i < n; i++) {
            cin >> choice;
            if (choice == 1) {
                cin >> title >> maxPlayers;

                g[i] = new BoardGame(title, maxPlayers);
            } else {
                cin >> title >> numCards;

                g[i] = new CardGame(title, numCards);
            }

        }
      mostComplexCardGame(g,n)->displayInfo();
    }
    return 0;
}