//在数组中删除首元素的时间复杂度为 O(n)
// ，这会导致出队操作效率较低。然而，我们可以采用以下巧妙方法来避免这个问题。

//我们可以使用一个变量 front 指向队首元素的索引，并维护一个变量 size 用于记录队列长度。定义 rear = front + size ，这个公式计算出的 rear 指向队尾元素之后的下一个位置。

//基于此设计，数组中包含元素的有效区间为 [front, rear - 1]，各种操作的实现方法如图 5-6 所示。

//入队操作：将输入元素赋值给 rear 索引处，并将 size 增加 1 。
//出队操作：只需将 front 增加 1 ，并将 size 减少 1 。
//可以看到，入队和出队操作都只需进行一次操作，时间复杂度均为O(1); 
#include <iostream>
 class arrayqueue
 {
    private:
        int *nums;
        int front;
        int queuesize;
        int queuecapacity;
    public:
        arrayqueue():nums(nullptr),front(0),queuecapacity(0),queuesize(0){}
        arrayqueue(int capacity)
        {
            nums = new int[capacity];
            queuecapacity = capacity;
            front = queuesize =0;
        }
        ~arrayqueue()
        {
            delete[] nums;
        }
        int capacity()const{return queuecapacity;}
        int size()const{return queuesize;}
        bool isempty()const{return queuesize == 0;}
        bool isfull()const{return queuecapacity == queuesize;}
        void push(int x)
        {
            if(isfull())
            {
                std::cout<<"队列已满"<<std::endl;
                return ;
            }
            int rear = (front + queuesize)%queuecapacity;
            nums[rear] = x;
            queuesize++;

        }
        int pop()
        {
            int num = nums[front];
            front = (front + 1) % queuecapacity;
            queuesize--;
            return num;
        }
        int peek()const
        {
            if(isempty())
            throw out_of_range("队列为空")；
            return  nums[front];
        }
        

 };