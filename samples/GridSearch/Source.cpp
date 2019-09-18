#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> split_string(string);

// Complete the gridSearch function below (took 22 minutes to complete)
string gridSearch(vector<string> G, vector<string> P) {
	for (size_t row = 0; row < G.size() - P.size() + 1; ++row)
	{
		int col = 0;
		string& cur_line = G[row];
		while (col < cur_line.size())
		{
			auto pos = cur_line.find(P[0], col);
			if (pos != string::npos)
			{
				col = pos + 1;
				bool match = true;
				for (size_t r2 = 1; match && r2 < P.size(); ++r2)
				{
					if (G[row + r2].substr(pos, P[0].size()) != P[r2])
						match = false;
				}
				if (match)
					return "YES";
			}
			else
				col = cur_line.size();
		}

	}
	return "NO";
}

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	int t;
	cin >> t;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int t_itr = 0; t_itr < t; t_itr++) {
		string RC_temp;
		getline(cin, RC_temp);

		vector<string> RC = split_string(RC_temp);

		int R = stoi(RC[0]);

		int C = stoi(RC[1]);

		vector<string> G(R);

		for (int i = 0; i < R; i++) {
			string G_item;
			getline(cin, G_item);

			G[i] = G_item;
		}

		string rc_temp;
		getline(cin, rc_temp);

		vector<string> rc = split_string(rc_temp);

		int r = stoi(rc[0]);

		int c = stoi(rc[1]);

		vector<string> P(r);

		for (int i = 0; i < r; i++) {
			string P_item;
			getline(cin, P_item);

			P[i] = P_item;
		}

		string result = gridSearch(G, P);

		fout << result << "\n";
	}

	fout.close();

	return 0;
}

vector<string> split_string(string input_string) {
	string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
		return x == y and x == ' ';
	});

	input_string.erase(new_end, input_string.end());

	while (input_string[input_string.length() - 1] == ' ') {
		input_string.pop_back();
	}

	vector<string> splits;
	char delimiter = ' ';

	size_t i = 0;
	size_t pos = input_string.find(delimiter);

	while (pos != string::npos) {
		splits.push_back(input_string.substr(i, pos - i));

		i = pos + 1;
		pos = input_string.find(delimiter, i);
	}

	splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

	return splits;
}
