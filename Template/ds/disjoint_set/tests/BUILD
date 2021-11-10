load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "disjoint_set_size_parity_test",
    srcs = ["disjoint_set_size_parity_test.cpp"],
    deps = [
        "//ds/disjoint_set:disjoint_set_size_parity",
        "//ds/disjoint_set:disjoint_set_size_parity_macros",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "disjoint_set_size_test",
    srcs = ["disjoint_set_size_test.cpp"],
    deps = [
        "//ds/disjoint_set:disjoint_set_size",
        "//ds/disjoint_set:disjoint_set_size_macros",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
