#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab10\Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		void createTestGraphFile(const string& filename) {
			ofstream file(filename);
			file << "4 5\n"
				<< "1 2 10\n" 
				<< "1 3 5\n"
				<< "2 3 2\n"
				<< "3 4 1\n"
				<< "4 1 7\n";
			file.close();
		}

		TEST_METHOD(TestReadGraph)
		{
			string testFilePath = "test_graph.txt";
			createTestGraphFile(testFilePath);

			bool result = read(testFilePath);
			Assert::IsTrue(result, L"Не вдалося зчитати файл графа");

			Assert::AreEqual(size_t(4), matrixW.size(), L"Неправильний розмір матриці ваг");
			Assert::AreEqual(matrixW[0][1], 10u, L"Неправильна вага для ребра (1 -> 2)");
			Assert::AreEqual(matrixW[0][2], 5u, L"Неправильна вага для ребра (1 -> 3)");
			Assert::AreEqual(matrixW[1][2], 2u, L"Неправильна вага для ребра (2 -> 3)");
			Assert::AreEqual(matrixW[2][3], 1u, L"Неправильна вага для ребра (3 -> 4)");
			Assert::AreEqual(matrixW[3][0], 7u, L"Неправильна вага для ребра (4 -> 1)");

			Assert::AreEqual(size_t(4), adjList.size(), L"Неправильний розмір списку суміжності");
			Assert::AreEqual(adjList[0][0].second, 10, L"Неправильна вага для суміжності (1 -> 2)");
			Assert::AreEqual(adjList[0][1].second, 5, L"Неправильна вага для суміжності (1 -> 3)");
			Assert::AreEqual(adjList[1][0].second, 2, L"Неправильна вага для суміжності (2 -> 3)");
			Assert::AreEqual(adjList[2][0].second, 1, L"Неправильна вага для суміжності (3 -> 4)");
			Assert::AreEqual(adjList[3][0].second, 7, L"Неправильна вага для суміжності (4 -> 1)");
		}
	};
}
