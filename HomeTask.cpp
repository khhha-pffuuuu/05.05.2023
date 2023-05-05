#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;



vector<int> naive_search_string(string text, string pattern) {
	int matches = 0;
	vector <int> ans;

	for (int i = 0; i < text.length(); i++) {
		if (text[i] == pattern[matches]) {
			matches += 1;
		}
		else {
			matches = 0;
		}

		if (matches == pattern.length()) {
			ans.push_back(i - matches + 1);
		}
	}

	return ans;
}



vector<int> z_function(string text) {
	int n = text.length();
	vector<int> z(n, 0);

	for (int i = 1, left = 0, right = 0; i < n; i++) {
		if (i <= right)
			z[i] = min(right - i + 1, z[i - left]);

		while (i + z[i] < n && text[z[i]] == text[i + z[i]])
			z[i]++;

		if (i + z[i] - 1 > right) {
			right = i + z[i] - 1;
			left = i;
		}
	}

	return z;
}

vector<int> z_function_search_string(string text, string pattern) {
	string new_text = pattern + text;
	vector <int> z = z_function(new_text);
	vector <int> ans;

	for (int i = pattern.length(); i < z.size(); i++) {
		if (z[i] >= pattern.length()) {
			ans.push_back(i - pattern.length());
		}
	}

	return ans;
}



int main() {
	setlocale(LC_ALL, "rus");

	string text = "Choose right answer. Choose your way. Choose your subject theme.", pattern = "Choose";

	vector <int> ans1 = naive_search_string(text, pattern);
	vector <int> ans2 = z_function_search_string(text, pattern);

	if (!ans1.empty() || !ans2.empty()) {
		cout << "Наивный поиск подстроки: ";
		for (int i = 0; i < ans1.size(); i++) {
			cout << ans1[i] << " ";
		}

		cout << endl;

		cout << "Поиск подстроки при помощи z-функции: ";
		for (int i = 0; i < ans2.size(); i++) {
			cout << ans2[i] << " ";
		}
	}
	else {
		cout << "Подстрока не содержится";
	}
}