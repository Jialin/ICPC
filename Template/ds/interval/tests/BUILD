load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "base_grouping_intervals_container_test",
    srcs = ["base_grouping_intervals_container_test.cpp"],
    deps = [
        "//ds/interval:base_grouping_intervals_container",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "base_intervals_container_test",
    srcs = ["base_intervals_container_test.cpp"],
    deps = [
        "//ds/interval:base_intervals_container",
        "//ds/interval:base_intervals_container_macros",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
