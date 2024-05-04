<snippet>
	<content><![CDATA[

namespace fast_factrize{
  long long fast_factrize_pow(long long n,long long k,const long long mod){
    __int128_t _n=n;
    __int128_t res=1;
    while(k){
      if(k&1){
        res*=_n;
        res%=mod;
      }
      _n*=_n;
      _n%=mod;
      k>>=1;
    }
    return res;
  }
  bool miller_rabin(long long n){
    if(n==2) return true;
    if(~n&1) return false;
    int s=__builtin_ctzll(n-1);
    long long d=(n-1)/(1LL<<s);
    vector<long long> _a;
    if(n<(1LL<<30)){
      _a={2,7,61};
    }else if(n<(1LL<<40)){
      _a={2,13,23,1662803};
    }else{
      _a={2,325,9375,28178,450775,9780504,1795265022};
    }
    for(auto& a:_a){
      if(n<=a) break;
      long long t=d;
      __int128_t y=fast_factrize_pow(a,t,n);
      while(t!=n-1&&y!=1&&y!=n-1){
        y*=y;
        y%=n;
        t*=2;
      }
      if(y!=n-1&&(~t&1)){
        return false;
      }
    }
    return true;
  }
  long long pollard_rho(long long n){
    if(~n&1) return 2;
    if(n%3==0) return 3;
    if(n%5==0) return 5;
    if(miller_rabin(n)) return n;
    long long c;
    auto f=[&](long long x){return (long long)(((__int128_t)x*(__int128_t)x+(__int128_t)c)%n);};
    for(c=1;c<n;c++){
      long long x=1,y=1,ys=1;
      __int128_t q=1;
      long long g=1;
      constexpr int m=128;
      for(int r=1;g==1;r<<=1){
        x=y;
        for(int i=0;i<r;i++) y=f(y);
        for(int k=0;g==1&&k<r;k+=m){
          ys=y;
          for(int i=0;i<m&&i<r-k;i++){
            q*=abs(x-(y=f(y)));
            q%=n;
          }
          g=gcd(n,(long long)q);
        }
      }
      if(g==n){
        do{
          g=gcd(n,abs(x-(ys=f(ys))));
        }while(g==1);
      }
      if(g!=n) return g;  
    }
  }
  vector<long long> factorize_init(long long n){
    if(n<=1) return {};
    long long p=pollard_rho(n);
    if(p==n) return {n};
    auto l=factorize_init(p);
    auto r=factorize_init(n/p);
    copy(r.begin(),r.end(),back_inserter(l));
    return l;
  }
  vector<long long> factorize(long long n){
    vector<long long> res=factorize_init(n);
    sort(res.begin(),res.end());
    return res;
  }
  vector<pair<long long,long long>> factorize_prime(long long n){
    vector<long long> res=factorize(n);
    vector<pair<long long,long long>> ret;
    for(int i=0;i<res.size();i++){
      if(i==0||res[i]!=res[i-1]) ret.push_back({res[i],1});
      else ret[ret.size()-1].second++;
    }
    return ret;
  }
  vector<long long> divisor(long long n){
    vector<pair<long long,long long>> v=factorize_prime(n);
    vector<long long> ret;
    auto f=[&](auto rc,int i,long long x)->void{
      if(i==(int)v.size()){
        ret.push_back(x);
        return;
      }
      for(int j=0;j<=v[i].second;j++){
        rc(rc,i+1,x);
        x*=v[i].first;
      }
    };
    f(f,0,1);
    sort(ret.begin(),ret.end());
    return ret;
  }
};
using namespace fast_factrize;
/*
*use:: vector<long long> d = divisor(n); to get all divisors(not only prime)
*use:: vector<pii> f = factorize_prime(n) to get prime factorisations and so prime divisors
*i think O(n^(1/4)) which means upto 1e30 for t=1? and t=1000 if n<=1e18
n<=1e18 with t=1000 tested: https://atcoder.jp/contests/abc293/submissions/39622575 =>438 ms
*/

]]></content>
	<!-- Optional: Set a tabTrigger to define how to trigger the snippet -->
	<tabTrigger>pollard</tabTrigger>
	<!-- Optional: Set a scope to limit where the snippet will trigger -->
	<scope>source.c++</scope>
</snippet>
