from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "my_vector_module",         # Название готового Python-модуля
        ["vector_module.cpp"],     # Исходный код на C++
        cxx_std=11,                # Стандарт C++
    ),
]

setup(
    name="my_vector_module",
    version="1.0",
    description="Vector algebra module using Pybind11",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)
