# vector

dynamic contiguous array

## 接口说明

* 构造函数，析构函数
* 重载赋值运算
* 下标访问
* `front()`, `back()`, `empty()`, `size()`, `clear()`
* `insert`, `erase`
* `push_back()`, `pop_back()`
* 迭代器及其相关操作

## 提示

* 模板类型可能是一个没有默认构造函数的类。

  例如`template<typename T>`，内部数据存储形式为`T val`，空节点就只能填入`T()`，但是没有默认构造函数的`T`无法构造

  尝试使用指针的形式存储数据

- 你的程序将会受到一定程度的鲁棒性检测

## 截至日期

3月19日（第五周周日）18:30
