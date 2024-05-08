#include <vector>
#include <iostream>

namespace ecp {
    struct DynamicInternalNode {
        int leader_id = -1;
        vector<int> children;
        DynamicInternalNode() {};
        DynamicInternalNode(int id) : leader_id(id) {};
    };

    template <typename T, typename U>
    class Tree {
    public:
        /**
         * Constructor of Tree
         * levels: The desired height of the tree
         * tree_a: Duplicate cluster representetives into 'a' closest clusters
         * tree_b: Search expansion parameter / number of relevant clusters to find
         *         This is a base setting, internally there is a priority queue to incrementally expand if desired
         */
        Tree(int levels, int tree_a, int tree_b, vector<T> leafs)
            : _L(levels), _a(tree_a), _b(tree_b), _leafs(leafs) {};

        ~Tree() {};

        void build_dynamic_tree();

        /**
         * Search the tree to a fixed limit (level),
         * necessary in the top down construction process
         */
        void depth_limited_search(T& point, int limit, DynamicInternalNode& root);

        /**
         * Search the tree for up to b relevant nodes at each level 
         * and then find the b most relevant clusters in the bottom level
         * p: query point
         * b: Search expansion parameter / number of relevant clusters to find
         *    This is a base setting, internally there is a priority queue to incrementally expand if desired
         */
        vector<T> search_tree(T p, int b);

        void trim_dynamic_tree(DynamicInternalNode curr) {
            if (curr.children.empty()) {
                return;
            } else {
                for (int i = 0; curr.children.size() < i; ++i) {
                    trim_dynamic_tree(curr.children[i]);
                }
            }
            curr.children.shrink_to_fit();
        };

    private:
        int _L;
        int _a;
        int _b;
        vector<T> _leafs; 
        DynamicInternalNode _root;
    }
}

