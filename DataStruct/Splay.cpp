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

/*************struct****************/
