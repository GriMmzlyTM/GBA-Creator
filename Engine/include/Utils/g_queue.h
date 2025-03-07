#pragma once

namespace ge {

template <typename TType, int TStartingSize> class queue {

  int _max_size = TStartingSize;
  int _curr_size;

  TType *_values = new TType[TStartingSize];

public:
  void push(TType val);
};

} // namespace ge
