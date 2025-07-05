#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

// Linear activation (identity)
double linear_activation(double x) {
    return x;
}

// Generate dataset (x1, x2, x3) and target y = 2x1 + 3x2 - x3 + 5
void generate_dataset(vector<vector<double>>& inputs, vector<double>& targets, int samples) {
    srand(time(0));
    for (int i = 0; i < samples; i++) {
        double x1 = (double)rand() / RAND_MAX;
        double x2 = (double)rand() / RAND_MAX;
        double x3 = (double)rand() / RAND_MAX;
        double y = 2 * x1 + 3 * x2 - 1 * x3 + 5;
        inputs.push_back({x1, x2, x3});
        targets.push_back(y);
    }
}

void train_linear_function() {
    const int features = 3;
    const int samples = 10;
    vector<vector<double>> inputs;
    vector<double> targets;
    generate_dataset(inputs, targets, samples);

    vector<double> weights(features, 0.0);
    double bias = 0.0;
    double learning_rate = 0.01;
    int epochs = 100;

    for (int epoch = 0; epoch < epochs; epoch++) {
        double mse = 0.0;
        for (int i = 0; i < samples; i++) {
            double prediction = bias;
            for (int j = 0; j < features; j++) {
                prediction += weights[j] * inputs[i][j];
            }
            double error = targets[i] - prediction;
            mse += error * error;

            // Update weights and bias
            for (int j = 0; j < features; j++) {
                weights[j] += learning_rate * error * inputs[i][j];
            }
            bias += learning_rate * error;
        }
        mse /= samples;
        cout << "Epoch " << epoch + 1 << " - MSE: " << mse << endl;
    }

    cout << "\nFinal Weights: ";
    for (double w : weights) cout << w << " ";
    cout << "\nFinal Bias: " << bias << endl;
}

int main() {
    train_linear_function();
    return 0;
}
