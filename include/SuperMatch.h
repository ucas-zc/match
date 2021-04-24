#ifndef _SUPERMATCH_H_
#define _SUPERMATCH_H_

#include "BinaryTree.h"
#include <vector>
#include <string>

namespace
{
    // 匹配成功返回1
    const int32_t MATCH_OK = 1;
    // 匹配失败返回0
    const int32_t MATCH_FAIL = 0; 
}

namespace NS_SUPERMATCH
{
    class Pattern
    {
        public:
            /**
             ** @brief 构造函数
             **/
            Pattern()
            {
                m_total = 0;
            }

            /**
             ** @brief 析构函数
             **/
            ~Pattern()
            {}

        public:
            char m_ch;                  //字符
            uint32_t m_total;           //字符被查找次数
    };
}

class SuperMatch
{
    public:
        /**
         ** @brief 构造函数
         **/
        SuperMatch();

        /**
         ** @brief 析构函数
         **/
        ~SuperMatch();

        /**
         ** @brief 构建状态机
         **
         ** @prame pattern 所有模式串
         **
         ** @return MATCH_OK 成功; MATCH_FAIL 失败
         **/
        int32_t build(std::vector<std::string> pattern);

        /**
         ** @brief 查找字符模式 
         **
         ** @prame ch 字符; pCurNode 当前结点
         **
         ** @return MATCH_OK 成功; MATCH_FAIL 失败
         **/
		int32_t findPattern(char ch, BinaryTree<NS_SUPERMATCH::Pattern> *&pCurNode);

		/**
         ** @brief 模式完全匹配
         **
         ** @prame str 字符串
         **
         ** @return MATCH_OK 成功; MATCH_FAIL 失败
         **/
        int32_t matchPattern(std::string str);

        /**
         ** @brief 模式子串匹配
         **
         ** @prame str 字符串
         **
         ** @return MATCH_OK 成功; MATCH_FAIL 失败
         **/
        int32_t subMatchPattern(std::string str);

		/**
         ** @brief 模式模糊匹配
         **
         ** @prame str 字符串
         **
         ** @return MATCH_OK 成功; MATCH_FAIL 失败
         **/
        int32_t fuzzyMatchPattern(std::string str);

        /**
         ** @brief 查找字符模式(不区分大小写) 
         **
         ** @prame ch 字符; pCurNode 当前结点
         **
         ** @return MATCH_OK 成功; MATCH_FAIL 失败
         **/
        int32_t softFindPattern(char ch, BinaryTree<NS_SUPERMATCH::Pattern> *&pCurNode);

        /**
         ** @brief 模式完全匹配(不区分大小写)
         **
         ** @prame str 字符串
         **
         ** @return MATCH_OK 成功; MATCH_FAIL 失败
         **/
        int32_t softMatch(std::string str);

        /**
         ** @brief 模式子串匹配(不区分大小写)
         **
         ** @prame str 字符串
         **
         ** @return MATCH_OK 成功; MATCH_FAIL 失败
         **/
        int32_t softSubMatch(std::string str);

        /**
         ** @brief 模式模糊匹配(不区分大小写)
         **
         ** @prame str 字符串
         **
         ** @return MATCH_OK 成功; MATCH_FAIL 失败
         **/
        int32_t softFuzzyMatch(std::string str);

        /**
         ** @brief 排序整合
         **
         ** @return MATCH_OK 成功; MATCH_FAIL 失败
         **/
        int32_t sort2Swap();

        /**
         ** @brief 销毁状态机
         **
         ** @return MATCH_OK 成功; MATCH_FAIL 失败
         **/
        int32_t destroy();

    private:
        /**
         ** @brief 模式树
         **/
        BinaryTree<NS_SUPERMATCH::Pattern> m_PatternTree;
		
        /**
         ** @brief 模式总数
         **/
        int32_t m_patternTotal;
 
};

#endif 
