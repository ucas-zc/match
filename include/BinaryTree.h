#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <iostream>
#include <cstdint>

namespace
{
    const int32_t OPT_OK = 1;
    const int32_t OPT_FAIL = 0;
}

template<typename _Tree>
class BinaryTree
{
    public:
        /**
         * @brief 构造函数
         */
        BinaryTree():m_tree_left(nullptr), m_tree_right(nullptr)
        {}

        /**
         * @brief 析构函数
         */
        ~BinaryTree()
        {}

        /**
         * @brief 根结点插入左结点
         *
         * @prame pNode 结点
         *
         * @return OPT_OK 成功; OPT_FAIL 失败
         */
        int32_t InsertLeftNode(BinaryTree<_Tree> *pNode)
        {
            //异常判断
            if (nullptr == pNode) {
                return OPT_FAIL;
            }

            this->m_tree_left = pNode;
            return OPT_OK;
        }

        /**
         * @brief 根结点插入右结点
         *
         * @prame pNode 结点
         *
         * @return RET::OPT_OK 成功; RET::FAIL 失败
         */
        int32_t InsertRightNode(BinaryTree<_Tree> *pNode)
        {
            //异常判断
            if (nullptr == pNode) {
                return OPT_FAIL;
            }

            this->m_tree_right = pNode;
            return OPT_OK;
        }

        /**
         * @brief 从当前结点插入左结点
         *
         * @prame pCurNode 当前结点; pNewNode 新结点
         *
         * @return OPT_OK 成功; OPT_FAIL 失败
         */
        int32_t InsertLeftNode(BinaryTree<_Tree> *pCurNode, BinaryTree<_Tree> *pNewNode)
        {
            //异常判断
            if (nullptr == pCurNode || nullptr == pNewNode) 
            {
                return OPT_FAIL;
            }

            pCurNode->m_tree_left = pNewNode;
            return OPT_OK;
        }

        /**
         * @brief 从当前结点插入右结点
         *
         * @prame pCurNode 当前结点; pNewNode 新结点
         *
         * @return OPT_OK 成功; OPT_FAIL 失败
         */
        int32_t InsertRightNode(BinaryTree<_Tree> *pCurNode, BinaryTree<_Tree> *pNewNode)
        {
            //异常判断
            if (nullptr == pCurNode || nullptr == pNewNode) 
            {
                return OPT_FAIL;
            }

            pCurNode->m_tree_right = pNewNode;
            return OPT_OK;
        }

        public:
            /**
             * @brief 结点内容
             */
            _Tree m_tree_data;

            /**
             * @brief 结点左指针
             */
            BinaryTree<_Tree> *m_tree_left;

            /**
             * @brief 结点右指针
             */
            BinaryTree<_Tree> *m_tree_right;

};

#endif
