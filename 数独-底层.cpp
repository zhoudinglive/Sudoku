#include<iostream>
#include<algorithm>
#include<time.h>
#include<cstdlib>
using namespace std;

class sudoku
{
private:
    int row,col,count;                                 //row:行  col：列  count作为计数，最大值为81
    int question_array[9][9],answer_array[9][9];       //qustion为用户看到的数独，answer为其解
    void printf(int **a,int n);                        //输出9*9矩阵
    bool is_place(int cnt);                            //根据count判断该位置是否能够放置数（余数法）
    void creat_partsudoku();                           //构造部分的数独，传入qustion数组，并随机化生成数独题目
    void creat_allsudoku(int cnt);
public:
    sudoku();                                          //构造函数，对数独数组进行初始随机化
    void creat_allsudoku(){ creat_allsudoku(count); }  //构造完整的数独，将其赋给question、answer数组
};

sudoku::sudoku()
{
    int temp;
    srand(time(0));

    /*初始化answer数组*/
    for(int i=0;i<9;++i)
        for(int j=0;j<9;++j)
            answer_array[i][j]=0;

    /*进一步随机化，增添随机性*/
    for(int i=0;i<9;++i)
    {
        temp=rand()%81;
        answer_array[temp/9][temp%9]=i+1;
    }

    count=0;
}

void sudoku::printf(int **a,int n)
{
    for(int i=0;i<n;++i)
    {
        if(i%3==0)
            cout<<endl;

        for(int j=0;j<n;++j)
        {
            if(j%3==0)
                cout<<" ";

            if(a[i][j]==0)
                cout<<"*"<<" ";
            else
                cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
}

bool sudoku::is_place(int cnt)
{
    /*count的变化范围由0~81，以行序优先，即有如下方式遍历每一个位置*/
    row=cnt/9;
    col=cnt%9;

    /*余数法判断同一行每一列中，是否有相同的元素*/
    for(int i=0;i<9;++i)
        if(answer_array[row][col]==answer_array[row][i]&&i!=col)
           return false;

    /*余数法判断同一列每一行中，是否有相同的元素*/
    for(int i=0;i<9;++i)
        if(answer_array[row][col]==answer_array[i][col]&&i!=row)
           return false;

    /*余数法判断每一个3*3的小格子里，是否有相同的元素*/
    int temprow=row/3*3;
    int tempcol=col/3*3;

    for(int i=temprow;i<temprow+3;++i)
        for(int j=tempcol;j<tempcol+3;++j)
            if(answer_array[row][col]==answer_array[i][j]&&i!=row&&j!=col)
               return false;

    return true;
}

void sudoku::creat_allsudoku(int cnt)
{
    /*count的变化范围由0~81，以行序优先，即有如下方式遍历每一个位置*/
    srand(time(0));
    row=cnt/9;
    col=cnt%9;

    /*判断cnt计数是否达到81.如果达到则说明整个数独矩阵已经创立完成*/
    if(cnt==81)
    {
        /*将已经完成求解的answer赋给qustion数组*/
        for(int i=0;i<9;++i)
            for(int j=0;j<9;++j)
                question_array[i][j]=answer_array[i][j];

        /*将qustion数组进行随机进行挖洞，形成数独题目*/
        for(int i=0;i<9;++i)
            for(int j=0;j<6;++j)
            {
                int temp=rand()%9;
                question_array[i][temp]=0;
            }

        for(int i=0;i<9;++i)
        {
            for(int j=0;j<9;++j)
                cout<<question_array[i][j]<<" ";
            cout<<endl;
        }

        cout<<endl;

        //printf((int**)answer_array,9);
        return ;
    }

    /*若不满足cnt==81，那么判断该位置是否可以填写数字，
      如果可以则递归下一层，否则回溯退回到初始状态*/
    if(answer_array[row][col]==0)
    {
        for(int i=1;i<=9;++i)
        {
            answer_array[row][col]=i;
            if(is_place(cnt))
               creat_allsudoku(cnt+1);
        }
        answer_array[row][col]=0;
    }
    else
        creat_allsudoku(cnt+1);
}

int main()
{
    sudoku one;
    one.creat_allsudoku();
}

