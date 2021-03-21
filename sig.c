
#include "sig.h"
#include <math.h>


float sigmoid(float x){
    float result;

    result = 1/(1+expf(-x));
    return result;
}


float sigder(float x){
    float result;
    result = sigmoid(x)*(1 - sigmoid(x));
    return result;

}
void trainer (double trinput[][3], double troutput[], int q, double weights[3])
    {

        double output[4];
        double error[4];
        double tranput[3][4];
        for (int i = 0; i < q; i++)
        {
            //thinktrain
            output[0] = sigmoid(dotproduct(trinput[0], weights, 3));
            output[1] = sigmoid(dotproduct(trinput[1], weights, 3));
            output[2] = sigmoid(dotproduct(trinput[2], weights, 3));
            output[3] = sigmoid(dotproduct(trinput[3], weights, 3));
            //thinktrain ---> error
            error[0]=(troutput[0]- output[0])*sigder(output[0]);
            error[1]=(troutput[1]- output[1])*sigder(output[1]);
            error[2]=(troutput[2]- output[2])*sigder(output[2]);
            error[3]=(troutput[3]- output[3])*sigder(output[3]);
            //errors ---> transpose
            for(int j = 0; j<3; j++)
            {
                for(int y = 0; y<4; y++){
                    tranput[j][y] = trinput[y][j];
                }
            }
            //transpose ---> adjustments
            weights[0] += dotproduct(tranput[0], error, 4);
            weights[1] += dotproduct(tranput[1], error, 4);
            weights[2] += dotproduct(tranput[2], error, 4);
        }
        
    }

double dotproduct( double *v1, double *v2, int size){
    double result = 0;

    for (int i = 0; i < size; i++)
    {
        result+= v1[i]*v2[i];
    }
    return result;
    
}

double think_an(double input[], double weights[3]){
    double result = dotproduct(input, weights, 3);
    return sigmoid(result);
}