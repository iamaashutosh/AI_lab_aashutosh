#include<iostream>

using namespace std;


int step_function(double x)
{
    return (x >=0? 1: 0);
}
int main()
{
    double inputs[4][2] = {
        {0,0},{0,1},{1,0},{1,1}
    };

    double weights[2] = {0.5,0.5};
    double bias = 0.2;

    double expected[4] = {0,1,1,1,};

    double learning_rate = 0.1;

    int epochs = 10;

    for(int epoch=0; epoch<epochs; epoch++)
    {
        cout <<"Epoch "<<epoch+1<<":\n";
        for(int i=0; i<4; i++)
        {
            double sum = weights[0] * inputs[i][0]+weights[1]*inputs[i][1]+bias;
            int output = step_function(sum);
            int error = expected[i] - output;

            weights[0] += learning_rate * error * inputs[i][0];
            weights[1] += learning_rate * error * inputs[i][1];
            bias += learning_rate*error;

            cout <<"Input:["<<inputs[i][0]<<", "<<inputs[i][1]<<"], Output: "<<output<<", Expected: "<<expected[i]<<", Error: "<<error<<"\n";
        }
        cout <<"Weights: ["<<weights[0]<<", "<<weights[1]<<"], Bias: "<<bias<<"\n\n";
    }
    return 0;
}