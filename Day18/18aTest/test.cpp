#include "pch.h"

#define TESTING
#include "../18a/main.cpp"

TEST(SanitizationTests, Simple) {
	string inOut[5][2] = {
		{"[[[[[9,8],1],2],3],4]", "[[[[0,9],2],3],4]"},
		{"[7,[6,[5,[4,[3,2]]]]]", "[7,[6,[5,[7,0]]]]"},
		{"[[6,[5,[4,[3,2]]]],1]", "[[6,[5,[7,0]]],3]"},
		{"[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]", "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]"},
		{"[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]", "[[3,[2,[8,0]]],[9,[5,[7,0]]]]"}
	};

	for(int testCase = 0; testCase < 5; ++testCase) {
		string const& input = inOut[testCase][0];
		string const& expected = inOut[testCase][1];

		stringstream ss;

		SnailfishNumberReference number = parseSnailFishNumber(input);
		number->Sanitize();
		ss << *number;

		string actual = ss.str();

		EXPECT_EQ(expected, actual);

		delete number;
	}
}

TEST(Addition, Simple) {
	SnailfishNumberReference a = parseSnailFishNumber("[[[[4,3],4],4],[7,[[8,4],9]]]");
	SnailfishNumberReference b = parseSnailFishNumber("[1,1]");

	SnailfishNumberReference result = a->Add(b);

	stringstream ss;
	ss << *result;

	string actual = ss.str();

	string expected = "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]";

	EXPECT_EQ(expected, actual);

	delete result;
}

TEST(Addition, Advanced) {
	vector<string> testCases[3] = {
		{"[1,1]", "[2,2]", "[3,3]", "[4,4]"},
		{"[1,1]", "[2,2]", "[3,3]", "[4,4]", "[5,5]"},
		{"[1,1]", "[2,2]", "[3,3]", "[4,4]", "[5,5]", "[6,6]"}
	};

	string expected[3] = {
		"[[[[1,1],[2,2]],[3,3]],[4,4]]",
		"[[[[3,0],[5,3]],[4,4]],[5,5]]",
		"[[[[5,0],[7,4]],[5,5]],[6,6]]"
	};

	for(int testCase = 0; testCase < 3; ++testCase) {
		SnailfishNumberReference sum = parseSnailFishNumber(testCases[testCase][0]);

		for(int i = 1; i < testCases[testCase].size(); ++i) {
			sum = sum->Add(parseSnailFishNumber(testCases[testCase][i]));
		}

		stringstream ss;
		ss << *sum;

		string actual = ss.str();

		EXPECT_EQ(expected[testCase], actual);

		delete sum;
	}
}


TEST(Addition, Difficult) {
	vector<string> testCase = {
		"[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]",
		"[7,[[[3,7],[4,3]],[[6,3],[8,8]]]]",
		"[[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]",
		"[[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]",
		"[7,[5,[[3,8],[1,4]]]]",
		"[[2,[2,2]],[8,[8,1]]]",
		"[2,9]",
		"[1,[[[9,3],9],[[9,0],[0,7]]]]",
		"[[[5,[7,4]],7],1]",
		"[[[[4,2],2],6],[8,7]]"
	};

	string expected = "[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]";

	SnailfishNumberReference sum = parseSnailFishNumber(testCase[0]);

	for(int i = 1; i < testCase.size(); ++i) {
		sum = sum->Add(parseSnailFishNumber(testCase[i]));
	}

	stringstream ss;
	ss << *sum;

	string actual = ss.str();

	EXPECT_EQ(expected, actual);

	delete sum;
}

TEST(Addition, AdvancedTinyCases) {
	vector<string> testCases[9] = {
		{"[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]", "[7,[[[3,7],[4,3]],[[6,3],[8,8]]]]"},
		{"[[[[4,0],[5,4]],[[7,7],[6,0]]],[[8,[7,7]],[[7,9],[5,0]]]]", "[[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]"},
		{"[[[[6,7],[6,7]],[[7,7],[0,7]]],[[[8,7],[7,7]],[[8,8],[8,0]]]]", "[[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]"},
		{"[[[[7,0],[7,7]],[[7,7],[7,8]]],[[[7,7],[8,8]],[[7,7],[8,7]]]]", "[7,[5,[[3,8],[1,4]]]]"},
		{"[[[[7,7],[7,8]],[[9,5],[8,7]]],[[[6,8],[0,8]],[[9,9],[9,0]]]]", "[[2,[2,2]],[8,[8,1]]]"},
		{"[[[[6,6],[6,6]],[[6,0],[6,7]]],[[[7,7],[8,9]],[8,[8,1]]]]", "[2,9]"},
		{"[[[[6,6],[7,7]],[[0,7],[7,7]]],[[[5,5],[5,6]],9]]", "[1,[[[9,3],9],[[9,0],[0,7]]]]"},
		{"[[[[7,8],[6,7]],[[6,8],[0,8]]],[[[7,7],[5,0]],[[5,5],[5,6]]]]", "[[[5,[7,4]],7],1]"},
		{"[[[[7,7],[7,7]],[[8,7],[8,7]]],[[[7,0],[7,7]],9]]", "[[[[4,2],2],6],[8,7]]"}
	};

	string expected[9] = {
		"[[[[4,0],[5,4]],[[7,7],[6,0]]],[[8,[7,7]],[[7,9],[5,0]]]]",
		"[[[[6,7],[6,7]],[[7,7],[0,7]]],[[[8,7],[7,7]],[[8,8],[8,0]]]]",
		"[[[[7,0],[7,7]],[[7,7],[7,8]]],[[[7,7],[8,8]],[[7,7],[8,7]]]]",
		"[[[[7,7],[7,8]],[[9,5],[8,7]]],[[[6,8],[0,8]],[[9,9],[9,0]]]]",
		"[[[[6,6],[6,6]],[[6,0],[6,7]]],[[[7,7],[8,9]],[8,[8,1]]]]",
		"[[[[6,6],[7,7]],[[0,7],[7,7]]],[[[5,5],[5,6]],9]]",
		"[[[[7,8],[6,7]],[[6,8],[0,8]]],[[[7,7],[5,0]],[[5,5],[5,6]]]]",
		"[[[[7,7],[7,7]],[[8,7],[8,7]]],[[[7,0],[7,7]],9]]",
		"[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]"
	};

	for(int testCase = 0; testCase < 9; ++testCase) {
		SnailfishNumberReference sum = parseSnailFishNumber(testCases[testCase][0]);

		for(int i = 1; i < testCases[testCase].size(); ++i) {
			sum = sum->Add(parseSnailFishNumber(testCases[testCase][i]));
		}

		stringstream ss;
		ss << *sum;

		string actual = ss.str();

		EXPECT_EQ(expected[testCase], actual);

		delete sum;
	}
}

TEST(Addition, HomeworkDifficult) {
	vector<string> testCase = {
		"[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]",
		"[[[5,[2,8]],4],[5,[[9,9],0]]]",
		"[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]",
		"[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]",
		"[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]",
		"[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]",
		"[[[[5,4],[7,7]],8],[[8,3],8]]",
		"[[9,3],[[9,9],[6,[4,9]]]]",
		"[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]",
		"[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]"
	};

	string expected = "[[[[6,6],[7,6]],[[7,7],[7,0]]],[[[7,7],[7,7]],[[7,8],[9,9]]]]";

	SnailfishNumberReference sum = parseSnailFishNumber(testCase[0]);

	for(int i = 1; i < testCase.size(); ++i) {
		sum = sum->Add(parseSnailFishNumber(testCase[i]));
	}

	stringstream ss;
	ss << *sum;

	string actual = ss.str();

	EXPECT_EQ(expected, actual);

	delete sum;
}

TEST(Magnitude, Simple) {
	vector<string> testCase = {
		"[9,1]",
		"[1,9]",
		"[[9,1],[1,9]]"
	};

	long expected[] = {29, 21, 129};

	for(int i = 0; i < testCase.size(); ++i) {
		SnailfishNumberReference number = parseSnailFishNumber(testCase[i]);
		long actual = number->Magnitude();

		EXPECT_EQ(expected[i], actual);

		delete number;
	}
}

TEST(Magnitude, Advanced) {
	vector<string> testCase = {
		"[[1,2],[[3,4],5]]",
		"[[[[0,7],4],[[7,8],[6,0]]],[8,1]]",
		"[[[[1,1],[2,2]],[3,3]],[4,4]]",
		"[[[[3,0],[5,3]],[4,4]],[5,5]]",
		"[[[[5,0],[7,4]],[5,5]],[6,6]]",
		"[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]"
	};

	long expected[] = { 143, 1384, 445, 791, 1137, 3488 };

	for(int i = 0; i < testCase.size(); ++i) {
		SnailfishNumberReference number = parseSnailFishNumber(testCase[i]);
		long actual = number->Magnitude();

		EXPECT_EQ(expected[i], actual);

		delete number;
	}
}

TEST(AdditionAndMagnitude, HomeworkDifficult) {
	vector<string> testCase = {
		"[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]",
		"[[[5,[2,8]],4],[5,[[9,9],0]]]",
		"[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]",
		"[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]",
		"[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]",
		"[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]",
		"[[[[5,4],[7,7]],8],[[8,3],8]]",
		"[[9,3],[[9,9],[6,[4,9]]]]",
		"[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]",
		"[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]"
	};

	string expected = "[[[[6,6],[7,6]],[[7,7],[7,0]]],[[[7,7],[7,7]],[[7,8],[9,9]]]]";

	SnailfishNumberReference sum = parseSnailFishNumber(testCase[0]);

	for(int i = 1; i < testCase.size(); ++i) {
		sum = sum->Add(parseSnailFishNumber(testCase[i]));
	}

	stringstream ss;
	ss << *sum;

	string actual = ss.str();

	EXPECT_EQ(expected, actual);

	long expectedMagnitude = 4140;

	long actualMagnitude = sum->Magnitude();

	EXPECT_EQ(expectedMagnitude, actualMagnitude);

	delete sum;
}
