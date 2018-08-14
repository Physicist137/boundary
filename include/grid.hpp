#pragma once
#include <array>

template <typename Value, int rows, int cols>
class Grid {
	std::array<Value, rows*cols> _grid;

public:
	Grid() : _grid() {}

	const Value& operator()(int i, int j) const;
	Value& operator()(int i, int j);

	const Value& cartesian(int i, int j) const;
	Value& cartesian(int i, int j);

	const Value& center(int i, int j) const;
	Value& center(int i, int j);
};


template <typename Value, int rows, int cols>
const Value& Grid<Value, rows, cols>::operator()(int i, int j) const {
	return _grid[i * cols + j];
}

template <typename Value, int rows, int cols>
Value& Grid<Value, rows, cols>::operator()(int i, int j) {
	return _grid[i * cols + j];
}

template <typename Value, int rows, int cols>
const Value& Grid<Value, rows, cols>::cartesian(int i, int j) const {
	return this->operator()(rows-(i+1), j);
}

template <typename Value, int rows, int cols>
Value& Grid<Value, rows, cols>::cartesian(int i, int j) {
	return this->operator()(rows-(i+1), j);
}

template <typename Value, int rows, int cols>
const Value& Grid<Value, rows, cols>::center(int i, int j) const {
	return this->cartesian(i - rows/2, j - cols/2);
}

template <typename Value, int rows, int cols>
Value& Grid<Value, rows, cols>::center(int i, int j) {
	return this->cartesian(i - rows/2, j - cols/2);
}


