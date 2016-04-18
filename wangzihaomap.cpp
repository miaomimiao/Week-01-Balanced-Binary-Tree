#include <map>
#include <string>
#include <iostream>
using namespace std;
int main()
{
//插入
       Map<int, string> mapStudent;
       mapStudent.insert(pair<int, string>(1, “student_one”));
       mapStudent.insert(pair<int, string>(2, “student_two”));
       mapStudent.insert(pair<int, string>(3, “student_three”));
       map<int, string>::iterator  iter;
       for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
  {
       cout<<iter->first<<”   ”<<iter->second<<end;
  }
       //删除
       map<int, string>::iterator iter;
       iter = mapStudent.find(1);
       mapStudent.erase(iter);
       return 0;
}

