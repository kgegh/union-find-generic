#include <unordered_map>
#include <vector>
#include <cassert>


template <typename T>
class union_find {

private:
    std::unordered_map<T,int> ids;
    std::vector<int> parent, size_;
    int id = 0;

public:
    union_find() {}
    
    union_find(int size) {
        parent = std::vector<int>(size, -1);
    }

    void make_set(T value) {
        if (ids.count(value)) return;
        ids[value] = id;
        if (parent.size() < id+1) {
            parent.push_back(id);
            size_.push_back(1);
        }
        else {
            parent[id] = id;
            size_[id] = 1;
        }
        id++;
    }

    // return id of value
    int find(T value) {
        int x = ids[value];
        while (parent[x] != x) {
            x = parent[x] = parent[parent[x]];
        }
        return x;
    }

    void merge(T value1, T value2) {
        int x = find(value1);
        int y = find(value2);

        if (x == y) return;

        if (size_[x] < size_[y]) std::swap(x, y);

        parent[y] = x;
        size_[x] += size_[y];
    }

    bool same(T value1, T value2) {
        return find(value1) == find(value2);
    }

    int size(T value) {
        return size_[find(value)];
    }
};


int main() {
    union_find<char> uf;
    //a b c d e f g h i
    for (char c = 'a'; c <= 'i'; c++) uf.make_set(c);

    assert(uf.same('a','b') == false);

    uf.merge('a', 'b');

    assert(uf.same('a','b') == true);
    assert(uf.same('b','c') == false);
    assert(uf.size('a') == 2);
}
