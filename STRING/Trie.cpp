/*字典树*/

const int CHAR=26,MAXN=100000;

struct Trie
{
    int tot,root,child[MAXN][CHAR];
    bool flag[MAXN];

    Trie()
    {
        memset(child[1],0,sizeof(child[1]));
        flag[1]=true;
        root=tot=1;
    }

    void Insert(const char *str)
    {
        int *cur=&root;
        for(const char*p=str;*p;p++)
        {
            cur=&child[*cur][*p-'a'];
            if(*cur==0)
            {
                *cur=++tot;
                memset(child[tot],0,sizeof(child[tot]));
                flag[tot]=false;
            }
        }

        flag[*cur]=true;
    }

    bool Query(const char *str)
    {
        int *cur=&root;
        for(const char *p=str;*p&&*cur;p++)
            cur=&child[*cur][*p-'a'];
        return (*cur)&&flag[*cur];
    }

}tree;


