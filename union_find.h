#include <unordered_map>
#include <vector>


/**
 * Union-find or disjoint-set data structure with generics
 * https://en.wikipedia.org/wiki/Disjoint-set_data_structure
 */
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
        size_ = std::vector<int>(size, -1);
    }

    // create a new set containing only value
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
        if (!ids.count(value)) return -1;
        int x = ids[value];
        while (parent[x] != x) {
            x = parent[x] = parent[parent[x]];
        }
        return x;
    }

    // merge two sets
    // will not insert a value if it is missing
    void merge(T value1, T value2) {
        int x = find(value1);
        int y = find(value2);
        if (x == y || x == -1 || y == -1) return;
        if (size_[x] < size_[y]) std::swap(x, y);
        parent[y] = x;
        size_[x] += size_[y];
    }

    // check if two values belong to the same set
    bool same(T value1, T value2) {
        return find(value1) == find(value2);
    }

    // the size of the set value belongs to
    int size(T value) {
        int id = find(value);
        if (id == -1) return 0;
        return size_[id];
    }
};

