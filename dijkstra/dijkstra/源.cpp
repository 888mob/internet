#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define INF 0x3f3f3f3f
using namespace std;
struct node
{
	int	to;
	int	weight;
	string ip;
	int next;
} p;
const int maxn = 10000;
vector<node>v[maxn+10];
int dis[maxn+10];
int n;
int path[maxn + 10];


void dijsktra(int start)
{
	int	visit[maxn+10], mini, u, x;
	for (int i = 1; i <= maxn; i++)
		dis[i] = INF;
	for (unsigned int i = 0; i < v[start].size(); i++)
	{
		p = v[start][i];
		dis[p.to] = p.weight;
	}
	for (int i = 1; i <= n; i++)
	{
		if (i!=start&&dis[i] < INF) path[i] = start;
		else path[i] = -1;
	}
	dis[start] = 0;
	memset(visit, 0, sizeof(visit));
	visit[start] = 1;
	for (int i = 1; i < n; i++)
	{
		mini = INF;
		for (int j = 1; j <= n; j++)
		{
			if (visit[j] == 0 && dis[j] < mini)
			{
				mini = dis[j];
				u = j;
			}
		}
		visit[u] = 1;
		for (x = 0; x < v[u].size(); x++)
		{
			p = v[u][x];
			if (dis[p.to] > dis[u] + p.weight)
			{
				dis[p.to] = dis[u] + p.weight;
				path[p.to] = u;
			}
		}
	}
}
void deleteedge()
{
	int a, b;
	cout << "输入要边的两边顶点：";
	cin >> a >> b;
	int size1=v[a].size(), size2=v[b].size();
	for (int i = 0; i < size1; i++)
	{
		if (v[a][i].to == b)
		{
			v[a].erase(v[a].begin() + i);
			break;
		}
	}
	for (int i = 0; i < size2; i++)
	{
		if (v[b][i].to == a)
		{
			v[b].erase(v[b].begin() + i);
			break;
		}
	}
}

int main()
{
	int start;
	for (int i = 1; i <= maxn; i++)
		v[i].clear();
	n = 0;
	while (1)
	{
		int a, b, c;
		string ip1, ip2;
		cin >> a;
		if (a == -1) break;
		cin >> ip1 >> b >> ip2 >> c;
		n = max(n, max(a, b));
		p.to = b;
		p.weight = c;
		p.ip = ip1;
		v[a].push_back(p);
		p.to = a;
		p.weight = c;
		p.ip = ip2;
		v[b].push_back(p);
	}
	cin >> start;
	dijsktra(start);
	for (int i = 1; i <= n; i++)
	{
		if (i == start) continue;
		if (dis[i] == INF) continue;
		int t = i;
		while (path[path[t]] != -1)
		{
			t = path[t];
		}
		cout << "下一跳：" << t << endl;
		cout << "下一跳网络号：" << v[t][0].ip << endl;
		cout << "目的路由：" << i << endl;
		cout << "-----------" << endl;
	}
}
