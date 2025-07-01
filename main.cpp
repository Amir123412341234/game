#include <vector>
#include <iostream>
#include <chrono>
#include <functional>
#include <thread>

using namespace std;

vector<vector<char>> init(){
    vector<vector<char>> field(31);
    for(int i = 0; i < 31; i++){
        field[i].resize(81);
        for(int j = 0; j < 81; j++){
            field[i][j] = '.';
        }
    }
    field[15][0] = '*';
    return field;
}

void print(vector<vector<char>> field) {
    for(int i = 0; i < 31; i++){
        for(int j = 0; j < 80; j++){
            cout << field[i][j];
        }
        cout << "\n";
    }
}

char generate_enemy(){
    int a = rand() % 100;
    if (a > 10){
        return '.';
    }else{
        return '#';
    }
}

void generate_enemies(vector<vector<char>> &game){
    for(int i = 0; i < 31; i++){
        game[i][80] = generate_enemy();
    }

}

bool check_move(vector<vector<char>> game){
    for(int i = 0; i < 31; i++){
        for(int j = 0; j < 80; j++){
            if(game[i][j] == '*'){
                if(game[i][j + 1] == '#'){
                    return false;
                }
            }
        }
    }
    return true;
}

void game_step(vector<vector<char>> &game){
    vector<vector<char>> game_copy = game;
    for(int i = 0; i < 31; i++){
        for(int j = 0; j < 81; j++){
            if(game_copy[i][j] == '#'){
                game[i][j] = '.';
                game[i][j-1] = '#';
            }
        }
    }
}

int main(int argc, char *argv[])
{
    vector<vector<char>> game;
    game = init();
    while(true){
        system("cls");
        print(game);
        generate_enemies(game);
        bool save = check_move(game);
        if (save == false){
            cout << "You are lost!";
            break;
        }else{
            game_step(game);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

}
