#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;
struct node{
    int rank[2];
    int index;
};
int compare(node a,node b){
    if(a.rank[0]==b.rank[0]){
        if(a.rank[1]<b.rank[1])
            return 1;
        return 0;
    }
    else if(a.rank[0]<b.rank[0]){
        return 1;
    }
    return 0;
}
int* build(char*txt,int n){
    node suffixes[n];
    int index[n];
    int i=0;
    while(i<n){
        suffixes[i].index=i;
        suffixes[i].rank[0]=txt[i]-'a';
        if((i+1)<n){
            suffixes[i].rank[1]=txt[i+1]-'a';
        }
        else{
            suffixes[i].rank[1]=-1;
        }
        i++;
    }
    sort(suffixes,suffixes+n,compare);
    int k=4;
    while(k<2*n){
      int rank=0;
      int prev_rank=suffixes[0].rank[0];
      suffixes[0].rank[0]=rank;
      index[suffixes[0].index]=0;
      i=1;
      while(i<n){
          if(suffixes[i].rank[0]==prev_rank&&suffixes[i].rank[1]==suffixes[i-1].rank[1]){
              prev_rank=suffixes[i].rank[0];
              suffixes[i].rank[0]=rank;
          }
          else{
              prev_rank=suffixes[i].rank[0];
              suffixes[i].rank[0]=++rank;
          }
          index[suffixes[i].index]=i;
          i++;
      }
      i=0;
      while(i<n){
          int nextindex=suffixes[i].index+k/2;
          if(nextindex<n){
              suffixes[i].rank[1]=suffixes[index[nextindex]].rank[0];
          }
          else{
              suffixes[i].rank[1]=-1;
          }
          i++;
      }
      sort(suffixes,suffixes+n,compare);
      k*=2;  
    }
    int* suffix_array=new int[n];
    i=0;
    while(i<n){
        suffix_array[i]=suffixes[i].index;
        i++;
    }
    return suffix_array;
}
int main(){
    string input;
    cin>>input;
    string rev;
    rev=input;
    reverse(rev.begin(),rev.end());
    string append=input+"@"+rev;
    int n=append.size();
    char char_array[n+1];
    strcpy(char_array,append.c_str());
    int* suffArray=build(char_array,n);
    int LCP[n];
    LCP[0]=0;
    for(int i=1;i<n;i++){
         string a="",b="";
        for(int j=suffArray[i-1];j<n;j++){
                a+=char_array[j];
            }
        for(int j=suffArray[i];j<n;j++){
                b+=char_array[j];
            }
        int j=0,x=0,count=0;
        while(a[j]==b[x] &&(j<n && x<n)){
            j++;
            x++;
            count++;
        }
        LCP[i]=count;
    }
    for(int i=0;i<n;i++){
        cout<<LCP[i]<<" ";
    }
    int res=0;
	int startptr=0;
    int m=(n-1)/2;
	for(int i=1;i<n;++i){
		if((LCP[i]>res)){
			if((suffArray[i-1]<m && suffArray[i]>m)||(suffArray[i]<m && suffArray[i-1]>m)){
				res=LCP[i];
				startptr=suffArray[i];
			}
		}
	}
	for(int j=startptr;j<startptr+res;j++){
                cout<<char_array[j];
            }
    cout<<endl;
    return 0;
}