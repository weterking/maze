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
    memset(high, 0, sizeof(high));//��0��ֵ��rank��ǰsizeof(high)���ַ�
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
            Maze[i][j]='8';//'8'��ʾǽ
        }
    }
    for (int i=1; i<height; i++)
    {
        if (i%2 == 1)
        {
            for (int j=1; j<wid; j+=2)
            {
                Maze[i][j]='1';//'1'��ʾ��
            }
        }
        else
        {
            for (int j=2; j<wid; j+=2)
            {
                Maze[i][j]='9';//'9'��ʾ��
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
    int x,y;//��ʾѡ��Ŀ���ĺ�������
        int xt1,yt1,xt2,yt2;//��ʾѡ��Ŀ��㸽������ĺ�������
        int tarParity = 0;//��ʾѡ��Ŀ������ż��
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
                    x=rand()%(height-2)+1;        //������Ȧ�ڵ��������
                    y=(rand()+123)%(wid-2)+1;  //������Ȧ�ڵ��������
                }
                while (Maze[x][y] != '8');
                tarParity = x%2;                     //d��ʾѡ�еĵ��������л�����ż����

                if (tarParity == 0)                //ѡ�еĵ���ż���У�ѡ�����Ǳߣ�ѡ�������������µĵ�
                {
                    xt1=x+1;               //x������
                    yt1=y;                 //y������
                    xt2=x-1;
                    yt2=y;
                    if (findSet(findPos(xt1,yt1,wid)) != findSet(findPos(xt2,yt2,wid)))
                    {
                        Maze[x][y]='1';
                        unionSet(findPos(xt1,yt1,wid),findPos(xt2,yt2,wid));
                    }
                }
                else if (tarParity == 1)          //ѡ�еĵ��������У�ѡ�����ǵ㣬ѡ�������������ҵĵ�
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
