#include <bits/stdc++.h>
using namespace std;

signed main(){
    FILE *in=fopen("shafile", "rb");
    char s[100], t[100];
    fread(s, 1, 64, in);
    for(int i=0; i<64; ++i)s[i]=s[i]<='9'?s[i]-48:s[i]-'a'+10;
    for(int i=0; i<32; ++i)t[i]=16*s[i*2]+s[i*2+1];
    for(int i=0; i<32; ++i)cout<<t[i];
}
