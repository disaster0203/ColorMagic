#include "gtest\gtest.h"
#include "pch.h"
#include "..\ColorMagic\ColorSpaces\icolor.h"
#include "..\ColorMagic\ColorSpaces\xyz.h"

using namespace ColorSpaces;

class XYZ_Test : public ::testing::Test {
protected:
	xyz* yellow;
	xyz* black;
	xyz* white;

	virtual void SetUp()
	{
		yellow = new xyz(0.77f, 0.9278f, 0.1385f);
		black = new xyz(0.f, 0.f, 0.f);
		white = new xyz(1.f, 1.f, 1.f);
	}

	virtual void TearDown()
	{
		delete yellow;
		delete black;
		delete white;
	}
};

TEST_F(XYZ_Test, Constructor_Tests)
{
	EXPECT_EQ(*black, *(new xyz()));
	EXPECT_EQ(*yellow, *(new xyz(0.77f, 0.9278f, 0.1385f)));
	EXPECT_EQ(*white, *(new xyz(1.f, 1.f, 1.f)));
}

TEST_F(XYZ_Test, Operator_Tests)
{
	auto blue = new xyz(0.f, 0.f, 1.f);
	EXPECT_TRUE(*blue != *yellow);
	blue = yellow;
	EXPECT_TRUE(*blue == *yellow);
}