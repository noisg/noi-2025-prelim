#include <cstdio>
 
int a[10];
int b[10];
int main() {
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++) {
        scanf("%d", a+i);
    }
    for(int i=0; i<n; i++) {
        scanf("%d", b+i);
    }
    int ans = 0;
    for(int i=0; i<n; i++) {
        if(a[i]<b[i]) {
            ans += a[i];
        } else {
            ans += b[i];
        }
    }
    printf("%d", ans);
}