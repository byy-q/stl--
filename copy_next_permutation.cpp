//算法copy是吧一个顺序表的元素从一个位置复制到另一个位置
//语法是copy(start,end,to),其中to是一个迭代器，表示复制的目标位置，start和end是迭代器，表示要复制的区间
//算法next_permutation 语法是next_permutation(start,end),对[start,end)区间内的元素进行重新排列，按字典顺序产生下一个更大的排序
//当且仅当这个排列存在时，返回true
//对一个元素各不相同的顺序表，从字典序最小的排列开始，调用next_permutation n!次，就会得到所有的排列
#include <iostream>
template<typename T>
void permutations(T list[],int k,int m)
{
    //生成list[k:m]的所有排列
    //假设k<=m，将排列逐个输出
    do
    {
        copy(list,list+m+1,ostream_iterator<T>(cout," "));//把list[k:m]的元素复制到输出流中，每个元素后面跟一个空格
        cout<<endl;
    }
    while(next_permutation(list,list+m+1));//对list[k:m]进行重新排列，直到没有下一个更大的排列为止
    
}
//next_permutation算法有更一般的形式，他带有第三个参数compare
//next_permutation(start,end,compare),函数compare用来判定一个排列是否另一个排列小，在二元参数版本中
//比较操作由<执行
//在三元参数版本中，比较操作由compare执行