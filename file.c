#include "sig.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int randomf(int header[])
{
    srand(time(NULL));

    

    // setting of random colours
    int start = header[10];
    for(int j = 0; j< header[22]; j++){
    

        for(int i = 0 ; i< 3*header[18] ; i++){
            header[start+i] = (int)((float)rand()/RAND_MAX*255); 

        }
        start += 3 * header[18];
        start++;
        header[start]= 0;
        start++;
        header[start] = 0;
        
        
    }
    
     
     
    return 0;
}

// I use this function to transform my array with bytes to file
int write(char * filename, int message[], int n)
{
    FILE * fp;
    if((fp= fopen(filename, "w+"))==NULL)
    {
        perror("Error occured while opening file");
        return 1;
    }
     
    for(int i=0; i<n; i++)
    {
        putc(message[i], fp);
    }

    
     
    fclose(fp);
    return 0;
}

// I used this function to check colours just from file, but after few problems i decided to work with pixels in the array 
int read(char * filename, int pos){
    FILE * fp;
    int buffer[1];
    if((fp= fopen(filename, "r+"))==NULL)
    {
        perror("Error occured while opening file");
        return 1;
    }
    fseek(fp, pos, SEEK_SET);
    fread(buffer, 1, 1, fp);
    fclose(fp);
    return buffer[0];
}