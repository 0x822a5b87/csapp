#include <stack>
#include "iostream"
#include "string"

class Solution
{
public:
	bool isValid(std::string s)
	{
		std::stack<char> st;
		for (char & i : s)
		{
			if (isClose(i))
			{
				if (st.empty())
				{
					return false;
				}
				char &ch = st.top();
				st.pop();
				if (!isMatch(ch, i))
				{
					return false;
				}
			}
			else
			{
				st.push(i);
			}
		}
		return st.empty();
	}

private:
	bool isMatch(const char left, const char right)
	{
		if (left == '(')
		{
			return right == ')';
		}
		else if (left == '[')
		{
			return right == ']';
		}
		else if (left == '{')
		{
			return right == '}';
		}
		else
		{
			return true;
		}
	}

	bool isClose(const char ch)
	{
		return ch == ')' || ch == ']' || ch == '}';
	}
};

int main(int argc, char **argv)
{
	Solution solution;
	assert(solution.isValid("()"));
	assert(solution.isValid("([])"));
	assert(solution.isValid("({})"));
	assert(!solution.isValid("({)}"));
	assert(!solution.isValid("]"));
}