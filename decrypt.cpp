#include <bits/stdc++.h>
#define ll long long
//#define int long long
using namespace std;
template<typename T>
inline string to_string(const T& x){
  stringstream ss;
  return ss<<x,ss.str();
}
int now=0;
struct bigN:vector<ll>{
  const static int base=1<<29,width=29;
  bool negative=0;
  bigN(const_iterator a,const_iterator b):vector<ll>(a,b){}
  bigN(string s){
    if(s.empty())return;
    negative=0;
    ll t=0;
    bitset<1000> a;
    for(int i=0; i<int(s.size()); ++i)for(int j=0; j<8; ++j){
        a[(i+1<<3)-j-1]=(unsigned char)s[i]&1, s[i]>>=1;
    }

    for(int i=0, j=(int(s.size())<<3)%width-1; i<int(s.size())<<3; ++i, --j)
    {
        if(j==-1)
        {
            if(i)push_back(t);
            t=0, j=width-1;
        }
        t=(t<<1)+a[i];
    }
    push_back(t);
    trim();
  }
    bigN(const int &x){push_back(x), trim();}
    bigN(const ll &x){push_back(x), trim();}
    bigN(const char* x):bigN(to_string(x)){}
  bigN():negative(0){}
  string tostr()
  {
      bitset<1000> a;
      string xx;
      int tt=0;
      int ok=0,yy=now%29,zz=yy,i,j,k,t2=0;
      unsigned char aa=0;
      //cerr<<now<<"\n";
      //cerr<<(*this)[tt]<<" ";
      for(i=0;i<now;i++)
      {
          //cerr<<i<<" "<<t2+zz-1<<"\n";

          a[t2+zz-1]=(*this)[tt]&1;
          zz--;
          (*this)[tt]/=2;
          if(zz==0)
          {
              tt++;
              //cerr<<(*this)[tt]<<" ";
              t2=i+1;
              zz=29;
          }
      }

      aa=0;
      for(i=0;i<now;i++)
      {
          //cerr<<a[i];
          aa+=a[i]*(1<<(8-(i%8)-1));

          if(i%8==7)
          {
              //cerr<<aa;
              xx+=aa;
              aa=0;
          }

      }
      //cerr<<"\n";

      return xx;

  }
  void trim(){
    while(size()&&!back())pop_back();
    if(empty())negative=0;
  }
  void carry(int _base=base){
    for(size_t i=0;i<size();++i){
      if(at(i)>=0&&at(i)<_base)continue;
      if(i+1u==size())push_back(0);
      int r=at(i)&_base-1;
      if(r<0)r+=_base;
      at(i+1)+=(at(i)-r)>>29,at(i)=r;
    }
  }
  int abscmp(const bigN &b)const{
    if(size()>b.size())return 1;
    if(size()<b.size())return -1;
    for(int i=int(size())-1;i>=0;--i){
      if(at(i)>b[i])return 1;
      if(at(i)<b[i])return -1;
    }
    return 0;
  }
  int cmp(const bigN &b)const{
    if(negative!=b.negative)return negative?-1:1;
    return negative?-abscmp(b):abscmp(b);
  }
  bool operator<(const bigN&b)const{return cmp(b)<0;}
  bool operator>(const bigN&b)const{return cmp(b)>0;}
  bool operator<=(const bigN&b)const{return cmp(b)<=0;}
  bool operator>=(const bigN&b)const{return cmp(b)>=0;}
  bool operator==(const bigN&b)const{return !cmp(b);}
  bool operator!=(const bigN&b)const{return cmp(b)!=0;}
  bigN abs()const{
    bigN res=*this;
    return res.negative=0, res;
  }
  bigN operator-()const{
    bigN res=*this;
    return res.negative=!negative,res.trim(),res;
  }
  bigN operator+(const bigN &b)const{
    if(negative)return -(-(*this)+(-b));
    if(b.negative)return *this-(-b);
    bigN res=*this;
    if(b.size()>size())res.resize(b.size());
    for(size_t i=0;i<b.size();++i)res[i]+=b[i];
    return res.carry(),res.trim(),res;
  }
  bigN operator-(const bigN &b)const{
    if(negative)return -(-(*this)-(-b));
    if(b.negative)return *this+(-b);
    if(abscmp(b)<0)return -(b-(*this));
    bigN res=*this;
    if(b.size()>size())res.resize(b.size());
    for(size_t i=0;i<b.size();++i)res[i]-=b[i];
    return res.carry(),res.trim(),res;
  }
  bigN operator*(const bigN &b)const{
    bigN res;
    res.negative=negative!=b.negative;
    res.resize(size()+b.size());
    for(size_t i=0;i<size();++i)
      for(size_t j=0;j<b.size();++j)
      {
        //assert(at(i)*b[j]>=0);
        if((res[i+j]+=at(i)*b[j])>=base){
          res[i+j+1]+=res[i+j]/base;
          res[i+j]%=base;
        }
      }
        return res.trim(),res;
  }
  bigN operator/(const bigN &b)const{
    int base=1<<29;
    int norm=base/(b.back()+1);
    bigN x=abs()*norm, y=b.abs()*norm, q, r;
    q.resize(x.size());
    for(int i=(int)x.size()-1;i>=0;--i){
      r=r*base+x[i];
      int s1=r.size()<=y.size()?0:r[y.size()];
      int s2=r.size()<y.size()?0:r[y.size()-1];
      ll d=(((ll)base*s1)+s2)/y.back();
      //cout<<r<<endl; fflush(stdout);
      r=r-y*d;
      //cout<<d<<endl; fflush(stdout);
      //cout<<r<<endl; fflush(stdout);
      //cout<<y<<endl; fflush(stdout);
      while(r.negative)r=r+y,--d;
      q[i]=d;
    }
    q.negative=negative!=b.negative;
    return q.trim(),q;
  }
  bigN operator%(const bigN &b)const{
    return *this-(*this/b)*b;
  }
  friend istream& operator>>(istream &ss,bigN &b){
    string s;
    return ss>>s, b=s, ss;
  }
  friend ostream& operator<<(ostream &ss,const bigN &b){
    for(int i=0; i<b.size(); ++i)ss<<b[i]<<' '; ss<<endl;
    return ss;
  }
  template<typename T>
    operator T(){
      stringstream ss;
      ss<<*this;
      T res;
      return ss>>res,res;
    }

};

bigN Pow(bigN a, bigN b, bigN p){
    bigN c=1;
    //cout<<1; fflush(stdout);
    for(; b>0; a=a*a%p, b=b/2){
        if(b%2==1)c=c*a%p;
        //cout<<1; fflush(stdout);
    }
    return c;
}
bigN Pow(bigN a, bigN b){
    bigN c=1;
    //cout<<1; fflush(stdout);
    for(; b>0; a=a*a, b=b/2){
        if(b%2==1)c=c*a;
        //cout<<1; fflush(stdout);
    }
    return c;
}
bigN S[1000005],P;
bigN xx[15];
bigN F[15];
bigN ss[1000005][15];
bigN aaaa[15][15];
bigN bbbb[15][15];
int all[15];
bigN ans=0,g;
char aaa[15];
stack < int > tt;
bigN abc=Pow(2,29);
char abcde[1005];
void get(bigN &x,FILE* xxx)
{
    x=0;

    int t;
    while(~fscanf(xxx,"%s",abcde))
    {
        //cerr<<abcde<<"\n";
        int t=0;
        if(abcde[0]=='-'&&abcde[1]=='1'&&abcde[2]=='\0') break;
        for(int i=0;abcde[i]!='\0';i++) t=t*10+(abcde[i]-'0');
        tt.push(t);
    }
    while(!tt.empty())
    {
        x=x*abc+tt.top();
        tt.pop();
    }

}

signed main()
{
    freopen("check.txt","w+t",stdout);
        strcpy(aaa,"1.txt");
        srand(time(NULL));
        int N=9,K=5,i,j,k,ok=1,tt=0,M;
    bigN a,b;
        auto xxx=fopen("public.txt","r");
    get(P,xxx);
    get(g,xxx);

        fscanf(xxx,"%d",&M);

        for(i=0;i<M;i++) get(S[i],xxx);
        for(i=1;i<=N;i++) get(xx[i],xxx);
        for(i=1;i<K;i++) get(F[i],xxx);
        fclose(xxx);
        tt=1;
        for(i=1;i<=N;i++)
        {

            all[i]=i;
                aaa[0]=i+'0';
                xxx=fopen(aaa,"r");
                if(xxx==NULL) continue;
                for(j=0;j<M;j++)
                {
                    //cerr<<i<<" "<<j<<"\n";
                    get(ss[j][i],xxx);
                    //cerr<<i<<" "<<j<<"\n";
                }
                fclose(xxx);
        }
        for(i=1;i<=N;i++)
    {
        bigN aa=1;
        for(j=1;j<=N;j++)
        {
            aaaa[i][j]=Pow((xx[i]-xx[j]+P)%P,P-2,P);
            aa=aa*xx[i]%(P-1);
            bbbb[i][j]=Pow(F[j],aa,P);
        }
    }
        for(int ttt=0;ttt<M;ttt++)
    {
        if(ttt<=1) now=8*13;
        else now=8*6;
        tt=0;
        for(i=1;i<=N;i++)
        {
            a=Pow(g,ss[ttt][i]%(P-1),P);
            b=S[ttt];
            for(j=1;j<K;j++) b=b*bbbb[i][j]%P;
            if(a==b) all[tt++]=i;
        }
        ans=0;
        for(i=1;i<=K;i++)
        {
            bigN tt=1;
            for(j=1;j<=K;j++)
            {
                if(i==j) continue;
                tt=tt*(P-xx[all[j]]);
                tt=tt*aaaa[all[i]][all[j]]%P;
            }
            ans=(ans+tt*ss[ttt][all[i]]);
        }
        //cerr<<(ans%P)<<"\n";
        cout<<(ans%P).tostr();
        //cerr<<"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"<<(ttt+1)*100/M<<"%";
    }
}
