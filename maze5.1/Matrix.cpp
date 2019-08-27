#include "Matrix.h"

int dir[4][2]= {{0,1},{1,0},{-1,0},{0,-1}};

int Matrix::findSet(int x)
{
    if(x != parent[x])
        parent[x] = findSet(parent[x]);
    return parent[x];
}
void Matrix::Initialize()
{
    memset(high, 0, sizeof(high));//把0赋值到rank里前sizeof(high)个字符
    for(int i=0; i < MAXSIZE; ++i)
        parent[i] = i;
}
void Matrix::unionSet(int root1, int root2)
{
    int x = findSet(root1);
    int y = findSet(root2);
    if(x!=y)
    {
        if(high[x] > high[y])
            parent[y] = x;
        else
        {
            parent[x] = y;
            if(high[x] == high[y])
                ++high[y];
        }
    }
}
int Matrix::findPos(int x,int y,int wid)
{
    return x*wid+y;
}
Matrix::Matrix(int t)
{
    wid = t;
}
void Matrix::initMaze(int w, int h)
{
    wid  = w;
    height = h;
    Initialize();
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<wid; j++)
        {
            Maze[i][j]='8';//'8'表示墙
        }
    }
    for (int i=1; i<height; i++)
    {
        if (i%2 == 1)
        {
            for (int j=1; j<wid; j+=2)
            {
                Maze[i][j]='1';//'1'表示点
            }
        }
        else
        {
            for (int j=2; j<wid; j+=2)
            {
                Maze[i][j]='9';//'9'表示边
            }
        }
    }
}
int Matrix::getwid()
{
    return wid;
}
 int Matrix::getheight()
 {
     return height;
 }

void Matrix::makeMaze()
{
    int x,y;//表示选中目标点的横纵坐标
        int xt1,yt1,xt2,yt2;//表示选中目标点附近两点的横纵坐标
        int tarParity = 0;//表示选中目标点的奇偶性
        srand(time(NULL));
        int hsubWid = 0, wsubWid = 0;
        if(!((max(height, wid) - min(wid,height)) % 2))
        {
            if(height%2)
                hsubWid = wsubWid = 2;
            else
               hsubWid = wsubWid = 3;
        }
        else if(height % 2)
        {
            hsubWid = 2;
            wsubWid = 3;
            Maze[height - 2][wid - 2] = '1';
        }
        else if(wid % 2)
        {
            hsubWid = 3;
            wsubWid = 2;
            Maze[height - 2][wid - 2] = '1';
        }

            while (findSet(findPos(1,1,wid)) != findSet(findPos(height-hsubWid,wid-wsubWid,wid)))
            {
                do
                {
                    x=rand()%(height-2)+1;        //生成外圈内的随机行数
                    y=(rand()+123)%(wid-2)+1;  //生成外圈内的随机列数
                }
                while (Maze[x][y] != '8');
                tarParity = x%2;                     //d表示选中的点在奇数行还是在偶数行

                if (tarParity == 0)                //选中的点在偶数行，选到的是边，选到的其它是上下的点
                {
                    xt1=x+1;               //x是行数
                    yt1=y;                 //y是列数
                    xt2=x-1;
                    yt2=y;
                    if (findSet(findPos(xt1,yt1,wid)) != findSet(findPos(xt2,yt2,wid)))
                    {
                        Maze[x][y]='1';
                        unionSet(findPos(xt1,yt1,wid),findPos(xt2,yt2,wid));
                    }
                }
                else if (tarParity == 1)          //选中的点在奇数行，选到的是点，选到的其它是左右的点
                {
                    xt1=x;
                    yt1=y+1;
                    xt2=x;
                    yt2=y-1;
                    if (findSet(findPos(xt1,yt1,wid)) != findSet(findPos(xt2,yt2,wid)))
                    {
                        Maze[x][y]='1';
                        unionSet(findPos(xt1,yt1,wid),findPos(xt2,yt2,wid));
                    }
                }
            }
        if(!(height % 2))
        {
            Maze[height - 2][wid - 2] = '1';
            srand(time(NULL));
            int t = rand();
            if(t% 3 == 0)
                Maze[height - 3][wid - 2] = '1';
            else if(t % 3 == 1)
                Maze[height - 2][wid - 3] = '1';
            else if(t % 3 == 2)
            {
                Maze[height- 2][wid - 3] = '1';
                Maze[height - 3][wid - 2] = '1';
            }
        }

        for(int i = 0; i < height; i++)
        {
            Maze[i][0] = '8';
            Maze[i][wid - 1] = '8';
        }
        for(int i = 0; i < wid; i++)
        {
            Maze[0][i] = '8';
            Maze[height - 1][i] = '8';
        }
        int falg = 0;
        for(int i   = 0; i < height; i++)
        {
            for(int j =0; j < wid; j++)
            {

                if(Maze[i][j] == '8')
                    Maze[i][j] = '1';
                else if(Maze[i][j] == '1')
                    Maze[i][j] = '0';
                else if(Maze[i][j] == '9')
                {
                    falg++;
                    if(!(falg % 3))
                        Maze[i][j] = '0';
                    else
                        Maze[i][j] = '1';
                }
            }
        }
        srand(time(NULL));
        for(int i = 0; i < height; i++)
            for(int j = 0; j < wid; j++)
            {
                int count = 0;
                if(Maze[i][j] == '0')
                {
                    for(int k = 0; k < 4; k++)
                    {
                        int tx = i + dir[k][0];
                        int ty = j + dir[k][1];
                        if(Maze[tx][ty] == '1' && tx > 0 && ty > 0 && tx <= getheight() - 2 && ty <= getwid() - 2)
                        {
                            count++;
                        }

                    }
                    if(count == 4)
                    {
                        int t = rand()% 4;
                        int tx = i + dir[t][0];
                        int ty = j + dir[t][1];
                        if(Maze[tx][ty] == '1' && tx <= getheight() - 1 && ty <= getwid() - 1)
                        {
                            Maze[tx][ty] = '0';
                        }
                    }
                }
            }
}
