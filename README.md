# ITMO-IS-Algorithms-and-Data-Structures-2nd-semester-summary
Graphs and strings, конспект на Русском, код нет.<br>
Конспект чисто для себя, поэтому некоторые простые объяснения
(DFS, BFS, TPS) опущены. Код почти не проверялся - он передает идею
алгоритма, но мог быть написан с ошибками. Как говорится, думайте
сами.

# Алгоритмы на графах
## DFS
### [Code](lib/dfs.cpp)
### Описание
Известен также, как обход в глубину. Используется в многих алгоритмах.
С помощью него можно, например, определить компоненты связности или
сделать топологическую сортировку.</br>
### Асимптотика
Выводится из двух вещей:
- Обход всех вершин - O(|V|)
```c++
while (!visited[id]) {
    DFS(...)
}
```
- Обход всех элементов, которые хранят эти вершины
```c++
for (auto& i : graph[id]) {
    ...
}
```
В зависимости от типа хранения меняется асимптотика второго обхода
- Для списка смежности (каждая вершина хранит только вершины, в которые она ведет)</br>
  O(|E|)
- Для матрицы смежности (булева таблица, каждая вершина хранит
  список всех вершин, если она ведет в V<sub>i</sub> - то элемент i = true, иначе false)</br>
  O(|V|<sup>2</sup>), тк для каждой V мы делаем V проходов
- Для матрицы инцидентности (булева таблица, каждая вершина хранит
  список всех ребер, если она вершина смежна с E<sub>i</sub> - то элемент i = true, иначе false)</br>
  O(|V| * |E|), тк для каждой V мы делаем E проходов

Итого асимптотика O(1п + 2п), т.е. для списка смежности:<br>
O(|V| + |E|),<br>
Для матрицы смежности:<br>
O(|V| + |V|<sup>2</sup>) = O(|V|<sup>2</sup>),<br>
Для матрицы инцидентности:<br>
O(|V| * |V| * |E|) = O(|V|^2 * |E|)
> [!NOTE]
> Если все вершины лежат в одной компоненте связности, то асимптотика для списка смежности: O(|E|)

## BFS
### [Code](lib/bfs.cpp)
### Описание
Известен также, как обход в ширину. Используется в многих алгоритмах.
С помощью него можно, например, определить компоненты связности.
Отличие от DFS - тип обхода. Часто они взаимозаменяемые,
но есть и исключения.
### Асимптотика
Аналогична DFS

## Проверка графа на наличие цикла и его восстановление
### [Code](lib/find_cycle.cpp)
### Описание
Используем рекурсивный DFS для обхода. Помечаем вершину одним из
трех цветов:
- 0, если вершина не была посещена (цвет по умолчанию)
- 1, если мы рекурсивно вошли в вершину
- 2, если рекурсивно вышли

Если в результате мы получим ситуацию, когда встретили вершину, из которой рекурсивно
не вернулись:
```c++
if (color[i] == 1) {
    ...
}
```
то добавим эти две вершины как начало и конец цикла, пройдемся
задом наперед по массиву родителей, пока не придем во вторую вершину, ответ
развернем (тк проходили в обратном порядке)
### Асимптотика
См. DFS

## Топологическая сортировка
### [Code](lib/tps.cpp)
### Описание
Сортировка вершин в топологическом порядке, т.е.
для любой пары вершин выполняется условие:<br>
Для любого ребра E(V<sub>i</sub> -> V<sub>j</sub>), i < j.<br>
Следуя из определения, граф должен быть ориентированным и ациклическим.
### Асимптотика
- Проверка на ацикличность займет O(DFS)
- Работа алгоритма займет O(DFS)
- Итого O(2DFS) = O(DFS)

Если опустить проверку на ацикличность, на асимптотику это не повлияет,
только на константу.

## Поиск компонент сильной связности (Алгоритм Косараю)
### [Code](lib/kosaraju.cpp)
### Описание
Компонента сильной связности - множество вершин, в котором любые две
вершины сильно связаны.<br>
Вершины V<sub>i</sub> и V<sub>j</sub> сильно связаны, если существует
путь V<sub>i</sub> -> V<sub>j</sub> и одновременно V<sub>j</sub> ->
V<sub>i</sub>.
Порядок работы:
1. Использует псевдо-TPS (т.к. граф, конечно, ориентированный, но,
   очевидно, не ациклический (просто запоминаем порядок выхода из DFS))
2. Инвертирует ребра (можно объединить с прошлым пунктом для улучшения константы)
3. Создает массив visited
4. Если вершина не посещена -
   - Добавляет новую компоненту сильной связности в выходной массив,
     запускает DFS, в процессе добавляя вершины в последний элемент
     выходного массива, удаляет вершину из стека
   
   Иначе -
   - Удаляет из стека

Выходной массив и является массивом всех компонент сильной связности.
### Асимптотика
- Псевдо-TPS займет O(DFS)
- Инвертирование ребер займет O(DFS)
- Добавление в выходной массив займет O(DFS)

Итого - O(DFS)

## Конденсация графа
### [Code](lib/condensation.cpp)
LATER

## Поиск Гамильтонова цикла при выполнении достаточных условий (теоремы Дирака или Оре)
При соблюдении теоремы Оре
$`deg(V{i}) ≥ \frac{n}{2}`$,
или Дирака
$`deg(V{i}) + deg(V{j}) ≥ n`$, 
где $V{i}$, $V{j}$ - любые две вершины, а $deg(V)$ - степень вершины.

### [Code](lib/find_hamiltonian_cycle.cpp)
### Описание
Гамильтонов цикл - замкнутый путь, который проходит по всем вершинам графа и только 
один раз<br>
Разберем алгоритм построчно:
```c++
std::vector<unsigned long> q(graph.size());
for (unsigned long i = 0; i < graph.size(); ++i) {
    q[i] = i;
}
```
Здесь создается так называемая "очередь" (хотя это и массив), которая содержит все
вершины графа (порядок произвольный).
```c++
for (unsigned long c = 0; c < graph.size() * (graph.size() - 1); ++c) {
    ...
}
```
Этот цикл |V| * (|V| - 1) раз (magic number, откуда берется не знаю), иногда он будет работать за единицу,
иногда за n. Оба случая рассмотрим.
```c++
if (!graph[q[0]][q[1]]) {
    unsigned long i = 2;
    while (i < q.size() - 1 && (!graph[q[0]][q[i]] || !graph[q[1]][i + 1])) {
        ++i;
    }
    std::reverse(q.begin() + 1, q.begin() + i + 1);
}
q.push_back(q[0]);
q.erase(q.begin());
```
Тут мы ищем две соседних вершины, у которых нет смежности. Если попались такие вершины,
то ищем, с какими есть смежность, затем разворачиваем подотрезок от 1 до i
(либо V<sub>0</sub> смежно с V<sub>i</sub>, либо V<sub>1</sub> смежно с V<sub>i+1</sub>).
Таким образом, каждый раз выполняя reverse, мы добавляем минимум 1 смежную вершину.
Следовательно, эта операция будет происходить не больше |V| раз, работает она за O(|V|).<br>
Операция добавления в конец работает за O(1).

### Асимптотика
- Асимптотика цикла - O(|V|<sup>2</sup>)
- Асимптотика reverse - O(|V|). Reverse выполняется |V| раз, значит общая асимптотика
  таких операций O(|V|<sup>2</sup>).
- Общая асимптотика O(|V|<sup>2</sup> - |V| + |V|<sup>2</sup>) = O(2 * |V|<sup>2</sup>) =<br>
  O(|V|<sup>2</sup>).

> [!WARNING]
> Реализовывать алгоритм лучше на <i>матрице</i> смежности, иначе проверка на наличие ребра
> между вершинами увеличит асимптотику еще в |E| раз. Т.е. асимптотика на списке смежности
> и матрице инцидентности:<br>
> O(|V|<sup>2</sup> * |E| - |V| * |E| + |V|<sup>2</sup> * |E|) = O(|V|<sup>2</sup> * |E|)

## Поиск Эйлерова цикла
### [Code](lib/find_euler_cycle.cpp)
### Описание
Эйлеров цикл - замкнутый путь, проходящий по всем ребрам графа и только один раз.<br>
Для начала нужно проверить критерий эйлеровости графа:
- Степень каждой вершины (сумма входящих и исходящих в граф ребер для ориентированного графа) - четная.
- Все компоненты связности, кроме, может быть, одной не имеют ребер.

После проверки необходимо построить Эйлеров цикл.
Идем по ребрам V<sub>i</sub> вершины. Если у этой вершины есть неиспользованные ребра,
то помечаем ребро пройденным, добавляем смежную вершину в стек. Если таковых нет, 
удаляем верхнюю вершину из стека и добавляем ее в ответ.
### Асимптотика
- Проверка на эйлеровость занимает:
  - O(|V|) на проверку степеней
  - O(DFS) на проверку наличия элементов в компонентах связности.
  
  Итого - O(|V| + DFS) = O(DFS)
- Алгоритм работает за O(mark_edge * find_adjacent_vertex * |E|), т.к. мы проходимся по всем ребрам,
  находим и помечаем ребро и добавляем смежную вершину в стек. При правильной реализации:<br>
  - O(mark_edge) = O(find_adjacent_vertex) = O(1), весь алгоритм - O(|E|),<br>
  
  однако это требует доп. памяти (см. рекурсивную реализацию алгоритма за O(|E|)).

## Нахождение компонент связности в неориентированном графе
См. DFS или BFS

## Алгоритм Краскала
### [Code](lib/kraskal.cpp)
### Описание
Построить МСТ графа. МСТ - минимальное остовное дерево = остовное дерево, имеющее
минимально возможный вес, где вес дерева = сумма весов входящих в него ребер.<br>
Сначала мы сортируем ребра в порядке возрастания их весов.<br>
Затем разбиваем вершины на множества. По умолчанию - |V| множеств, состоящих
из одной вершины.<br><br>
Затем проходимся по отсортированному списку рёбер.<br>Проверяем, если смежные этому ребру
вершины находятся в разных множествах: 
- Добавляем ребро в ответ, множества сливаем.

Иначе -
- Пропускаем ребро

После того как мы прошли по всем ребрам, возвращаем ответ.

### Асимптотика
Общий вид - O(sort + init_union + |E| * find_union_parent * merge_union).<br>
При стандартной реализации используется СНМ, т. е. асимптотика find_union_parent =
merge_union = O(α(m, n)), где α - функция, обратная к функции Аккермана, которую
можно принять за константу, тк она принимает значения ⩽ 4.<br>
Однако, init_union (создание СНМ) - O(|E|).<br>
Итоговая асимптотика - O(sort + |E| + |E|) = O(sort + |E|)
> [!WARNING]
> Говорят, существуют проверяющие, которые дают задание придумать Краскала за
> O(|E|). Не забывайте, что существует сортировка подсчётом, работающая за O(n),
> т.е. за O(|E|).<br>То есть итоговая асимптотика O(sort + |E|) = O(|E| + |E|) = O(|E|)

## СНМ
### Описание
> [!NOTE]
> Вообще, СНМ нет в чек-листе, но если доказывать Краскала (или др. алгоритмы) с ним,
> скорее всего попросят пояснить.

СНМ - система непересекающихся множеств. Это - иерархическая структура данных,
позволяющая эффективно работать с множествами.<br>
Есть всего две операции - find и union.
- Если find(x) == find(y), то элементы лежат в одном множестве.
- Union(x, y) - объединить множества, в которых лежат элементы x и y.
  При реализации без эвристик, асимптотика find = O(1), а асимптотика
  Union = O(n)
- init = O(n)

#### Эвристики
Представим наше множество в виде корневого дерева, тогда СНМ - лес корневых деревьев.
Тогда, каждый раз выполняя merge, мы можем просто "подвязывать" корень одного дерева.
В таком случае, асимптотика merge = O(find), а O(find) = O(h), где h - высота дерева.<br>

Есть 3 вида эвристик (упрощения, ускорения) - 
- Ранговая
- Сжатия путей
- Весовая
#### Ранговая эвристика
Подвешиваем дерево с меньшей глубиной к дереву с большей глубиной.
Доказывается, что максимальный ранг ⩽ log(n), т.е. если не использовать другие
эвристики, то<br>
find = O(log(n))
#### Сжатия путей
Когда мы ищем родителя элемента, мы можем переподвесить элементы напрямую к корню,
таким образом уменьшая средний случай поиска родителя и ускоряя find, притом чем чаще
мы вызываем find, тем быстрее работает наше дерево.
Доказывается, что не используя другие эвристики:<br>
$$O(find) = O(\frac{log(\frac{n^2}{m})}{log(\frac{m}{n})}) = O(log(n))$$
#### Разбор асимптотики сжатия путей
n - число элементов, m - число операций.<br>
$`f(n, m) = \frac{log(\frac{n^2}{m})}{log(\frac{m}{n})}`$ - эта функция показывает, что
чем больше наше m, тем меньше выйдет итоговая асимптотика. Например, при m ≈ n,
f(n, ~n) ≈ log(n).<br>А уже при m ≈ n$`\sqrt(n)`$, f ≈ 1.
#### Асимптотика, используя эти два случая одновременно
find = merge = O(α(m, n)), где α(m, n) - функция, обратная к функции Аккермана,
α(m, n) ⩽ 4, что можно принять за константу.
#### Весовая эвристика
Очень схожа с ранговой, однако вместо высоты поддерева храним "вес" дерева, те
количество вершин входящих в него. Асимптотика совпадает с асимптотикой ранговой
эвристики. Также можно использовать вместе со сжатием путей, получая ту же
выходную асимптотику.
## Алгоритм Прима
### [Code](lib/prima.cpp)
> [!IMPORTANT]
> Для алгоритма Дейкстры (очень схож с алгоритмом Прима) я написал код получше,
> рекомендую также ознакомиться с ним.
### Описание
Алгоритм поиска MST. Для каждой вершины храним массив "ключей" (key, вес минимального ребра,
смежного с этой вершиной) и "предыдущих вершин" (prev, вершин, из которых исходит ребро,
вес которого является "ключом" этой вершины).<br>
Начнем алгоритм со стартовой вершины: для нее определим ключ 0 и предыдущую вершину
за null. Пройдемся по всем ребрам, смежным с ней:<br>
Если вес(w) ребра (i -> j) < key[j], то key[j] = w, а prev[j] = i. Так мы выбрали это
ребро как минимальное для вершины j.<br>
Затем ищем вершину с минимальным ключом, удаляем ее из списка вершин, которые можно
использовать, и повторяем проход по ребрам еще |V| - 1 раз. На выходе
получаем массив prev, из которого можно получить MST.
### Асимптотика
- Этот алгоритм работает за O(|V| * extract_min + |E| * decrease_key), т.к. мы |V| раз
  ищем вершину с минимальным ключом и максимум |E| раз этот ключ меняем.
- Для плотных графов рекомендуется оставить линейный поиск минимального ключа (extract_min
  = O(|V|)), тогда decrease_key будет происходить за O(1).<br>
  В таком случае асимптотика будет O(|V| * |V| + |E| * 1) = O(|V|<sup>2</sup> + |E|)<br>
  Т. к. граф плотный, то O(|E|) = O(|V|<sup>2</sup>) => итоговая асимптотика = O(|V|<sup>2</sup>).
- Для разреженных графов рекомендуется использовать приоритетную очередь (в данном случае
  на двоичной куче), т. к. в таком случае extract_min = decrease_key = O(log(|V|))
  (log(|V|) т. к. мы храним именно вершины).<br>
  Тогда асимптотика O(|V| * log(|V|) + |E| * log(|V|)).<br>
  O(|E|) >= O(|V|) => O(|V| * log(|V|) + |E| * log(|V|)) = O(2 * |E| * log(|V|)) =
  O(|E| * log(|V|)).
- Есть вариант с использованием фиб. кучи, в которой extract_min = O(log(|V|)),
  а decrease_key = O(1), тогда асимптотика сводится к<br>
  O(|V| * log(|V|) + |E|)

## Алгоритм Беллмана-Форда
### [Code](lib/bellman_ford.cpp)
### Описание
Алгоритм поиска наикратчайших путей от стартовой вершины до всех остальных. Работает
следующим образом - создаем массив кратчайших путей (min_path) для каждой вершины,
заполняем его ∞. Для стартовой вершины кратчайший путь будет 0. Далее проходимся по
всем ребрам, проводим релаксацию таким образом:<br>
Если для ребра (i -> j) истинно `min_path[j] > min_path[i] + вес этого ребра(w)`, то<br>
`min_path[j] = min_path[i] + w`<br>
Доказывается, что таких проходов по ребрам достаточно сделать |V| - 1 раз. Результатом
работы этого алгоритма будет массив min_path.
#### Поиск отрицательного цикла с помощью алгоритма Беллмана-Форда
Алгоритм выполняется также, однако для каждой вершины мы дополнительно храним вершину,
которая ведет в необходимую (массив prev). Т.е. релаксация будет выглядеть теперь так:
```c++
if (min_path[j] > min_path[i] + w[i][j]) {
    min_path[j] = min_path[i] + w[i][j];
    prev[j] = i;
}
```
После выполнения алгоритма |V| - 1 раз, мы запускаем еще один проход по ребрам.
Если у нас должна произойти релаксация после тех |V| - 1 итераций, то доказывается,
что в графе есть отрицательный цикл, а вершина, которую нужно "прорелаксировать",
либо лежит на этом цикле, либо достижима из него. Дабы не рисковать, пройдемся из
этой вершины |V| раз по массиву предков, чтобы быть уверенными, что теперь она
точно лежит на цикле:
```c++
for (int i = 0; i < V; ++i) {
    u = prev[u];
}
```
После этого пройтись снова по массиву предков и добавлять каждую пройденную вершину
в список, пока снова не встретим изначальную. Развернутая версия этого массива и будет
списком вершин, входящих в этот цикл.
### Асимптотика
#### Беллман-Форд
|V| - 1 раз мы проходимся по всем ребрам => O(|V| * |E|)
#### Поиск отрицательного цикла
Проходимся по ребрам, ПОКА не найдем нужную вершину, затем |V| раз по массиву предков,
затем еще раз максимум |V| раз, т. е. асимптотика O(|V| + |E|).

## Алгоритм DAG
### [Code](lib/dag.cpp)
### Описание
Под алгоритмом DAG подразумевают поиск кратчайшего пути в направленном ациклическом
графе. Создадим массив min_path, который будет хранить минимальные пути для каждой вершины.
Затем делаем топологическую сортировку. Вершине наверху TPS даем значение 0 в min_edge.<br>
Пока не пройдемся по всем вершинам (в порядке топсорта):<br>
- Пройдемся по всем ребрам, смежным с данной вершиной (i -> j). Если для ребра выполняется
  условие:<br>
  `min_path[j] > min_path[i] + weight[i][j]`, то `min_path[j] = min_path[i] + weight[i][j]`,
  то есть, релаксируем. Массив min_path и будет результатом алгоритма.
### Асимптотика
- Делаем TPS, то есть O(DFS).
- Плюс проходимся по всем ребрам, смежным с вершинами, то есть
  - O(|V| + |E|) для списка смежности
  - O(|V|<sup>2</sup>) для матрицы смежности
  - O(|V| * |E|) для матрицы инцидентности
  
  Эти асимптотики совпадают с O(DFS) => итоговая асимптотика O(DFS)

## Алгоритм Дейкстры
### [Code](lib/dijkstra.cpp)
### Описание
Алгоритм поиска наикратчайшего пути от заданной вершины до всех остальных.<br>
Напоминает алгоритм Прима (или Прима напоминает Дейкстры, не уверен). Алгоритм простой - 
создаем массив с минимальными путями до вершин min_edge, по умолчанию заполняем его ∞.
min_edge от стартовой вершины = 0. Далее |V| раз выполняем следующие действия:
- Ищем вершину с минимальным значением min_edge (i)
- Удаляем ее из списка вершин, которые можно использовать
- Проходимся по вершинам, смежным с ней (j)
  - Если `min_edge[j] > min_edge[i] + weight[i][j]`, то `min_edge[j] = min_edge[i] + weight[i][j]`.
- На выходе получаем массив keys, который списком кратчайших путей от s.

### Асимптотика
Аналогична с алгоритмом Прима (вывод тот же)
- Общий вид O(|V| * extract_min + |E| * decrease_key)
- Для плотных графов O(|V|<sup>2</sup>)
- Для разреженных с использованием приоритетной очереди
  - O(|E| * log(|V|)) (двоичная куча)
  - O(|V| * log(|V|) + |E|) (фибоначчиева куча)

> [!NOTE]
> Почему на алгоритме Дейкстры нельзя строить граф с отрицательными весами?
> Рекомендую ознакомиться с этим [видео](https://www.youtube.com/watch?app=desktop&v=fwaaNf2N4P8).

## Алгоритм Флойда-Уоршелла
### [Code](lib/floyd_warshall.cpp)
### Описание
Алгоритм позволяет найти кратчайший путь между всеми вершинами.<br>
Основная идея алгоритма - каждый раз между двумя вершинами (u и v) попробовать промежуточную (i),
и если путь через i (u -> i -> v) эффективнее (имеет меньший вес) пути (u -> v), или
пути (u -> v) не существует, то запоминаем, что вес пути (u -> v) = весу пути (u -> i -> v).
Проходимся по всем возможным вершинам, получаем ответ.
### Асимптотика
O(|V|<sub>3</sub>). Очев, если посмотреть код.
### Инвариант
На i-ой итерации находим все кратчайшие пути, которым разрешено проходить через промежуточные
вершины от 0 до i. (по Несветайлову М.)

## Поиск диаметра дерева
### Описание
Алгоритм состоит из 2 BFS:
- Когда доходим до самой дальней вершины - запоминаем ее
- От этой вершины делаем еще BFS - расстояние до самой дальней от нее вершины и
  есть диаметр дерева
### Асимптотика
O(2BFS) = O(BFS)

## Алгоритм Куна для поиска максимального паросочетания
### [Code](lib/kun.cpp)
### Описание
Алгоритм Куна работает на двудольных графах => поделим граф на левую и правую доли<br>
Для каждой вершины (i) левой доли запустим алгоритм:
0. Если мы уже посещали эту вершину - выходим, переподвязать не удалось.
   Иначе, помечаем вершину как посещенную (этот пункт потом пригодится).
1. Пройдемся по вершинам, смежным с i (j)
2. Если еще не было установлено паросочетание с j, то просто устанавливаем паросочетание
   i с j
3. Если уже было установлено, то пробуем "переподвязать" вершину (для вершины, у которой
   паросочетание с j, запускаем алгоритм с пункта 0). Если удалось переподвязать - устанавливаем
   паросочетание i с j, иначе вернемся к пункту 2.

Доказывается, что в результате этого алгоритма мы получаем максимальное паросочетание.
### Асимптотика
- Проход по всем вершинам левой доли - O(|V|).
- Для каждой вершины - рекурсивный алгоритм, похожий на DFS - O(DFS).
- Итого - (|V<sub>1</sub>| * DFS)
- Если делать на списке смежности - O(|V<sub>1</sub>| * (|V<sub>1</sub>| + |E|))
- Если граф разреженный - O(|V| * |E|)
- Если граф плотный - O(|V<sub>1</sub>|<sup>2</sup> * |V<sub>2</sub>|)<br>
  Откуда взялась |V<sub>2</sub>|? Мы не будем снова запускать DFS, если мы уже прошли через вершину
  |V<sub>2</sub>|.

## Алгоритм Форда-Фалкерсона
Лично для меня - сложность хард
### [Code](lib/ford_fulkerson.cpp)
### Поиск максимального потока
### Описание
Нужно найти максимальный поток в транспортной сети, представленной в виде графа.<br>
Для каждого ребра проведем обратное ребро, вес которого по умолчанию равен нулю (каким то
боком доказывается, что можно ходить в обратном направлении, почему - не знаю). Реализаций
алгоритма много, приведу свою (см. код).<br>
Представляем граф одновременно в виде списка и матрицы смежности. У несуществующих и обратных
ребер вес = 0. Также создаем массив parent - объясню далее. Значение максимального потока 
по умолчанию = 0. 
1. Проверяем наличие пути (start -> end) c помощью DFS. Пока проходимся заполняем массив parent.
   Если u -> v, то parent[v] = u. Если путь такой не нашли, возвращаем false и заканчиваем
   весь алгоритм. 
2. Если путь существует - пробегаемся по массиву parent с end до start, ищем delta.
   delta - минимальная пропускная способность у к-л ребра в этом пути
3. Снова пробегаемся, но теперь не считаем delta, а работаем с ним. У веса ребра (u -> v)
   вычитаем delta, а у ребра (v -> u) - добавляем.
4. Прибавляем к нашему ответу delta, возвращаемся к пункту 1.

В результате алгоритма у нас целое число - размер максимального потока этой транспортной
сети.
### Асимптотика
- Пункт 1 работает за O(DFS), в нашем случае за O(|E|).
- Пункты 2 и 3 работают за O(|E|).
- Количество раз выполнения этого алгоритма зависит от величины максимального потока, то есть:
`O(f * (|E| + |E| + |E|)) = O(|E| * f)`, где f - размер максимального потока. 
### Поиск максимального паросочетания
Дан двудольный граф. Представим, что у него есть сток и исток. Сток подключаем к каждой
вершине левой доли, а каждую вершину правой доли - к истоку. Пропускная способность всегда
равна 1. В таком случае, тот же алгоритм ищет уже не максимальный сток и исток, а максимальное
число паросочетаний (везде поток == 1, следовательно, из вершины левой доли мы не можем пустить
поток > 1, и так же в вершину правой доли пустить поток > 1, а в сток мы пускаем поток, равный
сумме вершин правой доли, которым нашлось паросочетание).
### Асимптотика
Максимально возможный поток - количество вершин правой доли => Асимптотика O(|E| * f) =
O(|V<sub>2</sub>| * |E|).

## Алгоритм Эдмондса-Карпа
### [Code](lib/edmonds_karp.cpp)
### Описание
Работает идентично Форду-Фалкерсону, однако использует BFS вместо DFS.
### Асимптотика
Ребро становится критическим не больше |V| раз, значит, все ребра становятся критическими
не больше |V| * |E| раз. После пускания потока вдоль кратчайшего пути, хотя бы одно ребро
становится критическим, значит всего может быть не более O(|V| * |E|) увеличений потока.
Добавляем еще BFS на каждую итерацию => O(|V| * |E|<sup>2</sup>)
(взял с [сайта](https://wiki.algocode.ru/index.php?title=Алгоритм_Эдмондса-Карпа),
что такое критическое ребро не знаю).

## Поиск мостов и точек сочленения
### [Code](lib/bridges_ap.cpp)
### Поиск мостов
### Описание
Введем понятия времен входа и выхода в вершину. Время входа - порядковый номер, обозначающий
какой по счету обрабатывается эта вершина в DFS. Время выхода вершины i - порядковый номер
входа вершины, на которой DFS, выходящий из i закончился (встретил посещенную вершину или
вершину, у которой нет ребер, кроме ведущего в нее). Тогда, если мы во время DFS встречаем
ситуацию, что, когда мы вернулись из вершины (j) так, что out[j] > in[i] (мы не вернулись в i
или не встретили пришедшие ей вершины), то (i -> j) - мост
### Асимптотика
O(DFS)
### Поиск точек сочленения
Все то же самое (даже асимптотика), кроме двух вещей
- Теперь знак нестрогий, т. е. out[j] >= in[i] - значит это точка сочленения
- Для вершины, из которой мы запускаемся - другие правила. Для нее - если количество запусков
  DFS от нее > 1, то она является точкой сочленения.

## Жадный алгоритм для поиска раскраски графа
### Описание
Пройдемся DFS по графу. Для каждой вершины сначала ищем минимальный цвет, не задействованный
соседями, а затем раскрашиваем эту вершину в полученный минимальный цвет.
### Асимптотика
Внутри каждой итерации DFS мы дополнительно проходимся по всем соседним вершинам с данной
(максимум |V|).<br>
O(DFS * |V|) = O(|V|<sup>2</sup> + |E|) (на списке смежности).

# Хеширование и строки
## Полиномиальная хеш-функция
Хеш-функция для последовательностей. hash = s<sub>0</sub> * k<sup>0</sup> +
s<sub>1</sub> * k<sup>1</sup> + s<sub>2</sub> * k<sup>2</sup> + ... +
s<sub>n</sub> * k<sup>n</sup> mod p.

## Алгоритм Рабина-Карпа
### [Code](lib/rabin_karp.cpp)
### Описание
Идея проста. У нас есть строка N длины n и строка M длины m (m <= n). Можно полиномиально
захешировать строку M и первые m элементов N. Затем, на каждой итерации удалять хэш первого
символа, домноженного на k<sup>m - 1</sup>, умножить хэш на k и добавить следующий символ.
Если у нас где-то в этих итерациях вышло, что хеш N == хеш M, то проверяем подстроку (на
случай коллизии). Если они равны, то подстрока нашлась.
### Асимптотика
Мы делаем m итераций хеширования обеих строк, затем n - m итераций смещения. Все они работают
за O(hash).
Тогда итоговая асимптотика - O(hash(n + m))
> [!WARNING]
> Так написано не neerc. Я с этим категорически не согласен. m + n - m = n. Я считаю,
> что асимптотика равна O(hash * n), но быть уверенным тоже не могу, поэтому запомните
> лучше обе.

> [!WARNING]
> Второй ворнинг. Оказалось, есть 2 реализации этого алгоритма. Версия, которую
> мне скинула Полина, действительно работает за O(n + m) и ест больше памяти. В общем,
> не вижу смысла ее рассматривать, т. к. она тупо хуже.

Однако, если учитывать коллизии и перепроверки строк, то в худшем случае - асимптотика
O(hash(m + (n - m)(m))) = O(hash * n * m).

## Префикс функция
### [Code](lib/prefix_function.cpp)
### Описание
Если откинуть душное определение с neerc, то если pref[i] = k, то S<sub>0, k</sub> ==
S<sub>i - k, i</sub>, k <= i, где S<sub>i, j</sub> - подстрока от i элемента до j
элемента.
### Алгоритм построения
Алгоритм, вместо того, чтобы постоянно пересчитывать префиксы действует таким образом:
- pref[0] = 0
- Затем идет перебор i = 1 to S.size() - 1
- k = pref[i - 1]
- Пока k > 0 и S[k] == S[i]
  - k = pref[k - 1]
- Если S[k] == S[i]
  - ++k
  - pref[i] = k

### Асимптотика
Данный алгоритм работает за O(n). For работает n раз. While внутри него сделает не
более, чем n - 1 итераций ЗА ВСЕ время работы алгоритма.
Итого O(n + n) = O(n).

> [!WARNING]
> В душе не чаю, как работает этот алгоритм и откуда берется асимптотика.
> Некоторые вещи в этом мире нужно просто запомнить...

### Построение Z-функции
Вроде че-то понял. Идея в том, что мы получаем значение из Z-функции по индексу i.
Это значение (j) должно лежать в ячейке по индексу i + (j - 1) (ведь в ячейке i
должна находиться 1, с увеличением i становится j). Затем, мы медленно уменьшаем j, тем
самым создаем "возрастание", присущее pref-функциям. Если мы заметили, что в ячейке
i + (j - 1) уже лежит значение, то выходим из цикла и продолжаем выполнение алгоритма.
### Асимптотика
Т. к. каждый элемент устанавливается только один раз, то внутренний цикл for сделает
не больше n итераций всего. Учитывая проход по всем элементам:
O(n + n) = O(n).

### Построение строки
> [!NOTE]
> Могу спокойно дать строку, которая сломает алгос.

Если значение элемента i префикс функции pref равняется нулю, то добавляем в строку
новый символ из алфавита. Иначе, добавляем в нее символ по индексу pref[i] - 1.
### Асимптотика
O(n), не вижу смысла доказывать, всё очевидно.

## Z-функция
### [Code](lib/z_function.cpp)
### Описание
Простыми словами, если z[i] = k, то S<sub>0, k</sub> == S<sub>i, i + k</sub>, где
S<sub>i, j</sub> подстрока от символа i до j.
### Алгоритм построения
Алгоритм использует одну простую идею - в некоторых случаях, можно не пересчитывать
значение, а взять заранее посчитанное. Для этого введем понятия left и right.
left - индекс символа, дублирующий начало строки, а right - граница, до которой
символы, начиная от left, соответственно совпадают с началом строки. Таким образом, с течением
алгоритма мы увеличиваем диапазон от left до right, тем самым предоставляя нам
больше заранее посчитанных значений. Подробнее можно почитать на neerc.
### Асимптотика
O(n) - т. к. если значения не посчитаны - мы их считаем, а если посчитаны, то
просто берем.

### Поиск подстроки (Алгоритм Кнута-Морриса-Пратта, только на Z-функции, вместо префикс)
Делаем Z-функцию от (искомая_подстрока + # + строка), где # - символ, который не встречается
ни в одной из этих строк. Тогда в местах, где элемент Z-функции (после #) принимает значение,
равное размеру искомой подстроки, и будет искомая подстрока.

### Асимптотика
O(длина_искомой_подстроки + длина_строки)

### Построение строки
Алгоритм очевидный, а объяснить его тяжело, лучше посмотрите код.
### Асимптотика
O(n), а как иначе?

### Построение по префикс-функции
Потом

## Алгоритм Кнута-Морриса-Пратта
Алгоритм поиска подстроки. См. Поиск подстроки в Z-функции, только используем префикс-функцию.
Асимптотика та же.
