#pragma once
#include<vector>
#include<Eigen/Dense>

// The boundary.
template <typename FloatingPoint, typename Value>
class SurfaceMesh {
	std::vector< Matrix<FloatingPoint, 2, 1> > _points;
	std::vector<Value> _value;

public:
	// Accessor functions.
	const Matrix<FloatingPoint, 2, 1>& point(int id) const;
	const Value& value(int id) const;

	// Tangent values.
	Matrix<FloatingPoint, 2, 1> forwardTangent(int id) const;
	Matrix<FloatingPoint, 2, 1> backwardTangent(int id) const;
	Matrix<FloatingPoint, 2, 1> middleTangent(int id) const;

	// Normal Values.
	Matrix<FloatingPoint, 2, 1> forwardNormal(int id) const;
	Matrix<FloatingPoint, 2, 1> backwardNormal(int id) const;
	Matrix<FloatingPoint, 2, 1> middleNormal(int id) const;
	
};
