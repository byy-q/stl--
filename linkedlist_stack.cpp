#include <vector>
class out_of_range;
struct listNode
{
    int val;
    listNode* next;
    listNode(int x){val = x,next = nullptr;}
};
class stack
{
    private:
        listNode* stacktop;//将第一个节点作为栈顶
        int stacksize;
    public:
        stack(listNode* ps = nullptr ,int size = 0):stacktop(ps),stacksize(size){}
        ~stack()
        {//遍历链表删除节点
            for(int i =0; i<stacksize;i++)
            {
                listNode* temp = stacktop->next;
                delete stacktop;
                stacktop = temp;
            }
        } 
        int size()const{return stacksize;}
        bool isempty()const{return stacksize == 0;}
        //入栈
        void push(int x)
        {
            listNode* node = new listNode(x);
            node->next = stacktop;
            stacktop = node ;
            stacksize ++;
        }
        //出栈
        int pop()
        {
            int num = top();
            listNode* temp =stacktop;
            stacktop = stacktop->next;
            delete temp->next;
            delete temp;
            return num;
        }
        int top(){
            if(size() == 0)
            throw out_of_range("栈为空");
            return stacktop->val;
        }
        std::vector<int> toVector()
        {
            std::vector<int>res(size());
            for(int i = size()-1;i>=0;i--)
            {
                res[i] = stacktop->val;
                stacktop = stacktop->next;
            }
            return res;
        }
};

