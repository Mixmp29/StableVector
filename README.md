<h2>Проект шаблонного типа данных StableVector</h2>

---
__Требования:__
- CMake v. 3.13+
- C++ 17
- GNU Make 4.1
- Clang 6.0.0

__Сборка:__
- ./build.sh

__Как запустить:__
- ./build/debug/bin/Test

---

__StableVector - это гибрид std::vector и std::list.__

В std::vector есть минус - легко инвалидирующиеся ссылки и итераторы. Они инвалидируются, когда вектор перераспределяют память, или когда удаляется/вставляется объект ближе к началу. 

Можно поделить контейнеры на "стабильные" и "нестабильные". В "стабильных" контейнерах ссылки и итераторы остаются действительными до тех пор, пока элемент не стерт, а итератор, которому было присвоено возвращаемое значение end(), всегда остается действительным до тех пор, пока не будет уничтожен связанный с ним StableVector.

Поскольку StableVector не копирует элементы внутри, некоторые операции обеспечивают более сильные гарантии безопасности исключений, чем в std::vector. 


<h2>Интерфейс</h2>

__Следующие операции доступны через публичный интерфейс:__
- Конструктор по умолчанию. Инициализирует контейнер по умолчанию. В данном случае указателям elements, first_free, cap приравнивается nullptr. Сложность: O(1).
- Конструктор копирования. Присваивает полям контейнера значения контейнера того же типа. Сложность: O(1).
- Конструктор перемещения. Присваивает полям контейнера значения временного объекта и присваивает им nullptr. Сложность: O(1).
- Конструктор инициализации листом. Присваивает полям контейнера nullptr, затем поочередно добавляет каждый элемент листа в контейнер с помощью функции push_back().  Сложность: (n · log(n)) из-за возможности перераспределения памяти.
- Деструктор. Освобождает память контейнера. Сложность: O(1).
- Оператор присваивания копированием. Присваивает полям контейнера значения присваиваемого контейнера того же типа. Сложность: O(1).
- Оператор присваивания перемещением. Присваивает полям контейнера значения присваиваемого временного объекта и присваивает им nullptr. Сложность: O(1).
- Оператор присваивания инициализацией листа. Присваивает полям контейнера nullptr, затем поочередно добавляет каждый элемент листа в контейнер с помощью функции push_back().  Сложность: O(n · log(n)) из-за возможности перераспределения памяти.
- Операторы сравнивания ==, !=, <, >.  Сравнивают размеры контейнеров. Елси размеры равны, то поочередно сравниваются объекты контейнеров. Если они проходят проверку соответствующего оператора, то возвращается значение true. Если хотя бы одно из условий не прошло проверку, то возвращается false. Сложность: O(n).
- Оператор индексации. Возвращает значение значение объекта по индексу. Если происходит выход за границы, то возвращает исключение. Сложность: O(1).
- Функция push_back() копированием и перемещением. Если не хватает памяти контейнера, то происходит перераспределение. Далее выделяет память для обычного или временного объекта и добавляет его в контейнер. Сложность: O(n).
- Функция reserve(). Выделяет память до указанного значения. Если значение меньше текущего, то ничего не происходит. Сложность: O(n).
- Функция resize(). Изменяет размер контейнера до указанного значения. Если значение меньше текущего размера, то указатель сдвигается влево пока размер больше значения. Если значение больше добавляется элемент по умолчанию с помощью функции push_back(). Сложность: O(n · log(n)).
- Функция size(). Возвращает размер контейнера путем вычитания указателя first_free и elements. Сложность: O(1).
- Функция capacity(). Возвращает размер выделенной памяти контейнера путем вычитания указателя cap и elements. Сложность: O(1).
- Функция empty(). Проверка на пустоту контейнера. Возвращает true, если elements равно 0. Сложность: O(1).
- Функция begin() константной и неконстантной версии. Возвращает итератор на начало контайнера. Сложность: O(1).
- Функция end() константной и неконстантной версии. Возвращает итератор на следующий за последним объектом. Сложность: O(1).

<h2>Итераторы</h2>

Структура данных представляет два вида итераторов: константный и неконстантный. Категория похожа на  RandomAccessIterator.

__Итераторы поддерживают следующие действия:__
- Разыменование для записи: *iter и iter→item.
- Инкремент: ++iter и iter++;
- Декремент: --iter и iter--;
- Операции сравнения: iter1 ==  iter2,  iter1 !=  iter2,  iter1 <  iter2,  iter1 >  iter2.
- Сложение/вычитание с числом: iter + n, iter += n, iter - n, iter -= n.
- Разность итераторов: iter2 — iter1.
