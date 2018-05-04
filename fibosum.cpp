#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define mod 1000000007
ll cal(ll );

ll fun(ll x)
{
    if(x==0)
        return 0;
    else if(x==1 || x==2)
        return 1;
    else if(x==3)
        return 2;
    else
    {
        return cal(x-1)%mod;
    }
}
ll cal(ll b)
{
     ll a[2][2]= {{1,1},{1,0}};
    ll result[2][2]={{1,0},{0,1}};

   // cout<<"pow= "<<b<<"\n";
    if(b==0)
    {
        return 1;
    }
    else
    {


        ll c[2][2];
        while(b>0)
        {
            if(b%2!=0)
            {
                c[0][0]=(((result[0][0])*(a[0][0]))%mod +  (result[0][1]*a[1][0])%mod)%mod;
                c[0][1]=(((result[0][0])*(a[0][1]))%mod + (result[0][1]*a[1][1] )%mod)%mod;
                c[1][0]=(((result[1][0])*(a[0][0]))%mod + (result[1][1]*a[1][0] )%mod)%mod;
                c[1][1]=(((result[1][0])*(a[0][1]))%mod + (result[1][1]*a[1][1] )%mod)%mod;
                result[0][0]=c[0][0];
                result[0][1]=c[0][1];
                result[1][0]=c[1][0];
                result[1][1]=c[1][1];
            }

                b=b/2;

                c[0][0]=(((a[0][0])*(a[0][0]))%mod + (a[0][1]*a[1][0])%mod)%mod;
                c[0][1]=(((a[0][0])*(a[0][1]))%mod + (a[0][1]*a[1][1])%mod)%mod;
                c[1][0]=(((a[1][0])*(a[0][0]))%mod + (a[1][1]*a[1][0])%mod)%mod;
                c[1][1]=(((a[1][0])*(a[0][1]))%mod + (a[1][1]*a[1][1])%mod)%mod;

                a[0][0]=c[0][0];
                a[0][1]=c[0][1];
                a[1][0]=c[1][0];
                a[1][1]=c[1][1];
        }
    }
     return result[0][0]%mod;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
  int t;
  cin>>t;
  while(t--)
  {
      ll a,b;
      cin>>a>>b;
      cout<<(mod+ mod + (2*fun(b+1)%mod)%mod -fun(a+1)%mod -fun(b-1)%mod)%mod <<"\n";   // remenber two negative item put two mod to compensate negative

     // cout<<fun(b+1)<<" "<<fun(a+1)<<" "<<fun (b-1) <<"\n";
  }
}
