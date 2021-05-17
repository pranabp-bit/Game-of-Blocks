#include <iostream>
#include<bits/stdc++.h>
using namespace std;

class game{
    private:
        int num;                      //number of players
        vector<int>v;                 //holds position of all players, initial position=1;
        int size_of_board;
        int no_of_snakes;
        int no_of_ladders;
        map<int,int> snakes;         //holds mouth and tail of all snake
        map<int,int> ladders;        //holds foot and top of all ladders
        
    public:
        game(int n, int b, int s, int l){num=n; size_of_board=b; no_of_snakes=s; no_of_ladders=l; for(int i=0;i<n;i++){v.push_back(1);}}  //default constructor
        int get_position(int player_i){return v[player_i];}                                                                               //return position of player at index i
        void set_position(int player_i,int pos){v[player_i]=pos;}                                                                         //set position of playre at index i to pos.
        void update_position(int player_i,int dice);                                                                                      //updates the position of player_i when dice shows number "dice"
        void generate_board();//generates position of snakes and ladders 
        void print_snakes(){for(auto i:snakes){cout<< i.first << " to " << i.second<<", ";}cout<<endl;}                                   //print head and tail of snakes
        void print_ladders(){for(auto i:ladders){cout<<i.first<<" to " << i.second<<", ";}cout<<endl;}                                    //print foot and top of ladders
};

void game::generate_board(){
    int m=size_of_board;               
    int s=no_of_snakes;
    int l=no_of_ladders;
    int arr[m-2];                       
    for(int i = 2; i < m; ++i)
        arr[i-2] = i;
        
    random_shuffle(arr, arr+m-2);                //shuffle numbers from 2 to size_of_board-1 
    
    for(int i=0;i<s;i++){                        //choose initial s for mouth of snake
        int mouth=arr[i];                        //(ensuring that 2 snakes, or 2 ladder_foots dont occur on same pos, also both snake and ladder don't occur on the same position)   
        int tail= (rand() %(mouth - 1)) + 1;     //generate a random tail in range [1,moouth) 
        snakes.insert(make_pair(mouth,tail));
    }
    
    for(int i=s;i<s+l;i++){                      //then choose next l for foot of ladder  
        int foot=arr[i];                    
        int top= (rand() %(m - foot)) + foot+1;  //generate a random top in range (foot,m];
        ladders.insert(make_pair(foot,top));    
    }
    
}

void game::update_position(int player_i,int dice){
    int i=player_i;
    if(v[i]+dice>size_of_board){
        return;                                 //can't go outside the board
    }
    v[i]+=dice;
    if(snakes.find(v[i])!=snakes.end()){
        cout<<" Oops, snake-bite!! ";
        v[i]=snakes[v[i]];
    }
    else if(ladders.find(v[i])!=ladders.end()){
        cout<<" Yes, climbed up the ladder!! ";
        v[i]=ladders[v[i]];
    }
}


int main() {
    srand(time(0));
    
    int num_of_players=3;
    int board_size=75;
    int num_of_snakes=7;
    int num_of_ladders=6;
    
    game gm(num_of_players, board_size, num_of_snakes, num_of_ladders);                //object of class game
    
    gm.generate_board();                                                               //generate board with parameters given to gm
    
    cout<<"The snakes will take a player from ";                                       //show all the snakes on the board 
    gm.print_snakes();                                                                 
    
    cout<<"The ladders will take a player from ";                                      //show all the ladders on the board
    gm.print_ladders();

    int flag=0;
    while(flag!=1){                                                                    //Run the loop till any player wins
        for(int i=0;i<num_of_players;i++){
            int dice=(rand() %( 6 )) + 1;                                              //generate random number on dice from [1,6]
            
            cout<<"Player "<<i+1<<"'s turn: current position="<<gm.get_position(i);
            
            cout<<" dice="<<dice<<" ";
            
            gm.update_position(i,dice);
            
            cout<<"New position="<<gm.get_position(i)<<endl;
            
            if(gm.get_position(i)==board_size){                                        //some player reached the end
                cout<<"Player "<<i+1<<" wins!!";
                flag=1;
                break;
            }
        }
    }

	return 0;
}
//further scope, corner cases, throw error for invalid number of snakes, ladders. take size input as LxB instead of single integer.

/*sample game 1:
  The snakes will take a player from 6 to 1, 13 to 2, 38 to 22, 41 to 25, 57 to 9, 58 to 56, 68 to 5, 
  The ladders will take a player from 4 to 42, 18 to 68, 27 to 29, 47 to 62, 54 to 64, 63 to 65, 
  Player 1's turn: current position=1 dice=3  Yes, climbed up the ladder!! New position=42
  Player 2's turn: current position=1 dice=5  Oops, snake-bite!! New position=1
  Player 3's turn: current position=1 dice=4 New position=5
  Player 1's turn: current position=42 dice=4 New position=46
  Player 2's turn: current position=1 dice=5  Oops, snake-bite!! New position=1
  Player 3's turn: current position=5 dice=1  Oops, snake-bite!! New position=1
  Player 1's turn: current position=46 dice=1  Yes, climbed up the ladder!! New position=62
  Player 2's turn: current position=1 dice=4 New position=5
  Player 3's turn: current position=1 dice=5  Oops, snake-bite!! New position=1
  Player 1's turn: current position=62 dice=4 New position=66
  Player 2's turn: current position=5 dice=6 New position=11
  Player 3's turn: current position=1 dice=4 New position=5
  Player 1's turn: current position=66 dice=4 New position=70
  Player 2's turn: current position=11 dice=2  Oops, snake-bite!! New position=2
  Player 3's turn: current position=5 dice=2 New position=7
  Player 1's turn: current position=70 dice=6 New position=70
  Player 2's turn: current position=2 dice=4  Oops, snake-bite!! New position=1
  Player 3's turn: current position=7 dice=6  Oops, snake-bite!! New position=2
  Player 1's turn: current position=70 dice=2 New position=72
  Player 2's turn: current position=1 dice=6 New position=7
  Player 3's turn: current position=2 dice=6 New position=8
  Player 1's turn: current position=72 dice=1 New position=73
  Player 2's turn: current position=7 dice=5 New position=12
  Player 3's turn: current position=8 dice=6 New position=14
  Player 1's turn: current position=73 dice=3 New position=73
  Player 2's turn: current position=12 dice=2 New position=14
  Player 3's turn: current position=14 dice=5 New position=19
  Player 1's turn: current position=73 dice=5 New position=73
  Player 2's turn: current position=14 dice=4  Yes, climbed up the ladder!! New position=68
  Player 3's turn: current position=19 dice=1 New position=20
  Player 1's turn: current position=73 dice=2 New position=75
  Player 1 wins!!
*/

/*sample game 2:
  The snakes will take a player from 13 to 1, 19 to 5, 24 to 20, 32 to 10, 40 to 34, 64 to 41, 66 to 63, 
  The ladders will take a player from 4 to 71, 6 to 47, 9 to 27, 46 to 52, 51 to 55, 59 to 66, 
  Player 1's turn: current position=1 dice=3  Yes, climbed up the ladder!! New position=71
  Player 2's turn: current position=1 dice=1 New position=2
  Player 3's turn: current position=1 dice=4 New position=5
  Player 1's turn: current position=71 dice=6 New position=71
  Player 2's turn: current position=2 dice=2  Yes, climbed up the ladder!! New position=71
  Player 3's turn: current position=5 dice=3 New position=8
  Player 1's turn: current position=71 dice=2 New position=73
  Player 2's turn: current position=71 dice=1 New position=72
  Player 3's turn: current position=8 dice=5  Oops, snake-bite!! New position=1
  Player 1's turn: current position=73 dice=4 New position=73
  Player 2's turn: current position=72 dice=6 New position=72
  Player 3's turn: current position=1 dice=4 New position=5
  Player 1's turn: current position=73 dice=6 New position=73
  Player 2's turn: current position=72 dice=3 New position=75
  Player 2 wins!!
*/
