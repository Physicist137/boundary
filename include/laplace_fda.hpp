#pragma once
#include <grid.hpp>
#include <vector>

template <typename Value>
class PointFDA {
	int _i;
	int _j;
	Value _value;

public:
	PointFDA(int i, int j, const Value& value) : _i(i), _j(j), _value(value) {}
	inline int row() const {return _i;}
	inline int col() const {return _j;}
	inline const Value& value() const {return _value;}
};

template <typename Value, int rows, int cols>
class LaplaceFDA {
	Grid<Value, rows, cols> _grid;
	Grid<Value, rows, cols> _old;
	std::vector<PointFDA<Value> > _boundary;

public:
	LaplaceFDA() : _grid(), _old(), _boundary() {}
	explicit LaplaceFDA(const std::vector<PointFDA<Value> >& boundary) : _grid(), _old(), _boundary(boundary) {}

	inline const Grid<Value, rows, cols>& grid() const {return _grid;}
	inline const Value& grid(int i, int j) const {return _grid(i, j);}

	void emplace_boundary(int i, int j, const Value& value);
	void push_back_boundary(const PointFDA<Value>& point);
	
	// FDA Iteration.
	void iterate();
};


template <typename Value, int rows, int cols>
void LaplaceFDA<Value, rows, cols>::emplace_boundary(int i, int j, const Value& value) {
	_boundary.emplace_back(i, j, value);
}

template <typename Value, int rows, int cols>
void LaplaceFDA<Value, rows, cols>::push_back_boundary(const PointFDA<Value>& point) {
	_boundary.push_back(point);
}


template <typename Value, int rows, int cols>
void LaplaceFDA<Value, rows, cols>::iterate() {
	// Iteration withuot the contour.
	for (int i = 1; i < rows-1; ++i)
		for (int j = 1; j < cols-1; ++j) 
			_grid(i, j) = 0.25 * (_old(i+1, j) + _old(i-1, j) + _old(i, j+1) + _old(i, j-1));
	
	// Iterate the upper portion contour.
	for (int j = 1; j < cols-1; ++j)
		_grid(0, j) = 0.25 * (_old(1, j) + _old(0, j+1)	+ _old(0, j-1));

	// Iterate the lower portion contour.
	for (int j = 1; j < cols-1; ++j)
		_grid(rows-1, j) = 0.25 * (_old(rows-2, j) + _old(rows-1, j+1) + _old(rows-1, j-1));

	// Iterate the left portion contour.
	for (int i = 1; i < rows-1; ++i)
		_grid(i, 0) = 0.25 * (_old(i, 1) + _old(i+1, 0) + _old(i-1, 0));

	// Iterate the right portion contour.
	for (int i = 1; i < rows-1; ++i)
		_grid(i, cols-1) = 0.25 * (_old(i, cols-2) + _old(i+1, cols-1) + _old(i-1, cols-1));

	// Iterate corners.
	_grid(0, 0)				= 0.25 * (_old(1, 0) + _old(0, 1));
	_grid(0, cols-1)		= 0.25 * (_old(0, cols-2) + _old(1, cols-1));
	_grid(rows-1, 0)		= 0.25 * (_old(rows-2, 0) + _old(rows-1, 1));
	_grid(rows-1, cols-1)	= 0.25 * (_old(rows-2, cols-1) + _old(rows-1, cols-2));

	// Iterate boundary points.
	for (const PointFDA<Value>& point : _boundary) 
		_grid(point.row(), point.col()) = point.value();

	// Update the old grid.
	_old = _grid;
}
