#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

double linear_activation(double x) {
    return x;
}

double random_weight() {
    return ((double)rand() / RAND_MAX) * 2.0 - 1.0;
}

void generate_dataset(vector<vector<double>>& inputs, vector<double>& targets, vector<double>& true_weights, int n, int samples = 10) {
    double bias = 5.0;
    true_weights.resize(n);
    for (int i = 0; i < n; i++) {
        true_weights[i] = random_weight();
    }

    for (int i = 0; i < samples; i++) {
        vector<double> sample(n);
        double y = bias;
        for (int j = 0; j < n; j++) {
            sample[j] = (double)rand() / RAND_MAX;
            y += true_weights[j] * sample[j];
        }
        inputs.push_back(sample);
        targets.push_back(y);
    }
}

void train_linear_perceptron(int n) {
    vector<vector<double>> inputs;
    vector<double> targets;
    vector<double> true_weights;
    generate_dataset(inputs, targets, true_weights, n);

    vector<double> weights(n, 0.0);
    double bias = 0.0;
    double learning_rate = 0.01;
    int epochs = 100;
    int samples = inputs.size();

    for (int epoch = 0; epoch < epochs; epoch++) {
        double mse = 0.0;
        for (int i = 0; i < samples; i++) {
            double prediction = bias;
            for (int j = 0; j < n; j++) {
                prediction += weights[j] * inputs[i][j];
            }
            double error = targets[i] - prediction;
            mse += error * error;

            for (int j = 0; j < n; j++) {
                weights[j] += learning_rate * error * inputs[i][j];
            }
            bias += learning_rate * error;
        }
        mse /= samples;
        cout << "Epoch " << epoch + 1 << " - MSE: " << mse << endl;
    }

    cout << "\nFinal Weights for n = " << n << ": ";
    for (double w : weights) cout << w << " ";
    cout << "\nFinal Bias: " << bias << endl;
}

int main() {
    srand(time(0));
    train_linear_perceptron(4);
    train_linear_perceptron(5);
    return 0;
}
