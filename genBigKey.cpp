#include <bits/stdc++.h>
using namespace std;
char key[100], tokey[10000], pdf[20000007]; int n=32, m=20000000, t=100, l;
signed main(){
    char s1[10000], s2[10000];
    cin>>s1>>s2;
    FILE *Key=fopen("key.txt", "rb"), *Pdf=fopen(s1, "rb");
    l=n=fread(key, 1, n, Key), m=fread(pdf, 1, m, Pdf);
    for(int i=0; i<n; ++i)tokey[i]=key[i];
    for(int i=0; i<t; ++i){
        for(int j=l+n-2; j>=0; --j){
            int s=0;
            for(int k=0; k<n; ++k)if(j-k<l&&j-k>=0)s+=(int)tokey[j-k]*key[k];
            tokey[j]=s;
        }
        l+=n-1;
    }
    for(int i=0; i<m; ++i)pdf[i]^=tokey[i%l];
    FILE *Res=fopen(s2, "wb");
    fwrite(pdf, 1, m, Res);
}
