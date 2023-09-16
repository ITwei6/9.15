#pragma once
#include "RBTree.h"

namespace tao
{

    //����ģ�������ʵ������ͬ�ĺ����
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

        //����������ʵ����Ϊ�洢pair<K,V>���͵�
        
        //map��set�ĵ�������������ĵ�����
        typedef typename RBTree<K, pair<const K, V>, map_keyoft>::iterator iterator;
        //map����ͨ������������ͨ�ģ�const�ľ���const��
        typedef typename RBTree<K, pair<const K, V>, map_keyoft>::const_iterator const_iterator;
        //ͨ���洢ʱ���ͽ�K����Ϊconst���͵�

      //��������֪���������Ƕ���ͻ����Զ������ͻ��Ǿ�̬������������Ҫ��ʽ���������ʲô
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
        pair<iterator,bool> insert(const pair<K,V>& kv)//����������������ɺ����������������й�
            //ֱ�ӵ��ú�����Ľӿ�
        {
            return _rb.Insert(kv); //��Ϊmap�ײ�����������pair��������
        }
    private:
        RBTree<K, pair<const K,V>, map_keyoft>  _rb;
        //pair�ǿ����޸ĵģ����������K���޷����޸ĵģ�
    };//���ݴ���ģ�����T��ͬ�Ĳ������ú�������治ͬ������
}
