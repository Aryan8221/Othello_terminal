#include<iostream>
#include <cmath>
#include <fstream>
#include <thread>
#include <chrono>
//#include <conio.h>
#include <string>
#include <stdlib.h>

using namespace std;

void counter(string *arr, int n);
void Rankings();
int get_size();
bool is_possible(char arr[12][12][141], int size, int row, int column, int round, char turn);
void swap(char arr[12][12][141], int size, int row, int column, int round, char turn);
void first_spaces(int n);
void style_2();
void main_arr(int n, char arr[12][12][141], int menu_num, int spaces, string &num_1, string &num_2, int ai);
void get_input(char arr[12][12][141], int &CursorY, int &CursorX, int n, int turn[], int &round, bool &flag, bool &run, int x, int y, int ai, string &name_1, string &name_2);
void Scores(int n, char arr[12][12][141], string &a, string &b, int spaces, int turn, int round);
void Help_below_board(int n, int space);
void NEW_GAME_STYLE();
void LOAD_GAME_STYLE();
void RANKING_STYLE();
void EXIT_STYLE();
void WELCOME_TO_OTHELLO_STYLE();
void menu_style(char arr[12][12][141]);

int main() {
    char arr[12][12][141];
    menu_style(arr);

    return 0;
}

int get_size() {
    int size;
    first_spaces(75);
    cout << "Board length: ";
    cin >> size;
    while (true) {
        if (size > 3 && size < 13 && size % 2 == 0) {
            return size;
        } else {
            first_spaces(75);
            cout << "Wrong number !" << endl;
            first_spaces(75);
            cout << "Please enter an even number between 4 and 12 for board length" << endl;
            first_spaces(75);
            cout << "Board length: ";
            cin >> size;
        }
    }
}

bool is_possible(char arr[12][12][141], int size, int row, int column, int round, char turn) {
    if (arr[row][column][round] != ' ') {
        return false;
    }
    int temp_row = row + 2;
    int temp_column = column;
    while (temp_row < size && temp_row >= 0 && arr[row + 1][column][round] != ' ' && arr[row + 1][column][round] != turn && arr[temp_row][column][round] != ' ') {
        if (arr[temp_row][column][round] == turn) {
            return true;
        }
        temp_row++;
    }
    temp_row = row - 2;
    while (temp_row < size && temp_row >= 0 && arr[row - 1][column][round] != ' ' && arr[row - 1][column][round] != turn && arr[temp_row][column][round] != ' ') {
        if (arr[temp_row][column][round] == turn) {
            return true;
        }
        temp_row--;
    }
    temp_column = column + 2;
    while (temp_column < size && temp_column >= 0 && arr[row][column + 1][round] != ' ' && arr[row][column + 1][round] != turn && arr[row][temp_column][round] != ' ') {
        if (arr[row][temp_column][round] == turn) {
            return true;
        }
        temp_column++;
    }
    temp_column = column - 2;
    while (temp_column < size && temp_column >= 0 && arr[row][column - 1][round] != ' ' && arr[row][column - 1][round] != turn && arr[row][temp_column][round] != ' ') {
        if (arr[row][temp_column][round] == turn) {
            return true;
        }
        temp_column--;
    }
    temp_row = row + 2;
    temp_column = column + 2;
    while (temp_column < size && temp_column >= 0 && temp_row < size && temp_row >= 0 && arr[row + 1][column + 1][round] != ' ' && arr[row + 1][column + 1][round] != turn && arr[temp_row][temp_column][round] != ' ') {
        if (arr[temp_row][temp_column][round] == turn) {
            return true;
        }
        temp_row++;
        temp_column++;
    }
    temp_row = row - 2;
    temp_column = column - 2;
    while (temp_column < size && temp_column >= 0 && temp_row < size && temp_row >= 0 && arr[row - 1][column - 1][round] != ' ' && arr[row - 1][column - 1][round] != turn && arr[temp_row][temp_column][round] != ' ') {
        if (arr[temp_row][temp_column][round] == turn) {
            return true;
        }
        temp_row--;
        temp_column--;
    }
    temp_row = row - 2;
    temp_column = column + 2;
    while (temp_column < size && temp_column >= 0 && temp_row < size && temp_row >= 0 && arr[row - 1][column + 1][round] != ' ' && arr[row - 1][column + 1][round] != turn && arr[temp_row][temp_column][round] != ' ') {
        if (arr[temp_row][temp_column][round] == turn) {
            return true;
        }
        temp_row--;
        temp_column++;
    }
    temp_row = row + 2;
    temp_column = column - 2;
    while (temp_column < size && temp_column >= 0 && temp_row < size && temp_row >= 0 && arr[row + 1][column - 1][round] != ' ' && arr[row + 1][column - 1][round] != turn && arr[temp_row][temp_column][round] != ' ') {
        if (arr[temp_row][temp_column][round] == turn) {
            return true;
        }
        temp_row++;
        temp_column--;
    }
    return false;
}

void swap(char arr[12][12][141], int size, int row, int column, int round, char turn) {
    arr[row][column][round] = turn;
    bool is_changable = false;
    int temp_row = row + 2;
    int temp_column = column;
    while (temp_row < size && temp_row >= 0 && arr[row + 1][column][round] != ' ' && arr[row + 1][column][round] != turn && arr[temp_row][column][round] != ' ') {
        if (arr[temp_row][column][round] == turn) {
            is_changable = true;
            break;
        }
        temp_row++;
    }
    if (is_changable) {
        for (int i = row + 1; i < temp_row; i++) {
            arr[i][column][round] = turn;
        }
    }
    is_changable = false;
    temp_row = row - 2;
    while (temp_row < size && temp_row >= 0 && arr[row - 1][column][round] != ' ' && arr[row - 1][column][round] != turn && arr[temp_row][column][round] != ' ') {
        if (arr[temp_row][column][round] == turn) {
            is_changable = true;
            break;
        }
        temp_row--;
    }
    if (is_changable) {
        for (int i = row - 1; i > temp_row; i--) {
            arr[i][column][round] = turn;
        }
    }
    is_changable = false;
    temp_column = column + 2;
    while (temp_column < size && temp_column >= 0 && arr[row][column + 1][round] != ' ' && arr[row][column + 1][round] != turn && arr[row][temp_column][round] != ' ') {
        if (arr[row][temp_column][round] == turn) {
            is_changable = true;
            break;
        }
        temp_column++;
    }
    if (is_changable) {
        for (int i = column + 1; i < temp_column; i++) {
            arr[row][i][round] = turn;
        }
    }
    is_changable = false;
    temp_column = column - 2;
    while (temp_column < size && temp_column >= 0 && arr[row][column - 1][round] != ' ' && arr[row][column - 1][round] != turn && arr[row][temp_column][round] != ' ') {
        if (arr[row][temp_column][round] == turn) {
            is_changable = true;
            break;
        }
        temp_column--;
    }
    if (is_changable) {
        for (int i = column - 1; i > temp_column; i--) {
            arr[row][i][round] = turn;
        }
    }
    is_changable = false;
    temp_row = row + 2;
    temp_column = column + 2;
    while (temp_column < size && temp_column >= 0 && temp_row < size && temp_row >= 0 && arr[row + 1][column + 1][round] != ' ' && arr[row + 1][column + 1][round] != turn && arr[temp_row][temp_column][round] != ' ') {
        if (arr[temp_row][temp_column][round] == turn) {
            is_changable = true;
            break;
        }
        temp_row++;
        temp_column++;
    }
    if (is_changable) {
        temp_row = row + 1;
        for (int i = column + 1; i < temp_column; i++) {
            arr[temp_row][i][round] = turn;
            temp_row++;
        }
    }
    is_changable = false;
    temp_row = row - 2;
    temp_column = column - 2;
    while (temp_column < size && temp_column >= 0 && temp_row < size && temp_row >= 0 && arr[row - 1][column - 1][round] != ' ' && arr[row - 1][column - 1][round] != turn && arr[temp_row][temp_column][round] != ' ') {
        if (arr[temp_row][temp_column][round] == turn) {
            is_changable = true;
            break;
        }
        temp_row--;
        temp_column--;
    }
    if (is_changable) {
        temp_row = row - 1;
        for (int i = column - 1; i > temp_column; i--) {
            arr[temp_row][i][round] = turn;
            temp_row--;
        }
    }
    is_changable = false;
    temp_row = row - 2;
    temp_column = column + 2;
    while (temp_column < size && temp_column >= 0 && temp_row < size && temp_row >= 0 && arr[row - 1][column + 1][round] != ' ' && arr[row - 1][column + 1][round] != turn && arr[temp_row][temp_column][round] != ' ') {
        if (arr[temp_row][temp_column][round] == turn) {
            is_changable = true;
            break;
        }
        temp_row--;
        temp_column++;
    }
    if (is_changable) {
        temp_row = row - 1;
        for (int i = column + 1; i < temp_column; i++) {
            arr[temp_row][i][round] = turn;
            temp_row--;
        }
    }
    is_changable = false;
    temp_row = row + 2;
    temp_column = column - 2;
    while (temp_column < size && temp_column >= 0 && temp_row < size && temp_row >= 0 && arr[row + 1][column - 1][round] != ' ' && arr[row + 1][column - 1][round] != turn && arr[temp_row][temp_column][round] != ' ') {
        if (arr[temp_row][temp_column][round] == turn) {
            is_changable = true;
            break;
        }
        temp_row++;
        temp_column--;
    }
    if (is_changable) {
        temp_row = row + 1;
        for (int i = column - 1; i > temp_column; i--) {
            arr[temp_row][i][round] = turn;
            temp_row++;
        }
    }
}

void ai_nums(char arr[12][12][141], int size,int &row, int &column, int round, char turn){
    this_thread::sleep_for(chrono::seconds(2));
    int max = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int sum = 0;
            int temp_sum = 1;
            if (arr[i][j][round] == ' ') {
                int temp_row = i + 2;
                int temp_column = j;
                while (temp_row < size && temp_row >= 0 && arr[i + 1][j][round] != ' ' &&
                       arr[i + 1][j][round] != turn && arr[temp_row][j][round] != ' ') {
                    temp_sum ++;
                    if (arr[temp_row][j][round] == turn) {
                        sum += temp_sum;
                        break;
                    }
                    temp_row++;
                }
                temp_sum = 1;
                temp_row = i - 2;
                while (temp_row < size && temp_row >= 0 && arr[i - 1][j][round] != ' ' &&
                       arr[i - 1][j][round] != turn && arr[temp_row][j][round] != ' ') {
                    temp_sum ++;
                    if (arr[temp_row][j][round] == turn) {
                        sum += temp_sum;
                        break;
                    }
                    temp_row--;
                }
                temp_sum = 1;
                temp_column = j + 2;
                while (temp_column < size && temp_column >= 0 && arr[i][j + 1][round] != ' ' &&
                       arr[i][j + 1][round] != turn && arr[i][temp_column][round] != ' ') {
                    temp_sum ++;
                    if (arr[i][temp_column][round] == turn) {
                        sum += temp_sum;
                        break;
                    }
                    temp_column++;
                }
                temp_sum = 1;
                temp_column = j - 2;
                while (temp_column < size && temp_column >= 0 && arr[i][j - 1][round] != ' ' &&
                       arr[i][j - 1][round] != turn && arr[i][temp_column][round] != ' ') {
                    temp_sum ++;
                    if (arr[i][temp_column][round] == turn) {
                        sum += temp_sum;
                        break;
                    }
                    temp_column--;
                }
                temp_sum = 1;
                temp_row = i + 2;
                temp_column = j + 2;
                while (temp_column < size && temp_column >= 0 && temp_row < size && temp_row >= 0 &&
                       arr[i + 1][j + 1][round] != ' ' && arr[i + 1][j + 1][round] != turn &&
                       arr[temp_row][temp_column][round] != ' ') {
                    temp_sum ++;
                    if (arr[temp_row][temp_column][round] == turn) {
                        sum += temp_sum;
                        break;
                    }
                    temp_row++;
                    temp_column++;
                }
                temp_sum = 1;
                temp_row = i - 2;
                temp_column = j - 2;
                while (temp_column < size && temp_column >= 0 && temp_row < size && temp_row >= 0 &&
                       arr[i - 1][j - 1][round] != ' ' && arr[i - 1][j - 1][round] != turn &&
                       arr[temp_row][temp_column][round] != ' ') {
                    temp_sum ++;
                    if (arr[temp_row][temp_column][round] == turn) {
                        sum += temp_sum;
                        break;
                    }
                    temp_row--;
                    temp_column--;
                }
                temp_sum = 1;
                temp_row = i - 2;
                temp_column = j + 2;
                while (temp_column < size && temp_column >= 0 && temp_row < size && temp_row >= 0 &&
                       arr[i - 1][j + 1][round] != ' ' && arr[i - 1][j + 1][round] != turn &&
                       arr[temp_row][temp_column][round] != ' ') {
                    temp_sum ++;
                    if (arr[temp_row][temp_column][round] == turn) {
                        sum += temp_sum;
                        break;
                    }
                    temp_row--;
                    temp_column++;
                }
                temp_sum = 1;
                temp_row = i + 2;
                temp_column = j - 2;
                while (temp_column < size && temp_column >= 0 && temp_row < size && temp_row >= 0 &&
                       arr[i + 1][j - 1][round] != ' ' && arr[i + 1][j - 1][round] != turn &&
                       arr[temp_row][temp_column][round] != ' ') {
                    temp_sum ++;
                    if (arr[temp_row][temp_column][round] == turn) {
                        sum += temp_sum;
                        break;
                    }
                    temp_row++;
                    temp_column--;
                }
                if (sum > max){
                    max = sum;
                    row = i;
                    column = j;
                }
            }
        }
    }
}

void first_spaces(int n) {
    for (int i = 0; i < n; i++) {
        cout << " ";
    }
}

void main_arr(int n, char arr[12][12][141], int menu_num, int spaces, string &name_1, string &name_2, int ai) {
    bool run = true;
    int turn[141];
    turn[0] = 0;
    int space_X = 5;
    int CursorX = 0, CursorY = 0;
    int round = 0;
    bool flag = false;

    if (menu_num == 1){

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < 141; ++k) {
                    arr[i][j][k] = ' ';
                }
            }
        }

        arr[n / 2 - 1][n / 2 - 1][0] = 'X';
        arr[n / 2][n / 2][0] = 'X';
        arr[n / 2][n / 2 - 1][0] = 'O';
        arr[n / 2 - 1][n / 2][0] = 'O';
    }
    else if (menu_num == 2){
        int counter = 0, i = 0, j = 0;
        string temp_1;
        char temp;

        string round_form_save;
        ifstream Read_Loadings("Loading_game.txt"); // Reading From Loading_game.txt
        getline(Read_Loadings, temp_1);// ignoring first line
        while (Read_Loadings.get(temp)){
            if (temp == ' '){
                break;
            }
            round_form_save.append(1, temp);
        }
        turn[round] = stoi(round_form_save);
        while (Read_Loadings.get(temp)){
            if (temp == ' '){
                break;
            }
            name_1.append(1, temp);
        }
        // getline(Read_Loadings, temp_1);// ignoring third line
        while (Read_Loadings.get(temp)){
            if (temp == ' '){
                break;
            }
            name_2.append(1, temp);
        }
        getline(Read_Loadings, temp_1);// ignoring fourth line
        while (Read_Loadings.get(temp)) { // Filling arr and arr_bool
            if (counter >= n){
                counter = counter - n;
                i++;
                j = 0;
            }
            arr[i][j][round] = temp;
            j++;
            counter++;
        }
        Read_Loadings.close();
    }
    bool is_ended = false;
    while(!is_ended) {
        while (run && round < n * n - 4) {
//            system("cls");
            system("clear");
            style_2();
            cout << endl;
            // Printing Scores and Names
            Scores(n, arr, name_1, name_2, spaces, turn[round], round);
            cout << endl;

            string Loding_game; // Used in case 'S'
            int x, y; // Position Of Characters

            first_spaces(spaces);
            for (int z = 0; z < 12 * n; z++) {
                if (z % 12 == 0 and z != 0 and z != 2 * n - 1) {
                    cout << "\u2566"; // '╦'
                } else if (z == 0) {
                    cout << "\u2554"; // '╔'
                } else {
                    if (z == 12 * n - 1) {
                        cout << "\u2550" << "\u2557"; // '═' + '╗'
                    } else {
                        cout << "\u2550"; // '═'
                    }
                }
            }
            cout << endl;
            for (int i = 0; i < n; i++) {
                first_spaces(spaces);
                //....
                for (int j = 0; j <= n; j++) {
                    cout << "\u2551"; // '║'
                    for (int space = 0; space < 2 * space_X + 1; space++) {
                        cout << " ";
                    }
                }
                cout << endl;
                first_spaces(spaces);
                cout << "\u2551"; // '║'
                for (int j = 0; j < n; j++) {
                    if (j == CursorX && i == CursorY) {
                        for (int space = 0; space < space_X; space++) {
                            cout << " ";
                        }
                        if (turn[round] % 2 == 0) {
                            cout << "x";
                        } else {
                            cout << "o";
                        }
                        // Modifying x, y Position
                        x = i;
                        y = j;

                        for (int space = 0; space < space_X; space++) {
                            cout << " ";
                        }
                        cout << "\u2551"; // '║'
                    } else {
                        for (int space = 0; space < space_X; space++) {
                            cout << " ";
                        }
                        if (arr[i][j][round] != '0') {
                            cout << arr[i][j][round];
                        } else {
                            cout << " ";
                        }
                        for (int space = 0; space < space_X; space++) {
                            cout << " ";
                        }
                        cout << "\u2551"; // '║'
                    }
                }

                cout << endl;
                first_spaces(spaces);

                for (int j = 0; j <= n; j++) {
                    cout << "\u2551"; // '║'
                    for (int space = 0; space < 2 * space_X + 1; space++) {
                        cout << " ";
                    }
                }

                cout << endl;
                first_spaces(spaces);

                //....
                for (int z = 0; z < 12 * n; z++) {
                    if (i != n - 1) {
                        if (z % 12 == 0 and z != 0 and z != 2 * n - 1) {
                            cout << "\u256C"; // '╬'
                        } else if (z == 0) {
                            cout << "\u2560"; // '╠'
                        } else {
                            if (z == 12 * n - 1) {
                                cout << "\u2550" << "\u2563"; // '═' + '╣'
                            } else {
                                cout << "\u2550"; // '═'
                            }
                        }
                    } else {
                        if (z % 12 == 0 and z != 0 and z != 2 * n - 1) {
                            cout << "\u2569"; // '╩'
                        } else if (z == 0) {
                            cout << "\u255A"; // '╚'
                        } else {
                            if (z == 12 * n - 1) {
                                cout << "\u2550" << "\u255D"; // '═' + '╝'
                            } else {
                                cout << "\u2550"; // '═'
                            }
                        }
                    }
                }
                cout << endl;
            }
            Help_below_board(n, spaces);

            if (ai == 1) {
                get_input(arr, CursorY, CursorX, n, turn, round, flag, run, x, y, ai, name_1, name_2);
            } else if (ai == 2){
                if (turn[round] % 2 == 0) {
                    get_input(arr, CursorY, CursorX, n, turn, round, flag, run, x, y, ai, name_1, name_2);
                } else {
                    int x_max, y_max;
                    char turnch;
                    if (turn[round] % 2 == 1) {
                        turnch = 'O';
                    } else {
                        turnch = 'X';
                    }
                    ai_nums(arr, n, x_max, y_max, round, turnch);
                    flag = false;
                    round++;
                    for (int i = 0; i < n; ++i) {
                        for (int j = 0; j < n; ++j) {
                            arr[i][j][round] = arr[i][j][round - 1];
                        }
                    }
                    swap(arr, n, x_max, y_max, round, turnch);
                    turn[round] = turn[round - 1] + 1;
                    if (turn[round] % 2 == 1) {
                        turnch = 'O';
                    } else {
                        turnch = 'X';
                    }
                    for (int i = 0; i < n; ++i) {
                        for (int j = 0; j < n; ++j) {
                            if (is_possible(arr, n, i, j, round, turnch)) {
                                flag = true;
                                break;
                            }
                        }
                    }
                    if (!flag) {
                        turn[round]--;
                    }
                }
            }
        }
        int x_num = 0;
        int o_num = 0;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (arr[j][k][round] == 'X') {
                    x_num++;
                } else if (arr[j][k][round] == 'O') {
                    o_num++;
                }
            }
        }
        if (run) {
            if (x_num > o_num) {
                cout << "winner is " << name_1 << endl;
                this_thread::sleep_for(chrono::seconds(5));
                ofstream Rank("Rankings.txt", ios::app);
                Rank << " " << name_1 << " ";
                Rank.close();
            } else if (o_num > x_num) {
                cout << "winner is " << name_2 << endl;
                this_thread::sleep_for(chrono::seconds(5));
                ofstream Rank("Rankings.txt", ios::app);
                Rank << " " << name_2 << " ";
                Rank.close();
//                this_thread::sleep_for(chrono::seconds(5));
            } else {
                cout << "draw";
                this_thread::sleep_for(chrono::seconds(5));
                ofstream Rank("Rankings.txt", ios::app);
                Rank << " " << name_2 << " ";
                Rank.close();
//                this_thread::sleep_for(chrono::seconds(5));
            }
            cout << "You can go to scoreboard with pressing any key or go back to last move with pressing u :";
//            char Undo_after_finishing = getchar();
            is_ended = true;
            if (getchar() == 'u') {
                round--;
                is_ended = false;
            }
            is_ended = true;
        }
    }
    menu_style(arr);
}

void get_input(char arr[12][12][141], int &CursorY, int &CursorX, int n, int turn[], int &round, bool &flag, bool &run, int x, int y, int ai, string &name_1, string &name_2){
    switch (getchar()) {
        case 'w':
            if (CursorY <= 0) {
                break;
            }
            CursorY -= 1;
            break;
        case 's':
            if (CursorY >= n - 1) {
                break;
            }
            CursorY += 1;
            break;
        case 'a':
            if (CursorX <= 0) {
                break;
            }
            CursorX -= 1;
            break;
        case 'd':
            if (CursorX >= n - 1) {
                break;
            }
            CursorX += 1;
            break;
        case 'p': // Put
            char turnch;
            if (turn[round] % 2 == 1) {
                turnch = 'O';
            } else {
                turnch = 'X';
            }
            if (!is_possible(arr, n, x, y, round, turnch)) {
                break;
            } else {
                flag = false;
                round++;
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        arr[i][j][round] = arr[i][j][round - 1];
                    }
                }
                swap(arr, n, x, y, round, turnch);
                turn[round] = turn[round - 1] + 1;
                if (turn[round] % 2 == 1) {
                    turnch = 'O';
                } else {
                    turnch = 'X';
                }
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        if (is_possible(arr, n, i, j, round, turnch)) {
                            flag = true;
                            break;
                        }
                    }
                }
                if (!flag) {
                    turn[round]--;
                }
            }
            break;
        case 'u':
            if (round != 0) {
                round -= ai;
            }
            break;
        case 'e': // Exit
            menu_style(arr);
            run = false;
            break;
        case 'v': { // Save
            cout << "saved!" << endl;
            //                this_thread::sleep_for(chrono::seconds(2));
            ofstream Loading("Loading_game.txt", ios::out);
            Loading << n << endl;
            Loading << turn[round] << " " << name_1 << " " << name_2 << " " << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    Loading << arr[i][j][round];
                }
            }
            Loading.close();
            menu_style(arr);
        }
            run = false;
            break;
        default:
            break;
    }
}

void WELCOME_TO_OTHELLO_STYLE(){
    cout << "                                                                                                                                                                             " << endl;
    cout << "                                                                                                                                                                             " << endl;
    cout << "                          ,--,                                ____              ___                                   ___      ,---,                ,--,    ,--,             " << endl;
    cout << "                        ,--.'|                              ,'  , `.          ,--.'|_                               ,--.'|_  ,--.' |              ,--.'|  ,--.'|             " << endl;
    cout << "         .---.          |  | :               ,---.       ,-+-,.' _ |          |  | :,'   ,---.             ,---.    |  | :,' |  |  :              |  | :  |  | :     ,---.   " << endl;
    cout << "        /. ./|          :  : '              '   ,'\\   ,-+-. ;   , ||          :  : ' :  '   ,'\\           '   ,'\\   :  : ' : :  :  :              :  : '  :  : '    '   ,'\\  " << endl;
    cout << "     .-'-. ' |   ,---.  |  ' |      ,---.  /   /   | ,--.'|'   |  ||        .;__,'  /  /   /   |         /   /   |.;__,'  /  :  |  |,--.   ,---.  |  ' |  |  ' |   /   /   | " << endl;
    cout << "    /___/ \\: |  /     \\ '  | |     /     \\.   ; ,. :|   |  ,', |  |,        |  |   |  .   ; ,. :        .   ; ,. :|  |   |   |  :  '   |  /     \\ '  | |  '  | |  .   ; ,. : " << endl;
    cout << " .-'.. '   ' . /    /  ||  | :    /    / ''   | |: :|   | /  | |--'         :__,'| :  '   | |: :        '   | |: ::__,'| :   |  |   /' : /    /  ||  | :  |  | :  '   | |: : " << endl;
    cout << "/___/ \\:     '.    ' / |'  : |__ .    ' / '   | .; :|   : |  | ,              '  : |__'   | .; :        '   | .; :  '  : |__ '  :  | | |.    ' / |'  : |__'  : |__'   | .; : " << endl;
    cout << ".   \\  ' .\\   '   ;   /||  | '.'|'   ; :__|   :    ||   : |  |/               |  | '.'|   :    |        |   :    |  |  | '.'||  |  ' | :'   ;   /||  | '.'|  | '.'|   :    | " << endl;
    cout << " \\   \\   ' \\ |'   |  / |;  :    ;'   | '.'|\\   \\  / |   | |`-'                ;  :    ;\\   \\  /          \\   \\  /   ;  :    ;|  :  :_:,''   |  / |;  :    ;  :    ;\\   \\  /  " << endl;
    cout << "  \\   \\  |--\" |   :    ||  ,   / |   :    : `----'  |   ;/                    |  ,   /  `----'            `----'    |  ,   / |  | ,'    |   :    ||  ,   /|  ,   /  `----'   " << endl;
    cout << "   \\   \\ |     \\   \\  /  ---`-'   \\   \\  /          '---'                      ---`-'                                ---`-'  `--''       \\   \\  /  ---`-'  ---`-'            " << endl;
    cout << "    '---\"       `----'             `----'                                                                                                 `----'                             " << endl;
    cout << "                                                                                                                                                                             " << endl;
}

void NEW_GAME_STYLE() {
    first_spaces(75);
    cout << "  __     _   _                  _____                      " << endl;
    first_spaces(75);
    cout << " /_ |   | \\ | |                / ____|                     " << endl;
    first_spaces(75);
    cout << "  | |   |  \\| | _____      __ | |  __  __ _ _ __ ___   ___ " << endl;
    first_spaces(75);
    cout << "  | |   | . ` |/ _ \\ \\ /\\ / / | | |_ |/ _` | '_ ` _ \\ / _ \\" << endl;
    first_spaces(75);
    cout << "  | |_  | |\\  |  __/\\ V  V /  | |__| | (_| | | | | | |  __/" << endl;
    first_spaces(75);
    cout << "  |_(_) |_| \\_|\\___| \\_/\\_/    \\_____|\\__,_|_| |_| |_|\\___|" << endl;
    first_spaces(75);
    cout << "                                                           " << endl;
    first_spaces(75);
    cout << "                                                           " << endl;
    first_spaces(75);
}

void LOAD_GAME_STYLE() {
    cout << "  ___      _                     _    _____                      " << endl;
    first_spaces(75);
    cout << " |__ \\    | |                   | |  / ____|                     " << endl;
    first_spaces(75);
    cout << "    ) |   | |     ___   __ _  __| | | |  __  __ _ _ __ ___   ___ " << endl;
    first_spaces(75);
    cout << "   / /    | |    / _ \\ / _` |/ _` | | | |_ |/ _` | '_ ` _ \\ / _ \\" << endl;
    first_spaces(75);
    cout << "  / /_ _  | |___| (_) | (_| | (_| | | |__| | (_| | | | | | |  __/" << endl;
    first_spaces(75);
    cout << " |____(_) |______\\___/ \\__,_|\\__,_|  \\_____|\\__,_|_| |_| |_|\\___|" << endl;
    first_spaces(75);
    cout << "                                                                 " << endl;
    first_spaces(75);
}

void RANKING_STYLE() {
    cout << "  ____     _____             _    _             " << endl;
    first_spaces(75);
    cout << " |___ \\   |  __ \\           | |  (_)            " << endl;
    first_spaces(75);
    cout << "   __) |  | |__) |__ _ _ __ | | ___ _ __   __ _ " << endl;
    first_spaces(75);
    cout << "  |__ <   |  _  // _` | '_ \\| |/ | | '_ \\ / _` |" << endl;
    first_spaces(75);
    cout << "  ___) _  | | \\ | (_| | | | |   <| | | | | (_| |" << endl;
    first_spaces(75);
    cout << " |____(_) |_|  \\_\\__,_|_| |_|_|\\_|_|_| |_|\\__, |" << endl;
    first_spaces(75);
    cout << "                                           __/ |" << endl;
    first_spaces(75);
    cout << "                                          |___/ " << endl;
    first_spaces(75);
}

void EXIT_STYLE() {
    cout << "  _  _     ______      _ _   " << endl;
    first_spaces(75);
    cout << " | || |   |  ____|    (_| |  " << endl;
    first_spaces(75);
    cout << " | || |_  | |__  __  ___| |_ " << endl;
    first_spaces(75);
    cout << " |__   _| |  __| \\ \\/ | | __|" << endl;
    first_spaces(75);
    cout << "    | |_  | |____ >  <| | |_ " << endl;
    first_spaces(75);
    cout << "    |_(_) |______/_/\\_|_|\\__|" << endl;
    first_spaces(75);
    cout << "                             " << endl;
    first_spaces(75);
    cout << "                             " << endl;
    first_spaces(75);
}

void style_2(){
    first_spaces(40);
    cout << "         _______               _____                    _____                    _____                    _____            _____           _______         " << endl;    first_spaces(40);
    cout << "        /::\\    \\             /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\          /\\    \\         /::\\    \\        " << endl;    first_spaces(40);
    cout << "       /::::\\    \\           /::\\    \\                /::\\____\\                /::\\    \\                /::\\____\\        /::\\____\\       /::::\\    \\       " << endl;    first_spaces(40);
    cout << "      /::::::\\    \\          \\:::\\    \\              /:::/    /               /::::\\    \\              /:::/    /       /:::/    /      /::::::\\    \\      " << endl;    first_spaces(40);
    cout << "     /::::::::\\    \\          \\:::\\    \\            /:::/    /               /::::::\\    \\            /:::/    /       /:::/    /      /::::::::\\    \\     " << endl;    first_spaces(40);
    cout << "    /:::/~~\\:::\\    \\          \\:::\\    \\          /:::/    /               /:::/\\:::\\    \\          /:::/    /       /:::/    /      /:::/~~\\:::\\    \\    " << endl;    first_spaces(40);
    cout << "   /:::/    \\:::\\    \\          \\:::\\    \\        /:::/____/               /:::/__\\:::\\    \\        /:::/    /       /:::/    /      /:::/    \\:::\\    \\   " << endl;    first_spaces(40);
    cout << "  /:::/    / \\:::\\    \\         /::::\\    \\      /::::\\    \\              /::::\\   \\:::\\    \\      /:::/    /       /:::/    /      /:::/    / \\:::\\    \\  " << endl;    first_spaces(40);
    cout << " /:::/____/   \\:::\\____\\       /::::::\\    \\    /::::::\\    \\   _____    /::::::\\   \\:::\\    \\    /:::/    /       /:::/    /      /:::/____/   \\:::\\____\\ " << endl;    first_spaces(40);
    cout << "|:::|    |     |:::|    |     /:::/\\:::\\    \\  /:::/\\:::\\    \\ /\\    \\  /:::/\\:::\\   \\:::\\    \\  /:::/    /       /:::/    /      |:::|    |     |:::|    |" << endl;    first_spaces(40);
    cout << "|:::|____|     |:::|    |    /:::/  \\:::\\____\\/:::/  \\:::\\    /::\\____\\/:::/__\\:::\\   \\:::\\____\\/:::/____/       /:::/____/       |:::|____|     |:::|    |" << endl;    first_spaces(40);
    cout << " \\:::\\    \\   /:::/    /    /:::/    \\::/    /\\::/    \\:::\\  /:::/    /\\:::\\   \\:::\\   \\::/    /\\:::\\    \\       \\:::\\    \\        \\:::\\    \\   /:::/    / " << endl;    first_spaces(40);
    cout << "  \\:::\\    \\ /:::/    /    /:::/    / \\/____/  \\/____/ \\:::\\/:::/    /  \\:::\\   \\:::\\   \\/____/  \\:::\\    \\       \\:::\\    \\        \\:::\\    \\ /:::/    /  " << endl;    first_spaces(40);
    cout << "   \\:::\\    /:::/    /    /:::/    /                    \\::::::/    /    \\:::\\   \\:::\\    \\       \\:::\\    \\       \\:::\\    \\        \\:::\\    /:::/    /   " << endl;    first_spaces(40);
    cout << "    \\:::\\__/:::/    /    /:::/    /                      \\::::/    /      \\:::\\   \\:::\\____\\       \\:::\\    \\       \\:::\\    \\        \\:::\\__/:::/    /    " << endl;    first_spaces(40);
    cout << "     \\::::::::/    /     \\::/    /                       /:::/    /        \\:::\\   \\::/    /        \\:::\\    \\       \\:::\\    \\        \\::::::::/    /     " << endl;    first_spaces(40);
    cout << "      \\::::::/    /       \\/____/                       /:::/    /          \\:::\\   \\/____/          \\:::\\    \\       \\:::\\    \\        \\::::::/    /      " << endl;    first_spaces(40);
    cout << "       \\::::/    /                                     /:::/    /            \\:::\\    \\               \\:::\\    \\       \\:::\\    \\        \\::::/    /       " << endl;    first_spaces(40);
    cout << "        \\::/____/                                     /:::/    /              \\:::\\____\\               \\:::\\____\\       \\:::\\____\\        \\::/____/        " << endl;    first_spaces(40);
    cout << "         ~~                                           \\::/    /                \\::/    /                \\::/    /        \\::/    /         ~~              " << endl;    first_spaces(40);
    cout << "                                                       \\/____/                  \\/____/                  \\/____/          \\/____/                          " << endl;    first_spaces(40);
    cout << "                                                                                                                                                           " << endl;
}

void Help_below_board(int n, int spaces){
    cout << endl;
    first_spaces(spaces - 20);
    for (int i = 0; i < 7 * 1.5 * n + 54; i++){
        cout << "\u2500";
    }
    cout << endl;
    first_spaces(spaces - 20);
    cout << "Exit: e";
    first_spaces(1.5 * n);
    cout << "Save: v";
    first_spaces(1.5 * n);
    cout << "Undo: U";
    first_spaces(1.5 * n);
    cout << "Up: w";
    first_spaces(1.5 * n);
    cout << "Left: a";
    first_spaces(1.5 * n);
    cout << "Down: s";
    first_spaces(1.5 * n);
    cout << "Right: d";
    first_spaces(1.5 * n);
    cout << "Put: p";
    cout << endl;
}

void Scores(int n, char arr[12][12][141], string &a, string &b, int spaces, int turn, int round){
    int x_num = 0, o_num = 0;

    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
            if (arr[j][k][round] == 'X') {
                x_num++;
            } else if (arr[j][k][round] == 'O') {
                o_num++;
            }
        }
    }

    first_spaces(spaces);
    cout << "Player 1: " << a;
    first_spaces(3 * n);
    cout << "Symbol: X";
    first_spaces(3 * n);
    cout << "Pieces: " << x_num << endl << endl ;


    first_spaces(spaces);
    cout << "Player 2: " << b;
    first_spaces(3 * n);
    cout << "Symbol: O";
    first_spaces(3 * n);
    cout << "Pieces: " << o_num << endl << endl;


    first_spaces(spaces + 6 * n - 3);

    if (turn % 2 == 0){
        cout << "Turn: " << a; // Turn X
    }
    else{
        cout << "Turn: " << b; // Turn O
    }
}

void menu_style(char arr[12][12][141]) {
    int menu_num;
    int spaces;
    int n;
    string name_1, name_2;

//    system("cls");
    system("clear");
    WELCOME_TO_OTHELLO_STYLE();
    cout << endl;
    first_spaces(75);
    cout << "Created by Aryan & Mehdi" << endl;
//    this_thread::sleep_for(chrono::seconds(5));
//    system("cls");
    system("clear");

    NEW_GAME_STYLE();
    LOAD_GAME_STYLE();
    RANKING_STYLE();
    EXIT_STYLE();

    cin >> menu_num;
//    first_spaces(75);
    if (menu_num == 1) {
        first_spaces(75);
        cout << "play with someone else : 1" << endl;
        first_spaces(75);
        cout <<"play with computer : 2" << endl;
        first_spaces(75);
        int ai;
        cin >> ai;
        if(ai == 2) {
            first_spaces(75);
            cout << "name 1: ";
            cin >> name_1;
            name_2 = "computer";
            cout << endl;
        }
        else if (ai == 1){
            first_spaces(75);
            cout << "name 1: ";
            cin >> name_1;
            first_spaces(75);
            cout << "name 2: ";
            cin >> name_2;
        }
        else{
            while (ai != 2 and ai != 1) {
                first_spaces(75);
                cout << "1 or 2 :/" << endl;
                first_spaces(75);
                cout << "play with someone else : 1" << endl;
                first_spaces(75);
                cout << "play with computer : 2" << endl;
                first_spaces(75);
                cin >> ai;
                cout << endl;
            }
            if(ai == 2) {
                first_spaces(75);
                cout << "name 1: ";
                cin >> name_1;
                first_spaces(75);
                name_2 = "computer";
            }
            else if (ai == 1){
                first_spaces(75);
                cout << "name 1: ";
                cin >> name_1;
                first_spaces(75);
                cout << "name 2: ";
                cin >> name_2;
            }
        }
        n = get_size();
        if (n == 4) {
            spaces = 90;
        } else if (n == 6) {
            spaces = 80;
        } else if (n == 8) {
            spaces = 70;
        } else if (n == 10) {
            spaces = 60;
        } else if (n == 12) {
            spaces = 50;
        }
        //...
        main_arr(n, arr, menu_num, spaces, name_1, name_2, ai);
    } else if (menu_num == 2) {
        string temp;

        ifstream Read_Loadings("Loading_game.txt");
        while (getline (Read_Loadings, temp)) {
            n = stoi(temp);
            break;
        }


        if (n == 4) {
            spaces = 90;
        } else if (n == 6) {
            spaces = 80;
        } else if (n == 8) {
            spaces = 70;
        } else if (n == 10) {
            spaces = 60;
        } else if (n == 12) {
            spaces = 50;
        }
        main_arr(n, arr, menu_num, spaces, name_1, name_2, 1);
        //        load(arr);
    }
    else if (menu_num == 3){
        Rankings();
    }
}

void Rankings(){
    string a;
    string b;
    ifstream read("Rankings.txt");
    while (getline (read, b)) {
        a.append(b);
    }

    read.close();
    int n = 0;
    string *arr = new string[n];

    string temp = "";
    for (int i = 0; i < a.size(); i++){
        if (i == a.size() - 1){
            temp.append(1, a[i]);
            arr[n] = temp;
            break;
        }
        if (a[i] == ' '){
            arr[n] = temp;
            n++;
            temp = "";
            continue;
        }
        temp.append(1, a[i]);
    }

    n += 1;

    counter(arr, n);
}

void counter(string *arr, int n){
    int c[n];
    for (int i = 0; i < n; i++){
        c[i] = 1;
    }

    for (int i = 0; i < n; i++){
        if (i != n - 1) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i] == " ") {
                    c[i] = 0;
                    continue;
                } else if (arr[i] == arr[j]) {
                    arr[j] = " ";
                    c[i]++;
                }
            }
        }
        else{
            if (arr[i] == " "){
                c[i] = 0;
            }
            else{
                c[i] = 1;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (arr[i] == " "){
            continue;
        }
        else{
            first_spaces(75);
            cout << arr[i] << " " << c[i] << endl;
        }
    }
}