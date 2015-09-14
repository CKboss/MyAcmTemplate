/*Suffix Automaton*/

/** 一点性质
 * 1.代码中 p->len 变量，它表示该状态能够接受的最长的字符串长度。
 *     该状态能够接受的最短的字符串长度。实际上等于该状态的 fa 指针指向的结点的 len + 1
 *      (p->len)-(p->fa->len)：表示该状态能够接受的不同的字符串数,不同的字符串之间是连续的,
 *      既:p 和 p->fa 之间 有最长的公共后缀长度 p->fa->len
 * 2. num 表示这个状态在字符串中出现了多少次，该状态能够表示的所有字符串均出现过 num 次
 * 3. 序列中第i个状态的子结点必定在它之后，父结点必定在它之前。
 *     既然p出现过，那么p->fa肯定出现过。因此对一个点+1就代表对整条fa链+1.
 * 4. 从root到每一个接收态表示一个后缀,到每一个普通节点表示一个子串
 * 5. 以某个字母开头的不同子串的数目,用DFS求
 * 
 * 串A="abaaaba"
它的后缀自动机是：
abaaaba
1 -- a ---> 2
1 -- b ---> 3
2 -- a ---> 7
2 -- b ---> 3
3 -- a ---> 4
4 -- a ---> 5
5 -- a ---> 6
6 -- b ---> 8
7 -- a ---> 6
7 -- b ---> 8
8 -- a ---> 9


banana
1--- a --->6
1--- b --->2
1--- n --->8
2--- a --->3
3--- n --->4
4--- a --->5
5--- n --->7
6--- n --->8
7--- a --->9
8--- a --->10
10--- n --->7

num:
7,1,1,1,1,3,1,2,1,2,

*/

const int CHAR=26,maxn=251000;

struct SAM_Node
{
    SAM_Node *fa,*next[CHAR];
    int len,id,pos;
    SAM_Node(){}
    SAM_Node(int _len)
    {
        fa=0; len=_len;
        memset(next,0,sizeof(next));
    }
};

SAM_Node SAM_node[maxn*2],*SAM_root,*SAM_last;
int SAM_size;

SAM_Node *newSAM_Node(int len)
{
    SAM_node[SAM_size]=SAM_Node(len);
    SAM_node[SAM_size].id=SAM_size;
    return &SAM_node[SAM_size++];
}

SAM_Node *newSAM_Node(SAM_Node *p)
{
    SAM_node[SAM_size]=*p;
    SAM_node[SAM_size].id=SAM_size;
    return &SAM_node[SAM_size++];
}

void SAM_init()
{
    SAM_size=1;
    SAM_root=SAM_last=newSAM_Node(0);
    SAM_node[0].pos=0;
}

void SAM_add(int x,int len)
{
    SAM_Node *p=SAM_last,*np=newSAM_Node(p->len+1);
    np->pos=len;SAM_last=np;
    for(;p&&!p->next[x];p=p->fa)
        p->next[x]=np;
    if(!p)
    {
        np->fa=SAM_root;
        return ;
    }
    SAM_Node *q=p->next[x];
    if(q->len==p->len+1)
    {
        np->fa=q;
        return ;
    }
    SAM_Node *nq=newSAM_Node(q);
    nq->len=p->len+1;
    q->fa=nq; np->fa=nq;
    for(;p&&p->next[x]==q;p=p->fa)
        p->next[x]=nq;
}

void SAM_build(char *s)
{
    SAM_init();
    int len=strlen(s);
    for(int i=0;i<len;i++)
        SAM_add(s[i]-'a',i+1);
}


/// !!!!!!!!!!!!! 统计每个节点出现的次数  
  
int c[maxn],num[maxn];  
SAM_Node* top[maxn];  
  
void Count(char str[],int len)  
{  
    memset(c,0,sizeof(c));
    memset(num,0,sizeof(num));
    
    for(int i=0;i<SAM_size;i++) c[SAM_node[i].len]++;  
    for(int i=1;i<=len;i++) c[i]+=c[i-1];  
    for(int i=0;i<SAM_size;i++) top[--c[SAM_node[i].len]]=&SAM_node[i];  
  
    SAM_Node *p=SAM_root;  
    for(;p->len!=len;p=p->next[str[p->len]-'a']) num[p->id]=1; num[p->id]=1;  
  
    for(int i=SAM_size-1;i>=0;i--)  
    {  
        p=top[i];  
        if(p->fa)  
        {  
            SAM_Node *q=p->fa; num[q->id]+=num[p->id];  
        }  
    }  
}  

/* L , R 该状态出现的最左和最右位置 */

void Count(char str[],int len)
{
    memset(c,0,sizeof(c));
    memset(num,0,sizeof(num));

    for(int i=0;i<SAM_size;i++) c[SAM_node[i].len]++;
    for(int i=1;i<=len;i++) c[i]+=c[i-1];
    for(int i=0;i<SAM_size;i++) top[--c[SAM_node[i].len]]=&SAM_node[i];

    memset(L,0,sizeof(L));
    memset(R,0,sizeof(R));

    SAM_Node *p=SAM_root;
    for(;p->len!=len;p=p->next[str[p->len]-'a'])
    {
        L[p->id]=R[p->id]=p->len;
        num[p->id]=1;
    }
    L[p->id]=R[p->id]=p->len;
    num[p->id]=1;

    for(int i=SAM_size-1;i>=0;i--)
    {
        p=top[i];
        if(L[p->id]==0&&R[p->id]==0)
        {
            L[p->id]=R[p->id]=p->pos;
        }
        if(p->fa)
        {
            SAM_Node* q=p->fa;
            if(L[q->id]==0||L[q->id]>L[p->id])
                L[q->id]=L[p->id];
            if(R[q->id]==0||R[q->id]<R[p->id])
                R[q->id]=R[p->id];

            num[q->id]+=num[p->id];
        }
    }
}
