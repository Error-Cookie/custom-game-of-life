#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <fstream>
#include <chrono>
#include <thread>

#define FIRST 0
#define LAST 4
#define W 12
#define H 10
#define sleep(x) this_thread::sleep_for(chrono::milliseconds(x));
//# - dead
//0 - alive
//1 - permanent
//2 - toxic
//3 - generator
//4 - exploding

using namespace std;

int generation = 0;
char map[H][W];

void printMap() {
    cout << generation << endl;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cout << map[i][j];
        }
        cout << endl;
    }
    cout << endl;
    return;
}

void buildMap(vector<tuple<int, int, int>>& blocks) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            map[i][j] = '#';
        }
    }
    for (int i = 0; i < blocks.size(); i++) {
        map[get<0>(blocks[i])][get<1>(blocks[i])] = get<2>(blocks[i]) + 48;
    }
    return;
}

void getInput() {
    int blocks;
    vector<tuple<int, int, int>> blockmap;
    ifstream input("input.txt");

    input >> blocks;
    for (int i = 0; i < blocks; i++) {
        tuple<int, int, int> block;
        input >> get<0>(block) >> get<1>(block) >> get<2>(block);
        if (get<0>(block) - 1 < W && get<1>(block) - 1 < H && (get<2>(block) <= LAST && get<2>(block) >= FIRST)) blockmap.push_back(block);
        else {
            i--;
            cout << "Not a valid block coordinate or type." << endl;
        }
    }

    buildMap(blockmap);
    return;
}

void copyMap(char tmp_map[H][W]) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            tmp_map[i][j] = map[i][j];
        }
    }
}

bool nextGeneration() {
    char tmp_map[H][W];
    copyMap(tmp_map);
    vector<pair<int, int>> bombs;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (tmp_map[i][j] == '1') continue;
            if (tmp_map[i][j] == '2') {
                for (int k = ((i == 0) ? 0 : -1); k < ((i == H-1) ? 1 : 2); k++) {
                    for (int l = ((j == 0) ? 0 : -1); l < ((j == W-1) ? 1 : 2); l++) {
                        if (!(k == 0 && l == 0) && tmp_map[i+k][j+l] == '0') map[i+k][j+l] = '#';
                    }
                }
                continue;
            }
            if (tmp_map[i][j] == '3') {
                srand(time(NULL));
                int direction = rand() % 8;
                if (direction != 4) map[i-1+(direction/3)][j-1+(direction%3)] = '0';
                continue;
            }
            if (tmp_map[i][j] == '4') {
                bombs.push_back({i, j});
                continue;
            }
            int living = 0;
            for (int k = ((i == 0) ? 0 : -1); k < ((i == H-1) ? 1 : 2); k++) {
                for (int l = ((j == 0) ? 0 : -1); l < ((j == W-1) ? 1 : 2); l++) {
                    if (!(k == 0 && l == 0) && tmp_map[i+k][j+l] != '#') living++;
                }
            }
            if (living < 2) map[i][j] = '#';
            else if (living == 3) map[i][j] = '0';
            else if (living == 8) map[i][j] = '4';
            else if (living > 3) map[i][j] = '#';
        }
    }
    for (int i = 0; i < bombs.size(); i++) {
        for (int k = ((bombs[i].first == 0) ? 0 : -1); k < ((bombs[i].first == H-1) ? 1 : 2); k++) {
                for (int l = ((bombs[i].second == 0) ? 0 : -1); l < ((bombs[i].second == W-1) ? 1 : 2); l++) {
                    if (tmp_map[bombs[i].first+k][bombs[i].second+l] == '0' || tmp_map[bombs[i].first+k][bombs[i].second+l] == '4') map[bombs[i].first+k][bombs[i].second+l] = '#';
                }
            }
    }
    generation++;
    return true;
}

int main() {
    getInput();
    printMap();
    while (nextGeneration()) {
        printMap();
        sleep(500);
    }
    return 0;
}