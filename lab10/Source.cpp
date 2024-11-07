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
		cerr << "Файл не відкривається для зчитування."
			<< endl;
		return false;
	}
	unsigned int N, M;
	file >> N >> M;
	if (N <= 0 || M <= 0) {
		cerr << "Неправильна структура файла."
			<< "перевірте кількість вершин та ребер."
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
			cerr << "Ребро графа неправильно записано."
				<< endl;
			return false;
		}
		if (u < 1 || u > N) {
			cerr << "Неправильні індекси ребра " << (i + 1) <<"."
				<< endl;
			return false;
		}
		matrixW[v - 1][u - 1] = w;
		adjList[v - 1].push_back({ u - 1, w });
	}
}

void printW() {
	for (size_t i = 0; i < adjList.size(); i++){
		cout << "Вершина графа номер " << (i + 1)
			<< ": ";
		for (const auto& edge : adjList[i])
			cout << " -> " << (edge.first + 1) << " (вага шляху: "
			<< edge.second << ") ";
		cout << endl;
	}
}

void printMatrix() {
	cout << "Матриця ваг для зчитаного графа:" << endl;
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
		cerr << "Файл для збереження не відкривається для запису"
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
	cout << "Матриця ваг збережена." << endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string path;
	cout << "Введіть шлях до графа з вагами ребер: ";
	getline(cin, path);
	if (!read(path)) {
		return 1;
	}
	printW();
	printMatrix();
	string save;
	cout << "Введіть шлях до файлу, де буде "
		<< "збережено матрицю ваг графа: ";
	getline(cin, save);
	saveM(save);
	return 0;
}