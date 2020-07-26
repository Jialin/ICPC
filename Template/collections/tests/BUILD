load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "bitset_test",
    srcs = ["bitset_test.cpp"],
    deps = [
        "//collections:bitset",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "unique_counter_test",
    srcs = ["unique_counter_test.cpp"],
    deps = [
        "//collections:unique_counter",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
