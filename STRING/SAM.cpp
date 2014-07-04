/*Suffix Automaton*/

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
    SAM_size=0;
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


/*拓扑排序和Left,Right,num*/


 ///get tupo sort
    for(int i=0;i<SAM_size;i++)
        c[SAM_node[i].len]++;
    for(int i=1;i<=len;i++)
        c[i]+=c[i-1];
    for(int i=0;i<SAM_size;i++)
        top[--c[SAM_node[i].len]]=&SAM_node[i];

    ///get L,R,num
    SAM_Node *p=SAM_root;
    for(;p->len!=len;p=p->next[str[p->len]-'a'])
    {
        num[p->id]=1;
        L[p->id]=R[p->id]=p->len;
    }
    for(int i=SAM_size-1;i>=0;i--)
    {
        p=top[i];
        if(L[p->id]==0&&R[p->id]==0)
        {
            L[p->id]=R[p->id]=p->pos;
        }
        if(p->fa)
        {
            SAM_Node *q=p->fa;
            num[q->id]+=num[p->id];
            if(L[q->id]==0||L[q->id]>L[p->id])
                L[q->id]=L[p->id];
            if(R[q->id]==0||R[q->id]<R[p->id])
                R[q->id]=R[p->id];
        }
    }

