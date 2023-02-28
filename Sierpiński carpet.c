#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
static int Power;  //We calsulate the Power in main(), but we also need it in HollowOut()
void HollowOut(int Start_x,int Stop_x,int Start_y,char* Map){

    //The length of the side of the square to be cut
    int Step = ((Stop_x - Start_x + 1) / 3);

    //Lock on to the square
    int X1 = Start_x + Step;
    int X2 = X1 + Step;
    int Y1 = Start_y + Step;
    int Y2 = Y1 + Step;

    for(int i=X1;i<X2;i++)
        for(int j=Y1;j<Y2;j++){
            Map[Power*i+j] = ' ';    //modify directly on the Map
        }
            
}
//******************************************
void Carpet(int n,int Start_x,int Stop_x,int Start_y,char* Map){  //n represent the iteration of recursion left
    //two basic situation                                         //since it is a square we just need three point to lock on it
    if( n==0 ){
        return;
    }
    else if (n==1)
    {
        HollowOut(Start_x,Stop_x,Start_y,Map);
        Carpet(0,Start_x,Stop_x,Start_y,Map);                     //Go back to the situation when n==0
    }

    HollowOut(Start_x,Stop_x,Start_y,Map);                        //Hollow out this area first

    for(int i=0;i<3;i++){                                         //Go to 8 small areas around
        for(int j=0;j<3;j++){

            //The side lengths of the surrounding small square
            int Step = ((Stop_x - Start_x + 1) / 3);

            //Lock on to the square
            int X1 = Start_x + Step * i;
            int X2 = X1 + Step - 1;                               ////Different from the part in HollowOut, we need to -1 at last to divide the square
            int Y1 = Start_y + Step * j;
            
            Carpet(n-1,X1,X2,Y1,Map);
        }   
    }   
    
}
//*************************************
int main(int argc, char *argv[]){
    
    int k;
    scanf("%d", &k);
    Power = pow(3, k);  //3^k =2187, int is enough

    char* Map = (char*) malloc(sizeof(char)*pow(Power,2));
    memset(Map,'#',sizeof(char)*pow(Power,2));
    //Copies '#' for Power^2 times to Map. 

    Carpet(k,0,Power-1,0,Map);
    

    for (int i=0;i<Power;i++){
        for (int j=0;j<Power;j++)
            printf("%c",Map[Power*i+j]);
        printf("\n");
    }
    return 0;
}