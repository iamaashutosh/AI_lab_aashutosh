#include<iostream>
#include<cmath>
using namespace std;

double sigmoid(double x){
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1 - x); 
}

int main()
{
    double inputs[4][2]={{0,0},{0,1},{1,0},{1,1}};
    double y[4]={0,1,1,0};

    double w1 = 0.34, w2 = 0.5;
    double w3 = 0.5, w4 = 0.69;
    double b1 = 0.3, b2 = 0.44;

    double w5 = 0.5, w6 = 0.5, b3 = 0.1;

    double learning_rate = 0.1;
    int epochs = 10009;

    for(int epoch=0; epoch<epochs; epoch++)
    {
        for(int i=0; i<4; i++)
        {
            double x1 = inputs[i][0];
            double x2 = inputs[i][1];

            // Forward pass
            double z1 = x1*w1 + x2*w2 + b1;
            double h1 = sigmoid(z1);

            double z2 = x1*w3 + x2*w4 + b2;
            double h2 = sigmoid(z2);

            double op = h1*w5 + h2*w6 + b3;
            double yhat = sigmoid(op);

            // Error
            double dL = yhat - y[i];
            double dyhat = yhat * (1 - yhat);

            // Output layer gradients
            double d5 = dL * dyhat * h1;
            double d6 = dL * dyhat * h2;
            double db3 = dL * dyhat;

            // Update output weights and bias
            w5 -= learning_rate * d5;
            w6 -= learning_rate * d6;
            b3 -= learning_rate * db3;

            // Hidden layer gradients (backprop from output layer)
            double dh1 = dL * dyhat * w5 * sigmoid_derivative(h1);
            double dh2 = dL * dyhat * w6 * sigmoid_derivative(h2);

            // Update hidden weights and biases
            w1 -= learning_rate * dh1 * x1;
            w2 -= learning_rate * dh1 * x2;
            b1 -= learning_rate * dh1;

            w3 -= learning_rate * dh2 * x1;
            w4 -= learning_rate * dh2 * x2;
            b2 -= learning_rate * dh2;
        }
    }

    // Test the trained network
    cout << "\nTrained XOR Neural Network:\n";
    for(int i = 0; i < 4; i++) {
        double x1 = inputs[i][0];
        double x2 = inputs[i][1];

        double z1 = x1*w1 + x2*w2 + b1;
        double h1 = sigmoid(z1);

        double z2 = x1*w3 + x2*w4 + b2;
        double h2 = sigmoid(z2);

        double op = h1*w5 + h2*w6 + b3;
        double yhat = sigmoid(op);

        cout << "Input: [" << x1 << ", " << x2 << "] -> Predicted: " << (yhat > 0.5 ? 1 : 0) << " (" << yhat << ")\n";
    }

    return 0;
}
