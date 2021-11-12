load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "disjoint_set_groups_test",
    srcs = ["disjoint_set_groups_test.cpp"],
    deps = [
        "//ds/disjoint_set:disjoint_set_groups",
        "//ds/disjoint_set:disjoint_set_groups_macros",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "disjoint_set_max_test",
    srcs = ["disjoint_set_max_test.cpp"],
    deps = [
        "//ds/disjoint_set:base_disjoint_set_value_macros",
        "//ds/disjoint_set:disjoint_set_max",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "disjoint_set_min_max_test",
    srcs = ["disjoint_set_min_max_test.cpp"],
    deps = [
        "//ds/disjoint_set:base_disjoint_set_value_macros",
        "//ds/disjoint_set:disjoint_set_min_max",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "disjoint_set_parity_test",
    srcs = ["disjoint_set_parity_test.cpp"],
    deps = [
        "//ds/disjoint_set:disjoint_set_parity",
        "//ds/disjoint_set:disjoint_set_parity_macros",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "disjoint_set_test",
    srcs = ["disjoint_set_test.cpp"],
    deps = [
        "//ds/disjoint_set",
        "//ds/disjoint_set:disjoint_set_macros",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
