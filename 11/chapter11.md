# 第十一章 关联容器

## 相关容器

1. **有序关联容器**

   基于红黑树（red-black-tree）时间复杂度都在O(log n)

   * map
   * set
   * multimap
   * mulitset

2. **无序关联容器**

   基于哈希表（hash）时间复杂度都在O(1),最坏为O(n)

   * unordered_map
   * unordered_set
   * unordered_multimap
   * unordered_multiset

## 知识点

* **类型别名**

| 名字        | 内容                                   |
| :---------- | :------------------------------------- |
| key_type    | 对应关键字                             |
| mapped_type | 对应关键字映射的类型                   |
| value_type  | 对应存放的值，map为pair，set为key_type |



* **find和count的优劣**

  find是判断是否存在的最好方式，因为find找到就返回了

  count则是需要全部遍历一遍

  

* **[]下标方式**

  []通过该方式遇到一个未存在的key时，会自动插入一个map[key]=0

  

* **insert 和 []**

  insert pair 和 [],下标更新的map是最后一个value，而insert是第一个插入的key，value

  

* **lower_bound和upper_bound**

  两者均返回一个指针，lower指向第一个大于等于val的值，upper指向第一个严格大于val的值

  之所以叫lower和upper取自数学中的上下界

  例如val=3 数组{1，2，3，3，3，5}

  可知，3的下界为第一个3，上界为5,表示为[3,5];

  所以lower指向第一个3，upper指向大于3的5

  

*  **map.erase()**

  关联容器中的删除函数，有特殊情况，例如在多重map和set中，erase(key),返回的是删除该key的个数

## 

