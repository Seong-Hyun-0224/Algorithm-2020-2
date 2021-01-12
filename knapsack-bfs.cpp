#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <functional>
using namespace std;

#define n 4 //아이템의 개수

struct node {
	int level; //상태공간트리의 레벨, 고려하는 item을 나타냄
	int profit;
	int weight;
	double bound;
	bool include[n + 1];//아이템의 포함 여부
};

int maxprofit;//현재까지의 최대 이익
node best_node;//maxprofit를 만족하는 노드

int W = 16;//베낭의 허용가능 무게
int w[] = { 0, 2, 5, 10, 5 }; //각 아이템의 무게
int p[] = { 0, 40, 30, 50, 10 };//각 아이템의 값어치

struct cmp { //우선순위큐에서 bound 값이 큰 순서대로 가져옴
	bool operator()(node a, node b) {
		return a.bound < b.bound;
	}
};
std::priority_queue<node, vector<node>, cmp> pq;//시스템 제공 우선순위 큐

void bound(node *u) { //노드 u의 bound값을 계산
	int j;
	int totweight;

	if (u->weight > W) //노드 u의 무게가 베낭의 허용용량 초과
		u->bound = 0; //bound 값을 0으로 하여 유망성 없음 나타냄
	else { //bound 계산식을 적용하여 아래에 코드를 완성하시오.
		float result = (float)u->profit;
		j = u->level + 1;
		totweight = u->weight;
		while (j <= n && totweight + w[j] <= W) {
			totweight = totweight + w[j];
			result = result + p[j];
			j++;
		}
		if (j <= n) {
			result = result + (W - totweight) * p[j] / w[j];
		}
		u->bound = result;
	}
}

void knapsack_bfs()
{
	node u, v;

	v.level = 0; v.profit = 0; v.weight = 0; //초기화
	for (int i = 1; i <= n; i++)
		v.include[i] = false;
	bound(&v);
	printf("삽입: level=%d, profit=%d, weight=%d, bound=%g, maxprofit=%d\n",
		v.level, v.profit, v.weight, v.bound, maxprofit);
	pq.push(v);

	while (!pq.empty()) {
		v = pq.top();
		pq.pop();
		printf("삭제: level=%d, profit=%d, weight=%d, bound=%g, maxprofit=%d",
			v.level, v.profit, v.weight, v.bound, maxprofit);
		if (v.bound > maxprofit)
			printf("-유망함\n");
		else
			printf("-유망하지 않음\n");
		if (v.bound > maxprofit) {
			for (int i = 1; i <= n; i++)
				u.include[i] = v.include[i];
			u.level = v.level + 1;

			u.weight = v.weight + w[u.level];
			u.profit = v.profit + p[u.level];
			u.include[u.level] = true; //아이템 베낭에 넣음
			bound(&u);
			if (u.weight <= W && u.profit > maxprofit) {
				maxprofit = u.profit;
				best_node = u;
			}
			if (u.bound > maxprofit)
				pq.push(u);
			printf("\t왼쪽자식: level=%d, profit=%d, weight=%d, bound=%g, maxprofit=%d",
				u.level, u.profit, u.weight, u.bound, maxprofit);
			if (u.bound > maxprofit)
				printf("-삽입\n");
			else
				printf("-버림\n");

			u.weight = v.weight;
			u.profit = v.profit;
			u.include[u.level] = false;//아이템 베낭에 넣지 않음
			bound(&u);
			if (u.bound > maxprofit)
				pq.push(u);
			printf("\t오른쪽자식: level=%d, profit=%d, weight=%d, bound=%g, maxprofit=%d",
				u.level, u.profit, u.weight, u.bound, maxprofit);
			if (u.bound > maxprofit)
				printf("-삽입\n");
			else
				printf("-버림\n");
		}
	}
}

int main()
{
	printf("아이템 수 n: %d, 베낭 용량 W: %d\n", n, W);
	printf("i\tp\tw\tp/w\n");
	for (int i = 1; i <= n; i++) {
		printf("%d\t%d\t%d\t%d\n", i, p[i], w[i], p[i] / w[i]);
	}
	printf("\n");

	maxprofit = 0;
	knapsack_bfs();

	printf("\n");
	printf("최대이익:%d, 베낭무게:%d\n", best_node.profit, best_node.weight);
	printf("베낭에 포함되는 아이템: ");
	for (int i = 1; i <= n; i++) {
		if (best_node.include[i])
			printf("아이템 %d, ", i);
	}
	printf("\n");

	return 0;
}

/*결과
아이템 수 n: 4, 베낭 용량 W: 16
i       p       w       p/w
1       40      2       20
2       30      5       6
3       50      10      5
4       10      5       2

삽입: level=0, profit=0, weight=0, bound=115, maxprofit=0
삭제: level=0, profit=0, weight=0, bound=115, maxprofit=0-유망함
		왼쪽자식: level=1, profit=40, weight=2, bound=115, maxprofit=40-삽입
		오른쪽자식: level=1, profit=0, weight=0, bound=82, maxprofit=40-삽입
삭제: level=1, profit=40, weight=2, bound=115, maxprofit=40-유망함
		왼쪽자식: level=2, profit=70, weight=7, bound=115, maxprofit=70-삽입
		오른쪽자식: level=2, profit=40, weight=2, bound=98, maxprofit=70-삽입
삭제: level=2, profit=70, weight=7, bound=115, maxprofit=70-유망함
		왼쪽자식: level=3, profit=120, weight=17, bound=0, maxprofit=70-버림
		오른쪽자식: level=3, profit=70, weight=7, bound=80, maxprofit=70-삽입
삭제: level=2, profit=40, weight=2, bound=98, maxprofit=70-유망함
		왼쪽자식: level=3, profit=90, weight=12, bound=98, maxprofit=90-삽입
		오른쪽자식: level=3, profit=40, weight=2, bound=50, maxprofit=90-버림
삭제: level=3, profit=90, weight=12, bound=98, maxprofit=90-유망함
		왼쪽자식: level=4, profit=100, weight=17, bound=0, maxprofit=90-버림
		오른쪽자식: level=4, profit=90, weight=12, bound=90, maxprofit=90-버림
삭제: level=1, profit=0, weight=0, bound=82, maxprofit=90-유망하지 않음
삭제: level=3, profit=70, weight=7, bound=80, maxprofit=90-유망하지 않음

최대이익:90, 베낭무게:12
베낭에 포함되는 아이템: 아이템 1, 아이템 3,
계속하려면 아무 키나 누르십시오 . . .
*/