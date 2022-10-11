//
// Created by 乔奥 on 2022/10/9.
//
/**
 * 此B+树的结构如下所示：
 *             251(root)
 *           /          \
 *     119｜167         251|341|975
 *   (children[0])     (children[1])
 */
using namespace std;

#ifndef BPlusTree_BPlusTree_H
#define BPlusTree_BPlusTree_H

#define MAX_KEY_COUNT_HALF 4 //每个节点中的最大元素数量

namespace BPlusTree {

    class Non_Leaf_Node;

    //抽象节点，是所有节点的父类，不可单独使用
    class Virtual_Node {
    public:
        Virtual_Node();

        virtual ~Virtual_Node();

        int key_count; // 储存在本节点的元素数量
        int keys[MAX_KEY_COUNT_HALF * 2];
        bool isLeafNode;
        Non_Leaf_Node *parent;

        Virtual_Node *getSibling();
    };

    Virtual_Node::Virtual_Node() {
        key_count = 0;
        parent = nullptr;
    }

    Virtual_Node::~Virtual_Node() {}

    //叶子节点
    class Leaf_Node : public Virtual_Node {
    public:
        Leaf_Node();

        virtual ~Leaf_Node();

        Leaf_Node *next_node; //叶子节点的下一个节点指针
        Leaf_Node *pre_node; //叶子节点的上一个节点指针
        int values[MAX_KEY_COUNT_HALF * 2];

        bool InsertKeyAndValue(int key, int value); //插入值
        bool DeleteKey(int key, int value); //删除值
        int SplitFromMidToNewNodeAndReturnsFirstKey(Leaf_Node *new_node); //节点分裂
        bool Merge(Leaf_Node *pNode); //节点合并
    };

    Leaf_Node::Leaf_Node() {
        isLeafNode = true;
        pre_node = nullptr;
        next_node = nullptr;
    }

    Leaf_Node::~Leaf_Node() noexcept {}

    //非叶子节点
    class Non_Leaf_Node : public Virtual_Node {
    public:
        Non_Leaf_Node();

        virtual ~Non_Leaf_Node();

        Virtual_Node *children[MAX_KEY_COUNT_HALF * 2 + 1]; //children指针总比key多1

        bool InsertKey(int key, int value); //插入值
        bool DeleteKey(int key, int value); //删除值
        int Split(Leaf_Node *pNode); //节点分裂
        bool Merge(Leaf_Node *pNode); //节点合并
    };

    Non_Leaf_Node::Non_Leaf_Node() {
        isLeafNode = false;
        for (int i = 0; i < MAX_KEY_COUNT_HALF * 2 + 1; i++) {
            children[i] = nullptr;
        }
    }

    Non_Leaf_Node::~Non_Leaf_Node() {
        for (int i = 0; i < MAX_KEY_COUNT_HALF * 2 + 1; i++) {
            children[i] = nullptr;
        }
    }

    //树结构
    class BpTree {
    public:
        BpTree();

        virtual ~BpTree();

        int Search(int key); //查找key
        bool Insert(int key, int value); //插入key和value
        bool Delete(int key); //删除key

    protected:
        Virtual_Node *root; //根节点

        Leaf_Node *FindLeafNodeByKey(int key);
        bool AddNewNodeToTree(Non_Leaf_Node *parent, int new_node_first_key, Virtual_Node *new_node);
    };

    BpTree::BpTree() {
        root = nullptr;
    };

    BpTree::~BpTree() {}

}; // end of namespace

#endif //BPlusTree_BPlusTree_H
