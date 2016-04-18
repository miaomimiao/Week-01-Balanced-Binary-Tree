//set内部实现
#include <iostream>
#include <string>
#include <set>
using namespace std;

struct strLess
{
   bool operator() (const char *s1, const char *s2) const
   {
    return strcmp(s1, s2) < 0;
   }
};

void printSet(set<int> s)
{
   copy(s.begin(), s.end(), ostream_iterator<int>(cout, ", ") );
   cout<<endl;
}

void main()
{
   set<int> s1; 
   pair<iterator, bool> insert(value) ;  //元素插入 1,插入value，返回pair配对对象，可以根据.second判断是否插入成功。(提示:value不能与set容器内元素重复)
   iterator insert(&pos, value)  ;      //2,在pos位置之前插入value，返回新元素位置，但不一定能插入成功
   cout<<"\ns1.erase(70) = "<<endl;    //元素删除
   s1.erase(70);
   printSet(s1);


   if (s1.find(10) != s1.end())        //元素查找
       cout<<"OK!"<<endl;
   else
       cout<<"not found!"<<endl;
       return 0；
}
