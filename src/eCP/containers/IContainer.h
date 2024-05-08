#include <algorithm>

namespace ecp {
    template <class T>
    struct Neighborhood {
        int point_id = -1;
        T distance;

        Neighborhood(T dist) : distance(dist) {}

        bool operator < (const Neighborhood<T>& str)  const {
            return distance < str.distance;
        }

        bool operator > (const Neighborhood<T>& str) const {
            return distance > str.distance;
        }
 
    }


    template <class T, class U>
    class IContainer {
    public:
        /**
         * Check against max distance after each computation
         */
        virtual T distance_with_halt() = 0;

        /**
         * Calculate x distance computations and check against max distance
         */
        virtual T distance_with_halt_unrolled() = 0;

        /**
         * Calculate the full distance with x computations at a time
         */
        virtual T distance_full_unrolled() = 0;

        virtual bool halting_check(T distance) = 0;

        virtual void sort_neighbors() = 0;

        bool add(U& point) {
            T distance = _default_value;
            if (_do_scan && !_query_point.descriptor.empty() && point.descriptor.size() == _query_point.descriptor.size()) {
                distance = distance_with_halt_unrolled(point);
            }
            return add(point.id, distance);
        }
        bool add(U& point, int index) {
            T distance = _default_value;
            if (_do_scan && !_query_point.descriptor.empty() && point.descriptor.size() == _query_point.descriptor.size()) {
                distance = distance_with_halt_unrolled(point);
            }
            return add(index, distance);

        }

        bool add(int id, T distance) {
            if (halting_check(distance)) {
                // check if we have less than _k neighbors
                if (_neighbors < (_k - 1)) {
                    _neighborhood[_halt_index].distance = distance;
                    _neighborhood[_halt_index].point_id = id;
                    _neighbors++;
                    _halt_index++;
                } else if (_neighbors < _k) { // final empty space
                    _neighborhood[_halt_index].distance = distance;
                    _neighborhood[_halt_index].point_id = id;
                    _neighbors++;
                    _halting_threshold = distance;

                    for (int i = 0; i < _k; ++i) {
                        if (halting_check(_neighborhood[i].distance)) {
                            _halt_index = i;
                            _halting_distance = _neighborhood[i].distance;
                        }
                    }
                } else {
                    _neighborhood[_halt_index] = distance;
                    _neighborhood[_halt_index] = id;
                    _halting_threshold = distance;

                    for (int i = 0; i < _k; ++i) {
                        if (halting_check(_halting_distance)) {
                            _halt_index = i;
                            _halting_distance = _neighborhood[i].distance;
                        }
                    }
                }
                return true;
            }
            return false;
        }

        bool add_no_duplicate_ids(U& point, T distance) {
            if (halting_check(distance)) {
                for (int i = 0; i < _neigbors; ++i) {
                    if (_neighborhood[i].point_id == id) {
                        // No case where the distance can be different
                        return false;
                    }
                }
            }
        }

        vector<int> get_neighbor_ranks() {
            int current_size = _k;
            if (_neighbors < _k) current_size = _neighbors;
            auto ret = vector<int>(current_size);
            for (int i = 0; i < current_size; ++i) {
                ret[i] = _neighborhood[i].point_id;
            }
            return ret;
        };

        T get_query_point() {
            return _query_point;
        }

        void set_k(int k) {
            _k = k;
            _neighborhood = vector<Neighborhood<T>>(k);
            for (int i = 0; i < k; ++i) {
                _neighborhood[i] = Neighborhood<T>(_default_value);
            }
        }

        void set_b(int b) {
            _b = b;
        }

        void set_query_point(T& point) {
            _query_point = point;
        }
    
    protected:
        U _query_point;
        int _k;
        int _neighbors;
        T _halting_distance; // Least similar according to used metric
        T _default_value;
        int _halt_index;
        vector<Neighborhood<T>> _neighborhood;
        boolean _do_scan = true;
        int _b;

        void sort_neighbors_internal(bool greater) {
            if (greater)
                std::sort(_neighborhood.begin(), _neighborhood.end(), std::greater<Neighborhood<T>>())
            else
                std::sort(_neighborhood.begin(), _neighborhood.end())
        }
    }
}

template class ecp::Neighborhood<float>;
template class ecp::IContainer<float, IDescriptor<vector<float>>>;