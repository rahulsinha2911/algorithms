typedef long double ld;

int n; cin>>n;
ld a[n][n], b[n];
for(int i=0;i<n;++i) for(int j=0;j<n;++j) cin>>a[i][j];
for(int i=0;i<n;++i) cin>>b[i];

int per[n]; for(int i=0;i<n;++i) per[i]=i;
for(int k=0;k<n;++k){
  ld mx=0; int idx;
  for(int i=k;i<n;++i) if(mx<a[i][k]) mx=a[i][k], idx=i;
  swap(per[k], per[idx]);
  for(int i=0;i<n;++i) swap(a[k][i], a[idx][i]);

  for(int i=k+1;i<n;++i){
    a[i][k]/=a[k][k];
    for(int j=k+1;j<n;++j) a[i][j]-=a[i][k]*a[k][j];
  }
}

ld y[n], x[n];
for(int i=0;i<n;++i){
  y[i]=0;
  for(int j=0;j<i;++j) y[i]+=y[j]*a[i][j];
  y[i]=b[per[i]]-y[i];
}

for(int i=n-1;i>=0;--i){
  x[i]=0; for(int j=i+1;j<n;++j) x[i]+=a[i][j]*x[j];
  x[i]=y[i]-x[i]; x[i]/=a[i][i];
}
