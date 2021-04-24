#
# * github查看本页面存在乱码，请点击右上角进入编辑模式进行查看 *
#
# 字符串状态机模式匹配
# 本状态机的设计基于二叉树进行设计，以下例进行说明：
# 例如，状态机由about，apple，bear，beat，count等组成，那么以上五个单词可按字母构成下述树形结构
#                               root
#                                |
#                        -----------------
#                        |       |       |
#                        a       b       c 
#                        |       |       |
#                     ------     e       o
#                     |    |     |       |
#                     b    p     a       u
#                     |    |     |       |
#                     o    p  ------     n
#                     |    |  |    |     |
#                     u    l  r    t     t
#                     |    |
#                     t    e   
#
# 根据树转二叉树的规则进行转换，可转换为如下二叉树：
#                                a
#                                |
#                        ----------------
#                        |              |
#                        b              b
#                        |              |
#                  -----------     -----------
#                  |         |     |         |
#                  o         p     e         c
#                  |         |     |         |
#                ---       ---   ---       ---
#                |         |     |         |
#                u         p     a         o
#                |         |     |         |
#              ---       ---   ---       ---
#              |         |     |         |
#              t         l     r         u
#                        |     |         |
#                      ---     ---     --- 
#                      |         |     |
#                      e         t     n
#                                      |
#                                    ---
#                                    |
#                                    t
#
# 树转换完成，即可直接用二叉树进行构建状态机
#
# 编译规则
#
# 编译动态库/静态库：
# rm -rf build
# mkdir build
# cd build
# cmake -DCMAKE_BUILD_TYPE=SHARED -DCMAKE_BUILD_RPATH=/opt/ide ..
# make
# cmake -DCMAKE_BUILD_TYPE=STATIC -DCMAKE_BUILD_RPATH=/opt/ide ..
# make
#
# GTEST测试：
# rm -rf build
# mkdir build
# cd build
# cmake -DCMAKE_BUILD_TYPE=GTEST -DCMAKE_BUILD_RPATH=/opt/ide ..
# make
# make gen_coverage_html （测试代码覆盖率）
