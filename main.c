#include "sig.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
double weights[3];

double dotproduct( double *v1, double *v2, int size){
    double result = 0;

    for (int i = 0; i < size; i++)
    {
        result+= v1[i]*v2[i];
    }
    return result;
    
}

void trainer (double trinput[][3], double troutput[], int q)
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

double think_an(double input[]){
    double result = dotproduct(input, weights, 3);
    return sigmoid(result);
}


int main (int argc, char *argv[]){
   srand(time(NULL));
    int header[374] = {// info header 14 bytes//
                0x42, 0x4d, //"BM"
                0x06, 0x17, 0x00, 0x00, //size of whole file in bytes
                0x00, 0x00, //reserved bytes
                0x00, 0x00, // reserved bytes
                0x36, 0x00, 0x00, 0x00, // starting addres of pixel array
                    
                //dib header 40 bytes//
                0x28, 0x00, 0x00, 0x00, // size of header
                0x0a, 0x00, 0x00, 0x00, // bitmap w, px
                0x0a, 0x00, 0x00, 0x00, // bitmap h, px
                0x01, 0x00, // number of color planes must be 1
                0x18, 0x00, // number of bits per px
                0x00, 0x00, 0x00, 0x00, // compression method
                0x00, 0x14, 0x00, 0x00, // image size
                0x00, 0x00, 0x00, 0x00,// horizontal resol
                0x00, 0x00, 0x00, 0x00, // vertical resol
                0x00, 0x00, 0x00, 0x00, // numbers of colours in colour palette
                0x00, 0x00, 0x00, 0x00, // number of important colours
                //pixel array//
                0x24, 0x1c, 0xed,
                0x24, 0x1c, 0xed, 
                0x00, 0x00, // gap of raw
                0x24, 0x1c, 0xed, 
                0x24, 0x1c, 0xed, 
                0x00, 0x00};// end
    
    int dummy[374] = {// info header 14 bytes//
                0x42, 0x4d, //"BM"
                0x06, 0x17, 0x00, 0x00, //size of whole file in bytes
                0x00, 0x00, //reserved bytes
                0x00, 0x00, // reserved bytes
                0x36, 0x00, 0x00, 0x00, // starting addres of pixel array
                    
                //dib header 40 bytes//
                0x28, 0x00, 0x00, 0x00, // size of header
                0x0a, 0x00, 0x00, 0x00, // bitmap w, px
                0x0a, 0x00, 0x00, 0x00, // bitmap h, px
                0x01, 0x00, // number of color planes must be 1
                0x18, 0x00, // number of bits per px
                0x00, 0x00, 0x00, 0x00, // compression method
                0x00, 0x14, 0x00, 0x00, // image size
                0x00, 0x00, 0x00, 0x00,// horizontal resol
                0x00, 0x00, 0x00, 0x00, // vertical resol
                0x00, 0x00, 0x00, 0x00, // numbers of colours in colour palette
                0x00, 0x00, 0x00, 0x00, // number of important colours
                //pixel array//
                0x00, 0x00, 0x00, //B , G, R
                0x00, 0x00, 0x00, 
                0x00, 0x00, // gap of raw
                0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 
                0x00, 0x00};// end
    char * infilename = "input.bmp";
    char * outfilename = "output.bmp";
    int n = sizeof(header)/sizeof(header[0]);
    randomf(header);
    write(infilename, header, n);
    //first training array with basic values
   double traininp[4][3]={ {0, 0.5, 1}, 
                        {0.5, 0, 0}, 
                        {0.9, 0.1, 0.1}, 
                        {0.5, 0.9, 0.9}};
    double trainout[4] = {0, 1, 1, 0};
    // second array to make weigts more accurate
    double traininp1[4][3] ={{1, 1, 0},
                            {1, 1, 1},
                            {0, 0, 0},
                            {1, 0, 1}};
    double trainout1[4] ={0, 0, 0, 0};  

   weights[0] = 2*(float)rand()/RAND_MAX -1;
   weights[1] = 2*(float)rand()/RAND_MAX -1;
   weights[2] = 2*(float)rand()/RAND_MAX -1;

    
   trainer(traininp, trainout, 10000);
   //feel free to coment second training and that there will be more colours in output.bmp, or both and you will get 2 same pictures
   trainer(traininp1, trainout1, 1000); 


    //analysis of first picture 
    int start = dummy[10];
    for(int j = 0; j<dummy[22]; j++){
        
        
        
        for(int i = 0; i < dummy[18]; i++){
        
            double filepxl[3] = {(float)header[start+2+(3*i)]/255, (float)header[start+1+(3*i)]/255,(float)header[start+(3*i)]/255 };
            if (think_an(filepxl)> 0.4)
            {
                dummy[start+2+(3*i)]= header[start+2+(3*i)];
                dummy[start+1+(3*i)]=header[start+1+(3*i)];
                dummy[start+(3*i)]=header[start+(3*i)];
                printf("dummy: %d\n %d\n %d\n",dummy[start+2+(3*i)], dummy[start+1+(3*i)],dummy[start+(3*i)]);
            }
            
            
        }
        start+= header[18]*3;
        start++;
        dummy[start]= 0;
        start++;
        dummy[start] = 0;
           
        
        
    }
    printf("%d\n",dummy[63]);
    n = sizeof(dummy)/sizeof(dummy[0]);

    write(outfilename, dummy, n);
    
    return 0;


}