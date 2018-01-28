#include<bits/stdc++.h>
using namespace std;
long long bit1[1000001];
long long bit2[1000001];
void update1(long long ,long long);                   // range update for 1st fenwick tree
long long query1(long long  );                         //and range query on 1st fenwick tree
void update2(long long ,long long);                   // range update for 1st fenwick tree
long long query2(long long);                          //and range query on 2st fenwick tree
long long n;
int main()
{
	
		long long c;                  //no of operations
		cin>>n>>c;
		for(long i=0;i<c;i++)
		{
			long long in,p,q,v;
			cin>>in;
			if(in==0)
			{
				cin>>p>>q>>v;
				update1(p,v);
				update1(q+1,(-1*v));
				update2(p,v*(p-1));
				update2(q+1,(v*(-1*q)));
			}
			else
			{
				cin>>p>>q;
				cout<<query1(q)*q - query2(q) - query1(p-1)*(p-1) + query2(p-1)<<endl;
			}
		}
}
void update1(long long x,long long v)
{
	while(x<=n)
	{
		bit1[x]+=v;
		x+=x&(-x);
	}
}
void update2(long long x,long long v)
{
	while(x<=n)
	{
		bit2[x]+=v;
		x+=x&(-x);
	}
}
long long query1(long long x)
{   
    long long sum=0;
	while(x>0)
	{
		sum+=bit1[x];
		x-=x&(-x);
	}
	return sum;
}
long long query2(long long x)
{
    long long sum=0;
	while(x>0)
	{
		sum+=bit2[x];
		x-=x&(-x);
	}
	return sum;
}

