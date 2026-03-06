/*二叉树结构体*/
struct TreeNode
{
    int val;//值
    TreeNode *left;//左子树
    TreeNode *right;//右子树
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};
TreeNode *n1 = new TreeNode(1);
TreeNode *n2 = new TreeNode(2);
TreeNode *n3 = new TreeNode(3);
TreeNode *n4 = new TreeNode(4);
TreeNode *n5 = new TreeNode(5);
int main()
{
n1 ->left = n2;
n1 ->right = n3;
n2 ->left = n4;
n2 ->right = n5;
/*插入与删除节点*/
TreeNode *P = new TreeNode(0);
//在n1于n2之间插入节点
n1 ->left = P;
P ->left = n2;
//删除节点P
n1 ->left = n2;
delete P;
return 0;
}
/*层序遍历*/
#include <vector>
#include <queue>
using std::vector;
using std::queue;
vector<int>levelorder(TreeNode *root)
{
    //初始化队列，加入根节点
    queue<TreeNode*>que;
    que.push(root);
    vector<int>res;//保存遍历序列
    while(!que.empty())
    {
        TreeNode *node = que.front();
        que.pop();
        res.push_back(node->val);
        //将左右子树加入队列
        if(node->left)que.push(node->left);
        if(node->right)que.push(node->right);
    }
    return res;

}
//深度优先搜索
/*前序遍历*/
void preorder(TreeNode *root,vector<int> &res)
{
    if(root == nullptr)
    return ;
    //访问优先级 根节点-.左子树->右子树
    res.push_back(root->val);
    preorder(root->left,res);
    preorder(root->right,res);
}
/*中序遍历*/
void inorder(TreeNode *root,vector<int> &res)
{
    if(root == nullptr)
    return ;
    //访问优先级 左子树->根节点->右子树
    inorder(root->left,res);
    res.push_back(root->val);
    inorder(root->right,res);
}
/*后序遍历*/
void postorder(TreeNode *root,vector<int> &res)
{
    if(root == nullptr)
    return ;
    //访问优先级 左子树->右子树->根节点
    postorder(root->left,res);
    postorder(root->right,res);
    res.push_back(root->val);

}
//空间复杂度分析：O(n)，其中n为二叉树的节点数。在最坏情况下，二叉树可能退化成链表，此时递归调用的深度为n，
//栈空间的使用为O(n)。在平均情况下，二叉树的高度为O(log n)，此时递归调用的深度为O(log n)，栈空间的使用为O(log n)。因此，空间复杂度为O(n)。
//二叉搜索树
/*二叉搜索树的定义：对于二叉搜索树中的每个节点，左子树中的所有节点的值都小于该节点的值，右子树中的所有节点的值都大于该节点的值。*/
 TreeNode *root;
 /*查找节点*/
 TreeNode* search(int num)
 {
    TreeNode *cur = root;
    //循环查找，越过叶节点后跳出
    while(cur != nullptr)
    {
        //目标节点在cur的右子树中
        if(cur ->val <num)
        cur = cur ->right;
        //目标节点在cur的左子树中
        else if(cur->val > num)
        cur = cur->left;
        //找到节点，跳出
        else
        break;
    }
    return cur;
 }
 /*插入节点*/
 void insert(int num)
 {
    //如果树为空，则初始化根节点
    if(root = nullptr)
    {
    root = new TreeNode(num);
    return ;
    }
    TreeNode *cur = root,*pre = nullptr;
    while(cur != nullptr)
    {
        //找到重复节点，直接返回
        if(cur->val == num)
        return ;
        pre = cur;
        //插入位置在cur的左子树
        if(cur->val > num)
        cur = cur->left;
        //插入位置在cur的右子树
        else
        cur = cur ->right;
    }
    //插入节点
    TreeNode *node = new TreeNode(num);
    if(pre ->val > num)
    pre->left = node;
    else
    pre->right = node;
 }
/*删除节点*/
void remove(int num)
{
    //树为空，直接返回
    if(root == nullptr)
    return ;
    TreeNode *cur = root, *pre = nullptr;
    //循环查找，越过叶节点后跳出
    while(cur != nullptr)
    {
        //目标节点在cur的右子树
        if(cur ->val <num)
        cur = cur ->right;
        //目标节点在cur的左子树
        else if (cur ->val >num)
        cur =cur ->left;
        //找到节点，跳出
        else
        break;
    }
    //未找到目标节点，直接返回
    if(cur == nullptr)
    return ;
    //删除节点为叶节点或仅有一个子节点
    if(cur ->left == nullptr || cur ->right == nullptr)
    {
        TreeNode *child = (cur ->left != nullptr)? cur->left : cur ->right;
        //删除节点cue
        if(cur != root)
        {
            if(pre ->left == cur)
            pre ->left = child;
            else
            pre-> right = child;
        }
        else
        root = child;
        delete cur;
    }
    //删除节点有两个子节点
    else
    {
        //找到右字数的最小节点，中序遍历
        TreeNode *temp = cur ->right;
        while(temp ->left != nullptr)
        temp = temp ->left;
        int tempVal = temp ->val;
        remove(tempVal);
        cur ->val = tempVal;
    }
}
/*AVL树节点*/
struct AVLnode
{
    int val;//节点值
    int height = 0;//节点高度
    AVLnode *left;
    AVLnode *right;
    AVLnode() = default;
    explicit AVLnode(int x):val(x){}
};
//获取节点高度
int height(AVLnode *node)
{
    return (node == nullptr)? -1 : node ->height;
}
//更新节点高度
void updateHeight(AVLnode *node)
{
    node ->height = std::max(height(node ->left),height(node->right)) +1;
}
/*获取平衡因子*/
int BalanceFactor(AVLnode *node)
{
    if(node == nullptr)
    return 0;
    return height(node ->left) - height(node ->right);
}
/*右旋操作*/
AVLnode* RightRotate(AVLnode* node)
{
    AVLnode *child = node ->left;
    AVLnode *grandchild = child ->right;
    //以child为原点，将node 向右旋转
    child ->right = node;
    node ->left =grandchild;
    updateHeight(node);
    updateHeight(child);
    return child;
}
/*左旋操作*/
AVLnode* LeftRotate(AVLnode *node)
{
    AVLnode *child = node ->right;
    AVLnode *grandchild = child ->left;
    child ->left = node;
    node ->right= grandchild;
    updateHeight(node);
    updateHeight(child);
    //返回子树根节点
    return child;
}
/*执行旋转操作，使该子树重新平衡*/
AVLnode* rotate(AVLnode *node)
{
    int _balanceFactor = BalanceFactor(node);
    //左偏树
    if(_balanceFactor > 1)
    {
        if(BalanceFactor(node ->left) >= 0)
        return RightRotate(node);
        else//先左旋再右旋
        {
            node ->left = LeftRotate(node ->left);
            return RightRotate(node);
        }
    }
    //右偏树
    else if(_balanceFactor < -1)
    {
        if(BalanceFactor(node ->right) <=0)
        return LeftRotate(node);
        else//先右旋再左旋
        {
            node ->right = RightRotate(node ->right);
            return LeftRotate(node);
        }
    }
    return node;
}
AVLnode *Root;
void insert(int val)
{
    Root = insertHelper(Root,val);
}
/*递归插入节点，辅助方法*/
AVLnode * insertHelper(AVLnode *node,int val)
{
    if(node == nullptr)
    return new AVLnode(val);
    /*查找插入位置并插入节点*/
    if(node ->val >val)
    node ->left = insertHelper(node ->left,val);
    else if(node ->val < val)
    node ->right = insertHelper(node ->right,val);
    else 
    return node;//重复节点不插入
    updateHeight(node);
    //执行旋转操作，使该子树重新平衡
    node = rotate(node);
    return node;
}
/* 删除节点 */
void remove(int val) {
    Root = removeHelper(Root, val);
}

/* 递归删除节点（辅助方法） */
AVLnode *removeHelper(AVLnode *node, int val) {
    if (node == nullptr)
        return nullptr;
    /* 1. 查找节点并删除 */
    if (val < node->val)
        node->left = removeHelper(node->left, val);
    else if (val > node->val)
        node->right = removeHelper(node->right, val);
    else {
        if (node->left == nullptr || node->right == nullptr) {
            AVLnode *child = node->left != nullptr ? node->left : node->right;
            // 子节点数量 = 0 ，直接删除 node 并返回
            if (child == nullptr) {
                delete node;
                return nullptr;
            }
            // 子节点数量 = 1 ，直接删除 node
            else {
                delete node;
                node = child;
            }
        } else {
            // 子节点数量 = 2 ，则将中序遍历的下个节点删除，并用该节点替换当前节点
            AVLnode *temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            int tempVal = temp->val;
            node->right = removeHelper(node->right, temp->val);
            node->val = tempVal;
        }
    }
    updateHeight(node); // 更新节点高度
    /* 2. 执行旋转操作，使该子树重新恢复平衡 */
    node = rotate(node);
    // 返回子树的根节点
    return node;
}