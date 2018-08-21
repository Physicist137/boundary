#pragma once
#include<vector>
#include<Eigen/Dense>

template <typename FloatingPoint, typename Value>
class Point {
	Eigen::Matrix<FloatingPoint, 2, 1> _point;
	Value _value;

public:
	Point(const Eigen::Matrix<FloatingPoint, 2, 1>& point, const Value& value)
	: _point(point), _value(value) {}

	inline const Eigen::Matrix<FloatingPoint, 2, 1>& point() const {return _point;}
	inline const Value& value() const {return _value;}
};

template <typename FloatingPoint, typename Value>
Point<FloatingPoint, Value> operator+(const Point<FloatingPoint, Value>& a, const Point<FloatingPoint, Value>& b) {
	return Point<FloatingPoint, Value>(a.point() + b.point(), a.value() + b.value());
}

template <typename FloatingPoint, typename Value>
Point<FloatingPoint, Value> operator-(const Point<FloatingPoint, Value>& a, const Point<FloatingPoint, Value>& b) {
	return Point<FloatingPoint, Value>(a.point() - b.point(), a.value() - b.value());
}

template <typename FloatingPoint, typename Value>
Point<FloatingPoint, Value> operator*(const Point<FloatingPoint, Value>& a, const FloatingPoint& num) {
	return Point<FloatingPoint, Value>(a.point() * num, a.value() * num);
}

template <typename FloatingPoint, typename Value>
Point<FloatingPoint, Value> operator* (const FloatingPoint& num, const Point<FloatingPoint, Value>& a) {
	return Point<FloatingPoint, Value>(a.point() * num, a.value() * num);
}

template <typename FloatingPoint, typename Value>
Point<FloatingPoint, Value> operator/(const Point<FloatingPoint, Value>& a, const FloatingPoint& num) {
	return Point<FloatingPoint, Value>(a.point() / num, a.value() / num);
}

// ----------------------------------------------------------
template <typename FloatingPoint, typename Value>
class SurfaceMesh {
	std::vector<Point<FloatingPoint, Value>> _points;

public:
	// Accessor functions.
	inline const Point<FloatingPoint, Value>& point(int id) const {return _points[id];}
	inline const typename std::vector<Point<FloatingPoint, Value>>::size_type size() const {return _points.size();}

	// Tangent values.
	Point<FloatingPoint, Value> forwardTangent(int id) const;
	Point<FloatingPoint, Value> backwardTangent(int id) const;
	Point<FloatingPoint, Value> centralTangent(int id) const;

	// Normal Values.
	Eigen::Matrix<FloatingPoint, 2, 1>& normalVector(const Eigen::Matrix<FloatingPoint, 2, 1>& tangent) const;
};

template <typename FloatingPoint, typename Value>
Point<FloatingPoint, Value> SurfaceMesh<FloatingPoint, Value>::forwardTangent(int id) const {
	return _points[id+1] - _points[id];
}

template <typename FloatingPoint, typename Value>
Point<FloatingPoint, Value> SurfaceMesh<FloatingPoint, Value>::backwardTangent(int id) const {
	return _points[id] - _points[id-1];
}

template <typename FloatingPoint, typename Value>
Point<FloatingPoint, Value> SurfaceMesh<FloatingPoint, Value>::centralTangent(int id) const {
	return (_points[id+1] - _points[id-1]) / 2.0;
}

template <typename FloatingPoint, typename Value>
Eigen::Matrix<FloatingPoint, 2, 1>& SurfaceMesh<FloatingPoint, Value>::normalVector
(const Eigen::Matrix<FloatingPoint, 2, 1>& tangent) const {
	return Eigen::Matrix<FloatingPoint, 2, 1>{-tangent(1,0), -tangent(0,0)};
}
