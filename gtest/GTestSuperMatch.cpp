#include "SuperMatch.h"
#include "gtest/gtest.h"

namespace 
{
	class TestSuperMatch : public testing::Test
	{
		void SetUp() override
		{};

		void TearDown() override
		{};
	};
}

TEST_F(TestSuperMatch, TEST_SUPERMATCH)
{
	SuperMatch super;
	std::vector<std::string> pattern;
	pattern.push_back("abcdefg");
	pattern.push_back("abcefgd");
	pattern.push_back("gfedcba");
	pattern.push_back("acds*");
	ASSERT_EQ(MATCH_OK, super.build(pattern));
	ASSERT_EQ(MATCH_OK, super.matchPattern("abcdefg"));
	ASSERT_EQ(MATCH_OK, super.matchPattern("abcefgd"));
	ASSERT_EQ(MATCH_OK, super.matchPattern("gfedcba"));
	ASSERT_EQ(MATCH_FAIL, super.matchPattern("gfedcbaad"));    //超长
	ASSERT_EQ(MATCH_FAIL, super.matchPattern("gfed"));         //子串
	ASSERT_EQ(MATCH_FAIL, super.matchPattern("gedcba"));
	ASSERT_EQ(MATCH_FAIL, super.matchPattern("abcfg"));
	ASSERT_EQ(MATCH_FAIL, super.matchPattern("abfgd"));

	ASSERT_EQ(MATCH_OK, super.subMatchPattern("abcdef"));
	ASSERT_EQ(MATCH_OK, super.subMatchPattern("abcde"));
	ASSERT_EQ(MATCH_OK, super.subMatchPattern("abcd"));
	ASSERT_EQ(MATCH_OK, super.subMatchPattern("abc"));
	ASSERT_EQ(MATCH_OK, super.subMatchPattern("ab"));
	ASSERT_EQ(MATCH_OK, super.subMatchPattern("a"));
	ASSERT_EQ(MATCH_OK, super.subMatchPattern("abcd"));

	ASSERT_EQ(MATCH_OK, super.fuzzyMatchPattern("acdsdsf"));
	ASSERT_EQ(MATCH_FAIL, super.fuzzyMatchPattern("acdddsf"));
	ASSERT_EQ(MATCH_FAIL, super.fuzzyMatchPattern("acd"));

	ASSERT_EQ(MATCH_OK, super.softMatch("AbcDeFg"));
	ASSERT_EQ(MATCH_OK, super.softMatch("ABceFGd"));
	ASSERT_EQ(MATCH_OK, super.softMatch("GfeDcbA"));

	ASSERT_EQ(MATCH_OK, super.softSubMatch("GfeD"));
	ASSERT_EQ(MATCH_OK, super.softSubMatch("GfeD"));
	ASSERT_EQ(MATCH_OK, super.softSubMatch("GfeD"));
	ASSERT_EQ(MATCH_OK, super.softFuzzyMatch("AcDsdsf"));
}
