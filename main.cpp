#include <curses.h>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

void sleep_for_ms(size_t ms) {
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono;      // nanoseconds, system_clock, seconds
    sleep_for(milliseconds(ms));
}

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
            printw("%c", field[i][j]);
        }
        printw("\n");
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

void move_space_ship_up(vector<vector<char>> &game){
    vector<vector<char>> game_copy = game;
    for(int i = 0; i < 31; i++){
        for(int j = 0; j < 81; j++){
            if(game_copy[i][j] == '*'){
                game[i][j] = '.';
                game[i-1][j] = '*';
            }
        }
    }
}

void move_space_ship_down(vector<vector<char>> &game){
    vector<vector<char>> game_copy = game;
    for(int i = 0; i < 31; i++){
        for(int j = 0; j < 81; j++){
            if(game_copy[i][j] == '*'){
                game[i][j] = '.';
                game[i+1][j] = '*';
            }
        }
    }
}

int main(int argc, char *argv[])
{
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    cbreak();
    vector<vector<char>> game;
    game = init();
    while(true){
        clear();
        print(game);
        refresh();
        generate_enemies(game);
        bool save = check_move(game);
        if (save == false){
            clear();
            printw("You are lost!");
            refresh();
            break;
        }else{
            game_step(game);
        }
        timeout(500);
        int key = getch();
        if (key == KEY_UP) {
            move_space_ship_up(game);
        } else if (key == KEY_DOWN) {
            move_space_ship_down(game);
        }
    }
    endwin();
}



