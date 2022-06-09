#include <bits/stdc++.h>
using namespace std;

signed main(){
    string s;
    while(getline(cin, s)){
        cout<<"echo '";
        for(int i=0; i<s.size(); ++i){
            if(s[i]=='\'')cout<<"'\"'\"'";
            else cout<<s[i];
        }
        cout<<"' >> $theFile\n";
    }
}
