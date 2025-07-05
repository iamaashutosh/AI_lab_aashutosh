#include<iostream>

using namespace std;


int step_function(double x)
{
    return (x >=0?1:0);
}
int main()
{
    double weights[2] = {0.5,1.0};
    double bias = -0.7;

    double inputs[4][2] = {
        {0,0},
        {0,1},
        {1,0},
        {1,1}
    };

    double exp_outputs[4] = {0,0,0,1};

    int epochs = 10;
    double learning_rate = 0.1;

    for(int epoch =0; epoch<epochs; epoch++)
    {
        cout<<"Epoch:"<<epoch+1<<"\n";
        for(int i=0; i<4; i++)
        {
            double sum = weights[0]*inputs[i][0] + weights[1]*inputs[i][1] + bias;

            int output = step_function(sum);
            int error = exp_outputs[i] - output;

            
            weights[0] += learning_rate * error* inputs[i][0];
            weights[1] += learning_rate * error* inputs[i][1];
            bias += learning_rate * error;

            cout<<"Inputs:["<<inputs[i][0]<<","<<inputs[i][1]<<"], Output:["<<output<<"], expected :"<<exp_outputs[i]<<", error:"<<error<<"\n";

        }
        cout<<"\nWeights:["<<weights[0]<<","<<weights[1]<<"]\nBias:"<<bias<<"\n\n\n";
    }
}