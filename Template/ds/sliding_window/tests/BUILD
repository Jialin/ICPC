load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "max_sliding_window_test",
    srcs = ["max_sliding_window_test.cpp"],
    deps = [
        "//ds/sliding_window:base_sliding_window_macros",
        "//ds/sliding_window:max_sliding_window",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "min_sliding_window_test",
    srcs = ["min_sliding_window_test.cpp"],
    deps = [
        "//ds/sliding_window:base_sliding_window_macros",
        "//ds/sliding_window:min_sliding_window",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
