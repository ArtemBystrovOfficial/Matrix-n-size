#include <valarray>
#include <cstdarg>
#include <iostream>
#include <exception>

template <typename T>
struct Matrix
{
#define FOREVER for(;;)
public:

	Matrix(int n...) : size(n)
	{		
		va_list ap; va_start(ap, n);
		size = n;
		while (n--)
		{
			sizes.push_back(va_arg(ap, int));
			if (ap == nullptr && n != 0)throw std::exception("ERR-> So many or low arguments Matrix :: Constructor");
		}
		va_end(ap);

		int sum = std::accumulate(sizes.begin(), sizes.end(), 1, multi);
		mat.resize(sum);
	}

	int Slice_Vec(std::vector<int> & sizes_from)
	{
		if(sizes_from.size()!=sizes.size()) throw std::exception("ERR-> Diferent arguments Matrix");
		
		int index = 0;
		int k = 1;
		for (int i = sizes_from.size()-1; i >=0; --i)
		{
			if(i+1<sizes.size())k *= sizes[i+1];
			index += k*sizes_from[i];
		}
		if(index>=mat.size()) throw std::exception("ERR-> Bad index");
		return index;
	}

	T & operator()(...)
	{
		va_list ap; va_start(ap, size);
		int n = size;
		std::vector < int > sizes_from;
		while (n--)
		{
			sizes_from.push_back(va_arg(ap, int));
			if (ap == nullptr && n!=0 )throw std::exception("ERR-> So many or low arguments Matrix");
		}
		va_end(ap);
		return mat[Slice_Vec(sizes_from)];
		
	}

private:
	int size = 1;
	std::vector<int> sizes{};
	std::valarray <T> mat{};
};

int main()
{	
	using namespace std;
	Matrix<int> mt(3, 10 , 10, 20);
	for (int x = 0; x < 20; x++)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				mt(i, j, x) = i + j + x;
			}
		}
	}
	for (int x = 0; x < 20; x++)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				cout << mt(i, j, x) << " ";
			}
			cout << '\n';
		}
		cout << '\n';
	}
}
//OUTPUT EXAMPLE
/*
....
3 4 5 6 7 8 9 10 11 12
4 5 6 7 8 9 10 11 12 13
5 6 7 8 9 10 11 12 13 14
6 7 8 9 10 11 12 13 14 15
7 8 9 10 11 12 13 14 15 16
8 9 10 11 12 13 14 15 16 17
9 10 11 12 13 14 15 16 17 18
10 11 12 13 14 15 16 17 18 19
11 12 13 14 15 16 17 18 19 20
12 13 14 15 16 17 18 19 20 21

4 5 6 7 8 9 10 11 12 13
5 6 7 8 9 10 11 12 13 14
6 7 8 9 10 11 12 13 14 15
7 8 9 10 11 12 13 14 15 16
8 9 10 11 12 13 14 15 16 17
9 10 11 12 13 14 15 16 17 18
10 11 12 13 14 15 16 17 18 19
11 12 13 14 15 16 17 18 19 20
12 13 14 15 16 17 18 19 20 21
13 14 15 16 17 18 19 20 21 22

5 6 7 8 9 10 11 12 13 14
6 7 8 9 10 11 12 13 14 15
7 8 9 10 11 12 13 14 15 16
8 9 10 11 12 13 14 15 16 17
9 10 11 12 13 14 15 16 17 18
10 11 12 13 14 15 16 17 18 19
11 12 13 14 15 16 17 18 19 20
12 13 14 15 16 17 18 19 20 21
13 14 15 16 17 18 19 20 21 22
14 15 16 17 18 19 20 21 22 23
...
*/
