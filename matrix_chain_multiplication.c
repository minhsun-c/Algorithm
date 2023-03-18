#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 2147483647
#define MUL(i, j) mul[(i) * mcnt + j]
#define SEP(i, j) sep[(i) * mcnt + j]
int mcnt; // matrix count
int *dim; // dimension of matrics
int *mul; // count of multiplication;
int *sep; // where to sep

void allocate() {
    dim = (int *)malloc(sizeof(int) * (mcnt+1));
    mul = (int *)malloc(sizeof(int) * mcnt * mcnt);
    sep = (int *)malloc(sizeof(int) * mcnt * mcnt);
}

void chain(int start, int end) {
    if (start == end) {
        printf("A%d", start+1);
        return;
    }
    printf("(");
    chain(start, SEP(start, end));
    chain(SEP(start, end)+1, end);
    printf(")");
}

void solve(int r, int c) {
    if (r >= mcnt || c >= mcnt) return;
    int min = INT_MAX, mink, tmp;
    for (int k=r; k<c; k++) {
        tmp = MUL(r,k) + MUL(k+1, c) + dim[r] * dim[k+1] * dim[c+1];
        if (tmp < min) {
            min = tmp;
            mink = k;
        }
    }
    SEP(r, c) = mink;
    MUL(r, c) = min;
    solve(r+1, c+1);
}

int main() {
    scanf("%d", &mcnt);
    allocate();
    for (int i=0; i<=mcnt; i++) scanf("%d", &dim[i]);
    for (int i=0; i<mcnt; i++) MUL(i, i) = 0;
    for (int i=1; i<mcnt; i++) solve(0, i);
    chain(0, mcnt-1);
    prinf("\n");
}
