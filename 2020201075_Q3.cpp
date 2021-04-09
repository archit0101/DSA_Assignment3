#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
struct node{
    ll val;
    ll index;
};
void swap(node*a,node*b){
    node tmp=*a;
    *a=*b;
    *b=tmp;
}
class minHeap{
    public:
    ll size;
    node* h;
    minHeap(node a[],ll n){
        h=a;
        size=n;
        for(ll i=(size-1)/2;i>=0;i--)
            heapify(i);
    }
    void heapify(ll i){
        ll l=2*i+1;
        ll r=2*i+2;
        ll small=i;
        if(l<size&&h[l].val<h[i].val)small=l;
        if(r<size&&h[r].val<h[small].val)small=r;
        if(small!=i){
            swap(&h[i],&h[small]);
            heapify(small);
        }
    }
    node getmin(){
        return h[0];
    }
    void replacemin(node a){
        h[0]=a;
        heapify(0);
    }
};
void merge(ll v[],ll start,ll mid,ll end){
    ll size_left=mid-start+1;
    ll size_right=end-mid;
    ll left[size_left];
    ll right[size_right];
    for(ll i=0;i<size_left;i++){
        left[i]=v[start+i];
    }
    for(ll i=0;i<size_right;i++){
        right[i]=v[mid+1+i];
    }
    ll i=0,j=0,k=start;
    while(i<size_left && j<size_right){
        if(left[i]<=right[j]){
            v[k]=left[i];
            i++;
        }
        else{
            v[k]=right[j];
            j++;
        }
        k++;
    }
    if(i<size_left){
        while(i<size_left){
            v[k]=left[i];
            i++;
            k++;
        }
    }
    if(j<size_right){
        while(j<size_right){
            v[k]=right[j];
            j++;
            k++;
        }
    }
}
void mergesort(ll v[],ll start,ll end){
    //cout<<v[0];
    if(start<end){
        ll mid=(start+end)/2;
        mergesort(v,start,mid);
        mergesort(v,mid+1,end);
        merge(v,start,mid,end);
    }
}
FILE* open_file(char* fname,char* mod){
    FILE* f=fopen(fname,mod);
    if(f==NULL){
        perror("Error!!!Unable to open file!");
        exit(EXIT_FAILURE);
    }
    return f;
}
void mergeFiles(char*output_file,ll n,ll k){
    FILE* index[k];
    ll i=0;
    while(i<k){
        char fname[2];
        snprintf(fname,sizeof(fname),"%lld",i);
        index[i]=open_file(fname,"r");
        i++;
    }
    FILE* fout=open_file(output_file,"w");
    node* h=new node[k];
    i=0;
    while(i<k){
        if(fscanf(index[i],"%lld,",&h[i].val)!=1)
            break;
        h[i].index=i;
        i++;
    }
    minHeap heap(h,i);
    for(ll freq=0;freq<i;){
        node root=heap.getmin();
        fprintf(fout,"%lld,",root.val);
        if(fscanf(index[root.index],"%lld,",&root.val)!=1){
            root.val=LLONG_MAX;
            freq++;
        }
        heap.replacemin(root);
    }
    i=0;
    while(i<k){
        fclose(index[i]);
        int z=remove(to_string(i).c_str());
        i++;
    }
    fclose(fout);
}
void create_chunks(char*input_file,ll chunksize,ll ways){
    FILE* input=open_file(input_file,"r");
    FILE* out[ways];
    char fname[2];
    ll i=0;
    while(i<ways){
        snprintf(fname,sizeof(fname),"%lld",i);
        out[i]=open_file(fname,"w");
        i++;
    }
    ll* a=(ll*)malloc(chunksize*sizeof(ll));
    bool flag=true;
    ll nxtopf=0;
    ll j;
    while(flag){
        j=0;
        while(j<chunksize){
            if(fscanf(input,"%lld,",&a[j])!=1){
                flag=false;
                break;
            }
            j++;
        }
        mergesort(a,0,j-1);
        ll x=0;
        while(x<j){
            fprintf(out[nxtopf],"%lld,",a[x]);
            x++;
        }
        nxtopf++;
    }
    ll x=0;
    while(x<ways){
        fclose(out[x]);
        x++;
    }
    fclose(input);
}
void kmergesort(char* input_file,char*output_file,ll ways,ll chunksize){
    create_chunks(input_file,chunksize,ways);
    mergeFiles(output_file,chunksize,ways);
}
ll fileSize(string file_name){
    ifstream file(file_name);
    string data = "";
    long long count = 0;
    while(getline(file, data,',')) count++;
    return count;
}
int main(int argc, char* argv[]){
    ll chunkSize=1000;
    ll k;
    string input_file=argv[1];
    string output_file=argv[2];
    long long int filesize=fileSize(input_file);
    if(filesize<1000)
        chunkSize=filesize;
    else if(filesize>100000 && filesize<=10000000)
        chunkSize=10000;
    else if(filesize>10000000)
        chunkSize=1000000;
    k=ceil(float(filesize)/chunkSize);
    //cout<<k<<endl;
    int n=input_file.size();
    int m=output_file.size();
    //cout<<n<<" "<<m<<endl;
    char ip[n],op[m];
    strcpy(ip,input_file.c_str());
    strcpy(op,output_file.c_str());
    kmergesort(ip,op,k,chunkSize);
    return 0;
}