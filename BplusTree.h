//
// Created by 乔奥 on 2022/10/9.
//
#include <vector>

using namespace std;

#ifndef BPLUSTREE_BPLUSTREE_H
#define BPLUSTREE_BPLUSTREE_H

#define MAX_KEY_COUNT 4 //每个节点中的最大元素数量

namespace BplusTree {

    template<class key_type, class value_type>
    class Non_Leaf_Node;

    //抽象节点，是所有节点的父类，不可单独使用
    template<class key_type, class value_type>
    class Virtual_Node {
    public:
        Virtual_Node() = default;

        virtual ~Virtual_Node();

        int key_count; // 储存在本节点的元素数量
        key_type keys[MAX_KEY_COUNT];
        bool isLeafNode;
        Non_Leaf_Node<key_type, value_type> *parent;

        Virtual_Node *getSibling();
    };

    //叶子节点
    template<class key_type, class value_type>
    class Leaf_Node : public Virtual_Node<key_type, value_type> {
    public:
        Leaf_Node();

        virtual ~Leaf_Node();

        Leaf_Node<key_type, value_type> *next_node; //叶子节点的下一个节点指针
        Leaf_Node<key_type, value_type> *pre_node; //叶子节点的上一个节点指针

        bool InsertKey(key_type key, value_type value); //插入值
        bool DeleteKey(key_type key, value_type value); //删除值
        int Split(Leaf_Node<key_type, value_type> *pNode); //节点分裂
        bool Merge(Leaf_Node<key_type, value_type> *pNode); //节点合并
    };

    //非叶子节点
    template<class key_type, class value_type>
    class Non_Leaf_Node : public Virtual_Node<key_type, value_type> {
    public:
        Non_Leaf_Node();

        virtual ~Non_Leaf_Node();

        vector<Virtual_Node<key_type, value_type> *> children;

        bool InsertKey(key_type key, value_type value); //插入值
        bool DeleteKey(key_type key, value_type value); //删除值
        int Split(Leaf_Node<key_type, value_type> *pNode); //节点分裂
        bool Merge(Leaf_Node<key_type, value_type> *pNode); //节点合并
    };

    //树结构
    template<class key_type, class value_type>
    class BplusTree {
    public:
        BplusTree() = default;
        virtual ~BplusTree();
        value_type Search(key_type key); //查找key
        bool Insert(key_type key, value_type value); //插入key和value
        bool Delete(key_type key); //删除key

    protected:
        Virtual_Node<key_type, value_type> root; //根节点
    };


}; // end of namespace

#endif //BPLUSTREE_BPLUSTREE_H
