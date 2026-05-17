# FilterBool

A small C++ boolean filter object.

`BoolFilter` smooths boolean input by requiring the same input value for a
configurable number of consecutive updates before changing the output state.
If `required_stable_samples` is set to `0`, it is treated as `1`.
