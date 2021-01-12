#include <stdio.h>

/*
4. 탐욕 알고리즘
4.1 최소비용 신장트리
	4.1.1 프림 알고리즘
	4.1.2 크루스칼 알고리즘
4.2 단일출발점 최단경로 문제를 푸는 다익스트라 알고리즘
4.3 스케줄 짜기
	4.3.1 시스템 내부의 총 시간의 최소화
	4.3.2 마감시간 있는 스케줄 짜기
4.4 허프만 코드
	4.4.1 전칰드
	4.4.2 허프만 알고리즘
4.5 탐욕 알고리즘과 동적계획 알고리즘의 비교: 배낭채우기 문제
	4.5.1 0-1 배낭 채우기 문제의 탐욕적인 해법
	4.5.2 배낭 빈틈없이 채우기 문제의 탐욕적인 접근방법
	4.5.3 0-1 배낭 채우기 문제를 푸는 동적계획법
	4.5.4 0-1 배낭 채우기 문제를 푸는 동적계획법 알고리즘의 계산
*/

//4.1 최소비용 신장트리
//4.1.1 프림 알고리즘
void prim(int n,       // 입력: 정점의 수
	const number W[][],  // 입력: 그래프의 인접행렬식 표현
	set_of_edges& F)     // 출력: 그래프의 MST에 속한 이음선의 집합
{
	index i, vnear;
	number min;
	edge e;
	index nearest[2..n];
	number distance[2..n];
	F = Ø;
	for (i = 2; i <= n; i++) {	// 초기화
		nearest[i] = 1;	      // vi에서 가장 가까운 정점을
		v1으로 초기화
			distance[i] = W[1][i];	// vi과 v1을 잇는 이음선의 
		가중치로 초기화
	}
	repeat(n - 1 times) {		// n-1개의 정점을 Y에 추가한다
		min = ;
		for (i = 2; i <= n; i++)		    // 각 정점에 대해서
			if (0 <= distance[i] <= min) { // distance[i]를 검사하여
				min = distance[i];		    // 가장 가까이 있는 vnear을
				vnear = i;			    // 찾는다.
			}
		e = vnear와 nearest[vnear]를 잇는 이음선;
		e를 F에 추가;
		distance[vnear] = -1;		// 찾은 노드를 Y에 추가한다.
		for (i = 2; i <= n; i++)
			if (W[i][vnear] < distance[i]) {// Y에 없는 각 노드에 대해서 
				distance[i] = W[i][vnear];    // distance[i]를 갱신한다.
				nearest[i] = vnear;
			}
	}
}
//4.1.2 크루스칼 알고리즘
void kruskal(int n, int m,	   // 입력: 정점의 수 n, 이음선의 수 m
	set_of_edges E,  // 입력: 가중치를 포함한 이음선의 집합
	set_of_edges& F) {// 출력: MST를 이루는 이음선의 집합
	index i, j;
	set_pointer p, q;
	edge e;
	E에 속한 m개의 이음선을 가중치의 비내림차순으로 정렬;
	F = emptyset;
	initial(n);
	while (F에 속한 이음선의 개수가 n - 1보다 작다) {
		e = 아직 점검하지 않은 최소의 가중치를 가진 이음선;
		i, j = e를 이루는 양쪽 정점의 인덱스;
		p = find(i);
		q = find(j);
		if (!equal(p, q)) {
			merge(p, q);
			e를 F에 추가;
		}
	}
}

//4.2 다익스트라 알고리즘


//4.3 스케줄 짜기
//4.3.2 마감시간이 있는 스케줄 짜기
