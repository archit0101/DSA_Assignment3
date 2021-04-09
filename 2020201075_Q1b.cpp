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
    int k;
    //cout<<input.length();
    cin>>input>>k;
    int m=input.length();
    /*string append=input+input;
    int n = append.length();*/
    char char_array[m + 1];
    strcpy(char_array, input.c_str());
    int *suffixArr = build(char_array,m);
    int max=0;
    for(int i=0;i<=m-k;i++){
        string a="",b="";
        for(int j=suffixArr[i];j<m;j++){
                a+=char_array[j];
            }
        for(int j=suffixArr[i+k-1];j<m;j++){
                b+=char_array[j];
            }
            //cout<<a<<" "<<b<<endl;
        int j=0,x=0,count=0;
        while(a[j]==b[x] &&(j<m && x<m)){
            j++;
            x++;
            count++;
        }
        if(count>max){
            max=count;
        }
    }
    if(max==0){
        cout<<"-1"<<endl;
    }
    else
    cout<<max<<endl;
    return 0;
}