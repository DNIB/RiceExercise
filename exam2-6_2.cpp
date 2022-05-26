#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
using namespace std;

class Game{
private:
    int n, a[100][100], s[100][100]={1};
public:
    void setGame(int _n){
        n=_n;
    }
    int check_array(int x, int y){
        for(int cy=0;cy<n;cy++){
            for(int cx=0;cx<2*n;cx++){
                if(a[x][y]==a[cx][cy]&&(x!=cx||y!=cy)){
                    return -1;
                }
            }
        }
        return 0;
    }
    void random_array(){
        for(int y=0;y<n;y++){
            for(int x=0;x<2*n;x++){
                a[x][y]=rand()%(2*n*n)+1;
                x+=check_array(x,y);
            }
        }
    }
    void print_array(){
        for (int y=0;y<n;y++){
            for(int x=0;x<2*n;x++){
                if(s[x][y] == 1){
                    printf("%4d ", a[x][y]);
                }
	            else{
                    printf("%4s ", "*"); 
                }
            }
            printf("\n");
        } 
        puts("");
    }

    void set_shadow(int value){
        for (int y=0;y<n;y++){
            for(int x=0;x<2*n;x++){
                s[x][y]=value;
            }
        }
    }
    void run(){
        srand(time(0));
        int n,temp=0,pt[3],ct[3],pp=0,cp=0;
        int x1,y1,x2,y2;
        char play;
        printf("Enter n: ");
        scanf("%d",&n);
        setGame(n);
        random_array();
        set_shadow(1);
        print_array();
        while(temp<2*n*n){
            printf("Your picks: ");
            scanf("%d%d%d%d",&y1,&x1,&y2,&x2);
            x1--;y1--;x2--;y2--;
            while(s[x1][y1]==1||s[x2][y2]==1){
                printf("The numbers cannot be retaken.\n");
                printf("Your picks: ");
                scanf("%d%d%d%d",&y1,&x1,&y2,&x2);
                x1--;y1--;x2--;y2--;
            }
            s[x1][y1]=1;
            s[x2][y2]=1;
            pt[0]=a[x1][y1]+a[x2][y2];
            pt[1]=a[x1][y1];
            pt[2]=a[x2][y2];
            do{
                x1=rand()%(2*n);
                y1=rand()%n;
            }
            while(s[x1][y1]==1);
            s[x1][y1]=1;
            do{
                x2=rand()%(2*n);
                y2=rand()%n;
            }
            while(s[x2][y2]==1);
            s[x2][y2]=1;
            ct[0]=a[x1][y1]+a[x2][y2];
            ct[1]=a[x1][y1];
            ct[2]=a[x2][y2];
            print_array();
            printf("Your number: %d %d\nComputers's number: %d %d \n",pt[1],pt[2],ct[1],ct[2]);
            if(pt[1]%2==pt[2]%2){
                pp+=pt[0];
            }
            if(ct[1]%2==ct[2]%2){
                cp+=ct[0];
            }
            printf("Your points: %d Computer’s points: %d\n",pp,cp);
            temp+=4;
            if(temp>=2*n*n){
                break;
            }
            printf("Continue to play (Y|N)? ");
            scanf(" %c",&play);
            if(toupper(play)=='N'){
                break;
            }
        }
        printf("The player gets total %d points.\nThe computer gets total %d points.\n",pp,cp);
        if(pp>cp){
            printf("Congratulations! You’re the winner.\n");
        }
        if(pp==cp){
            printf("No one wins the game.\n");
        }
        if(pp<cp){
            printf("Sorry! Computer is the winner.\n");
        }
    }
};

int main(){
    Game game;
    game.run();
}