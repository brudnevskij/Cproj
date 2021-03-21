#include "sig.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
int main (int argc, char *argv[]){
    
    /*                                              bmp variables                                                     */

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

    /*                                              training variables                                                  */
    // synaptic weights
    double weights[3];
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
    /*                                                     functions                                                  */
    //training

    trainer(traininp, trainout, 10000, weights);
    //feel free to coment second training and that there will be more colours in output.bmp, or both and you will get 2 same pictures
    trainer(traininp1, trainout1, 1000, weights); 
    
    //bmps creation
  
    //input.bmp
    int n = sizeof(header)/sizeof(header[0]);
    randomf(header);
    write(infilename, header, n);

    //analysis of first picture output.bmp 
    int start = dummy[10];
    bmp_analyzer(dummy, header, start, weights);
    n = sizeof(dummy)/sizeof(dummy[0]);

    write(outfilename, dummy, n);
    
    return 0;


}