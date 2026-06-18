#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // Для автоматической конвертации std::vector
#include <vector>
#include <cmath>
#include <stdexcept>

namespace py = pybind11;

// --- 1. Функции для работы с векторами (std::vector<double>) ---

std::vector<double> vector_add(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) throw std::invalid_argument("Vectors must have the same size");
    std::vector<double> result(a.size());
    for (size_t i = 0; i < a.size(); ++i) result[i] = a[i] + b[i];
    return result;
}

std::vector<double> vector_sub(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) throw std::invalid_argument("Vectors must have the same size");
    std::vector<double> result(a.size());
    for (size_t i = 0; i < a.size(); ++i) result[i] = a[i] - b[i];
    return result;
}

double vector_dot(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) throw std::invalid_argument("Vectors must have the same size");
    double dot_product = 0.0;
    for (size_t i = 0; i < a.size(); ++i) dot_product += a[i] * b[i];
    return dot_product;
}

// --- 2. Класс Vector3D ---

class Vector3D {
public:
    double x, y, z;

    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

    double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3D normalize() const {
        double len = length();
        if (len == 0.0) throw std::runtime_error("Cannot normalize a zero vector");
        return Vector3D(x / len, y / len, z / len);
    }
};

// --- 3. Интеграция с Pybind11 ---

PYBIND11_MODULE(my_vector_module, m) {
    m.doc() = "C++ Vector Algebra module powered by Pybind11";

    // Экспорт свободных функций
    m.def("add", &vector_add, "Add two vectors");
    m.def("sub", &vector_sub, "Subtract two vectors");
    m.def("dot", &vector_dot, "Calculate dot product of two vectors");

    // Экспорт класса Vector3D
    py::class_<Vector3D>(m, "Vector3D")
        .def(py::init<double, double, double>(), py::arg("x") = 0.0, py::arg("y") = 0.0, py::arg("z") = 0.0)
        .def_readwrite("x", &Vector3D::x)
        .def_readwrite("y", &Vector3D::y)
        .def_readwrite("z", &Vector3D::z)
        .def("length", &Vector3D::length, "Get the length of the 3D vector")
        .def("normalize", &Vector3D::normalize, "Get the normalized 3D vector");
}
