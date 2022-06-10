#include <bits/stdc++.h>
#define ll long long
//#define int long long
using namespace std;
//cout
//cerr
template<typename T>
inline string to_string(const T& x){
  stringstream ss;
  return ss<<x,ss.str();
}
struct bigN:vector<ll>{
  const static int base=1<<29,width=29;
  bool negative=0;
  bigN(const_iterator a,const_iterator b):vector<ll>(a,b){}
  bigN(string s){
    if(s.empty())return;
    //if(s[0]=='-')negative=1,s=s.substr(1);
    //else negative=0;
    negative=0;
    ll t=0;
    bitset<1000> a;
    for(int i=0; i<int(s.size()); ++i)
    {
        //cerr<<(int) s[i]<<" ";
        for(int j=0; j<8; ++j)
        {
            a[(i+1<<3)-j-1]=(unsigned char)s[i]&1, s[i]>>=1;
            //cout<<(i+1<<3)-j-1<<" "<<((unsigned char)s[i]&1)<<"\n";
        }
    }
    //for(int i=0;i<8*int(s.size());i++) cerr<<a[i];
    //cerr<<"\n";
    //for(int i=0; i<int(s.size())<<3; ++i)cout<<a[i]; cout<<endl;
    for(int i=0, j=(int(s.size())<<3)%width-1; i<int(s.size())<<3; ++i, --j){
        if(j==-1){
            if(i)
            {
                //cerr<<t<<" ";
                push_back(t);
            }
            t=0, j=width-1;
        }
        t=(t<<1)+a[i];
    }
    push_back(t);
    //cerr<<t<<"\n";
    /*for(int i=int(s.size())*8-1;i>=0;i-=width){
      ll t=0;
      for(int j=max(0,i-width+1);j<=i;++j)
        t=t*2+((unsigned char)s[j>>3]&1), s[j>>3]>>=1, cout<<j<<' '<<t<<' '<<(int)s[j>>3]<<endl;
      push_back(t);
    }*/
    trim();
  }
  //template<typename T>
    bigN(const int &x){push_back(x), trim();}
    bigN(const ll &x){push_back(x), trim();}
    bigN(const char* x):bigN(to_string(x)){}
  bigN():negative(0){}
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
        if((res[i+j]+=at(i)*b[j])>=base){
          res[i+j+1]+=res[i+j]/base;
          res[i+j]%=base;
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
    /*if(b.negative)ss<<'-';
    ss<<(b.empty()?0:b.back());
    for(int i=int(b.size())-2;i>=0;--i)
      ss<<setw(width)<<setfill('0')<<b[i];*/
    for(int i=0; i<b.size(); ++i)ss<<b[i]<<' ';
    ss<<-1;
    ss<<endl;
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

bigN P,Q;
bigN g=43;

bigN ss[1000005][15];
bigN xx[15];
bigN F[15];
bigN f[15];

char tt[1005];
int xxx[5005];
bigN S[1000005],s[1000005];
bigN aaaa[15][15];


signed main()
{

        P=2;
        Q=127;
        P=Pow(P,Q)-1;
        bigN P2=P*(P-1);

        srand(7122);
        FILE* file = fopen("key.txt", "r");
        //file.open("key.txt",ios::in|ios::binary);
        strcpy(tt,"1.txt");
        freopen("public.txt","w+t",stdout);
        int N=9,K=5,m,i,j,k,ok=0,t,M=0,xax=0;
        string aa,bb;
        char xxx;
        bigN TT;
        cout<<P<<g;
        for(xax=0;xax<32;)
        {
            xxx=getc(file);
            aa+=xxx;
            xax++;
            //cerr<<xax<<" "<<xxx<<"\n";
            if(xax%13==0)
        {
            s[M]=aa;
            S[M]=Pow(g,s[M],P);
            aa.clear();
            M++;

        }
        }

        if(xax%13)
    {
        s[M]=aa;
        S[M]=Pow(g,s[M],P);
        aa.clear();
        M++;

    }
    cout<<M<<"\n";
    for(i=0;i<M;i++) cout<<S[i];
        for(i=1;i<=N;i++)
        {
            string t;
            for(j=0;j<4;j++) t+=char(rand()&255);
                xx[i]=t;
                xx[i]=xx[i]%P;
                cout<<xx[i];
        }
        for(i=1;i<K;i++)
        {
            string t;
            for(j=0;j<4;j++) t+=char(rand()&255);
                f[i]=t;
                f[i]=f[i]%P;
                F[i]=Pow(g,f[i],P);
                cout<<F[i];
        }
        freopen("ans.txt","w+t",stdout);
        for(i=0;i<M;i++) cout<<s[i];
        for(i=1;i<=N;i++)
    {
        bigN aa=1;
        for(j=1;j<K;j++)
        {
            aa=aa*xx[i]%P2;
            aaaa[i][j]=f[j]*aa;
        }
    }
        for(i=1;i<=N;i++)
        {
            tt[0]=i+'0';
                freopen(tt,"w+t",stdout);
            for(k=0;k<M;k++)
        {
            ss[k][i]=s[k];
            for(j=1;j<K;j++) ss[k][i]=(ss[k][i]+aaaa[i][j]);
            cout<<ss[k][i]%(P*(P-1));
            //cerr<<"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"<<((i-1)*M+k+1)*100/(M*N)<<"%";
        }
        }
        return 0;
}
