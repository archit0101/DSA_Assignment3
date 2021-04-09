#include<stdio.h>
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
bool check_bit(long long N,int i);
struct Trie_Node{
    Trie_Node* child[2];
    bool isPresent;
};

Trie_Node* getNode(){
    Trie_Node* temp= new Trie_Node;
    temp->child[0]=NULL;
    temp->isPresent=false;
    temp->child[1]=NULL;
    return temp;
}
void insert_val(Trie_Node* root,long long val){
    Trie_Node* pointer=root;
    for(int i=39;i>=0;i--){
        int x=check_bit(val,i);
        //cout<<x;
        if(!pointer->child[x]){
            pointer->child[x]=getNode();
        }
        pointer=pointer->child[x];
    }
    pointer->isPresent=true;
}
bool check_bit(long long N,int i){
    long long x=1;
    return (bool)(N & (x<<i));
}
int Max_XOR(Trie_Node*root, long long val){
    Trie_Node* pointer=root;
    int ans=0;
    for(int i=39;i>=0;i--){
        int x=check_bit(val,i);
        if(pointer->child[x^1]){
            ans=ans+(1<<i);
            cout<<(1<<i)<<endl;
            //cout<<ans<<endl;
            pointer=pointer->child[x^1];
        }
        else{
            pointer=pointer->child[x];
        }
    }  
    return ans;
}

int main(){
    Trie_Node*root=getNode();
    int N,q;
    cin>>N>>q;
    long long ans[q];
    for(int i=0;i<N;i++){
        long long a;
        cin>>a;
        insert_val(root,a);
        //cout<<endl;
    }
    for(int i=0;i<q;i++){
        long long a;
        cin>>a;
        ans[i]=Max_XOR(root,a);
    }
    for(int i=0;i<q;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}