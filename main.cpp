#include <bits/stdc++.h>
#include <unistd.h>
using namespace std ;

int col=40,row=70;

void create (int arr[][70]){
    for(int i=0;i<col;++i)
        for(int j=0;j<row;++j)
            arr[i][j]=rand() % 2;
}


int count (int arr[][70],int &x,int &y){
    int sum = 0;
    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            int cols = (x + i + col) % col;
            int rows = (y + j + row) % row;
            sum += arr[cols][rows];
        }
    }
    sum -= arr[x][y];
  return sum;
}


void check(int arr[][70]){
    for(int i=0;i<col;++i){
        for(int j=0;j<row;++j){

            int sum=count(arr,i,j);

            if (arr[i][j]==1 && (sum>3 || sum<2))
                arr[i][j]=0;

            else if(arr[i][j]==0 && sum==3)
                arr[i][j]=1;
        }
    }
}


void draw(int arr[][70]){
    for(int i=0;i<col;++i){
        for(int j=0;j<row;++j){

            if(arr[i][j]==1)
                cout<<"⬛";
            else
                cout<<"⬜";
        }
        cout<<"\n";
    }
}


int main ()
{
    int arr[row][70];
    double speed=0.2;
    srand(time(NULL));
    cout<<"Enter speed (seconds , enter 0 for default=0.2 sec) : ";
    cin>>speed;
    (speed ? speed : speed=0.2);
    speed*=1000000;
    create(arr);
    while(true){
        draw(arr);
        check(arr);
        usleep(speed);
        system("clear");
   }
}
