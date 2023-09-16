#pragma once
#include "RBTree.h"
namespace tao
{

    //����ģ�������ʵ������ͬ�ĺ����
    template <class K>//���ݴ���ģ�����T��ͬ�Ĳ������ú�������治ͬ������
    class set
    {
        //����ĺ������ʵ�����ɴ洢K���͵�
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
        //����д�ǲ��еģ���Ϊ��ģ�廹û��ʵ����������������ʵ������Ҳ�е���û��ʵ��������û�г�Ա
        typedef typename RBTree<K, K, set_keyoft>::const_iterator iterator;//-> K �������޸� V�����޸�

        typedef typename  RBTree<K, K, set_keyoft>::const_iterator const_iterator;//-> K V ���������޸�
        //���߱�������������ͣ������������ģ���ﶨ�壬����ģ��ʵ��������ȥ��

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

        //�����iterator��const_iterator
        pair<iterator,bool> insert(const K& kv)
        {
            //����insert���ص����������ͨ������_treeIterator<T,T&,T*> iterator

            typename RBTree<K, K, set_keyoft>::iterator ret= _rb.Insert(kv);//��Ϊset�ײ�����������K��������

            return pair<iterator, bool>(ret.fisrt, ret.second);
        }
    private:
        RBTree<K, K, set_keyoft>  _rb;
    };
}


//set��key�ǲ������޸ĵģ�map��keyҲ�������޸ģ���value�������޸ĵġ�
//������������ʵ��һ����ģ���ʵ������ķ����أ�
//���ｫset��iterator��const_iterator�����const_iterator
// 
//����map��ĵ�������ͨ������ͨ��const����const�����ʵ��k�����޸�v�����޸��أ�
//�ڴ洢��ʱʵ�ֵģ���ģ�����ʱ��const K ��ô���key�Ͳ����Ա��޸�