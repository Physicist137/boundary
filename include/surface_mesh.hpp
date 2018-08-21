#pragma once
#include<vector>
#include<Eigen/Dense>

template <typename FloatingPoint, typename Value>
class Point {
	Matrix<FloatingPoint, 2, 1> _point;
	Value _value;

public:
	Point(const Matrix<FloatingPoint, 2, 1> point, const Value& value)
	: _point(point), _value(value) {}

	inline const Matrix<FloatingPoint, 2, 1>& point() const {return _point;}
	inline const Value& value() const {return _value;}
};

template <typename FloatingPoint, typename Value>
Point<FloatingPoint, Value> operator+(const Point<FloatingPoint, Value>& a, const Point<FloatingPoint, Value>& b) {
	return Point(a.point() + b.point(), a.value() + b.value());
}

template <typename FloatingPoint, typename Value>
Point<FloatingPoint, Value> operator-(const Point<FloatingPoint, Value>& a, const Point<FloatingPoint, Value>& b) {
	return Point(a.point() - b.point(), a.value() - b.value());
}

template <typename FloatingPoint, typename Value>
Point<FloatingPoint, Value> operator*(const Point<FloatingPoint, Value>& a, const FloatingPoint& num) {
	return Point(a.point() * num, a.value() * num);
}

template <typename FloatingPoint, typename Value>
Point<FloatingPoint, Value> operator* (const FloatingPoint& num, const Point<FloatingPoint, Value>& a) {
	return Point(a.point() * num, a.value() * num);
}

template <typename FloatingPoint, typename Value>
Point<FloatingPoint, Value> operator/(const Point<FloatingPoint, Value>& a, const FloatingPoint& num) {
	return Point(a.point() / num, a.value() / num);
}

// ----------------------------------------------------------
template <typename FloatingPoint, typename Value>
class SurfaceMesh {
	std::vector< Matrix<FloatingPoint, 2, 1> > _points;
	std::vector<Value> _value;

public:
	// Accessor functions.
	inline const Matrix<FloatingPoint, 2, 1>& point(int id) const {return _points[id];}
	inline const Value& value(int id) const {return _value[id];}
	inline const std::vector<Value>::size_type size() const {return _value.size();}

	// Tangent values.
	Matrix<FloatingPoint, 2, 1> forwardTangent(int id) const;
	Matrix<FloatingPoint, 2, 1> backwardTangent(int id) const;
	Matrix<FloatingPoint, 2, 1> middleTangent(int id) const;

	// Normal Values.
	Matrix<FloatingPoint, 2, 1> forwardNormal(int id) const;
	Matrix<FloatingPoint, 2, 1> backwardNormal(int id) const;
	Matrix<FloatingPoint, 2, 1> middleNormal(int id) const;	
};


