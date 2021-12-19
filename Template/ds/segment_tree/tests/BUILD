load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "lazy_compact_segment_tree_min_test",
    srcs = ["lazy_compact_segment_tree_min_test.cpp"],
    deps = [
        "//ds/segment_tree:base_lazy_compact_segment_tree_macros",
        "//ds/segment_tree:lazy_compact_segment_tree_min",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
