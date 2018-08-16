#pragma once
#include <Eigen/Dense>
#include <vector>
#include <array>


template <typename FloatingPoint, typename Value>
class Vertex {
	Eigen::Matrix<FloatingPoint, 2, 1> _position;
	Value _value;

public:
	inline const Eigen::Matrix<FloatingPoint, 2, 1>& position() const {return _position;}
	inline const Value& value() const {return _value;}
};

template <typename FloatingPoint, typename Value>
class Mesh {
	// The vertices, edges and triangles.
	std::vector<Vertex<FloatingPoint, Value>> _vertices;
	std::vector<std::array<int, 2>> _edges;
	std::vector<std::array<int, 3>> _triangles;

public
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
	};

public:
	Triangle triangle(int id);

	// Functions for constructing vertices.
	int addVertex(const Vertex<FloatingPoint, Value>& vertex);

	// Functions for constructing edges from two known vertices.
	int addEdgeBlindly(int v1, int v2);

	// Functions for constructing triangles.
	int addTriangleBlindlyFromVertices(int v1, int v2, int v3);

	// Add a vertex, near a triangle, creating another triangle.
	int integrateVertex(int triangle, const Vertex<FloatingPoint, Value>& vertex);
};


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
	_edge.push_back({v1, v2});
	return _edges.size() - 1;
}

template <typename FloatingPoint, typename Value>
int Mesh<FloatingPoint, Value>::addTriangleBlindlyFromVertices(int v1, int v2, int v3) {
	_triangles.push_back({v1, v2, v3});
	return _triangles.size() - 1;
}

template <typename FloatingPoint, typename Value>
int integrateVertex(int triangle, const Vertex<FloatingPoint, Value>::triangle(int id) {
	// TODO.
}
