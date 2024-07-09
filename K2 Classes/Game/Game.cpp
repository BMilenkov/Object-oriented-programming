#include <iostream>
#include <cstring>
using namespace std;
class ExistingGame{
    char Message[50];
public:
    ExistingGame(char *Message=""){
        strcpy(this->Message,Message);
    }
    void message(){
        cout<<Message;
    }
};
class Game{
protected:
    char name[100];
    double price;
    bool OnSale;
    void Copy(const Game &G){
        strcpy(this->name,G.name);
        this->price= G.price;
        this->OnSale= G.OnSale;
    }
public:
    Game(char *name="", double price=0.0, bool sale = true){
        strcpy(this->name,name);
        this->price= price;
        this->OnSale=sale;
    }
        Game(const Game &G){
        Copy(G);
    }
    friend ostream & operator<<(ostream & o, const Game& g) {
        o<<"Game: "<< g.name <<", regular price: $" << g.price;
        if (g.OnSale){
            o<<", bought on sale";
        }
        return o;
    }
    //NE SMEE Const reference da prima!!!
    friend istream & operator>>(istream & in, Game& g){
        in.get();
        in.getline(g.name,100);
        in>>g.price>>g.OnSale;
        return in;
    }
    bool operator ==(Game &G){
        return !strcmp(this->name,G.name);
    }
    virtual double calc(){
        if(OnSale)
            return 0.3*price;
        return price;
    }
};
class SubscriptionGame :public Game {
private:
    double monthly_fee;
    int month;
    int year;
public:
    explicit SubscriptionGame(char *name = "", double price = 0.0,
                              bool sale = true, double monthly_fee = 0.0, int month = 1, int year = 1900)
            : Game(name, price, sale) {
        this->monthly_fee = monthly_fee;
        this->month = month;
        this->year = year;
    }

    friend ostream &operator<<(ostream &o, const SubscriptionGame &SG) {
        Game g(SG);
        cout << g;
        return o << ", monthly fee: $" << SG.monthly_fee << ", purchased: " << SG.month << "-" << SG.year << endl;
    }

    friend istream &operator>>(istream &in, SubscriptionGame &g) {
        in.get();
        in.getline(g.name, 100);
        in >> g.price >> g.OnSale;
        in >> g.monthly_fee >> g.month >> g.year;
        return in;
    }

    double calc() {
        double temp = Game::calc();
        int MY = 12 * (2018 - year - 1);
        int MM = (12 - month + 1) + 4;
        return temp + monthly_fee * (MY + MM);
        }
    };
    class User {
    private:
        char name[100];
        Game **games;
        int count;
    public:
        User(char *name = "") {
            strcpy(this->name, name);
            this->games = nullptr;
            this->count = 0;
        }

        User(const User &U) {
            strcpy(this->name, U.name);
            this->games = new Game *[U.count];
            for (int i = 0; i < U.count; i++)
                this->games[i] = U.games[i];
        }
        User &operator += (Game &G) {
            for (int i = 0; i < count; i++) {
                if (*(games[i]) == G) {
                    throw ExistingGame("The game is already in the collection\n");
                }
            }
           Game **temp = new Game * [count+1];
                    for (int i = 0; i < count; i++) {
                        temp[i] = games[i];
                    }
                auto *SG = dynamic_cast<SubscriptionGame *>(&G);
                if (SG)
                    temp[this->count++] = new SubscriptionGame(*SG);
                else
                    temp[this->count++] = new Game(G);
                delete[] this->games;
                this->games = temp;
            return *this;
        }

        double total_spent() {
            double sum = 0.0;
            for (int i = 0; i < count; i++) {
                sum += games[i]->calc();
            }
            return sum;
        }
        friend ostream &operator<<(ostream &out, const User &U) {
            out <<endl<< "User: " << U.name << endl;
            for (int i = 0; i < U.count; i++) {
                SubscriptionGame *casted = dynamic_cast<SubscriptionGame *>(U.games[i]);
                if (casted)
                    out <<"- "<< *casted;
                else
                    out <<"- "<<*U.games[i] << endl;
            }
            out<<endl;
            return out;
        }
    };
    int main() {
        int test_case_num;

        cin >> test_case_num;

        // for Game
        char game_name[100];
        float game_price;
        bool game_on_sale;

        // for SubscritionGame
        float sub_game_monthly_fee;
        int sub_game_month, sub_game_year;

        // for User
        char username[100];
        int num_user_games;

        if (test_case_num == 1) {
            cout << "Testing class Game and operator<< for Game" << std::endl;
            cin.get();
            cin.getline(game_name, 100);
            //cin.get();
            cin >> game_price >> game_on_sale;

            Game g(game_name, game_price, game_on_sale);

            cout << g;
        } else if (test_case_num == 2) {
            cout << "Testing class SubscriptionGame and operator<< for SubscritionGame" << std::endl;
            cin.get();
            cin.getline(game_name, 100);

            cin >> game_price >> game_on_sale;

            cin >> sub_game_monthly_fee;
            cin >> sub_game_month >> sub_game_year;

            SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month,
                                sub_game_year);
            cout << sg;
        } else if (test_case_num == 3) {
            cout << "Testing operator>> for Game" << std::endl;
            Game g;

            cin >> g;

            cout << g;
        } else if (test_case_num == 4) {
            cout << "Testing operator>> for SubscriptionGame" << std::endl;
            SubscriptionGame sg;

            cin >> sg;

            cout << sg;
        } else if (test_case_num == 5) {
            cout << "Testing class User and operator+= for User" << std::endl;
            cin.get();
            cin.getline(username, 100);
            User u(username);

            int num_user_games;
            int game_type;
            cin >> num_user_games;

            try {

                for (int i = 0; i < num_user_games; ++i) {

                    cin >> game_type;

                    Game *g;
                    // 1 - Game, 2 - SubscriptionGame
                    if (game_type == 1) {
                        cin.get();
                        cin.getline(game_name, 100);

                        cin >> game_price >> game_on_sale;
                        g = new Game(game_name, game_price, game_on_sale);
                    } else if (game_type == 2) {
                        cin.get();
                        cin.getline(game_name, 100);

                        cin >> game_price >> game_on_sale;

                        cin >> sub_game_monthly_fee;
                        cin >> sub_game_month >> sub_game_year;
                        g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee,
                                                 sub_game_month, sub_game_year);
                    }

                    //cout<<(*g);


                    u += (*g);
                }
            } catch (ExistingGame &ex) {
                ex.message();
            }

            cout << u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

        } else if (test_case_num == 6) {
            cout << "Testing exception ExistingGame for User" << std::endl;
            cin.get();
            cin.getline(username, 100);
            User u(username);

            int num_user_games;
            int game_type;
            cin >> num_user_games;

            for (int i = 0; i < num_user_games; ++i) {

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1) {
                    cin.get();
                    cin.getline(game_name, 100);

                    cin >> game_price >> game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                } else if (game_type == 2) {
                    cin.get();
                    cin.getline(game_name, 100);

                    cin >> game_price >> game_on_sale;

                    cin >> sub_game_monthly_fee;
                    cin >> sub_game_month >> sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month,
                                             sub_game_year);
                }

                //cout<<(*g);

                try {
                    u += (*g);
                }
                catch (ExistingGame &ex) {
                    ex.message();
                }
            }

            cout << u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
        } else if (test_case_num == 7) {
            cout << "Testing total_spent method() for User" << std::endl;
            cin.get();
            cin.getline(username, 100);
            User u(username);

            int num_user_games;
            int game_type;
            cin >> num_user_games;

            for (int i = 0; i < num_user_games; ++i) {

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1) {
                    cin.get();
                    cin.getline(game_name, 100);

                    cin >> game_price >> game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                } else if (game_type == 2) {
                    cin.get();
                    cin.getline(game_name, 100);

                    cin >> game_price >> game_on_sale;

                    cin >> sub_game_monthly_fee;
                    cin >> sub_game_month >> sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month,
                                             sub_game_year);
                }

                //cout<<(*g);

               try {
                   u += (*g);
               } catch (ExistingGame e){
                   e.message();
               }
            }

            cout << u;

            cout << "Total money spent: $" << u.total_spent() << endl;
        }
    }