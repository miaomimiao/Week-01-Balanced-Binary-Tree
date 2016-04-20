# map和set

map和set是stl中的关联容器

# set
set用于存储数据，并且能从一个数据集合中取出数据。
它的每个元素的值必须唯一，而且系统会根据该值来自动将数据排序。
每个元素的值不能直接被改变。因为它内部的是红黑树。

## 红黑树：红黑树是自平衡的二叉查找树
二叉查找树：
二叉查找树是每个节点只允许两个节点的树，每个节点必然大于其左子树的每一个值又小于右子树的每一个值
可以提供对数时间的元素插入和访问。
但是在某些情况下二叉查找树可能会退化成类似链表的高度较高的树，影响插入和访问的时间效率。
为了解决这样的问题，可以采用某些插入删除方式使查找树尽量平衡（没有节点深度过大）。
诸如AVL树RB树和treap和splay树等。
set中使用红黑树完成。
红黑树是每个节点都带有颜色属性的二叉查找树，颜色或红色或黑色。在二叉查找树强制一般要求以外，
对于任何有效的红黑树我们增加了如下的额外要求:
1. 节点是红色或黑色。
2. 根节点是黑色。
3. 每个叶节点（NIL节点，空节点）是黑色的。
4. 每个红色节点的两个子节点都是黑色。(从每个叶子到根的所有路径上不能有两个连续的红色节点)
5. 从任一节点到其每个叶子的所有路径都包含相同数目的黑色节点。

这些约束强制了红黑树的关键性质: 从根到叶子的最长的可能路径不多于最短的可能路径的两倍长。结果是这个树大致上是平衡的。
因为操作比如插入、删除和查找某个值的最坏情况时间都要求与树的高度成比例，
这个在高度上的理论上限允许红黑树在最坏情况下都是高效的，而不同于普通的二叉查找树。
每插入一个节点会破坏原有的规则，必须要对原有的节点移位和改颜色。
回到set，set以红黑树为底层机制，所有set的操作都是调用红黑树，所以set有些操作要求就和红黑树的性质有关了，
如：我们不能通过迭代器改变set的值，因为红黑树的结构和值的大小有关系，删改元素后原有的指针依然能用。
	
## set的使用方法：
* 元素插入：`insert()`
* 中序遍历：类似`vector`遍历（用迭代器）
* 反向遍历：利用反向迭代器`reverse_iterator`。
```cpp
set<int> s;
...
set<int>::reverse_iterator rit;
for(rit=s.rbegin();rit!=s.rend();rit++)
```
* 元素删除：与插入一样，可以高效的删除，并自动调整使红黑树平衡。
```cpp		
set<int> s;
s.erase(2);        //删除键值为2的元素
s.clear();
```
* 元素检索：`find()`，若找到，返回该键值迭代器的位置，否则，返回最后一个元素后面一个位置。
```cpp
set<int> s;
set<int>::iterator it;
it=s.find(5);    //查找键值为5的元素
if(it!=s.end())    //找到
	cout<<*it<<endl;
else            //未找到
	cout<<"未找到";
```
* 自定义比较函数
	* 元素不是结构体：
	
	```cpp
    struct Info
    ```
    * 如果元素是结构体，可以直接将比较函数写在结构体内。
    
    ```cpp
    struct Info
    {
    	string name;
    	float score;
    	//重载“<”操作符，自定义排序规则
    	bool operator < (const Info &a) const
    	{
        	//按score从大到小排列
    		return a.score<score;
    	}
    }
    set<Info> s;
    ...
    set<Info>::iterator it;
    ```

# map

map 和 set使用相同的数据结构，不同的是 其中的Iterator的格式不一样，map使用pair这种配对的数据，
并根据pair中第一个元素的值进行排序，而set的iterator并不具备天生的pair类型的元素，
直接根据其中的元素进行排序。map的节点是一对数据，set的节点是一个数据。

map的形式 `map<type1, type2> mymap`;

set的形式  `set<type> myset`;

一般map是对有关联的事物存储，操作。  
set是对一个字段进行存储，操作。

使用关键字key来标示每一个成员，相当于字典,把一个值映射成另一个值,如果想创建字典的话，map就是一个很好的选择。
map底层采用的是树型结构,多数使用平衡二叉树实现,查找某一值是常数时间,遍历起来效果也不错,
只是每次插入值的时候,会重新构成底层的平衡二叉树,效率有一定影响。

### map的使用方法：
* 声明方式：`map<int, string> mapStudent;`
* 数据的插入
在构造map容器后，我们就可以往里面插入数据了。这里讲三种插入数据的方法：
	* 用insert函数插入pair数据
	```cpp
	map<int, string> mapStudent;
	mapStudent.insert(pair<int, string>(1, "student_one"));
	```
	* 用insert函数插入value_type数据
	```cpp
	map<int, string> mapStudent;
	mapStudent.insert(map<int, string>::value_type (1, "student_one"));
	```
	* 用数组方式插入数据
	```cpp
	map<int, string> mapStudent;
	mapStudent[1] = "student_one";
	mapStudent[2] = "student_two";
	```
* map的大小
在往map里面插入了数据，我们怎么知道当前已经插入了多少数据呢，可以用size函数：
	`Int nSize = mapStudent.size();`
* 数据的遍历
	* 应用前向迭代器
	```cpp
	map<int, string>::iterator iter;
	for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
		Cout<<iter->first<<"        "<<iter->second<<end;
	```
	* 应用反相迭代器
	```cpp
	map<int, string>::reverse_iterator iter;
	for(iter = mapStudent.rbegin(); iter != mapStudent.rend(); iter++)
				Cout<<iter->first<<"        "<<iter->second<<end;
	```
	* 用数组方式
	```cpp
	int nSize = mapStudent.size()
	for(int nIndex = 1; nIndex <= nSize; nIndex++) 
		Cout<<mapStudent[nIndex]<<end;
	```
* 数据的查找（包括判定这个关键字是否在map中出现）
		这里给出三种数据查找方法
	* 用count函数来判定关键字是否出现，但是无法定位数据出现位置
	* 用find函数来定位数据出现位置它返回的一个迭代器，
		当数据出现时，它返回数据所在位置的迭代器，如果map中没有要查找的数据，它返回的迭代器等于end函数返回的迭代器
	```cpp
	int main()
	{
		map<int, string> mapStudent;
		mapStudent.insert(pair<int, string>(1, “student_one"));
		mapStudent.insert(pair<int, string>(2, “student_two"));
		mapStudent.insert(pair<int, string>(3, “student_three"));
		map<int, string>::iterator iter;
		iter = mapStudent.find(1);
		if(iter != mapStudent.end())
		{
			Cout<<"Find, the value is "<<iter->second<<endl;
		}
		Else
		{
			Cout<<"Do not Find"<<endl;
		}
	}//这个方法用来判定数据是否出现
	```
	* Lower_bound函数用法，这个函数用来返回要查找关键字的下界(是一个迭代器)
	* Upper_bound函数用法，这个函数用来返回要查找关键字的上界(是一个迭代器)
		例如：map中已经插入了1，2，3，4的话，如果lower_bound(2)的话，返回的2，而upper-bound（2）的话，返回的就是3
	* Equal_range函数返回一个pair，pair里面第一个变量是Lower_bound返回的迭代器，pair里面第二个迭代器是Upper_bound返回的迭代器，如果这两个迭代器相等的话，则说明map中不出现这个关键字，程序说明
	```cpp
	mapPair = mapStudent.equal_range(2);
	if(mapPair.first == mapPair.second)
		cout<<"Do not Find"<<endl;
	```
* 数据的清空与判空
清空map中的数据可以用clear()函数，判定map中是否有数据可以用empty()函数，它返回true则说明是空map
* 数据的删除
这里要用到erase函数，它有三个重载了的函数
	* 迭代器删除 
	```cpp
	iter = mapStudent.find(1);
	mapStudent.erase(iter);
	```
	* 用关键字删除
	```cpp
	Int n = mapStudent.erase(1);//如果删除了会返回1，否则返回0`
	```
	* 用迭代器，成片的删除一下代码把整个map清空
	```cpp
	mapStudent.earse(mapStudent.begin(), mapStudent.end());
	//成片删除要注意的是，也是STL的特性，删除区间是一个前闭后开的集合
	```
