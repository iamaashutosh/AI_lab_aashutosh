#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int heuristic(const vector<char>& state) {
    vector<char> goal = {'A', 'B', 'C', 'D'};
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        if (state[i] != goal[i])
            count++;
    }
    return count;
}

void printStack(const vector<char>& stack) {
    for (char c : stack)
        cout << c << " ";
    cout << endl;
}

void printMove(int i, int j, const vector<char>& newStack, int h) {
    cout << "Swapped index " << i << " and " << j << ": ";
    printStack(newStack);
    cout << "Heuristic: " << h << "\n\n";
}

void hillClimb(vector<char> initial) {
    cout << "Initial stack:\n";
    printStack(initial);
    int current_h = heuristic(initial);
    cout << "Initial Heuristic: " << current_h << "\n\n";

    vector<string> moveHistory;
    while (true) {
        vector<char> bestState = initial;
        int bestH = current_h;
        bool improved = false;

        for (int i = 0; i < 3; ++i) {
            vector<char> temp = initial;
            swap(temp[i], temp[i + 1]);
            int h = heuristic(temp);
            printMove(i, i + 1, temp, h);

            if (h < bestH) {
                bestH = h;
                bestState = temp;
                improved = true;
            }
        }

        if (!improved) {
            cout << "No better neighbors. Algorithm stuck in local minimum.\n";
            break;
        }

        initial = bestState;
        current_h = bestH;

        cout << "Moved to better state:\n";
        printStack(initial);
        cout << "Updated Heuristic: " << current_h << "\n\n";

        if (current_h == 0) {
            cout << "Goal reached!\n";
            break;
        }
    }
}

int main() {
    vector<char> initial = {'C', 'A', 'D', 'B'};
    hillClimb(initial);
    return 0;
}
