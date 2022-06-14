//
//  6086.cpp
//  ProblemSolve
//
//  Created by 김성찬 on 2022/06/14.
//
//

//
// No. 6086
// 최대 유량
// Platinum IV
//

//
// 최대 유량
//

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <memory.h>
#include <algorithm>
using namespace std;
#define MAX_NODE 52
#define INF 987654321

int N_Pipe; // number of pipe
int capacity[MAX_NODE][MAX_NODE], flow[MAX_NODE][MAX_NODE];

int MaximumFlow(int start_node, int end_node)
{
    // flow를 0으로 초기화
    memset(flow, 0, sizeof(flow));

    // 최대 유량
    int total_flow = 0;

    while (true)
    {
        // 1. BFS로 경로 탐색

        // 해당 경로에서 직전 노드를 저장하는 벡터
        vector<int> parent(MAX_NODE, -1);

        // BFS를 위한 queue
        queue<int> Q;

        parent[start_node] = start_node;
        Q.push(start_node);

        // BFS 시작 : queue가 비어있지 않은 동안 && end_node의 경로 상 직전 노드가 존재하지 않는 동안
        while (!Q.empty() && parent[end_node] == -1)
        {
            // 현재 탐색할 노드
            int now = Q.front(); Q.pop();

            for (int next = 0; next < MAX_NODE; next++)
            {
                // now에서 next로의 용량이 now에서 next로의 유량보다 크고
                // next를 탐색하지 않은 경우
                if (capacity[now][next] > flow[now][next] && parent[next] == -1)
                {
                    // next를 queue에 넣는다.
                    Q.push(next);
                    parent[next] = now;
                }
            }
        }
        
        // end_node의 경로 상 직전 노드가 없다면
        // 경로가 존재하지 않는 것이므로 종류한다.
        if (parent[end_node] == -1)
            break;
        
        // 2. 경로가 존재하는 경우, 해당 경로의 최대 유량 계산
        int local_maximum_flow = INF;

        for (int p = end_node; p != start_node; p = parent[p])
        {
            // parent[p]에서 p로 흘러갈 수 있는 유량 계산
            int local_flow = capacity[parent[p]][p] - flow[parent[p]][p];

            // local_maximum_flow를 업데이트
            local_maximum_flow = min(local_flow, local_maximum_flow);
        }

        // 3. 경로를 따라 유량 업데이트
        for (int p = end_node; p != start_node; p = parent[p])
        {
            flow[parent[p]][p] += local_maximum_flow;
            flow[p][parent[p]] -= local_maximum_flow;
        }

        // 4. 최대 유량 업데이트
        total_flow += local_maximum_flow;
    }

    return total_flow;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    // 파이프의 개수
    cin >> N_Pipe;

    // 하나의 간선을 이루는 두 노드의 알파벳
    char node_1, node_2;

    // node_1과 node_2가 만드는 간선의 capacity
    int local_capacity;

    // 노드에 해당하는 인덱스
    int idx = 0;

    // 노드와 대응하는 인덱스의 매핑
    map<char, int> id;

    // capacity를 0으로 초기화
    memset(capacity, 0, sizeof(capacity));

    // N_Pipe 개의 파이프에 대한 정보를 입력
    for (int i = 0; i < N_Pipe; i++)
    {
        cin >> node_1 >> node_2 >> local_capacity;

        if (id.find(node_1) == id.end())
            id[node_1] = idx++;

        if (id.find(node_2) == id.end())
            id[node_2] = idx++;

        capacity[id[node_1]][id[node_2]] += local_capacity;
        capacity[id[node_2]][id[node_1]] += local_capacity;
    }

    cout << MaximumFlow(id['A'], id['Z']);
    return 0;
}