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