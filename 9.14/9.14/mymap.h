#pragma once
#include "RBTree.h"

namespace tao
{

    //根据模板参数来实例化不同的红黑树
    template <class K,class V>
    class map
    {
        struct map_keyoft
        {
            const K& operator()(const pair<K, V>& kv)
            {
                return kv.first;
            }
        };
    public:

        //这里红黑树被实例化为存储pair<K,V>类型的
        
        //map和set的迭代器就是树里的迭代器
        typedef typename RBTree<K, pair<const K, V>, map_keyoft>::iterator iterator;
        //map的普通迭代器就是普通的，const的就是const的
        typedef typename RBTree<K, pair<const K, V>, map_keyoft>::const_iterator const_iterator;
        //通过存储时，就将K设置为const类型的

      //编译器不知道这个是内嵌类型还是自定义类型还是静态变量，所以需要显式表明这个是什么
        iterator begin()
        {
           return  _rb.begin();
        }
        iterator end()
        {
           return  _rb.end();
        }

        V& operator[](const pair<K,V>& kv)
        {

        }
        pair<iterator,bool> insert(const pair<K,V>& kv)//插入的数据类型是由红黑树存的数据类型有关
            //直接调用红黑树的接口
        {
            return _rb.Insert(kv); //因为map底层红黑树里存的是pair类型数据
        }
    private:
        RBTree<K, pair<const K,V>, map_keyoft>  _rb;
        //pair是可以修改的，但是里面的K是无法被修改的！
    };//根据传给模板参数T不同的参数，让红黑树来存不同的数据
}
