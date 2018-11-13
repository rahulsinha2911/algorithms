#include<bits/stdc++.h>
//22 #include<stdlib.h>
//#include<stdio.h>
typedef long long int ll;
using namespace std;
int main()
{  int n,m,x,y,st,w;
   cout<<"type the no of vertex and edge\n";
   cin>>n>>m;
   vector<pair<int,int> >v[n+1];
   pair<int,int>pr;
   bool b[n+1]={0};
   multiset<pair<int,int> >s;
    int par[n+1];
    int dis[n+1];
   // cout<<"type the no of vertex and edge\n";
   //cin>>n>>m;
    for(ll i=1;i<=n;i++)
   {
     dis[i]=7000;
     s.insert({7000,i});
   }
    s.insert({0,1});
    for(int i=1;i<=m;i++)
    {
        cout<<"type the vetex connection and its weight\n";
       cin>>x>>y>>w;
       pr.first=w;
        pr.second=y;
       // v[x].push_back(make_pair(w,y));
      v[x].push_back(pr);       //right method
    }
    //cout<<v[1][2].first;
    cout<<"type the start point\n";
    cin>>st;
    dis[st]=0;
    s.insert({0,st});
    while(!s.empty())
    {
        pair<int,int>ot=*s.begin();
        //wrong way  pair<int,int>::iterator it=ms.begin();
        int wn=ot.first;
        int  nd=ot.second;
        s.erase(s.begin());
        if(b[nd]==0)    // unvisited node
        {
            b[nd]=1;
            for(int i=0;i<v[nd].size();i++)
            {
                int wuv=v[nd][i].first;
                int vex=v[nd][i].second;
                if(wuv+wn<dis[vex])
                {
                  dis[vex]=wuv+wn;
                  par[vex]=nd;
                  s.insert({dis[vex],vex});
               }
      }
 }
 }for(int i=1;i<=n;i++)
 cout<<dis[i]<<" ";
 }
