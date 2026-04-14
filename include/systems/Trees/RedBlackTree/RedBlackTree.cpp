// Copyright (c) 2026, ZiMing


#pragma once
#include <iostream>
#include <optional> // C++17 安全返回值
namespace cfs{
namespace containers{
// 红黑树的定义:
// 1. 每个节点要么是红色要么是黑色
// 2. 根节点必须是黑色
// 3. 每个叶子结点必须是黑色 (NULL节点 哨兵节点)
// 4. 如果一个节点是红色 那么它的两个子节点一定是黑色 也就是说红色节点不能连续
// 5. 从任意节点到叶子节点的路径包含同样数量的黑色节点 

// 节点颜色枚举
enum class Color{
    RED,
    BLACK
};

template<typename Key, typename Value>
// 红黑树节点类 红黑树的每一个节点
class RBTreeNode{
    Key key; // 一个节点本身的key
    Value value; // 一个节点本身的value
    Color color; // 节点颜色
    RBTreeNode* left; // 左子树指针
    RBTreeNode* right; // 右子树指针
    RBTreeNode* parent; // 父节点指针

    // 构造函数
    RBTreeNode(const Key&k, const Value&value, Color color, RBTreeNode* nilNode) : 
        key(k), value(value), color(color), left(nilNode), right(nilNode), parent(nilNode) {}

    ~RBTreeNode() = default; // 默认析构函数

    };

template<typename Key, typename Value>
class RBTree{
private:
    RBTreeNode<Key, Value>* nil; // 空的哨兵节点
    RBTreeNode<Key, Value>* root; // 红黑树的根节点

    // 左旋函数: 将节点X的右边孩子Y上位 X变成Y的左边孩子
    void left_rotate(RBTreeNode<Key, Value>* x){
        auto y = x->right; // Y是X的右孩子
        x->right = y->left; // 将Y的左子树变成X的右子树

        if(y->left != nil){
            y->left->parent = x; // 更新Y的左子树的父节点为X
        }
        y->parent = x->parent;
        if(x->parent == nil){
            root = y; // 如果X是根节点 那么更新根节点为Y
        }else if(x == x->parent->left){
            x->parent->left = y; // 如果X是左孩子 那么更新父节点的左孩子为Y
        }else if(x == x->parent->right){
            x->parent->right = y; // 如果X是右孩子 那么更新父节点的右孩子为Y
        }

        y->left = x;
        x->parent = y;
    }

    

}
}