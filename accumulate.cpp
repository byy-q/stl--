//STL的accumulate算法，对顺序表元素顺序求和
//语法是 accumulate(start,end,initialvalue)，其中start和end是迭代器，initialvalue是初始值
//求和区间是[start,end)，即包含start但不包含end
#include<iostream>
template<typename T>
T sum(T a[],int n)
{
    T theSum = 0;
    return accumulate(a,a+n,theSum);
}
//更通用的写法
//accumulate(start,end,initialvalue,operation)，operation是一个二元函数对象，表示对区间内元素进行什么样的操作
template<typename T>
T product(T a[],int n)
{
    T theProduct = 1;
    return accumulate(a,a+n,theProduct,multiplies<T>());
}//multiplies是一个函数对象，表示对区间内元素进行乘法操作
//计算n个元素的乘积
