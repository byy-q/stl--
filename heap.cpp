#include  <queue>
#include <vector>
#include <priority_queue>
int main()
{
    /*初始化小堆顶*/
    priority_queue<int,std::vector<int>,greater<int>MinHeap;
    //初始化大堆顶
    priority_queue<int,std::vector<int>,less<int>MaxHeap;
    //元素入堆
    MaxHeap.push(3);
    MaxHeap.push(1);
    MaxHeap.push(2);

}
//索引映射公式封装为函数
//获取左子节点的索引
ind left (int i)
{
    return 2*i+1;
}
//获取右子节点的索引
int right(int i)
{
    return  2*i+2;
}
//获取父节点的索引
int parent(int i)
{
    return (i-1)/2;
}
//访问堆顶元素
int peak()
{
    return MaxHeap[0];
}
/*元素入堆*/
void push(int val)
{
    //添加节点
    MaxHeap.push_back(val);
    //从底至顶堆化
    siftUp(MaxHeap.size() - 1);
}
void siftUp(int i)
{
    while(true)
    {
        //获取父节点的索引
        int p = parent(i);
        //当越过根节点或节点无需修复时，结束堆化
        if(p < 0||MaxHeap[p] >= MaxHeap[i])
        break;
        swap(MaxHeap[p],MaxHeap[i]);
        i = p;
    }
}
void pop()
{
    if(MaxHeap.isEmpty())
    throw out_of_range("Heap is empty");
    swap(MaxHeap[0],MaxHeap[MaxHeap.size() - 1]);
    MaxHeap.pop_back();
    siftDown(0);
}
void siftDown(int i)
{
    while(true)
    {
        int l =left(i),r = right(i),ma = i;
        if(l < MaxHeap.size() &&MaxHeap[l] > MaxHeap[ma])
        ma = l;
        if(r < MaxHeap.size() && Maxheap[r] > MaxHeap[ma])
        ma = r;
        if(ma == i)
        break;
        swap(MaxHeap[ma],MaxHeap[i]);
        i = ma;
    }
}
MaxHeap(std::vector<int> nums)
{
    MaxHeap = nums;//堆化除叶节点以外的其他节点
    for(int i = parent(MaxHeap.size() - 1);i >= 0;i--)
    {
        siftDown(i);
    }
}
/*基于堆查找数组中最大的k个元素*/
priority_queue<int,std::vector<int>,greater<int>>topKHeap(std::vextor<int> &nums,int k)
{
    priorty_queue<int,std::vector<int>,greater<int>>MinHeap;
    //将数组前k个元素入堆
    for(int i=0;i < k;i++)
    {
        MinHeap.push_back(nums[i]);
    }
    //遍历剩余元素，维护堆中元素为当前最大的k个
    for(int i = k;i<nums=size();i++)
    {
        //若当前元素大于堆顶元素，咋替换堆顶元素并调整堆
        if(nunms[i] > MinHeap.top())
        {
            MinHeap.pop();
            MinHeap.push(nums[i]);
        }
    }
    return MinHeap;
}
