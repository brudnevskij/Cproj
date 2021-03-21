
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
