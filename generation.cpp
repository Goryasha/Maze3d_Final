#include <iostream>
#include <vector>
#include "function.h"
#include <stack>
#include <algorithm>
#include <map>
#include <random>
#include <ctime>
#include <set>

auto comp(std::pair<char, int> &a, std::pair<char, int> &b) -> bool {
    return a.second > b.second;
}


auto gen(size_t side_x, size_t side_y, size_t side_z, float weightx, float weighty, float weightz,
         std::vector<float> &vertex, std::vector<int> &index) -> Point {
    /**
     * @param weights хранит приоритеты создания прохода по определённой оси
     */
    std::vector<std::pair<char, int>> weights = {{'x', static_cast<int>(weightx * 10)},
                                                 {'y', static_cast<int>(weighty * 10)},
                                                 {'z', static_cast<int>(weightz * 10)}};
    std::cout << "weight_x: " << weights[0].second << '\n';
    std::cout << "weight_y: " << weights[1].second << '\n';
    std::cout << "weight_z: " << weights[2].second << '\n';
    /**
     * @param vis для каждой вершин хранит одно из двух её состояний: посещённая, непосещённая
     * @param maze хранит словарь Вершина : Списокк смежных вершин
     * @param st стек, используемый в алгоритме генерации
     * @param vert_ind словарь Вершина : Индекс, Отдалённость от корня лабиринта
     */
    auto vis = std::vector(side_x, std::vector<std::vector<int>>(side_y, std::vector<int>(side_z, false)));
    auto maze = std::map<Point, std::vector<Point>>();
    auto st = std::stack<Point>();
    vis[0][0][0] = true;
    st.push(Point(0, 0, 0));
    auto vert_ind = std::map<Point, std::pair<int, int>>();

    /**
     * заполнение индексов вершин
     */
    auto k = 0;
    for (size_t x = 0; x < side_x; x++)
        for (size_t y = 0; y < side_y; y++)
            for (size_t z = 0; z < side_z; z++) {
                vert_ind[Point(x, y, z)] = std::make_pair(k, 0);
                k++;
            }
    vert_ind[Point(0, 0, 0)].second = 1;

    /**
     * генерация лабиринта
     */
    while (!st.empty()) {
        auto p = st.top();
        auto neighbours = std::vector<Point>();
        auto dir = std::vector<char>();
        auto st_dir = std::set<char>();
        std::random_device rd;
        std::mt19937 gen(rd());

        /**
         * выбираем в каком порядке будет проверять направления для создания прохода, с учетом приоритетов
         */
        while (dir.size() < 3) {
            auto coin = gen() % (weights[0].second + weights[1].second + weights[2].second);
            if (coin < weights[0].second && !st_dir.contains('x')) {
                dir.push_back('x');
                st_dir.insert('x');
            }
            if (coin < weights[0].second + weights[0].second && coin >= weights[0].second && !st_dir.contains('y')) {
                dir.push_back('y');
                st_dir.insert('y');
            }
            if (coin >= weights[0].second + weights[1].second && !st_dir.contains('z')) {
                dir.push_back('z');
                st_dir.insert('z');
            }
        }
        /**
         * проверять направления для создания прохода
         */
        if (dir[0] == 'x') {
            if (p.x > 0)
                if (!vis[p.x - 1][p.y][p.z])
                    neighbours.emplace_back(p.x - 1, p.y, p.z);
            if (p.x < side_x - 1)
                if (!vis[p.x + 1][p.y][p.z])
                    neighbours.emplace_back(p.x + 1, p.y, p.z);
        } else if (dir[0] == 'y') {
            if (p.y > 0)
                if (!vis[p.x][p.y - 1][p.z])
                    neighbours.emplace_back(p.x, p.y - 1, p.z);
            if (p.y < side_y - 1)
                if (!vis[p.x][p.y + 1][p.z])
                    neighbours.emplace_back(p.x, p.y + 1, p.z);
        } else {
            if (p.z > 0)
                if (!vis[p.x][p.y][p.z - 1])
                    neighbours.emplace_back(p.x, p.y, p.z - 1);
            if (p.z < side_z - 1)
                if (!vis[p.x][p.y][p.z + 1])
                    neighbours.emplace_back(p.x, p.y, p.z + 1);
        }
        if (neighbours.empty()) {
            if (dir[1] == 'x') {
                if (p.x > 0)
                    if (!vis[p.x - 1][p.y][p.z])
                        neighbours.emplace_back(p.x - 1, p.y, p.z);
                if (p.x < side_x - 1)
                    if (!vis[p.x + 1][p.y][p.z])
                        neighbours.emplace_back(p.x + 1, p.y, p.z);
            } else if (dir[1] == 'y') {
                if (p.y > 0)
                    if (!vis[p.x][p.y - 1][p.z])
                        neighbours.emplace_back(p.x, p.y - 1, p.z);
                if (p.y < side_y - 1)
                    if (!vis[p.x][p.y + 1][p.z])
                        neighbours.emplace_back(p.x, p.y + 1, p.z);
            } else {
                if (p.z > 0)
                    if (!vis[p.x][p.y][p.z - 1])
                        neighbours.emplace_back(p.x, p.y, p.z - 1);
                if (p.z < side_z - 1)
                    if (!vis[p.x][p.y][p.z + 1])
                        neighbours.emplace_back(p.x, p.y, p.z + 1);
            }
        }
        if (neighbours.empty()) {
            if (dir[2] == 'x') {
                if (p.x > 0)
                    if (!vis[p.x - 1][p.y][p.z])
                        neighbours.emplace_back(p.x - 1, p.y, p.z);
                if (p.x < side_x - 1)
                    if (!vis[p.x + 1][p.y][p.z])
                        neighbours.emplace_back(p.x + 1, p.y, p.z);
            } else if (dir[2] == 'y') {
                if (p.y > 0)
                    if (!vis[p.x][p.y - 1][p.z])
                        neighbours.emplace_back(p.x, p.y - 1, p.z);
                if (p.y < side_y - 1)
                    if (!vis[p.x][p.y + 1][p.z])
                        neighbours.emplace_back(p.x, p.y + 1, p.z);
            } else {
                if (p.z > 0)
                    if (!vis[p.x][p.y][p.z - 1])
                        neighbours.emplace_back(p.x, p.y, p.z - 1);
                if (p.z < side_z - 1)
                    if (!vis[p.x][p.y][p.z + 1])
                        neighbours.emplace_back(p.x, p.y, p.z + 1);
            }
        }
        /**
         * в случае, если neighbours пустой, значит непосещённых вершин рядом нет, значит зашли в тупик, возвращаемся
         * на одну вершину в стеке назад
         *
         * иначе, если можем пойти в определённом направлении в 2 стороны, то выбираем, куда пойдём
         */
        if (neighbours.empty()) {
            st.pop();
        } else {
            std::random_device rd;
            std::mt19937 gen(rd());
            auto num = static_cast<size_t>(gen() % neighbours.size());
            maze[p].push_back(neighbours[num]);
            maze[neighbours[num]].push_back(p);
            vis[neighbours[num].x][neighbours[num].y][neighbours[num].z] = true;
            st.push(neighbours[num]);
        }
    }
    /**
     * записываем в вектор вершин их координаты
     */
    for (auto item: vert_ind) {
        vertex.push_back(static_cast<float>(item.first.x));
        vertex.push_back(static_cast<float>(item.first.y));
        vertex.push_back(static_cast<float>(item.first.z));
    }
    /**
     * записываем в вектор индексов попарно вершины, которые надо соединить
     */
    for (const auto &item: maze) {
        for (auto k: item.second) {
            index.push_back(vert_ind[item.first].first);
            index.push_back(vert_ind[k].first);
        }
    }
    /**
     * запускаем функцию cost от корневой вершины и затем находим любую из наиболее удалённых от корневой вершину
     */
    cost(Point(0, 0, 0), maze, vert_ind);
    auto max_cost = 0;
    auto p = Point(0, 0, 0);
    for (auto item: vert_ind) {
        if (item.second.second > max_cost) {
            max_cost = item.second.second;
            p = item.first;
        }
    }
    m_print(maze);
    /**
     * возращаем наиболее удалённую вершину
     */
    return p;
}

auto cost(Point p0, std::map<Point, std::vector<Point>> &maze, std::map<Point, std::pair<int, int>> &vert_ind) -> void {
    for (auto item: maze[p0]) {
        if (vert_ind[item].second == 0) {
            vert_ind[item].second = vert_ind[p0].second + 1;
            cost(item, maze, vert_ind);
        }
    }
}


auto m_print(std::map<Point, std::vector<Point>> &maze) -> void {
    for(auto item : maze){
        item.first.cor();
        std::cout<<": ";
        for(auto item2 : item.second){
            item2.cor();
            std::cout<<"| ";
        }
        std::cout<<'\n';
    }
}

auto cleaning(std::vector<int> &v) -> void {
    auto s = std::set<std::pair<int, int>>();
    for (size_t i = 0; i < v.size(); i += 2) {
        if (v[i] > v[i + 1])
            s.insert(std::make_pair(v[i + 1], v[i]));
        else
            s.insert(std::make_pair(v[i], v[i + 1]));
    }
    v.clear();
    for (auto item: s) {
        v.push_back(item.first);
        v.push_back(item.second);
    }
}