#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int step_function(double x) {
    return x >= 0 ? 1 : 0;
}

vector<vector<int>> generate_truth_table(int n) {
    vector<vector<int>> table;
    int total = pow(2, n);
    for (int i = 0; i < total; i++) {
        vector<int> row(n);
        for (int j = 0; j < n; j++) {
            row[j] = (i >> (n - j - 1)) & 1;
        }
        table.push_back(row);
    }
    return table;
}

vector<int> generate_or_targets(const vector<vector<int>>& inputs) {
    vector<int> targets;
    for (auto input : inputs) {
        int result = 0;
        for (int x : input) result |= x;
        targets.push_back(result);
    }
    return targets;
}

void train_or_gate(int n) {
    vector<vector<int>> inputs = generate_truth_table(n);
    vector<int> targets = generate_or_targets(inputs);

    vector<double> weights(n, 0.0);
    double bias = 0.0;
    double learning_rate = 0.1;
    int epochs = 100;

    for (int epoch = 0; epoch < epochs; epoch++) {
        int correct = 0;
        cout << "\nEpoch " << epoch + 1 << ":\n";
        for (size_t i = 0; i < inputs.size(); i++) {
            double sum = bias;
            for (int j = 0; j < n; j++) {
                sum += weights[j] * inputs[i][j];
            }
            int output = step_function(sum);
            int error = targets[i] - output;

            cout << "Input: [";
            for (int x : inputs[i]) cout << x << " ";
            cout << "] Output: " << output << " Expected: " << targets[i] << " Error: " << error << "\n";

            if (error == 0) correct++;

            for (int j = 0; j < n; j++) {
                weights[j] += learning_rate * error * inputs[i][j];
            }
            bias += learning_rate * error;
        }
        cout << "Weights: ";
        for (double w : weights) cout << w << " ";
        cout << " Bias: " << bias << "\n";
    }

    int correct = 0;
    for (size_t i = 0; i < inputs.size(); i++) {
        double sum = bias;
        for (int j = 0; j < n; j++) {
            sum += weights[j] * inputs[i][j];
        }
        int output = step_function(sum);
        if (output == targets[i]) correct++;
    }
    double accuracy = (double)correct / inputs.size() * 100.0;

    cout << "\nOR Gate with n = " << n << endl;
    cout << "Final Weights: ";
    for (double w : weights) cout << w << " ";
    cout << "\nFinal Bias: " << bias;
    cout << "\nAccuracy: " << accuracy << "%\n";
}

int main() {
    train_or_gate(3);
    train_or_gate(4);
    return 0;
}
