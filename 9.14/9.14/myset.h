#pragma once
#include "RBTree.h"
namespace tao
{

    //根据模板参数来实例化不同的红黑树
    template <class K>//根据传给模板参数T不同的参数，让红黑树来存不同的数据
    class set
    {
        //这里的红黑树被实例化成存储K类型的
        struct set_keyoft
        {
            const K& operator()(const K& kv)
            {
                return kv;
            }
        };
       

       // 
    public:
        //typedef RBTree<K, K, set_keyoft>::iterator iterator;
        //这样写是不行的，因为类模板还没有实例化出对象来就算实例化，也有的类没有实例，里面没有成员
        typedef typename RBTree<K, K, set_keyoft>::const_iterator iterator;//-> K 不可以修改 V可以修改

        typedef typename  RBTree<K, K, set_keyoft>::const_iterator const_iterator;//-> K V 都不可以修改
        //告诉编译器这个是类型，这个类型在类模板里定义，等类模板实例化后再去找

        /*iterator begin()
        {
            return _rb.begin();
        }
        iterator end()
        {
            return _rb.end();
        }*/
        const_iterator begin()const
        {
            return _rb.begin();
        }
        const_iterator end()const
        {
            return _rb.end();
        }

        //这里的iterator是const_iterator
        pair<iterator,bool> insert(const K& kv)
        {
            //这里insert返回的是树里的普通迭代器_treeIterator<T,T&,T*> iterator

            typename RBTree<K, K, set_keyoft>::iterator ret= _rb.Insert(kv);//因为set底层红黑树里存的是K类型数据

            return pair<iterator, bool>(ret.fisrt, ret.second);
        }
    private:
        RBTree<K, K, set_keyoft>  _rb;
    };
}


//set的key是不允许修改的，map的key也不可以修改，但value是允许修改的。
//红黑树里是如何实现一种类模板而实现上面的方案呢？
//库里将set的iterator和const_iterator都设成const_iterator
// 
//但库map里的迭代器普通就是普通，const就是const，如果实现k可以修改v不能修改呢？
//在存储层时实现的，传模板参数时传const K 那么这个key就不可以被修改