#include <stdio.h>
#include <stdlib.h>
#define ADJ(i, j) adj[(i) * vertex + j]
#define SEP(i, j) sep[(i) * vertex + j]
#define INF -1
int vertex;
int *adj; // adjency matrix
int *sep;

void create_adj_mat() {
    adj = (int *) malloc(sizeof(int) * vertex * vertex);
    sep = (int *) malloc(sizeof(int) * vertex * vertex);
    for (int i=0; i<vertex; i++) {
        for (int j=0; j<vertex; j++) {
            if ((i ^ j) == 0) ADJ(i, j) = 0;
            else ADJ(i, j) = INF; 
            SEP(i,j) = INF;
        }
    }
    int v1, v2;
    while (scanf("%d%d", &v1, &v2) != EOF) {
        scanf("%d", &ADJ(v1-1, v2-1));
    }
}

void solve(int mid){
    for (int i=0; i<vertex; i++) {
        for (int j=0; j<vertex; j++) {
            if (i != mid && j != mid && i != j && ADJ(i,mid) != INF && ADJ(mid,j) != INF) {
                int tmp = ADJ(i, mid) + ADJ(mid, j);
                if ((ADJ(i, j) == INF) || (tmp < ADJ(i, j))) {
                    ADJ(i, j) = tmp;
                    SEP(i, j) = mid;
                }
            }
        }      
    }
}

void searchPath(int start, int end) {
    if (start == end) {
        return;
    }
    if (SEP(start, end) != INF){
        SEP(start, SEP(start, end));
        printf("%d -> ", SEP(start, end));
        SEP(SEP(start, end), end);
    }
}

void printPath() {
    for (int i=0; i<vertex; i++) {
        for (int j=0; j<vertex; j++) {
            printf("%d to %d dist: %d, %d ->  ", i, j, ADJ(i, j), i);
            searchPath(i, j);
            printf("%d\n", j);
        }
    }
        printf("\n");
}

int main() {
    scanf("%d", &vertex);    
    create_adj_mat();
    for (int i=0; i<vertex; i++) {
        solve(i);
    }
    printPath();
}
