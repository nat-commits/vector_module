import unittest
import my_vector_module as vm

class TestVectorModule(unittest.TestCase):

    def test_functions(self):
        # Сложение
        self.assertEqual(vm.add([1.0, 2.0], [3.0, 4.0]), [4.0, 6.0])
        # Вычитание
        self.assertEqual(vm.sub([5.0, 5.0], [2.0, 1.0]), [3.0, 4.0])
        # Скалярное произведение
        self.assertEqual(vm.dot([1.0, 2.0, 3.0], [4.0, 5.0, 6.0]), 32.0)
        
        # Проверка исключения при разной длине векторов
        with self.assertRaises(ValueError):
            vm.add([1.0], [1.0, 2.0])

    def test_vector3d_class(self):
        # Создание объекта класса Vector3D из C++
        v = vm.Vector3D(3.0, 4.0, 0.0)
        
        # Проверка чтения атрибутов
        self.assertEqual(v.x, 3.0)
        self.assertEqual(v.y, 4.0)
        self.assertEqual(v.z, 0.0)
        
        # Длина вектора (sqrt(3^2 + 4^2) = 5)
        self.assertEqual(v.length(), 5.0)
        
        # Нормализация
        v_norm = v.normalize()
        self.assertAlmostEqual(v_norm.x, 0.6)
        self.assertAlmostEqual(v_norm.y, 0.8)
        self.assertAlmostEqual(v_norm.z, 0.0)
        self.assertAlmostEqual(v_norm.length(), 1.0)

        # Исключение при нормализации нулевого вектора
        v_zero = vm.Vector3D(0, 0, 0)
        with self.assertRaises(RuntimeError):
            v_zero.normalize()

if __name__ == "__main__":
    unittest.main()
