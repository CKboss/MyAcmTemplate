/* Splay的各种操作 */
//暂时不完全,等我补完...

int tot,root,n,sz[maxn],ch[maxn][2],pre[maxn],rev[maxn];

void NewNode(int& x,int fa,int k) //静态建立新结点
{
    x=k;
    pre[x]=fa;
    ch[x][0]=ch[x][1]=0;
    rev[x]=0; sz[x]=1;
}

void Update_Rev(int r)//反转操作
{
    if(r)
    {
        swap(ch[r][0],ch[r][1]);
        rev[r]^=1;
    }
}

void Push_Up(int r)
{
    sz[r]=sz[ch[r][0]]+sz[ch[r][1]]+1;
}

void Push_Down(int r)
{
    if(rev[r])
    {
        Update_Rev(ch[r][0]);
        Update_Rev(ch[r][1]);
        rev[r]=0;
    }
}

void Build(int& x,int l,int r,int fa) //静态建树
{
    if(l>r) return ;
    int mid=(l+r)/2;
    NewNode(x,fa,mid);
    Build(ch[x][0],l,mid-1,x);
    Build(ch[x][1],mid+1,r,x);
    Push_Up(x);
}

void init()
{
    root=tot=0;
    ch[root][0]=ch[root][1]=sz[root]=pre[root]=rev[root]=0;
    Build(root,1,n,0);
}

void Rotate(int x,int kind) //旋转(基本不变)
{
    int y=pre[x];

    Push_Down(y);
    Push_Down(x);

    ch[y][!kind]=ch[x][kind];
    pre[ch[x][kind]]=y;

    if(pre[y])
        ch[pre[y]][ch[pre[y]][1]==y]=x;
    pre[x]=pre[y];

    ch[x][kind]=y;
    pre[y]=x;

    Push_Up(y);
}

void Splay(int r,int goal) //伸展(基本不变)
{
    Push_Down(r);
    while(pre[r]!=goal)
    {
        if(pre[pre[r]]==goal)
        {
            Push_Down(pre[r]);
            Push_Down(r);
            Rotate(r,ch[pre[r]][0]==r);
        }
        else
        {
            Push_Down(pre[pre[r]]);
            Push_Down(pre[r]);
            Push_Down(r);
            int y=pre[r];
            int kind=(ch[pre[y]][0]==y);

            if(ch[y][kind]==r) Rotate(r,!kind);
            else Rotate(y,kind);
            Rotate(r,kind);
        }
    }
    Push_Up(r);
    if(goal==0) root=r;
}

int Get_Min(int r) //最大最小,注意要pushdown
{
    Push_Down(r);
    while(ch[r][0])
    {
        r=ch[r][0];
        Push_Down(r);
    }
    return r;
}

int Get_Max(int r)
{
    Push_Down(r);
    while(ch[r][1])
    {
        r=ch[r][1];
        Push_Down(r);
    }
    return r;
}

void Remove() //移除根结点
{
    if(ch[root][0]==0)
    {
        root=ch[root][1];
        pre[root]=0;
    }
    else
    {
        int m=Get_Max(ch[root][0]);
        Splay(m,root);
        ch[m][1]=ch[root][1];
        pre[ch[root][1]]=m;
        root=m;
        pre[m]=0;
        Push_Up(root);
    }
}

/**************debug****************/

void showit(int x)
{
    if(x)
    {
        Push_Down(x);
        showit(ch[x][0]);
        printf("结点: %2d 左儿子: %2d 右儿子: %2d 父结点: %2d size: %2d rev: %2d \n",
               x,ch[x][0],ch[x][1],pre[x],sz[x],rev[x]);
        showit(ch[x][1]);
    }
}

void Debug()
{
    cout<<"-----------------------------\n";
    cout<<"root : "<<root<<endl;
    showit(root);
}

/*************Splay区间操作****************/
//POJ 3580 SuperMemo  : 内存池+区间加减+区间翻转+插入+删除+维护最值

const int maxn=220000;
const int INF=0x3f3f3f3f;
#define Key_Value ch[ch[root][1]][0]

int ch[maxn][2],rev[maxn],add[maxn],sz[maxn],pre[maxn],key[maxn],minn[maxn];
int root,tot1;
int s[maxn],tot2;

int n,q,a[maxn];

void NewNode(int& x,int father,int k)
{
    if(tot2) x=s[tot2--];
    else x=++tot1;

    ch[x][0]=ch[x][1]=rev[x]=add[x]=0;
    sz[x]=1; pre[x]=father; key[x]=minn[x]=k;
}

void Erase(int r)
{
    if(r)
    {
        s[++tot2]=r;
        Erase(ch[r][0]);
        Erase(ch[r][1]);
    }
}

void Upd_Rev(int x)
{
    if(!x) return ;
    swap(ch[x][0],ch[x][1]);
    rev[x]^=1;
}

void Upd_Add(int x,int d)
{
    if(!x) return ;
    key[x]+=d; minn[x]+=d;
    add[x]+=d;
}

void Push_Up(int x)
{
    sz[x]=sz[ch[x][1]]+sz[ch[x][0]]+1;
    minn[x]=key[x];
    if(ch[x][0]) minn[x]=min(minn[x],minn[ch[x][0]]);
    if(ch[x][1]) minn[x]=min(minn[x],minn[ch[x][1]]);
}

void Push_Down(int x)
{
    if(rev[x])
    {
        Upd_Rev(ch[x][0]); Upd_Rev(ch[x][1]);
        rev[x]=0;
    }
    if(add[x])
    {
        Upd_Add(ch[x][0],add[x]); Upd_Add(ch[x][1],add[x]);
        add[x]=0;
    }
}

void Build(int& x,int l,int r,int fa)
{
    if(l>r) return ;
    int mid=(l+r)/2;
    NewNode(x,fa,a[mid]);
    Build(ch[x][0],l,mid-1,x);
    Build(ch[x][1],mid+1,r,x);
    Push_Up(x);
}

void Init()
{
    root=tot1=tot2=0;
    ch[root][0]=ch[root][1]=pre[root]=sz[root]=0;
    minn[root]=key[root]=INF;
    NewNode(root,0,INF);
    NewNode(ch[root][1],root,INF);
    Build(Key_Value,1,n,ch[root][1]);
    Push_Up(ch[root][1]);
    Push_Up(root);
}

void Rotate(int x,int kind)
{
    int y=pre[x];
    Push_Down(y);
    Push_Down(x);
    ch[y][!kind]=ch[x][kind];
    pre[ch[x][kind]]=y;
    if(pre[y]) ch[pre[y]][ch[pre[y]][1]==y]=x;
    pre[x]=pre[y];
    pre[y]=x;
    ch[x][kind]=y;
    Push_Up(y);
}

void Splay(int r,int goal)
{
    Push_Down(r);
    while(pre[r]!=goal)
    {
        if(pre[pre[r]]==goal)
        {
            Push_Down(pre[r]);
            Push_Down(r);
            Rotate(r,ch[pre[r]][0]==r);
        }
        else
        {
            Push_Down(pre[pre[r]]);
            Push_Down(pre[r]);
            Push_Down(r);
            int y=pre[r];
            int kind=(ch[pre[y]][0]==y);
            if(ch[y][kind]==r) Rotate(r,!kind);
            else Rotate(y,kind);
            Rotate(r,kind);
        }
    }
    Push_Up(r);
    if(goal==0) root=r;
}

int Get_Kth(int r,int k)
{
    Push_Down(r);
    int t=sz[ch[r][0]]+1;
    if(k==t) return r;
    if(t<k) return Get_Kth(ch[r][1],k-t);
    else return Get_Kth(ch[r][0],k);
}

int Get_Min(int r)
{
    Push_Down(r);
    while(ch[r][0])
    {
        r=ch[r][0];
        Push_Down(r);
    }
    return r;
}

int Get_Max(int r)
{
    Push_Down(r);
    while(ch[r][1])
    {
        r=ch[r][1];
        Push_Down(r);
    }
    return r;
}

///.......do..it........

void ADD(int l,int r,int d)
{
    Splay(Get_Kth(root,l),0);
    Splay(Get_Kth(root,r+2),root);
    Upd_Add(Key_Value,d);
    Push_Up(ch[root][1]);
    Push_Up(root);
}

void REVERSE(int l,int r)
{
    Splay(Get_Kth(root,l),0);
    Splay(Get_Kth(root,r+2),root);
    Upd_Rev(Key_Value);
    Push_Up(ch[root][1]);
    Push_Up(root);
}

void DELETE(int p)
{
    Splay(Get_Kth(root,p),0);
    Splay(Get_Kth(root,p+2),root);
    Erase(Key_Value);
    pre[Key_Value]=0;
    Key_Value=0;
    Push_Up(ch[root][1]);
    Push_Up(root);
}

void INSERT(int p,int v)
{
    Splay(Get_Kth(root,p+1),0);
    Splay(Get_Kth(root,p+2),root);
    NewNode(Key_Value,ch[root][1],v);
    Push_Up(ch[root][1]);
    Push_Up(root);
}

int MIN(int l,int r)
{
    Splay(Get_Kth(root,l),0);
    Splay(Get_Kth(root,r+2),root);
    return minn[Key_Value];
}

void REVOLVE(int l,int r,int t)
{
    int len=r-l+1;
    t=(t%len+len)%len;
    if(t==0) return ;
    int c=r-t+1;
    ///[l..c-1] and [c..r]
    Splay(Get_Kth(root,c),0);
    Splay(Get_Kth(root,r+2),root);
    int temp=Key_Value;
    Key_Value=0;
    Push_Up(ch[root][1]);
    Push_Up(root);

    Splay(Get_Kth(root,l),0);
    Splay(Get_Kth(root,l+1),root);
    Key_Value=temp;
    pre[Key_Value]=ch[root][1];
    Push_Up(ch[root][1]);
    Push_Up(root);
}


void Remove_Root()//删掉根结点
{
    if(ch[root][1]==0 || ch[root][0]==0)
    {
        root=ch[root][0]+ch[root][1];
        pre[root]=0;
        return;
    }
    int k=Get_Min(ch[root][1]);//找到右子树中最小的
    Splay(k,root);//旋转过来，使得右子树没有左孩子
    ch[ch[root][1]][0]=ch[root][0];
    root=ch[root][1];
    pre[ch[root][0]]=root;
    pre[root]=0;
    Push_Up(root);
}


/*****************DEBUG*********************/  
  
void SHOW(int x)  
{  
    Push_Down(x);  
    if(ch[x][0]) SHOW(ch[x][0]);  
    printf("x: %d size: %d pre: %d left: %d right: %d key: %d\n",x,sz[x],pre[x],ch[x][0],ch[x][1],key[x]);  
    if(ch[x][1]) SHOW(ch[x][1]);  
}  
  
void DEBUG()  
{  
    cout<<"..........debug.............."<<endl;  
    SHOW(root);  
}  
