#include <iostream>

using namespace std;

struct Node
{
    Node *lchild;
    Node *rchild;
    int data;
};

class TreeNode
{
private:
    Node *root;
    void Inorder(Node *p);

public:
    TreeNode();

    ~TreeNode();

    // iterative insertion
    void Insert(int key);

    // recursive insertion
    Node *RInsert(Node *pointer, int key);

    void Inorder() { Inorder(this->root); }

    Node *getRoot();

    Node *Search(int key);

    Node *Delete(Node *pointer, int key);

    int Height(Node *p);
    Node *InPre(Node *p);
    Node *InSucc(Node *p);
};

void TreeNode::Insert(int key)
{
    Node *t = this->root;
    Node *r = NULL, *temp;
    // 当tree为空tree时，走这个block
    // 当t，也就是root为NULL时，create第一个node，记得把这个node assign to root.
    if (!t)
    {
        temp = new Node();
        temp->data = key;
        temp->lchild = temp->rchild = NULL;
        root = temp; // 这一步千万别忘记
        return;
    }

    // 当root存在时，走这个code block
    while (t)
    {
        r = t;
        if (key < t->data)
            t = t->lchild;
        else if (key > t->data)
            t = t->rchild;
        else
            return; // 元素不能重复
    }
    // 出了while，没有return到main，证明没有和key重复的元素，而且到了t==NULL的地方，这个地方可以insert一个新的node进来
    // 先create一个node：
    temp = new Node();
    temp->data = key;
    temp->lchild = temp->rchild = NULL;
    // 再看这个node应该放在t的left还是right，这里key其实也就是这个temp的data
    if (key < r->data)
        r->lchild = temp;
    else
        r->rchild = temp;
}

void TreeNode::Inorder(Node *p)
{
    if (p)
    {
        Inorder(p->lchild);
        cout << p->data << " ";
        Inorder(p->rchild);
    }
}

Node *TreeNode::getRoot()
{
    return root;
}

Node *TreeNode::Search(int key)
{
    Node *t = this->root;
    while (t)
    {
        if (key == t->data)
            return t;
        if (key < t->data)
            t = t->lchild;
        else
            t = t->rchild;
    }
    return NULL;
}

TreeNode::~TreeNode()
{
}

TreeNode::TreeNode()
{
    root = NULL;
}

Node *TreeNode::RInsert(Node *p, int key)
{
    Node *temp;
    if (!p)
    {
        temp = new Node;
        temp->data = key;
        temp->lchild = temp->rchild = NULL;
        // 这个条件一定要写，否则root还是为null
        if (this->getRoot() == NULL)
        {
            this->root = temp;
        }

        return temp;
    }
    if (key < p->data)
        p->lchild = RInsert(p->lchild, key);
    else if (key > p->data)
        p->rchild = RInsert(p->rchild, key);
    return p;
}

Node *TreeNode::Delete(Node *p, int key)
{
    Node *q;
    if (!p)
        return NULL;
    // if p is a leaf node,直接delete这个leafnode,从heap
    if (p->lchild == NULL && p->rchild == NULL)
    {
        // 如果这个p是root的话，删除root并且为NULL
        if (p == this->root)
            root = NULL;
        delete p;
        return NULL;
    }
    if (key < p->data)
        p->lchild = Delete(p->lchild, key);
    else if (key > p->data)
        p->rchild = Delete(p->rchild, key);
    else
    {
        // key == p->data 找到了这个node
        // 2个方案，inorder-predcessor，  inorder-sucessor
        // 根据height来决定
        if (Height(p->lchild) > Height(p->rchild))
        {
            // 从左边删除，要找到inorder的predcessor
            q = InPre(p->lchild);                   // 左边子树的最右边的node就是inorder-predcessor
            p->data = q->data;                      // 把找到的node p的data assign to p node
            p->lchild = Delete(p->lchild, q->data); // 删除这个q node，但是这个q 也许是leaf node，也许有其他children，因此继续recursive
            // 最终，recursive结束后，删除的是一个leaf node
        }
        else
        {
            q = InSucc(p->rchild);
            p->data = q->data;
            p->rchild = Delete(p->rchild, q->data);
        }
    }
    return p;
}

int TreeNode::Height(Node *p)
{
    int x, y;
    if (!p)
        return 0;
    x = Height(p->lchild);
    y = Height(p->rchild);
    return x > y ? x + 1 : y + 1;
}

Node *TreeNode::InPre(Node *p)
{
    // 当p不为NULL，且p的right child不为空，一直向右移动，直到移到最右边right most child 找到predcessor
    while (p && p->rchild != NULL)
    {
        p = p->rchild;
    }
    return p;
}

Node *TreeNode::InSucc(Node *p)
{
    while (p && p->lchild != NULL)
    {
        p = p->lchild;
    }
    return p;
}

int main()
{
    // TreeNode tn;
    // tn.Insert(10);
    // tn.Insert(5);
    // tn.Insert(20);
    // tn.Insert(8);
    // tn.Insert(30);

    // tn.Inorder(); // 5 8 10 20 30
    // cout << endl;
    // Node *result = tn.Search(10);
    // if (result)
    //     cout << "found the Node, the value is:" << result->data << endl;
    // else
    //     cout << "not found the key" << endl;

    // 测试recursive insertion
    TreeNode tn1;
    Node *root = tn1.getRoot();
    root = tn1.RInsert(root, 50);
    tn1.RInsert(root, 10);
    tn1.RInsert(root, 40);
    tn1.RInsert(root, 20);
    tn1.RInsert(root, 30);

    cout << "root value:" << tn1.getRoot()->data << endl;

    tn1.Inorder();
    cout << endl;
    // Node *result = tn1.Search(20);
    // if (result)
    //     cout << "found the Node, the value is:" << result->data << endl;
    // else
    //     cout << "not found the key" << endl;

    // delete
    tn1.Delete(root, 50);
    tn1.Inorder();
    cout << "root value:" << tn1.getRoot()->data << endl;

    return 0;
}
