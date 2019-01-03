#include <iostream>
#include <regex>
#include <string>
using namespace std;
int main()
{
	string s;
	while(1)
	{
		cout << "Please enter license plate Number:" << endl;
		cin >> s;
		std::regex reg("(A2|2A|A[B-DGH]|X[ABH]|2U|U[0-9]|V[0-9]|F[A-Z]|EAA|FA[A-Z])-[0-9]{3}"
					   "|[0-9]{3}-(A2|2A|A[B-DGH]|X[ABH]|2U|V[0-9]|U[0-9]|V3|F[A-Z]|FA[A-Z])"
					   "|AA-A[0-9]{2}"
					   "|FA[A-Z]-[0-9]{3}"
					   "|KK[A-Z]-[0-9]{4}"
					   "|EAL-[0-9]{4}");
		if (std::regex_match(s, reg))
		{
			cout << "is bus" << endl;
		}
		else
		{
			cout << "isn't bus" << endl;
		}
	}
}
