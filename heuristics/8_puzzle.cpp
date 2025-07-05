#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

const vector<vector<int>> GOAL = {{1,2,3},{4,5,6},{7,8,0}};
const vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
const vector<string> moveNames = {"up", "down", "left", "right"};

struct State {
    vector<vector<int>> board;
    string path;

    string serialize() const {
        string s;
        for (const auto& row : board)
            for (int val : row)
                s += to_string(val);
        return s;
    }

    pair<int,int> findZero() const {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (board[i][j] == 0)
                    return {i, j};
        return {-1, -1};
    }
};

int manhattanDistance(const vector<vector<int>>& board) {
    int dist = 0;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] != 0) {
                int val = board[i][j] - 1;
                int goalRow = val / 3;
                int goalCol = val % 3;
                dist += abs(i - goalRow) + abs(j - goalCol);
            }
    return dist;
}

bool isGoal(const vector<vector<int>>& board) {
    return board == GOAL;
}

void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int val : row)
            cout << val << " ";
        cout << "\n";
    }
}

void solvePuzzle(vector<vector<int>> startBoard) {
    cout << "Initial State:\n";
    printBoard(startBoard);
    cout << "Heuristic: " << manhattanDistance(startBoard) << "\n\n";

    queue<State> q;
    set<string> visited;

    q.push({startBoard, ""});
    visited.insert(State{startBoard, ""}.serialize());

    while (!q.empty()) {
        State current = q.front(); q.pop();

        if (isGoal(current.board)) {
            cout << "Goal reached!\n";
            cout << "Solution Path: " << current.path << "\n";
            cout << "Number of Moves: " << current.path.size() << "\n";
            return;
        }

        auto [x, y] = current.findZero();

        for (int d = 0; d < 4; ++d) {
            int nx = x + directions[d].first;
            int ny = y + directions[d].second;

            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                vector<vector<int>> newBoard = current.board;
                swap(newBoard[x][y], newBoard[nx][ny]);

                string key = State{newBoard, ""}.serialize();
                if (visited.count(key)) continue;

                int h = manhattanDistance(newBoard);
                cout << "State:\n";
                printBoard(newBoard);
                cout << "Heuristic: " << h << "\n\n";

                visited.insert(key);
                q.push({newBoard, current.path + moveNames[d] + " "});
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    vector<vector<int>> initial = {
        {1, 2, 3},
        {4, 0, 5},
        {7, 8, 6}
    };

    solvePuzzle(initial);
    return 0;
}
