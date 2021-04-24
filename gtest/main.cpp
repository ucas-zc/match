#include "gtest/gtest.h"

//主程序入口
int32_t main(int32_t argc, char **argv)
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
