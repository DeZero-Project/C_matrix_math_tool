import ctypes
from ctypes import POINTER, c_double, c_size_t, Structure
import sys, os
# 構造体の定義
class Matrix(Structure):
    _fields_ = [
        ("rows", c_size_t),
        ("cols", c_size_t),
        ("data", POINTER(c_double))
    ]
_lib_path = os.path.join(os.path.dirname(__file__), "libmtools.so")
lib = ctypes.CDLL(_lib_path)

create_matrix = lib.create_matrix
lib.create_matrix.argtypes = [c_size_t, c_size_t]
lib.create_matrix.restype = POINTER(Matrix)

print_matrix = lib.print_matrix
lib.print_matrix.argtypes = [POINTER(Matrix)]
lib.print_matrix.restype = ctypes.c_int

add_matrix = lib.add_matrix
lib.add_matrix.argtypes = [POINTER(Matrix), POINTER(Matrix)]
lib.add_matrix.restype = POINTER(Matrix)

sub_matrix = lib.sub_matrix
lib.sub_matrix.argtypes = [POINTER(Matrix), POINTER(Matrix)]
lib.sub_matrix.restype = POINTER(Matrix)

hadamard_product = lib.hadamard_product
lib.hadamard_product.argtypes = [POINTER(Matrix), POINTER(Matrix)]
lib.hadamard_product.restype = POINTER(Matrix)

dot_product = lib.dot_product
lib.dot_product.argtypes = [POINTER(Matrix), POINTER(Matrix)]
lib.dot_product.restype = POINTER(Matrix)

div_matrix = lib.div_matrix
lib.div_matrix.argtypes = [POINTER(Matrix), POINTER(Matrix)]
lib.div_matrix.restype = POINTER(Matrix)

free_matrix = lib.free_matrix
lib.free_matrix.argtypes = [POINTER(Matrix)]
lib.free_matrix.restype = None

