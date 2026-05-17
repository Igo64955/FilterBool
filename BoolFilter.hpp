#pragma once

#include <cstddef>

// BoolFilter debounces boolean input by requiring stable repeated samples
// before changing the output state.
class BoolFilter {
 public:
  // required_stable_samples sets how many consecutive identical inputs are needed
  // before the filtered output changes. A value of 0 is clamped to 1.
  explicit BoolFilter(std::size_t required_stable_samples = 1)
      : required_stable_samples_(required_stable_samples == 0 ? 1 : required_stable_samples) {}

  // Processes a new input sample and returns the current filtered output.
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

  // Returns the current filtered output without consuming a new input sample.
  bool output() const { return output_state_; }

 private:
  std::size_t required_stable_samples_;
  std::size_t stable_count_ = 0;
  bool candidate_state_ = false;
  bool output_state_ = false;
};
