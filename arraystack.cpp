#include <vector>
class ArrayStack
{
    private:
    std::vector<int>stack;
    public:
        int size()const{return stack.size();}
        bool isempty()const{return stack.size() == 0;}
        //入栈
        void push(int x)
        {
            stack.push_back(x);
        }
        //出栈
        int pop()
        {
            int num = top();
            stack.pop_back();
            return num;
        }
        int top(){
            if(stack.size() == 0)
            throw out_of_range("栈为空");
            return stack.back();
        }
        

};