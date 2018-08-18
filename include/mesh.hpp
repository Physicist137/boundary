#pragma once
#include <Eigen/Dense>
#include <vector>
#include <array>


template <typename FloatingPoint, typename Value>
class Vertex {
	Eigen::Matrix<FloatingPoint, 2, 1> _pos;
	Value _value;

public:
	explicit Vertex(const Eigen::Matrix<FloatingPoint, 2, 1>& pos) : _pos(pos), _value() {}
	Vertex(const Eigen::Matrix<FloatingPoint, 2, 1>& pos, const Value& value) : _pos(pos), _value(value) {}	
	
	inline const Eigen::Matrix<FloatingPoint, 2, 1>& position() const {return _pos;}
	inline const Eigen::Matrix<FloatingPoint, 2, 1>& vector() const {return _pos;}
	inline const Value& value() const {return _value;}
};

template <typename FloatingPoint, typename Value>
class Mesh {
	// The vertices, edges and triangles.
	std::vector<Vertex<FloatingPoint, Value>> _vertices;
	std::vector<std::array<int, 2>> _edges;
	std::vector<std::array<int, 3>> _triangles;

public:
	// The Mesh::Edge class.
	class Edge{
		std::array<int, 2> _ids;
	
		Vertex<FloatingPoint, Value>& _vertex1;
		Vertex<FloatingPoint, Value>& _vertex2;

	public:
		Edge(
			Vertex<FloatingPoint, Value>& v1,
			Vertex<FloatingPoint, Value>& v2
		) 	: _vertex1(v1), _vertex2(v2) {}
	};

	// The Mesh::Triangle class.
	class Triangle{
		std::array<int, 3> _ids;

		Vertex<FloatingPoint, Value>& _vertex1;
		Vertex<FloatingPoint, Value>& _vertex2;
		Vertex<FloatingPoint, Value>& _vertex3;

	public:
		Triangle(
			Vertex<FloatingPoint, Value>& v1,
			Vertex<FloatingPoint, Value>& v2,
			Vertex<FloatingPoint, Value>& v3
		) 	: _vertex1(v1), _vertex2(v2), _vertex3(v3) {}

		// Verifies if a point is inside a triangle.
		bool isInside(const Eigen::Matrix<FloatingPoint, 2, 1>& vector) const;
	};

public:
	Triangle triangle(int id);

	// Functions for constructing vertices.
	int addVertex(const Vertex<FloatingPoint, Value>& vertex);

	// Functions for constructing edges from two known vertices.
	int addEdgeBlindly(int v1, int v2);

	// Functions for constructing triangles.
	int addTriangleBlindlyFromVertices(int v1, int v2, int v3);

	// Add a vertex, inside a triangle, creating four triangles.
	int addVertexInsideTriangle(int triangle, const Vertex<FloatingPoint, Value>& vertex);
};

template <typename FloatingPoint, typename Value>
bool Mesh<FloatingPoint, Value>::Triangle::isInside(const Eigen::Matrix<FloatingPoint, 2, 1>& vector) const {
	Eigen::Matrix<FloatingPoint, 2, 1> edge12 = _vertex2.vector() - _vertex1.vector();
	Eigen::Matrix<FloatingPoint, 2, 1> edge13 = _vertex3.vector() - _vertex1.vector();
	Eigen::Matrix<FloatingPoint, 2, 1> edge23 = _vertex3.vector() - _vertex2.vector();

	Eigen::Matrix<FloatingPoint, 2, 2> matrix1;
	matrix1(0,0) = edge12(0,0);
	matrix1(0,1) = edge13(0,0);
	matrix1(1,0) = edge12(1,0);
	matrix1(1,1) = edge13(1,0);

	Eigen::Matrix<FloatingPoint, 2, 2> matrix2;
	matrix2(0,0) = -edge12(0,0);
	matrix2(0,1) = edge23(0,0);
	matrix2(1,0) = -edge12(1,0);
	matrix2(1,1) = edge23(1,0);

	Eigen::Matrix<FloatingPoint, 2, 2> matrix3;
	matrix3(0,0) = -edge13(0,0);
	matrix3(0,1) = -edge23(0,0);
	matrix3(1,0) = -edge13(1,0);
	matrix3(1,1) = -edge23(1,0);

	Eigen::Matrix<FloatingPoint, 2, 1> bvec1 = matrix1.inverse() * (vector - _vertex1.vector());
	Eigen::Matrix<FloatingPoint, 2, 1> bvec2 = matrix2.inverse() * (vector - _vertex2.vector());
	Eigen::Matrix<FloatingPoint, 2, 1> bvec3 = matrix3.inverse() * (vector - _vertex3.vector());
	
	if (bvec1(0,0) >= 1 or bvec1(0,0) <= 0) return false;
	if (bvec1(1,0) >= 1 or bvec1(1,0) <= 0) return false;
	if (bvec2(0,0) >= 1 or bvec2(0,0) <= 0) return false;
	if (bvec2(1,0) >= 1 or bvec2(1,0) <= 0) return false;
	if (bvec3(0,0) >= 1 or bvec3(0,0) <= 0) return false;
	if (bvec3(1,0) >= 1 or bvec3(1,0) <= 0) return false;
	return true;
}

template <typename FloatingPoint, typename Value>
typename Mesh<FloatingPoint, Value>::Triangle Mesh<FloatingPoint, Value>::triangle(int id) {
	return Mesh<FloatingPoint, Value>::Triangle(
		_vertices[_triangles[id][0]],
		_vertices[_triangles[id][1]],
		_vertices[_triangles[id][2]]
	);
}

template <typename FloatingPoint, typename Value>
int Mesh<FloatingPoint, Value>::addVertex(const Vertex<FloatingPoint, Value>& vertex) {
	_vertices.push_back(vertex);
	return _vertices.size() - 1;
}

template <typename FloatingPoint, typename Value>
int Mesh<FloatingPoint, Value>::addEdgeBlindly(int v1, int v2) {
	_edges.push_back({v1, v2});
	return _edges.size() - 1;
}

template <typename FloatingPoint, typename Value>
int Mesh<FloatingPoint, Value>::addTriangleBlindlyFromVertices(int v1, int v2, int v3) {
	_triangles.push_back({v1, v2, v3});
	return _triangles.size() - 1;
}

template <typename FloatingPoint, typename Value>
int Mesh<FloatingPoint, Value>::addVertexInsideTriangle(int triangle, const Vertex<FloatingPoint, Value>& vertex) {
	// TODO.
}
