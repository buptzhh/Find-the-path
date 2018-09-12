#include<iostream>  
#include<queue>  
#include<string>  

//使用说明：第一行，输入行数和列数
//一行一行地输入地图
//@代表终点 #代表障碍物 .代表空地 *代表箱子 X代表人物
//输入完地图后即可获得最少步数


using namespace std;
int state[10][10][10][10];//四维数组表示人和箱子的位置状态,开始全为0  

struct q
{
	int px, py, bx, by;
	q(int x, int y, int bx, int by) :px(x), py(y), bx(bx), by(by) 
	{}
};

    int moves[4][2] = { { 0,1 },{ 0,-1 },{ -1,0 },{ 1,0 } };//四个方向  
    char map[10][10];//地图数组  
    int chx, chy, cbx, cby, ex, ey, n, m;//分别表示当前人的位置，盒子的位置，终点位置，以及地图尺寸。  

bool bound(int x, int y)//边界检查，遇到不合理的位置返回真  
{
	if (x < 0 || y < 0 || x >= n || y >= m || map[x][y] == '#')
		return true;
	else
		return false;
}
//广度优先算法
int bfs()
{
	state[chx][chy][cbx][cby] = 1;              //当前状态位置设步数为1  
	q temp(chx, chy, cbx, cby);
	queue<q> que;                               //状态队列  
	que.push(temp);                             //初始状态入栈  
	while (que.size())                          //只要队列不为空就一直寻找  
	{
		temp = que.front();                     //获取首元素  
		que.pop();                              //首元素弹出  
		if (temp.bx == ex && temp.by == ey)
			return state[temp.px][temp.py][temp.bx][temp.by] - 1;//如果箱子在终点，结束，返回步数  
		for (int i = 0; i < 4; i++)             //四个方向开始搜索
		{
			                                    //更新人的位置  
			int px = temp.px + moves[i][0];
			int py = temp.py + moves[i][1];
			if (bound(px, py))
				continue;                       //如果这个位置非法，探寻其它方向  
			if (px == temp.bx&&py == temp.by)   //如果此时人的位置与箱子的位置重合，说明人应当推动了箱子  
			{
				if (bound(temp.bx + moves[i][0], temp.by + moves[i][1]))
					continue;                   //如果箱子移动的位置不合法，则重新探寻其它方向  
				state[px][py][temp.bx + moves[i][0]][temp.by + moves[i][1]] =
					state[temp.px][temp.py][temp.bx][temp.by] + 1;//箱子推动，则人和箱子位置改变，记录新状态  
				que.push(q(px, py, temp.bx + moves[i][0], temp.by + moves[i][1]));//新状态入栈  

			}
			else                                //人没有推动箱子  
			{
				if (state[px][py][temp.bx][temp.by])//如果移动后的状态出现过，则重新搜索新方向  
					continue;
				state[px][py][temp.bx][temp.by] = state[temp.px][temp.py][temp.bx][temp.by] + 1;
				                                //没有走过这条路就走着试试  
				que.push(q(px, py, temp.bx, temp.by));//更新状态  


			}

		}
	}
	return -1;                                  //如果所有位置都试过了，没有找到，说明不存在  

}


int main()
{
	cin >> n >> m;                         //输入行列数
	for (int i = 0; i < n; i++) {
		scanf_s("%s", map[i], m + 1);
	}
	for (int i = 0; i < n; i++)            //初始化人，箱子，终点的位置  
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == '*')
			{
				cbx = i;
				cby = j;
			}
			else if (map[i][j] == 'X') {
				chx = i;
				chy = j;
			}
			else if (map[i][j] == '@')
			{
				ex = i;
				ey = j;
			}
		}
	}
	int re = bfs();
	//printf("%d", re);
	if (re == -1)
		cout << "I'm sorry but no path is available" << endl;
	else if(re != -1)
		cout << "The number of the steps you need is " << re << endl;
	system("pause");
	return 0;
}