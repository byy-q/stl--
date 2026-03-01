#include <vector>
struct DoubleListNode
{
    int val;//节点值
    DoubleListNode *prev,*next;//前后节点指针
    DoubleListNode(int x):val(x),prev(nullptr),next(nullptr){}
};
class deque
{
    private:
        DoubleListNode *front, *rear;
        int queuesize = 0;
    public:
        deque():front(nullptr),rear(nullptr){}
        ~deque()
        {
            DoubleListNode *pre, *cur = front;
            while(cur != nullptr)
            {
                pre = cur;
                cur = cur->next;
                delete pre;
            }
        }
        int size()const{return queuesize;}
        bool isempty()const{return queuesize == 0;}
        void push(int num,bool isfront)
        {
            DoubleListNode *node = new DoubleListNode(num);
            if(isempty())
            {
                front = rear = node;
            }
            else if(isfront)
            {
                node->next = front;
                front = node ;
                queuesize++;
            }
            else
            {
                queuesize++;
                node->prev = rear;
                rear = node;
            }
        }
        void push_front(int num)
        {
            push(num,true);
        }
        void push_rear(int num)
        {
            push(num,false);
        }
        int pop(bool isfront)
        {
            if(isempty())
            throw out_of_range("队列为空");
            else if(isfront)
            {
                int num = front->val;
                DoubleListNode *nfront = front->next;
                if(nfront!=nullptr)
                {
                    front->next = nullptr;
                    nfront->prev=nullptr;
                }
                front = nfront;
                delete nfront;
                queuesize--;
                return num;
            }
            else
            {
                int num = rear->val;
                DoubleListNode *prerear = rear->prev;
                if(rear != nullptr)
                {
                    rear->prev = nullptr;
                    prerear->next = nullptr;
                }
                rear = prerear;
                delete prerear;
                queuesize--;
                return num;
            }
            
        }
        int pop_front()
        {
            pop(true);
        }
        int pop_last()
        {
            pop(false);
        }
        int peekfirst()
        {
            if(size() == 0)
            throw out_of_range("队列为空");
            return front->val;
        }
        int peeklast()
        {
            if(size() == 0)
            throw out_of_range("队列为空");
            return rear->val;
        }
        std::vector<int> toVector()
        {
            DoubleListNode* temp= front;
            std::vector<int> res(size());
            for(int i =0;i<size();i++)
            {
                res[i] = temp->val;
                front = front->next;
                delete temp;
                temp = front;
            }
            return res;
        }

};
