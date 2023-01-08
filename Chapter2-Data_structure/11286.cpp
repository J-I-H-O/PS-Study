#include <bits/stdc++.h>
using namespace std;

const int MAX = 100000;
int n, temp;

class MinHeap{
  public:
  pair<int, bool> elements[MAX + 1];  // <절댓값, 음수 여부>
  int heapSize = 0;

  void insertHeap(int x, bool isNegative) {
    // 우선 입력된 값을 힙의 마지막 원소로 추가
    elements[++heapSize] = {x, isNegative};

    // 새로 추가된 값과 부모 노드의 값을 비교하여 새로 추가된 값이 더 작을 경우, 부모 노드와 위치를 바꿈
    int curIdx = heapSize;
    // 새로 추가된 노드가 루트 노드가 아닌 상태이고, 부모 노드의 값보다 작은 경우
    while(curIdx != 1 && elements[curIdx].first <= elements[curIdx/2].first) {
      // 절댓값이 같으면 새로 추가된 노드의 값이 음수인 경우에만 부모 노드와 자리를 바꿈
      // 절대값이 같은 경우, 값이 음수인 노드가 더 위에 위치해야하기 때문
      if(elements[curIdx].first == elements[curIdx/2].first){
        if(!elements[curIdx].second)
          break;
      }
        
      // 부모 노드를 현재 노드와 교환
      pair<int, bool> temp = elements[curIdx];
      elements[curIdx] = elements[curIdx/2];
      elements[curIdx/2] = temp;
      
      curIdx /= 2;
    }
  }

  // 최소 힙에서 최솟값은 루트 노드
  int deleteHeap() {
    // 힙이 비어있는 경우, 0을 리턴
    if(heapSize <= 0) {
      return 0;
    }
    // 루트노드의 값(최솟값)을 미리 저장
    pair<int, bool> deleted = elements[1];

    // 힙 재구성
    // 루트 노드의 빈자리에는 일단 마지막 노드를 가져옴
    elements[1] = elements[heapSize--];
    int curIdx = 1;
    int child = curIdx*2; // 우선 왼쪽 자식노드 선택
    // 교환한 루트 노드와 자식 노드들을 비교, 자식 노드 중 더 작은 것과 교환
    while(child <= heapSize) {
      // 현재 노드의 오른쪽 자식 노드가 존재하고, 오른쪽 자식 노드의 값이 왼쪽 자식 노드의 값보다 작은 경우, 오른쪽 자식노드 선택
      if(child < heapSize && elements[child].first > elements[child + 1].first) {
        child++;
      }
      // 두 자식노드의 절댓값이 같은 경우
      else if(child < heapSize && elements[child].first == elements[child + 1].first) {
        // 오른쪽 자식 노드의 값이 음수이면 오른쪽 자식 노드 선택
        if(elements[child+1].second)
          child++;
      }

      // 자식 노드의 값이 현재 값보다 큰 경우 힙 재구성 종료
      if(elements[curIdx].first < elements[child].first) break;
      // 자식 노드의 값이 현재 값과 같은 경우, 현재 값이 음수면 값을 더이상 바꾸지 않고 종료
      // 절대값이 같은 경우, 값이 음수인 노드가 더 위에 위치해야하기 때문
      if(elements[curIdx].first == elements[child].first) {
        if(elements[curIdx].second)
          break;
      }

      // 현재 노드가 자식노드의 값보다 큰 경우, 선택한 자식노드와 현재노드 교환
      pair<int, bool> temp = elements[curIdx];
      elements[curIdx] = elements[child];
      elements[child] = temp;

      curIdx = child;
      child = curIdx*2;
    }

    // 음수의 절댓값인 경우
    if(deleted.second) 
      return -deleted.first;
    else
      return deleted.first;
  }
};

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);

  MinHeap* heap = new MinHeap();

  cin >> n;
  for(int i = 0; i < n; i++) {
    cin >> temp;
    if(temp == 0) {
      cout << heap->deleteHeap() << '\n';
    }
    else {
      heap->insertHeap(abs(temp), temp < 0);
    }
  }

  delete heap;

  return 0;
}