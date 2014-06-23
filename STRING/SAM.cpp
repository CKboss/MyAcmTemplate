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
