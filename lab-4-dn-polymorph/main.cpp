#include <libutils/io.h>
#include <iostream>
#include "figure.h"
#include "rectangle.h"
#include "triangle.h"
#include "trapeze.h"
#include "ellipse.h"
#include <vector>
#include <memory>

using namespace std;

void push(vector <shared_ptr<Figure>>& collection, const int& ind)
{
	auto it = collection.begin();
	int i = 0;
	int choose = utils::readInt("What figure you want to create?\n1.Ellipse\n2.Rectangle\n3.Trapeze\n4.Triangle\n ", 1, 4);
	switch (choose)
	{
	case 1:
	{
		do
		{
			if (i == ind)
			{
				double x = utils::readDouble("Enter the center of the ellipse.\nx=", 0.0, 10.0);
				double y = utils::readDouble("\ny=", 0.0, 10.0);
				while (true)
				{
					double a1 = utils::readDouble("Enter the first rad:", 1.5, 10.0);
					double b1 = utils::readDouble("\nEnter the second rad:", 2.5, 10.0);
					if ((a1 > b1) || (a1 == b1))
					{
						cout << "Error!Enter another data\n" << endl;
						continue;
					}
					collection.insert(it, make_shared<Ellipse>(x, y, a1, b1));
					break;
				}
				break;
			}
			++i;
			++it;
		} while (it != collection.end());
		break;
	}
	case 2:
	{
		do
		{
			if (i == ind)
			{
				while (true) {
					double x1 = utils::readDouble("Enter coordinates of the rectangle.\nx1=", 0.0, 10.0);
					double y1 = utils::readDouble("\ny1=", 0.0, 10.0);
					double x2 = utils::readDouble("\nx2=", 0.0, 10.0);
					double y2 = utils::readDouble("\ny2=", 0.0, 10.0);
					if ((y1 == y2) || (x1 == x2)||(x1>x2)||(y1>y2)) {
						cout << "Error!Enter another data\n" << endl;
						continue;
					}
					collection.insert(it, make_shared<Rectangle>(Rectangle(x1, x2, y1, y2)));
					break;
				}
				break;
			}
			++i;
			++it;
		} while (it != collection.end());
		break;
	}
	case 3:	{
		do {
			if (i == ind) {
				while (true) {
					double x1 = utils::readDouble("Enter the coordinates of the trapeze.\nx1=", 0.0, 10.0);
					double y1 = utils::readDouble("\ny1=", 0.0, 10.0);
					double x2 = utils::readDouble("\nx2=", 0.0, 10.0);
					double y3 = utils::readDouble("\ny3=", 0.0, 10.0);
					double x3 = utils::readDouble("\nx3=", 0.0, 10.0);
					double x4 = utils::readDouble("\nx4=", 0.0, 10.0);
					if ((y1 <= y3) || (x2== x3) || (x1 == x2) || (x3 == x4)||(x2=x4) || ((x1 == x4) && (x2 == x3))) {
						cout << "Error!Enter another data\n" << endl;
						continue;
					}
					collection.insert(it, make_shared<Trapeze>(Trapeze(x1, x2, x3, x4, y1, y3)));
					break;
				}
				break;
			}
			++i;
			++it;
		} while (it != collection.end());
		break;
	}
	case 4: {
		do {
			if (i == ind) {
				while (true) {
					double x1 = utils::readDouble("Enter the coordinates of the triangle.\nx1=", 0.0, 10.0);
					double y1 = utils::readDouble("\ny1=", 0.0, 10.0);
					double x2 = utils::readDouble("\nx2=", 0.0, 10.0);
					double y2 = utils::readDouble("\ny2=", 0.0, 10.0);
					double x3 = utils::readDouble("\nx3=", 0.0, 10.0);
					double y3 = utils::readDouble("\ny3=", 0.0, 10.0);
					if ((x1 == x2) || (x2 == x3) || (x1 == x3) || (y1 == y2) || (y2 == y3) || (y3 == y1)) {
						cout << "Error!Enter another data\n" << endl;
						continue;
					}
					Point a1(x1, y1);
					Point b1(x2, y1);
					Point c1(x3, y3);
					collection.insert(it, make_shared<Triangle>(Triangle(x1, y1, x2, y2, x3, y3)));
					break;
				}
				break;
			}
			++i;
			++it;
		} while (it != collection.end());
		break;
	}
	}
}

void pushToEnd(vector<shared_ptr<Figure>>& collection, const int& cnt)
{
	for (int i = 0; i < cnt; ++i)
	{
		int randomChoose = rand() % 4 + 1;
		switch (randomChoose)
		{
		case 1: {
			double x = rand() % 10;
			double y = rand() % 10;
			double a = rand() % 10;
			double b = rand() % 10;
			collection.push_back(make_shared<Ellipse>(Ellipse(x, y, a, b)));
		}
		case 2:
		{
			while (true)
			{
				double x1 = rand() % 10;
				double y1 = rand() % 10;
				double x2 = rand() % 10;
				double y2 = rand() % 10;
				if ((y1 == y2) || (x1 == x2) || (x1 > x2) || (y1 > y2)) {
					continue;
				}
				collection.push_back(make_shared<Rectangle>(Rectangle(x1, x2, y1, y2)));
				break;
			}
			break;
		}
		case 3:
		{
			while (true)
			{
				double y1 = rand() % 10;
				double x1 = rand() % 10;
				double x2 = rand() % 10;
				double y3 = rand() % 10;
				double x3 = rand() % 10;
				double x4 = rand() % 10;
				if ((y1 <= y3) || (x1 == x2)|| (x3 == x4) || (x1 == x2) || (x3 == x4) || ((x1 == x4) && (x2 == x3))) {
					continue;
				}
				Point a1(x1, y1);
				Point b1(x2, y1);
				Point c1(x3, y3);
				Point d1(x4, y3);
				collection.push_back(make_shared<Trapeze>(Trapeze(x1, x2, x3, x4, y1, y3)));;
				break;
			}
			break;
		}
		case 4:
		{
			while (true)
			{
				double y1 = rand() % 10;
				double x1 = rand() % 10;
				double y2 = rand() % 10;
				double x2 = rand() % 10;
				double y3 = rand() % 10;
				double x3 = rand() % 10;
				if ((x1 == x2) || (x2== x3) || (x1==x3) || (y1 == y2) || (y2== y3) || (y3==y1)) {
					continue;
				}
				collection.push_back(make_shared<Triangle>(Triangle(x1, y1, x2, y2, x3, y3)));
				break;
			}
			break;
		}
		}
	}
}

void output(const vector<shared_ptr<Figure>>& collection) {
	int count = collection.size();
	if ((count != 0) && (count <= 10))
	{
		cout << "Collection:" << endl;
		for (int i = 0; i < count; ++i)
		{
			cout << endl;
			collection[i].get()->print();
		}
	}
	else {
		cout << "COollection:" << endl;
		for (int i = 0; i < 10; ++i)
		{
			cout << endl;
			collection[i].get()->print();
		}
		cout << "..." << endl;
	}
}

void remove (vector<shared_ptr<Figure>>& collection, const int& ind) {
	int i = 0;
	for (auto it = collection.begin(); it != collection.end(); ++it) {
		if (i == ind) {
			collection.erase(it);
			break;
		}
		++i;
	}
}

double sumSquares(vector<shared_ptr<Figure>>& collection)
{
	double result = 0;
	for (int i = 0; i < collection.size(); ++i)
	{
		result += collection[i].get()->getSquare();
	}
	return result;
}


int main() {
	vector<shared_ptr<Figure>> collection; //�������� ������� ���������� �� ������� �����
	while (true) {
		system("cls");
		try {
			cout << "1) Create collection object by index" << endl;
			cout << "2) Create random objects in the end of collection" << endl;
			cout << "3) Delete by index" << endl;
			cout << "4) Calculate the minimal framing rectangle for an object" << endl;
			cout << "5) Equals two objects by index" << endl;
			cout << "6) Print collection" << endl;
			cout << "7) Calculate square" << endl;
			cout << "8) Calculate perimeter" << endl;
			cout << "9) Calculate the total square" << endl;
			cout << "10) Clear collection" << endl;
			cout << "0) Exit" << endl;

			int answer = utils::readInt("Your choose: ", 0, 10);
			switch (answer) {
			case 1: {
				if (collection.empty()) throw"Empty collection!";
				int index = utils::readInt("Enter index: ", 0, collection.size() - 1);
				push(collection, index);
				cout << "Element added\n" << endl;
				cout << "Press any key to continue" << endl;
				getchar();
				break;
			}
			case 2: {
				int count = utils::readInt("Enter the count of objects: ", 1, 7);
				pushToEnd(collection, count);
				cout << "Elements added\n" << endl;
				cout << "Press any key to continue" << endl;
				getchar();
				break;
			}
			case 3: {
				if (collection.empty())  throw "Empty collection!";
				int index = utils::readInt("Enter index: ", 0, collection.size() - 1);
				remove(collection, index);
				cout << "Element deleted\n" << endl;
				cout << "Press any key to continue" << endl;
				getchar();
				break;
			}
			case 4: {
				int ind = utils::readInt("Enter index: ", 0, collection.size() - 1);
				cout << "Minimal framing rectangle: " << endl;
				collection[ind].get()->getRectangle()->print();
				cout << "Press any key to continue" << endl;
				getchar();
				break;
				}
			case 5: {
				if ((collection.empty()) || (collection.size() < 2))  throw "There is nothing to compare!";
				int ind1 = utils::readInt("Enter index of first object: ", 0, collection.size() - 1);
				int ind2 = utils::readInt("Enter index of second object: ", 0, collection.size() - 1);
				if (collection.at(ind1).get()->equals(*(collection.at(ind2).get()))) cout << "Objects are equal" << endl;
				else cout << "Objects are not equal" << endl;
				cout << "Press any key to continue" << endl;
				getchar();
				break;
			}
			case 6: {
				if (collection.empty())  throw "Empty collection!";
				output(collection);
				cout << "Press any key to continue" << endl;
				getchar();
				break;
			}
			case 7: {
				int ind = utils::readInt("Enter index: ", 0, collection.size() - 1);
				cout << "The square of the object: " << collection[ind].get()->getSquare() << endl;
				cout << "Press any key to continue" << endl;
				getchar();
				break;
			}
			case 8: {
				int ind = utils::readInt("Enter index: ", 0, collection.size() - 1);
				cout << "The perimeter of the object: " << collection[ind].get()->getPerimeter() << endl;
				cout << "Press any key to continue" << endl;
				getchar();
				break;
			}
			case 9: {
				cout << sumSquares(collection) << endl;
				cout << "Press any key to continue" << endl;
				getchar();
				break;
			}
			case 10: {
				if (collection.empty())  throw "Empty collection!!";
				collection.clear();
				cout << "Collection cleared\n" << endl;
				cout << "Press any key to continue" << endl;
				getchar();
				break;
			}
			case 0: {
				return 0;
			}
			}
		}
		catch (const char* er) {
			cout << er << endl;
		}
	}
	return 0;
}