#include <bits/stdc++.h>
using namespace std;

signed main(){
    srand(time(0));
    FILE *out=fopen("key.txt", "wb");
    for(int i=0; i<32; ++i)fprintf(out, "%c", rand()&255);
}
