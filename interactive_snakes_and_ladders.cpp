//this is the interactive extention to the basic snakes and ladders game in the same repo
#include <iostream>
#include<bits/stdc++.h>

using namespace std;

class game {
private:
    int num;                      //number of players

    int size_of_board;
    int no_of_snakes;
    int no_of_ladders;
    map<int, int> snakes;         //holds mouth and tail of all snake
    map<int, int> ladders;        //holds foot and top of all ladders

public:
    game(int n, int b, int s, int l) { num = n; size_of_board = b; no_of_snakes = s; no_of_ladders = l; }  //default constructor

    void generate_board();//generates position of snakes and ladders 
    void print_snakes() { for (auto i : snakes) { cout << i.first << " to " << i.second << ", "; }cout << endl; }                                   //print head and tail of snakes
    void print_ladders() { for (auto i : ladders) { cout << i.first << " to " << i.second << ", "; }cout << endl; }                                    //print foot and top of ladders
    int update_player_position(int pos, int dice);
};

void game::generate_board() {
    int m = size_of_board;
    int s = no_of_snakes;
    int l = no_of_ladders;
    int arr[m - 2];
    for (int i = 2; i < m; ++i)
        arr[i - 2] = i;

    random_shuffle(arr, arr + m - 2);                //shuffle numbers from 2 to size_of_board-1 

    for (int i = 0; i < s; i++) {                        //choose initial s for mouth of snake
        int mouth = arr[i];                        //(ensuring that 2 snakes, or 2 ladder_foots dont occur on same pos, also both snake and ladder don't occur on the same position)   
        int tail = (rand() % (mouth - 1)) + 1;     //generate a random tail in range [1,moouth) 
        snakes.insert(make_pair(mouth, tail));
    }

    for (int i = s; i < s + l; i++) {                      //then choose next l for foot of ladder  
        int foot = arr[i];
        int top = (rand() % (m - foot)) + foot + 1;  //generate a random top in range (foot,m];
        ladders.insert(make_pair(foot, top));
    }

}

int game::update_player_position(int pos, int dice) {
    if (pos + dice > size_of_board) {
        return pos;                                 //can't go outside the board
    }
    pos += dice;
    if (snakes.find(pos) != snakes.end()) {
        cout << " Oops, snake-bite!! ";
        pos = snakes[pos];
    }
    else if (ladders.find(pos) != ladders.end()) {
        cout << " Yes, climbed up the ladder!! ";
        pos = ladders[pos];
    }
    return pos;
}

class player {
private:
    int pos;
    map<int, string>name;
    int p_index;
public:
    player() { pos = 1; }//default constructor
    void set_name(string a, int i) { name[i] = a; p_index = i; }
    string get_name() { return name[p_index]; }
    int get_position() { return pos; }                                                                               //return position of player at index i
    void set_position(int po) { pos = po; }                                                                         //set position of playre at index i to pos.
    void update_position(game gme, int dice) {
        pos = gme.update_player_position(pos, dice);
    };                                                                                      //updates the position of player_i when dice shows number "dice"
};

int main() {
    srand(time(0));

    int num_of_players = 3;
    int board_size = 75;
    int num_of_snakes = 7;
    int num_of_ladders = 6;
    cout << "Wanna Play ?" << endl;
    cout << "Enter number of players\n";
    cin >> num_of_players;
    vector<player>p(num_of_players);
    for (int i = 0; i < num_of_players; i++) {
        cout << "Enter name of player " << i + 1 << endl;
        string s;
        cin >> s;
        p[i].set_name(s, i);
    }

    cout << "Enter size of board\n";
    cin >> board_size;
    cout << "Enter number of snakes\n";
    cin >> num_of_snakes;
    cout << "Enter number of ladders\n";
    cin >> num_of_ladders;

    game gm(num_of_players, board_size, num_of_snakes, num_of_ladders);                //object of class game

    gm.generate_board();                                                               //generate board with parameters given to gm

    cout << "The snakes will take a player from ";                                       //show all the snakes on the board 
    gm.print_snakes();

    cout << "The ladders will take a player from ";                                      //show all the ladders on the board
    gm.print_ladders();
    cout << endl;

    int flag = 0;
    getchar();
    while (flag != 1) {                                                                    //Run the loop till any player wins
        for (int i = 0; i < num_of_players; i++) {
            cout << p[i].get_name() << "'s turn: Current position=" << p[i].get_position() << "\nPress enter key to roll the dice.";
            getchar();

            int dice = (rand() % (6)) + 1;                                              //generate random number on dice from [1,6]

            cout << " dice=" << dice << " ";

            p[i].update_position(gm, dice);

            cout << "New position=" << p[i].get_position() << endl << endl;

            if (p[i].get_position() == board_size) {                                        //some player reached the end
                cout << p[i].get_name() << " wins!!";
                flag = 1;
                break;
            }
        }
    }
    fflush(stdin);
    getchar();
    return 0;
}
/*Sample output:

Wanna Play ?
Enter number of players
2
Enter name of player 1
don
Enter name of player 2
john
Enter size of board
40
Enter number of snakes
4
Enter number of ladders
6
The snakes will take a player from 9 to 2, 11 to 2, 22 to 15, 27 to 1, 
The ladders will take a player from 12 to 22, 18 to 38, 21 to 39, 28 to 39, 31 to 36, 34 to 38, 

don's turn: Current position=1
Press enter key to roll the dice.
 dice=1 New position=2

john's turn: Current position=1
Press enter key to roll the dice.
 dice=2 New position=3

don's turn: Current position=2
Press enter key to roll the dice.
 dice=1 New position=3

john's turn: Current position=3
Press enter key to roll the dice.
 dice=4 New position=7

don's turn: Current position=3
Press enter key to roll the dice.
 dice=5 New position=8

john's turn: Current position=7
Press enter key to roll the dice.
 dice=4  Oops, snake-bite!! New position=2

don's turn: Current position=8
Press enter key to roll the dice.
 dice=6 New position=14

john's turn: Current position=2
Press enter key to roll the dice.
 dice=2 New position=4

don's turn: Current position=14
Press enter key to roll the dice.
 dice=2 New position=16

john's turn: Current position=4
Press enter key to roll the dice.
 dice=5  Oops, snake-bite!! New position=2

don's turn: Current position=16
Press enter key to roll the dice.
 dice=2  Yes, climbed up the ladder!! New position=38

john's turn: Current position=2
Press enter key to roll the dice.
 dice=1 New position=3

don's turn: Current position=38
Press enter key to roll the dice.
 dice=3 New position=38

john's turn: Current position=3
Press enter key to roll the dice.
 dice=3 New position=6

don's turn: Current position=38
Press enter key to roll the dice.
 dice=5 New position=38

john's turn: Current position=6
Press enter key to roll the dice.
 dice=3  Oops, snake-bite!! New position=2

don's turn: Current position=38
Press enter key to roll the dice.
 dice=4 New position=38

john's turn: Current position=2
Press enter key to roll the dice.
 dice=6 New position=8

don's turn: Current position=38
Press enter key to roll the dice.
 dice=3 New position=38

john's turn: Current position=8
Press enter key to roll the dice.
 dice=5 New position=13

don's turn: Current position=38
Press enter key to roll the dice.
 dice=5 New position=38

john's turn: Current position=13
Press enter key to roll the dice.
 dice=4 New position=17

don's turn: Current position=38
Press enter key to roll the dice.
 dice=2 New position=40

don wins!!


*/
