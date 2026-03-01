#include <string>
#include <vector>
#include <iostream>
struct Pair
{
    public:
    int key;
    std::string val;
    Pair(int Key,std::string Val ){this->key = Key,this->val = Val;}
};
class ArrayHashMap
{
    private:
        std::vector<Pair *>buckets;
    public:
        ArrayHashMap()
        {
            buckets = std::vector<Pair *>(100);
        }
        ~ArrayHashMap()
        {
            for(  const auto &bucket :buckets )
            {
                delete bucket;
            }
            buckets.clear();
        }
        int hash_func(int key)
        {
            int index = key %100;
            return index;
        }
        /*查询操作*/
        std::string Get(int key)
        {
            Pair *pair = buckets[hash_func(key)];
            if(pair == nullptr)
            return "";
            else
            return pair->val;
        }
        /*添加操作*/
        void Put(int key,std::string val)
        {
            Pair *pair = new Pair(key , val);
            int index = hash_func(key);
            buckets[index] = pair;
        }
        /*删除操作*/
        void Remove(int key)
        {
            int index = hash_func(key);
            delete buckets[index];
            buckets[index] = nullptr;
        }
        /*获取所有键值对*/
        std::vector<Pair *>pairSet()
        {
            std::vector<Pair *> pairset;
            for(Pair *pair:buckets)
            {
                if(pair != nullptr)
                pairset.push_back(pair);
            }
            return pairset;
        }
        /*获取所有键*/
        std::vector<int> keySet()
        {
            std::vector<int> keyset;
            for(Pair *pair: buckets)
            {
                if(pair != nullptr)
                keyset.push_back(pair->key);
            }
            return keyset;
        }
        /*获取所有值*/
        std::vector<std::string> valSet()
        {
            std::vector<std::string> valset;
            for(Pair *pair:buckets)
            {
                if(pair != nullptr)
                valset.push_back(pair->val);
            }
            return valset;
        }
        /*打印哈希表*/
        void print()
        {
            for(Pair* kv: pairSet())
            std::cout<<kv->key<<" "<<kv->val<<std::endl;
        }

};
class HashMapChain
{
    private:
        int size;//键对值数量
        int capacity;//哈希表容量
        double loadThres;//触发扩容的影响因子
        int extendRadio;//扩容倍数
        std::vector<std::vector<Pair *> >buckets;//桶数组
    public:
        HashMapChain():size(0),capacity(4),loadThres(2.0/3.0),extendRadio(2){buckets.resize(capacity);}
        ~HashMapChain()
        {
            for(auto &bucket : buckets)
            {
                for(Pair *pair :bucket)
                delete pair;
            }
            buckets.clear();
        }
        int hash_func(int key)
        {
            return key % capacity;
        }
        double LoadFactor()
        {
            return (double)size/(double)capacity;
        }
        /*查询操作*/
        std::string Get(int key)
        {
            int index = hash_func(key);
            for(Pair *pair : buckets[index])
            {
                if(key == pair->key)
                return pair->val;
            }
            return "";
        }
        /*添加操作*/
        void Put(int key,std::string val)
        {
            if(LoadFactor() > loadThres)
            {
                extend();
            }
            int index = hash_func(key);
            for(Pair* pair : buckets[index])
            {
                if(pair->key == key)
                pair->val = val;
                size++;
                return ;
            }
            buckets[index].push_back(new Pair(key,val));
            size++;
        }
        /*删除操作*/
        void Remove(int key)
        {
            int index = hash_func(key);
            auto &bucket = buckets[index];
            for(int i =0;i < bucket.size();i++)
            {
                if(bucket[i]->key == key)
                bucket.erase(bucket.begin() + i);
                bucket[i] = nullptr;
                return ;
            }
        }
         void extend() {
        // 暂存原哈希表
        std::vector<std::vector<Pair *>> bucketsTmp = buckets;
        // 初始化扩容后的新哈希表
        capacity *= extendRadio;
        buckets.clear();
        buckets.resize(capacity);
        size = 0;
        // 将键值对从原哈希表搬运至新哈希表
        for (auto &bucket : bucketsTmp) {
            for (Pair *pair : bucket) {
                Put(pair->key, pair->val);
                // 释放内存
                delete pair;
            }
        }
    }

    /* 打印哈希表 */
    void print() {
        for (auto &bucket : buckets) {
            std::cout << "[";
            for (Pair *pair : bucket) {
                std::cout << pair->key << " -> " << pair->val << ", ";
            }
            std::cout << "]\n";
        }
    }
};
class HashMapOpenAddressing
{
    private:
        int size;
        int capacity = 4;
        const double loadThres = 2.0/3.0;
        const int extendRadio = 2;
        std::vector<Pair *>buckets;
        Pair *TOMBSTONE = new Pair(-1, "-1");
    public:
        HashMapOpenAddressing():size(0),buckets(capacity,nullptr){}
        ~HashMapOpenAddressing()
        {
            for(Pair *pair:buckets)
                {
                    if(pair != nullptr&&pair!=TOMBSTONE)
                    delete pair;
                }
            delete TOMBSTONE;
        }
        int hash_func(int key)
        {
            return key % capacity;
        }
        double loadFactor()
        {
            return (double)size/(double)capacity;
        }
        int findBuckets(int key)
        {
            int index = hash_func(key);
            int firstTOMBSTONE = -1;
            while(buckets[index] != nullptr)
            {
                if(buckets[index]->key == key)
                {
                    if(firstTOMBSTONE != -1)
                    {
                        buckets[firstTOMBSTONE] = buckets[index];
                        buckets[index] = TOMBSTONE;
                        return firstTOMBSTONE;
                    }
                    return index;
                }
                if(firstTOMBSTONE == -1 && buckets[index] == TOMBSTONE)
                {
                    firstTOMBSTONE = index;
                }
                index = (index + 1 )%capacity;
            }
            return firstTOMBSTONE == -1? index :firstTOMBSTONE;
        }
        /* 查询操作 */
    std::string get(int key) {
        // 搜索 key 对应的桶索引
        int index = findBuckets(key);
        // 若找到键值对，则返回对应 val
        if (buckets[index] != nullptr && buckets[index] != TOMBSTONE) {
            return buckets[index]->val;
        }
        // 若键值对不存在，则返回空字符串
        return "";
    }

    /* 添加操作 */
    void put(int key, std::string val) {
        // 当负载因子超过阈值时，执行扩容
        if (loadFactor() > loadThres) {
            extend();
        }
        // 搜索 key 对应的桶索引
        int index = findBuckets(key);
        // 若找到键值对，则覆盖 val 并返回
        if (buckets[index] != nullptr && buckets[index] != TOMBSTONE) {
            buckets[index]->val = val;
            return;
        }
        // 若键值对不存在，则添加该键值对
        buckets[index] = new Pair(key, val);
        size++;
    }

    /* 删除操作 */
    void remove(int key) {
        // 搜索 key 对应的桶索引
        int index = findBuckets(key);
        // 若找到键值对，则用删除标记覆盖它
        if (buckets[index] != nullptr && buckets[index] != TOMBSTONE) {
            delete buckets[index];
            buckets[index] = TOMBSTONE;
            size--;
        }
    }

    /* 扩容哈希表 */
    void extend() {
        // 暂存原哈希表
        std::vector<Pair *> bucketsTmp = buckets;
        // 初始化扩容后的新哈希表
        capacity *= extendRadio;
        buckets = std::vector<Pair *>(capacity, nullptr);
        size = 0;
        // 将键值对从原哈希表搬运至新哈希表
        for (Pair *pair : bucketsTmp) {
            if (pair != nullptr && pair != TOMBSTONE) {
                put(pair->key, pair->val);
                delete pair;
            }
        }
    }

    /* 打印哈希表 */
    void print() {
        for (Pair *pair : buckets) {
            if (pair == nullptr) {
                std::cout << "nullptr" << std::endl;
            } else if (pair == TOMBSTONE) {
                std::cout << "TOMBSTONE" << std::endl;
            } else {
                std::cout << pair->key << " -> " << pair->val << std::endl;
            }
        }
    }
};
/*加法哈希*/
int AddHash(std::string key)
{
    long long hash = 0;
    const int MODULUS = 1000000007;
    for(unsigned char c :key)
    {
        hash = (hash + (int) c)%MODULUS;
    }
    return hash;
}
/*乘法哈希*/
int mulHash(std::string key)
{
    long long hash = 0;
    const int MODULUS = 1000000007;
    for(unsigned char c:key)
    {
        hash = (31 * hash + (int)c)%MODULUS;
    }
    return hash;
}
/*异或哈希*/
int xorHash(std::string key)
{
    long long hash = 0;
    const int MODULUS = 100000007;
    for(unsigned char c:key)
    {
        hash ^= (int) c;
    }
    return hash & MODULUS;
}
/*旋转哈希*/
int rotHash(std::string key)
{
    long long hash = 0;
    const int MODULUS = 1000000007;
    for (unsigned char c : key) {
        hash = ((hash << 4) ^ (hash >> 28) ^ (int)c) % MODULUS;
    }
    return (int)hash;
}