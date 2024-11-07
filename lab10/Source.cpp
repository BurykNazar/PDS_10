#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<string>
#include<vector>

#define NOMINMAX
#include<Windows.h>

using namespace std;

vector<vector<unsigned int>> matrixW;
vector<vector<pair<int, int>>> adjList;

const unsigned int INF = numeric_limits<unsigned int>::max();


bool read(const string& path) {
	ifstream file(path);
	if (!file.is_open()) {
		cerr << "���� �� ����������� ��� ����������."
			<< endl;
		return false;
	}
	unsigned int N, M;
	file >> N >> M;
	if (N <= 0 || M <= 0) {
		cerr << "����������� ��������� �����."
			<< "�������� ������� ������ �� �����."
			<< endl;
		return false;
	}
	matrixW.assign(N, vector<unsigned int>(N, INF));
	adjList.assign(N, vector<pair<int, int>>());

	for (size_t i = 0; i < N; i++) {
		matrixW[i][i] = 0;
	}

	for (size_t i = 0; i < M; i++) {
		unsigned int v, u, w;
		if (!(file >> v >> u >> w)) {
			cerr << "����� ����� ����������� ��������."
				<< endl;
			return false;
		}
		if (u < 1 || u > N) {
			cerr << "���������� ������� ����� " << (i + 1) <<"."
				<< endl;
			return false;
		}
		matrixW[v - 1][u - 1] = w;
		adjList[v - 1].push_back({ u - 1, w });
	}
}

void printW() {
	for (size_t i = 0; i < adjList.size(); i++){
		cout << "������� ����� ����� " << (i + 1)
			<< ": ";
		for (const auto& edge : adjList[i])
			cout << " -> " << (edge.first + 1) << " (���� �����: "
			<< edge.second << ") ";
		cout << endl;
	}
}

void printMatrix() {
	cout << "������� ��� ��� ��������� �����:" << endl;
	for (size_t i = 0; i < matrixW.size(); i++) {
		for (size_t j = 0; j < matrixW[i].size(); j++) {
			if (matrixW[i][j] == INF) {
				cout << setw(10) << "INF ";
			}
			else {
				cout << setw(10) << matrixW[i][j] << setw(10);
			}
		}
		cout << endl;
	}
}

void saveM(const string& path) {
	ofstream file(path);
	if (!file.is_open()) {
		cerr << "���� ��� ���������� �� ����������� ��� ������"
			<< endl;
		return;
	}
	for (size_t i = 0; i < matrixW.size(); i++) {
		for (size_t j = 0; j < matrixW[i].size(); j++) {
			if (matrixW[i][j] == INF) {
				file << setw(10) << "INF ";
			}
			else {
				file << setw(10) << matrixW[i][j] << setw(10);
			}
		}
		file << endl;
	}
	file.close();
	cout << "������� ��� ���������." << endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string path;
	cout << "������ ���� �� ����� � ������ �����: ";
	getline(cin, path);
	if (!read(path)) {
		return 1;
	}
	printW();
	printMatrix();
	string save;
	cout << "������ ���� �� �����, �� ���� "
		<< "��������� ������� ��� �����: ";
	getline(cin, save);
	saveM(save);
	return 0;
}