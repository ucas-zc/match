#include "SuperMatch.h"

/** 构造函数 **/
SuperMatch::SuperMatch()
{
    m_patternTotal = 0;
}

/** 析构函数 **/
SuperMatch::~SuperMatch()
{}

/** 构建状态机 **/
int32_t SuperMatch::build(std::vector<std::string> pattern)
{
    //异常判断
    if (pattern.empty()) {
        return MATCH_FAIL;
    }

    //开始构建状态机
    std::vector<std::string>::iterator iter = pattern.begin();
    for (; iter != pattern.end(); ++iter)
    {
        bool bFlag = false;
        BinaryTree<NS_SUPERMATCH::Pattern> *pCurNode = nullptr;
        for (uint32_t uIndex = 0; uIndex < (*iter).size(); ++uIndex)
        {
            //建立左子树
            if (bFlag) {
                BinaryTree<NS_SUPERMATCH::Pattern> *pNewNode = nullptr;
                try {
                    pNewNode = new BinaryTree<NS_SUPERMATCH::Pattern>;
                }catch(std::bad_alloc) {
                    return MATCH_FAIL;
                }

                if (nullptr == pNewNode) {
                    return MATCH_FAIL;
                }

                pNewNode->m_tree_data.m_ch = (*iter)[uIndex];
                pNewNode->m_tree_data.m_total = 0;
                if (MATCH_OK != m_PatternTree.InsertLeftNode(pCurNode, pNewNode))
                {
                    delete pNewNode;
                    pNewNode = nullptr;
                    return MATCH_FAIL;
                }

                pCurNode = pNewNode;
                continue;
            }

            //向右查找结点，查不到添加右结点，并从当前结点开始建立左子树
            if (MATCH_OK != findPattern((*iter)[uIndex], pCurNode))
            {
                bFlag = true;
                BinaryTree<NS_SUPERMATCH::Pattern> *pNode = nullptr;
                try    {
                    pNode = new BinaryTree<NS_SUPERMATCH::Pattern>;
                }catch(std::bad_alloc) {
                    return MATCH_FAIL;
                }

                if (nullptr == pNode) {
                    return MATCH_FAIL;
                }

                pNode->m_tree_data.m_ch = (*iter)[uIndex];
                pNode->m_tree_data.m_total = 0;
                if (MATCH_OK != m_PatternTree.InsertRightNode(pCurNode, pNode))
                {
                    delete pNode;
                    pNode = nullptr;
                    return MATCH_FAIL;
                }

                pCurNode = pNode;
                continue;
            }

            pCurNode = pCurNode->m_tree_left;
        }
    }

    return MATCH_OK;
}

/** 查找字符模式结点 **/
int32_t SuperMatch::findPattern(char ch, BinaryTree<NS_SUPERMATCH::Pattern> *&pCurNode)
{
    //向右进行遍历
    BinaryTree<NS_SUPERMATCH::Pattern> *pNode = nullptr;
    if (nullptr == pCurNode) {
        pNode = &m_PatternTree;
    }else {
        pNode = pCurNode;
    }

    while (nullptr != pNode) {
        //字符相同,返回成功
        pCurNode = pNode;
        if (pNode->m_tree_data.m_ch == ch) {
            ++pNode->m_tree_data.m_total;
            return MATCH_OK;
        }

        pNode = pNode->m_tree_right;
    }

    return MATCH_FAIL;
}

/** 模式完全匹配 **/
int32_t SuperMatch::matchPattern(std::string str)
{
    std::string::iterator iter = str.begin();
    BinaryTree<NS_SUPERMATCH::Pattern> *pCurNode = nullptr;
    for (; iter < str.end(); ++iter) {
        //当前结点右子树查找
        if (MATCH_OK != findPattern(*iter, pCurNode))
        {
            return MATCH_FAIL;
        }

        //当前字符查找到，指针指向左子树
        pCurNode = pCurNode->m_tree_left;
    }

    //依然存在左子树，则完全匹配失败
    if (nullptr != pCurNode) {
        return MATCH_FAIL;
    }

    return MATCH_OK;
}

/** 模式子串匹配 **/
int32_t SuperMatch::subMatchPattern(std::string str)
{
    std::string::iterator iter = str.begin();
    BinaryTree<NS_SUPERMATCH::Pattern> *pCurNode = nullptr;
    for (; iter < str.end(); ++iter) {
        //当前结点右子树查找
        if (MATCH_OK != findPattern(*iter, pCurNode))
        {
            return MATCH_FAIL;
        }

        //当前字符查找到，指针指向左子树
        pCurNode = pCurNode->m_tree_left;
    }

    return MATCH_OK;
}

/** 模式模糊匹配(*) **/
int32_t SuperMatch::fuzzyMatchPattern(std::string str)
{
    std::string::iterator iter = str.begin();
    BinaryTree<NS_SUPERMATCH::Pattern> *pCurNode = nullptr;
    for (; iter < str.end(); ++iter) {
        //当前结点右子树查找
        if (MATCH_OK != findPattern(*iter, pCurNode))
        {
            if ('*' == pCurNode->m_tree_data.m_ch)
            {
                return MATCH_OK;
            }

            return MATCH_FAIL;
        }

        //当前字符查找到，指针指向左子树
        pCurNode = pCurNode->m_tree_left;
    }

    //依然存在左子树，则完全匹配失败
    if (nullptr != pCurNode) {
        return MATCH_FAIL;
    }

    return MATCH_OK;
}

/** 查找字符模式结点(不区分大小写) **/
int32_t SuperMatch::softFindPattern(char ch, 
                BinaryTree<NS_SUPERMATCH::Pattern> *&pCurNode)
{
    //向右进行遍历
    BinaryTree<NS_SUPERMATCH::Pattern> *pNode = nullptr;
    if (nullptr == pCurNode) {
        pNode = &m_PatternTree;
    }else {
        pNode = pCurNode;
    }

    while (nullptr != pNode) {
        //字符相同,返回成功
        pCurNode = pNode;
        if (tolower(pNode->m_tree_data.m_ch) == tolower(ch))
        {
            ++pNode->m_tree_data.m_total;
            return MATCH_OK;
        }

        pNode = pNode->m_tree_right;
    }

    return MATCH_FAIL;
}

/** 模式完全匹配 **/
int32_t SuperMatch::softMatch(std::string str)
{
    std::string::iterator iter = str.begin();
    BinaryTree<NS_SUPERMATCH::Pattern> *pCurNode = nullptr;
    for (; iter < str.end(); ++iter) {
        //当前结点右子树查找
        if (MATCH_OK != softFindPattern(*iter, pCurNode))
        {
            return MATCH_FAIL;
        }

        //当前字符查找到指针指向左子树
        pCurNode = pCurNode->m_tree_left;
    }

    //依然存在左子树，则完全匹配失败
    if (nullptr != pCurNode) {
        return MATCH_FAIL;
    }

    return MATCH_OK;
}

/** 模式子串匹配 **/
int32_t SuperMatch::softSubMatch(std::string str)
{
    std::string::iterator iter = str.begin();
    BinaryTree<NS_SUPERMATCH::Pattern> *pCurNode = nullptr;
    for (; iter < str.end(); ++iter) {
        //当前结点右子树查找
        if (MATCH_OK != softFindPattern(*iter, pCurNode))
        {
            return MATCH_FAIL;
        }

        //当前字符查找到指针指向左子树
        pCurNode = pCurNode->m_tree_left;
    }

    return MATCH_OK;
}

/** 模式模糊匹配(*) **/
int32_t SuperMatch::softFuzzyMatch(std::string str)
{
    std::string::iterator iter = str.begin();
    BinaryTree<NS_SUPERMATCH::Pattern> *pCurNode = nullptr;
    for (; iter < str.end(); ++iter) {
        //当前结点右子树查找
        if (MATCH_OK != softFindPattern(*iter, pCurNode))
        {
            if ('*' == pCurNode->m_tree_data.m_ch)
            {
                return MATCH_OK;
            }

            return MATCH_FAIL;
        }

        //当前字符查找到指针指向左子树
        pCurNode = pCurNode->m_tree_left;
    }

    //依然存在左子树，则完全匹配失败
    if (nullptr != pCurNode) {
        return MATCH_FAIL;
    }

    return MATCH_OK;
}

int32_t SuperMatch::sort2Swap()
{}

/** 销毁状态机 **/
int32_t SuperMatch::destroy()
{
    return MATCH_OK;
}
