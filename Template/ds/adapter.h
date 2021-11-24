#pragma once

using namespace std;

namespace ds {

// Example usage:
//   ds::Adapter<priority_queue<int>> heap;
//   heap.container() // to access underlying container
template<typename Container>
struct Adapter : Container {
  typename Container::container_type& container() {
    return this->c;
  }
};

} // namespace ds
