//
//  1960.cpp
//  ProblemSolve
//
//  Created by 김성찬 on 2022/06/09.
//
//

//
// No. 1960
// 행렬만들기
// Gold II
//

//
// Greedy Algorithm
// Sort
// Maximum Flow
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MAX 1002
#define INF 987654321

int Size_Matrix;
int capacity[MAX][MAX], flow[MAX][MAX];
int START, END;

int MaximumFlow();

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> Size_Matrix;

    START = 0;
    END = 2 * Size_Matrix + 1;
    int total_flow = 0;

    for (int i = 1; i <= Size_Matrix; i++) 
    {
        cin >> capacity[START][i];
        total_flow += capacity[START][i];
    }
    
    for (int i = 1; i <= Size_Matrix; i++)
        cin >> capacity[Size_Matrix + i][END];

    for (int i = 1; i <= 2 * Size_Matrix; i++)
    {
        for (int j = 1; j <= 2 * Size_Matrix; j++)
        {
            capacity[i][j] = 1;
        }
    }

    int maximum_flow = MaximumFlow();

    if (maximum_flow == total_flow)
    {
        cout << 1 << endl;
        for (int i = 1; i <= Size_Matrix; i++)
        {
            for (int j = 1; j <= Size_Matrix; j++)
            {
                if (flow[i][Size_Matrix + j] > 0)
                    cout << 1;
                else
                    cout << 0;
            }
            cout << endl;
        }
    }
    else
    {
        cout << -1 << endl;
    }
}

int MaximumFlow()
{
    int total_flow = 0;

    while (true)
    {
        vector<int> parent(2 * (Size_Matrix + 1), -1);
        queue<int> q;
        parent[START] = START;
        q.push(START);

        while (!q.empty() && parent[END] == -1)
        {
            int now = q.front(); q.pop();

            for (int next = 0; next < MAX; next++)
            {
                if (capacity[now][next] > flow[now][next] && parent[next] == -1)
                {
                    q.push(next);
                    parent[next] = now;
                }
            }            
        }

        if (parent[END] == -1)
            break;

        int amount = INF;

        for (int node = END; node != START; node = parent[node])
        {
            amount = min(capacity[parent[node]][node] - flow[parent[node]][node], amount);
        }

        for (int node = END; node != START; node = parent[node])
        {
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
        }

        total_flow += amount;
    }

    return total_flow;
}