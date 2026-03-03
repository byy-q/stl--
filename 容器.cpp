#include <string>
#include <list>
#include <vector>
#include <deque>
#include <forward_list>
using namespace std;
list<string>authores = {"张三","李四","王五"};
vector<const char *>articles = {"a","an","the"};
forward_list<string>words(articles.begin()+1,articles.end());//使用迭代器构造，两个容器得到元素类型，容器类型都可以不同，只要元素类型可以转换

