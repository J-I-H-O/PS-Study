#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000001;
int u, v, weight, start, destination;
int n, m;            // n: 정점의 개수, m: 간선의 개수
bool visited[1001];  // 해당 정점의 방문 여부 체크
int dist[1001];      // 시작점에서 해당 정점까지의 거리 기록
int w[1001][1001];   // w[u][v]: 정점 u와 정점 v 사이의 가중치 기록

// 아직 방문하지 않은 정점들 중 시작점으로부터 가장 최소 거리를 가지는 정점의 인덱스 반환
// 다음에 방문한 정점으로 선택하기 위함
int getSmallestIdx() {
  int min = INF;
  int minIdx = 0;
  for(int i = 1; i <= n; i++) {
    // 아직 방문하지 않은 정점에 대해 최소 거리를 갖는 정점 찾기
    if(dist[i] < min && !visited[i]) {
      min = dist[i];
      minIdx = i;
    }
  }
  return minIdx;
}

// 선형 탐색으로 최소 비용을 찾도록 구현. 시간복잡도 O(n^2)
// 정점의 개수가 많고, 간선의 개수는 적을 때 비효율적으로 동작
// s: 시작 정점
void dijkstra(int s) {
  // 시작 정점 s의 인접 정점들에 대해 시작 정점으로부터의 거리 dist를 초기화
  for(int i = 1; i <= n; i++) {
    dist[i] = w[s][i];
  }

  // 시작 정점을 방문 표시
  visited[s] = true;
  dist[s] = 0;

  // 시작 정점을 제외한 나머지 정점들에 대해 반복하므로 반복횟수는 n - 1회
  for(int i = 1; i <= n - 1; i++) {
    // 방문하지 않은 정점들 중 시작점으로부터 최소 거리를 갖는 정점을 선택하고 방문처리
    int cur = getSmallestIdx();
    visited[cur] = true;
    
    for(int j = 1; j <= n; j++) {
      // 방문하지 않은 정점들에 대해서만 값을 갱신해줌.
      // 이미 방문한 정점들의 값은 갱신하지 않음에 유의 => 다익스트라 알고리즘이 음의 가중치가 존재할 때 동작하지 않는 이유
      if(!visited[j]) {
        if(dist[j] > dist[cur] + w[cur][j]) {
          dist[j] = dist[cur] + w[cur][j];
        }
      }
    }
  }
}

int main() {
  cin >> n >> m;

  for(int i = 1; i <= n; i++) {
    dist[i] = INF;
    for(int j = 1; j <= n; j++) {
      w[i][j] = INF;
    }
  }

  for(int i = 1; i <= m; i++) {
    cin >> u >> v >> weight;
    if(w[u][v] > weight)
      w[u][v] = weight;
  }
  cin >> start >> destination;

  dijkstra(start);
  cout << dist[destination];

  return 0;
}