#include<stdio.h>
int n,m;
int p[10000],f[10000];
void fifo(){
    for(int i=0;i<m;++i) f[i]=-1;
    int h=0;
    int s=0;
    for(int i=0;i<n;++i){
        int k=0;
        for(int r=0;r<m;++r)
        if(p[i]==f[r]){++h;k=1;break;}
        if(k==1)continue;
        for(int r=0;r<m;++r)
        if(f[r]==-1){
            f[r]=p[i];k=2;break;}
        if(k==2) continue;
        f[s]=p[i];
        s=(s+1)%m;
    }
    printf("FIFO :\t\t\t Page-Hit:%d\t\t\tPage-Fault:%d\n",h,n-h);
}
void lru(){
    for(int i=0;i<m;++i) f[i]=-1;
    int h=0;
    int t[m];
    for(int i=0;i<m;++i) t[i]=0;
    for(int i=0;i<n;++i){
        int k=0;
        for(int r=0;r<m;++r)
        if(f[r]!=-1) ++t[r];
        for(int r=0;r<m;++r)
        if(f[r]==p[i]){t[r]=1;k=1;break;}
        if(k==1){++h;continue;}
        for(int r=0;r<m;++r)
        if(f[r]==-1){f[r]=p[i];t[r]=1;
            k=2;break;}
        if(k==2) continue;
        int x=0;
        for(int r=1;r<m;++r)
        if(t[r]>t[x]) x=r;
        t[x]=1;f[x]=p[i];
    }
    printf("LRU :\t\t\t Page-Hit:%d\t\t\tPage-Fault:%d\n",h,n-h);
}
void optimal(){
    for(int i=0;i<m;++i) f[i]=-1;
    int h=0;
    for(int i=0;i<n;++i){
        int k=0;
        for(int r=0;r<m;++r)
        if(f[r]==p[i]){k=1;
            ++h;break;}
        if(k==1) continue;
        for(int r=0;r<m;++r)
        if(f[r]==-1){
        k=2;f[r]=p[i];break;}
        if(k==2) continue;
        int l=-1,xx=-1,y=1;
        for(int j=0;j<m;++j){
            y=1;
            for(k=i+1;k<n;++k)
             if(f[j]==p[k]){
                 y=0;
                 if(k>l){xx=j;l=k;}break;
             }
            if(y){
                f[j]=p[i];break;}
        }
        if(y) continue;
        f[xx]=p[i];
    }
    printf("OPTIMAL :\t\t Page-Hit:%d\t\t\tPage-Fault:%d\n",h,n-h);
}
int main(){
    printf("Enter No. of Page Strign and Page-Frame : ");
    scanf("%d%d",&n,&m);
    printf("Enter the Page-String : ");
    for(int i=0;i<n;++i)
    scanf("%d",&p[i]);
    fifo();lru();optimal();
}
