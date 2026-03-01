struct Node
{
    int val;
    Node* next;
    Node(int x):val(x),next(nullptr){}
};
class linkedListQueue
{
    private:
        Node *front,*rear;
        int queuesize;
    public:
        linkedListQueue()
        {
            front = nullptr;
            rear = nullptr;
            queuesize = 0;
        }
        ~linkedListQueue()
        {
            Node* temp = rear;
            for(int i =0;i<queuesize;i++)
            {
                temp = rear->next;
                delete rear->next;
            }
            delete temp;
        }
        int size()const{return queuesize;}
        bool isempty()const{return queuesize == 0;}
        void push(int x)
        {
            Node* node = new Node(x);
            if(queuesize == 0)
            {
                front = rear = node;
                queuesize ++;
            }
            else
            {
            node->next = rear;
            rear = node;
            queuesize++;
            }
        }
        
}