//#define sort(nums) sort(nums.begin(),nums.end())
#include <bits/stdc++.h>
#define mod 1000000007
#define deb(x) cout<<#x<<" "<<x<<endl
using namespace std;
using ll = long long int;

ll segtree[100000];


void jets(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

void buildtree(int* arr,ll* segtree,int start,int end,int node){
	if(start==end){
		segtree[node]=arr[start];
		return ;
	}
	ll mid=(start+end)/2;
	buildtree(arr,segtree,start,mid,(2*node)+1);
	buildtree(arr,segtree,mid+1,end,(2*node)+2);
	segtree[node]=segtree[(2*node)+1]+segtree[(2*node)+2];
}

int findsum(int node,int lx,int rx,int l, int r){
	if(r<lx || l>rx)
		return 0;
	if(lx>=l && rx<=r)
		return segtree[node];
	else{
		int mid=(lx+rx)/2;
		return findsum((2*node)+1,lx,mid,l,r)+
		findsum((2*node)+2,mid+1,rx,l,r);
	}
}

void update(int i,int val,int lx,int rx,int node){
	if(i<lx || i>rx)
		return ;
	segtree[node]+=val;
	if(lx!=rx){
		int mid=(lx+rx)/2;
		update(i,val,lx,mid,2*node+1);
		update(i,val,mid+1,rx,2*node+2);
	}
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    jets();
    int n,q;
    cin>>n>>q;
    ll size=n;
    if(n&(n-1)!=0){
    	while(size&(size-1)!=0)
    		size++;
    }
    int arr[size]={0};
    for(int i=0;i<n;i++){
    	cin>>arr[i];
    }
    cout<<size<<endl;
    memset(segtree,0,sizeof(segtree));
    buildtree(arr,segtree,0,n-1,0);
    for(int i=0;i<(2*n)-1;i++){
    	cout<<segtree[i]<<" ";
    }
    cout<<endl;
    while(q--){
    	int t,l,r;//t is the type if query i.e 1 means sum 2 means update
    	cin>>t>>l>>r;
    	if(t==1)
    	cout<<findsum(0,0,n-1,l,r)<<endl;
    	else{
    		int val=r-arr[l];
    		update(l,val,0,n-1,0);
    	}
    }
    return 0;
}