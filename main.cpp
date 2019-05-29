#define n 5
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

class Relation {
public:
	int s;
	virtual void print() {};
	virtual void operator& (Relation const &obj) {}; // Intersection
	virtual void operator| (Relation const &obj) {}; // Union
	virtual void operator> (Relation const &obj) {}; // Difference
	virtual void operator- (Relation const &obj) {}; // Symmetric Difference
	virtual void operator* (Relation const &obj) {}; // Composition
	virtual void operator^ (Relation const &obj) {}; // Include
	virtual void operator= (Relation const &obj) {}; // Include
	virtual void operator++ () {};     // Inversion
	virtual void operator! () {};     // P_
	virtual void decrease() {};     // P_
	void Pd() {};     // P_

	Relation() {}
	~Relation() {}
};

class RelationMatrix : public Relation
{
public:
	bool **arr;
	const static int s = n;

	void print() {
		for (int i = 0; i < s; i++) {
			for (int j = 0; j < s; j++) {
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	};

	void operator& (RelationMatrix const &obj) {
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				arr[i][j] = obj.arr[i][j] & arr[i][j];
			}
		}
	}; // Intersection

	void operator| (RelationMatrix const &obj)
	{
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				arr[i][j] = obj.arr[i][j] | arr[i][j];
			}
		}
	}; // Union

	void operator> (RelationMatrix const &obj)
	{
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				arr[i][j] = arr[i][j] > obj.arr[i][j];
			}
		}
	}; // Difference

	void operator- (RelationMatrix const &obj)
	{
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				arr[i][j] = (arr[i][j] > obj.arr[i][j]) | (obj.arr[i][j] > arr[i][j]);
			}
		}
	}; // Symmetric Difference

	void operator* (RelationMatrix const &obj)
	{
		bool **tmp;
		tmp = new bool*[s];
		for (int i = 0; i < s; i++)
		{
			tmp[i] = new bool[s];
		}

		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				tmp[i][j] = 0;
				for (int k = 0; k < s; k++)
				{
					tmp[i][j] = tmp[i][j] || (arr[i][k] && obj.arr[k][j]);
				}
			}
		}

		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				arr[i][j] = tmp[i][j];
			}
		}
	}; // Composition

	bool operator^ (RelationMatrix const &obj) // Include
	{
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				if ((arr[i][j] != obj.arr[i][j]) && arr[i][j] == 0) {
					return 0;
				}
			}
		}
		return 1;
	};

	void operator++ () // Inverse
	{
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < i; j++)
			{
				swap(arr[i][j], arr[j][i]);
			}
		}
	};

	void operator! () // P_
	{
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				arr[i][j] = !arr[i][j];
			}
		}
	};

	void decrease(int const obj[], bool **res, int size) // Decrease (zv)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				res[i][j] = arr[obj[i]][obj[j]];
			}
		}
	};

	void Pd() // PD
	{
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				arr[i][j] = !arr[i][j];
			}
		}

		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < i; j++)
			{
				swap(arr[i][j], arr[j][i]);
			}
		}
	};

	void operator= (const RelationMatrix& M)
	{
		arr = new bool*[s];

		for (int i = 0; i < s; i++)
			arr[i] = new bool[s];

		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				arr[i][j] = M.arr[i][j];
			}
		}
	}

	RelationMatrix(char rel_type = 'e') {
		/*
		e - empty
		1 - full
		d - diagonal
		a - anti_diagonal
		*/
		arr = new bool*[s];
		for (int i = 0; i < s; i++)
		{
			arr[i] = new bool[s];
			memset(arr[i], 0, s * sizeof(bool));
		}

		switch (rel_type)
		{
		case '1': {
			for (int i = 0; i < s; i++)
			{
				for (int j = 0; j < s; j++)
				{
					arr[i][j] = 1;
				}
			}
			break;
		}
		case 'd': {
			for (int i = 0; i < s; i++)
			{
				arr[i][i] = 1;
			}
			break;
		}
		case 'a': {
			for (int i = 0; i < s; i++)
			{
				for (int j = 0; j < s; j++)
				{
					arr[i][j] = (i != j);
				}
			}
			break;
		}
		default:

			break;
		}

	}
	RelationMatrix(int **matr) {
		arr = new bool*[s];

		for (int i = 0; i < s; i++)
			arr[i] = new bool[s];

		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				arr[i][j] = matr[i][j];
			}
		}
	}
	RelationMatrix(int matr[s][s]) {
		arr = new bool*[s];

		for (int i = 0; i < s; i++)
			arr[i] = new bool[s];

		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				arr[i][j] = matr[i][j];
			}
		}
	}
	~RelationMatrix() {}
};

class RelationVector : public Relation
{
public:
	vector<vector<int>> vec;
	const static int s = n;

	void print() {
		for (int i = 0; i < vec.size(); i++) {
			cout << "R(" << i << ") = ";
			for (int j = 0; j < vec[i].size(); j++) {
				cout << vec[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	};


	void operator& (RelationVector const &obj) {
		vector<vector<int>> tmp_vec = RelationVector().vec;
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < obj.vec[i].size(); j++)
			{
				if (binary_search(vec[i].begin(), vec[i].end(), obj.vec[i][j])
					&& binary_search(obj.vec[i].begin(), obj.vec[i].end(), obj.vec[i][j])) {
					tmp_vec[i].push_back(obj.vec[i][j]);
				}
			}
		}
		vec = tmp_vec;
	}; // Intersection

	void operator| (RelationVector const &obj)
	{
		vector<vector<int>> tmp_vec = vec;
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < obj.vec[i].size(); j++)
			{
				if (!binary_search(vec[i].begin(), vec[i].end(), obj.vec[i][j])
					&& binary_search(obj.vec[i].begin(), obj.vec[i].end(), obj.vec[i][j])) {
					tmp_vec[i].push_back(obj.vec[i][j]);
					sort(tmp_vec[i].begin(), tmp_vec[i].end());
				}
			}
		}
		vec = tmp_vec;
	}; // Union

	void operator> (RelationVector const &obj)
	{
		vector<vector<int>> tmp_vec = RelationVector().vec;
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < vec[i].size(); j++)
			{
				if (binary_search(vec[i].begin(), vec[i].end(), vec[i][j])
					&& !binary_search(obj.vec[i].begin(), obj.vec[i].end(), vec[i][j])) {
					tmp_vec[i].push_back(vec[i][j]);
				}
			}
		}
		vec = tmp_vec;
	}; // Difference

	void operator- (RelationVector const &obj)
	{
		vector<vector<int>> tmp_vec = RelationVector().vec;
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				if (binary_search(vec[i].begin(), vec[i].end(), j)
					!= binary_search(obj.vec[i].begin(), obj.vec[i].end(), j)) {
					tmp_vec[i].push_back(j);
				}
			}
		}
		vec = tmp_vec;
	};

	void operator* (RelationVector const &obj)
	{
		vector<vector<int>> tmp_vec = RelationVector().vec;

		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				bool tmp = false;
				for (int k = 0; k < s; k++)
				{
					tmp = tmp || (binary_search(obj.vec[i].begin(), obj.vec[i].end(), k)
						&& binary_search(vec[k].begin(), vec[k].end(), j));
				}
				if (tmp)
					tmp_vec[i].push_back(j);
			}
		}
		vec = tmp_vec;
	};

	bool include(RelationVector const &obj) // Include
	{
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < obj.vec[i].size(); j++)
			{
				if (!binary_search(vec[i].begin(), vec[i].end(), obj.vec[i][j]))
					return 0;
			}
		}
		return 1;
	};

	void operator++ () // Inverse
	{
		vector<vector<int>> tmp_vec = RelationVector().vec;
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				if (binary_search(vec[i].begin(), vec[i].end(), j)) {
					tmp_vec[j].push_back(i);
				}
			}
		}
		vec = tmp_vec;
	};

	void operator! () // P_
	{
		vector<vector<int>> tmp_vec = RelationVector().vec;
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				if (!binary_search(vec[i].begin(), vec[i].end(), j)) {
					tmp_vec[i].push_back(j);
				}
			}
		}
		vec = tmp_vec;
	};

	void decrease(int const obj[], int const &size) // Decrease (zv)
	{
		vector<vector<int>> tmp_vec = RelationVector().vec;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (binary_search(vec[obj[i]].begin(), vec[obj[i]].end(), obj[j])) {
					tmp_vec[i].push_back(j);
				}
			}
		}
		vec = tmp_vec;
	};

	void operator= (const RelationVector &obj)
	{
		vec.clear();
		for (int i = 0; i < s; i++) {
			vector<int> row;
			for (int j = 0; j < obj.vec[i].size(); j++) {
				row.push_back(obj.vec[i][j]);
			}
			vec.push_back(row);
		}
	}

	void Pd() // PD
	{
		vector<vector<int>> tmp_vec = RelationVector().vec;
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				if (!binary_search(vec[i].begin(), vec[i].end(), j)) {
					tmp_vec[i].push_back(j);
				}
			}
		}
		vec = tmp_vec;

		tmp_vec = RelationVector().vec;
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				if (binary_search(vec[i].begin(), vec[i].end(), j)) {
					tmp_vec[j].push_back(i);
				}
			}
		}
		vec = tmp_vec;
	};

	RelationVector(char rel_type = 'e') {
		/*
		e - empty
		1 - full
		d - diagonal
		a - anti_diagonal
		*/
		for (int i = 0; i < s; i++) {
			vector<int> row;
			vec.push_back(row);
		}


		switch (rel_type)
		{
		case '1': {
			for (int i = 0; i < s; i++)
			{
				for (int j = 0; j < s; j++)
				{
					vec[i].push_back(j);
				}
			}
			break;
		}
		case 'd': {
			for (int i = 0; i < s; i++)
			{
				vec[i].push_back(i);
			}
			break;
		}
		case 'a': {
			for (int i = 0; i < s; i++)
			{
				for (int j = 0; j < s; j++)
				{
					if (i != j) {
						vec[i].push_back(j);
					};
				}
			}
			break;
		}
		default:

			break;
		}

	}
	RelationVector(int **matr) {
		for (int i = 0; i < s; i++) {
			vector<int> row;
			for (int j = 0; j < s; j++) {
				if (matr[j][i]) {
					row.push_back(j);
				}
			}
			vec.push_back(row);
		}
	}
	RelationVector(int matr[s][s]) {
		for (int i = 0; i < s; i++) {
			vector<int> row;
			for (int j = 0; j < s; j++) {
				if (matr[j][i]) {
					row.push_back(j);
				}
			}
			vec.push_back(row);
		}
	}
	~RelationVector() {}
};

int main()
{

    int P[RelationMatrix::s][RelationMatrix::s] =
            { { 0,0,1,0,0 },
              { 0,0,1,0,0 },
              { 1,0,0,1,0 },
              { 0,0,1,1,0 },
              { 1,0,0,0,0 } };

    int Q[RelationMatrix::s][RelationMatrix::s] =
            { { 0,1,0,0,0 },
              { 0,1,0,0,0 },
              { 0,0,1,0,0 },
              { 0,1,0,0,1 },
              { 1,1,0,0,0 } };

    int R[RelationMatrix::s][RelationMatrix::s] =
            { { 0,0,0,1,0 },
              { 0,1,1,0,0 },
              { 0,1,0,0,1 },
              { 0,0,0,1,0 },
              { 1,0,1,0,0 } };


	RelationVector p(P);
	RelationVector q(Q);
	RelationVector r(R);

	RelationMatrix pm(P);
	RelationMatrix qm(Q);
	RelationMatrix rm(R);

	p*q;
	r.Pd();
	p - r;
	p.print();

	cout << endl;

	pm*qm;
	rm.Pd();
	pm - rm;
	pm.print();

	return 0;
}