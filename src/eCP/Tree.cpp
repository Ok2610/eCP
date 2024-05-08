#include <iostream>
#include <cmath>
#include <stdexcept>

#include "containers/IContainer.h"

using namespace ecp;
using std::cout;
using std::endl;

template <class T>
void Tree<T>::build_dynamic_tree() {
    if (_L < 1 || _L > 10) {
        throw std::invalid_argument(_L + " is not a valid index depth");
    }

    cout << "Building Tree with L = " << _L << " and treeA = " << _a;
    if (_L == 1) { // no hierarchy only _leafs array
        return;
    }

    // Build a dynamic root node
    int bucket_size = (int) std::ceil(std::pow(_leafs.size(), (1.0 / _L)));
    cout << "Bucket size: " << bucket_size << endl;
    _root = DynamicInternalNode();
    _root.children = vector<DynamicInternalNode>(bucket_size);
    for (int i = 0; i < bucket_size; ++i) {
        _root.children.emplace_back(DynamicInternalNode(i));
    }

    // We now have a root node with all the leaders of the top level that can be used for scanning
    for (int i = 2; i <= _L; ++i) {
        int indx = 0;
        // Total number of clusters for L
        int thrs = (int) std::pow((float) bucket_size, (float) i); 
        if (thrs > _leafs.size()) {
            thrs = _leafs.size();
        }
        while (indx < thrs) {
            // search with limit i 
            vector<DynamicInternalNode> ret = limited_dynamic_root_search(_leafs[indx], i-1, _root);
            if (ret.empty()) continue;
            /// TODO: ?? "add top treeA nearest"
            auto dn = DynamicInternalNode();
            dn.leader_id = leafs[indx].id;
            for (int x = 0; x < ret.size(); ++x) {
                // if (ret[x] != null) {
                if (ret[x].children.empty()) {
                    ret[x].children = vector<DynamicInternalNode>(bucket_size);
                }
                ret[x].children.add(dn);
                // }
            }
            indx++;
        }
    }
    // we have built the tree now but it's still in a dynamic structure
    // make the structure static and fixed size
    trim_dynamic_tree(_root);
}


template <typename T, typename U>
vector<DynamicInternalNode> Tree<T>::depth_limited_search(T& point, int limit, DynamicInternalNode& root) {
    auto ret = vector<DynamicInternalNode>(_a);
    auto current_node = root;
    int current_level = 1;
    U qdesc;
    // search the upper levels where we always only use k=1
    while (current_level <= limit) {
        if (current_level == limit) {
            qdesc = U(_a);
        } else {
            qdesc = U(1);
        }
        qdesc.set_query_point(p);
        vector<DynamicInternalNode>::iterator it;
        int at = 0;
        for (int i = 0; i < current_node.children.size(); ++i) {
            qdesc.add(_leafs[i].leader_id, at++);
        }

        if (current_level == limit) {
            break;
        } else {
            current_node = current_node.children[qdesc.get_neighbor_ranks()[0]];
            current_level++;
        }
    }

    qdesc.sort_neighbors();
    vector<int> res = qdesc.get_neighbor_ranks();
    for (int i = 0; i < res.size(); ++i) {
        ret[i] = current_node.children[res[i]];
    }
    return ret;
}

/// TODO: Add Priority Queue Logic here!
template <typename T, typename U>
vector<T> Tree<T,U>::search_tree(T p, int b) {
    // the a return value
    auto ret = vector<T>();
    // sanity check, if the root is null, the tree is not setup properly.
    if (!_root.children.empty()) {
        // working pointer to root
        DynamicInternalNode current = _root;
        U qdesc;
        // while traversing internal nodes, i.e. children (leafs are only on the bottom level). 
        while (!curr.children.empty()) {
            if (curr.children.get(0).children.empty()) {
                // if this is the last level we break before scanning.
                break;
            }
            // only find the single best matching cluster
            qdesc = U(b);
            qdesc.SetQueryPoint(p);
            // scan the current node of the tree (starting at root)

            for(int i = 0; i < curr.children.size(); ++i) {
                // add( point, id) is so that id can know the index of parent tree-node array in the results
                // returned from the knn.
                qdesc.add(_leafs[curr.children[i].leader_id], i);
            }
            // set the node to the next level.  NOTE we are skipping the qdesc.sortKNN() as it's only of size 1.
            curr = curr.children.get(qdesc.get_neighbor_ranks()[0]);
            qdesc = null;
        }
        // curr halts on the level below the bottom, now we scan it for the b best clusters
        qdesc = U(b);
        qdesc.SetQueryPoint(p);

        for (int i = 0; i < curr.children.size(); ++i) {
            qdesc.add(_leafs[curr.children[i].leader_id], curr.children[i].leader_id);
        }
        // now we need to sort as the knn is >1 
        qdesc.sort_neighbors();
        vector<int> neighbors = qdesc.get_neighbor_ranks();
        // replace the internal index offset for the actual indexEntrys.
        // create a new return array of size b
        ret = vector<T>(neighbors.size());
        for (int i=0; i < neighbors.size(); ++i) {
            //System.out.println(knn[i]);
            ret[i] = _leafs[neighbors[i]];
        }
    }
    return ret;
}


template class ecp::Tree<FloatVecDescriptor, IPFloatVecContainer>;
template class ecp::Tree<FloatVecDescriptor, L2FloatVecContainer>;