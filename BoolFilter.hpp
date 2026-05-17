#pragma once

#include <cstddef>

class BoolFilter {
 public:
  explicit BoolFilter(std::size_t required_stable_samples = 1)
      : required_stable_samples_(required_stable_samples == 0 ? 1 : required_stable_samples) {}

  bool update(bool input) {
    if (input == candidate_state_) {
      ++stable_count_;
    } else {
      candidate_state_ = input;
      stable_count_ = 1;
    }

    if (stable_count_ >= required_stable_samples_) {
      output_state_ = candidate_state_;
    }

    return output_state_;
  }

  bool output() const { return output_state_; }

 private:
  std::size_t required_stable_samples_;
  std::size_t stable_count_ = 0;
  bool candidate_state_ = false;
  bool output_state_ = false;
};
