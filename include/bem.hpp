#pragma once
#include <Eigen/Dense>
#include <vector>
#include <surface_mesh.hpp>
#include <utility>

template <typename FloatingPoint, typename Value>
class DoubleLayerBEM {
	std::vector<SurfaceMesh<FloatingPoint, Value>> _boundaries;

protected:
	std::pair<unsigned, unsigned> identify_boundary(unsigned value) const;

public:
	using Vector = Eigen::Matrix<FloatingPoint, 2, 1>;

	// Add boundaries
	inline void addBoundary(const SurfaceMesh<FloatingPoint, Value>& mesh) {_boundaries.push_back(mesh);}

	// The Exact Integral Operator Matrix components for a double layer potential under linear mesh apprx.
	FloatingPoint matrixForLinearMesh(int i, int j);
};

template <typename FloatingPoint, typename Value>
std::pair<unsigned, unsigned> DoubleLayerBEM<FloatingPoint, Value>::identify_boundary(unsigned value) const {
	unsigned size = _boundaries.size();
	unsigned accumulator_size = 0;
	unsigned deccumulator_id = value;
	for (unsigned k = 0; k < size; ++k) {
		accumulator_size += _boundaries[k].size();
		if (accumulator_size > value) return std::make_pair(k, deccumulator_id);
		deccumulator_id -= _boundaries[k].size();
	}

	throw "Given value is too high. No boundary point was found.";
}

#include <iostream>
template <typename FloatingPoint, typename Value>
FloatingPoint DoubleLayerBEM<FloatingPoint, Value>::matrixForLinearMesh(int i, int j) {
	// Identify the boundaries.
	std::pair<unsigned, unsigned> pair_i = identify_boundary(i);
	std::pair<unsigned, unsigned> pair_j = identify_boundary(j);
	std::pair<unsigned, unsigned> aux = identify_boundary(i+1);

	// Transcribe the boundaries.
	unsigned bi = pair_i.first;
	unsigned bj = pair_j.first;

	// Transcribe the elements.
	unsigned ei = pair_i.second;
	unsigned ej = pair_j.second;

	// Transcribe auxiliary element.
	unsigned ni;

	if (pair_i.first != aux.first) {
		// This means the ith point is in the very end.
		// Hereby we should close it. Pair: (bi, 0).
		ni = 0;	
	}

	else {
		// This means the ith point is not in the very end.
		// Hereby no closure is needed. Pick next.
		ni = aux.second;
	}


	// Pick up the vectors.
	Eigen::Matrix<FloatingPoint, 2, 1> xi = _boundaries[bi].point(ei).vector();
	Eigen::Matrix<FloatingPoint, 2, 1> xj = _boundaries[bj].point(ej).vector();
	Eigen::Matrix<FloatingPoint, 2, 1> xn = _boundaries[bi].point(ni).vector();

	// Calculate the integral coeficients.
	FloatingPoint a = (xn-xi).dot(xn-xi);
	FloatingPoint b = 2*(xj-xi).dot(xn-xi);
	FloatingPoint c = (xj-xi).dot(xj-xi);

	// Calculate the integral matrix elements.
	FloatingPoint delta = std::sqrt(4*a*c - b*b);
	FloatingPoint first = std::atan2(2*a-b, delta);
	FloatingPoint second = std::atan2(b,  delta);
	FloatingPoint integral = 2 / delta * (first + second);

	// Calculate the operator matrix elements.
	Eigen::Matrix<FloatingPoint, 2, 1> tangent = _boundaries[bi].forwardTangent(ei).vector();
	Eigen::Matrix<FloatingPoint, 2, 1> normal = _boundaries[bi].normalVector(tangent).normalized();
	FloatingPoint dotnormal = normal.dot(xj-xi);
	FloatingPoint kernel_operator = 1 / (2 * 3.1415926535) * dotnormal * integral * tangent.norm();

	// Debbuger.
	std::cout << "i=" << i;
	std::cout << ", j=" << j;	
	std::cout << ", bi=" << bi;
	std::cout << ", bj=" << bj;	
	std::cout << ", ei=" << ei;
	std::cout << ", ej=" << ej;	
	std::cout << ", ni=" << ni;
	std::cout << ", a=" << a;
	std::cout << ", b=" << b;	
	std::cout << ", c=" << c;
	std::cout << ", d=" << delta;
	std::cout << ", in=" << integral;
	std::cout << ", dn=" << dotnormal;
	std::cout << ", xi=(" << xi(0,0) << "," << xi(1,0) << ")";
	std::cout << ", xj=(" << xj(0,0) << "," << xj(1,0) << ")";
	std::cout << ", xn=(" << xn(0,0) << "," << xn(1,0) << ")";
	std::cout << ", ta=(" << tangent(0,0) << "," << tangent(1,0) << ")";
	std::cout << ", no=(" << normal(0,0) << "," << normal(1,0) << ")";
	std::cout << std::endl;	

	// Return the value.	
	return kernel_operator;
}
