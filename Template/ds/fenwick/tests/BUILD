load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "fenwick_2d_array_sum_test",
    srcs = ["fenwick_2d_array_sum_test.cpp"],
    deps = [
        "//ds/fenwick:base_fenwick_2d_array_macros",
        "//ds/fenwick:fenwick_2d_array_sum",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "fenwick_3d_array_sum_test",
    srcs = ["fenwick_3d_array_sum_test.cpp"],
    deps = [
        "//ds/fenwick:base_fenwick_3d_array_macros",
        "//ds/fenwick:fenwick_3d_array_sum",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "fenwick_max_test",
    srcs = ["fenwick_max_test.cpp"],
    deps = [
        "//ds/fenwick:base_fenwick_macros",
        "//ds/fenwick:fenwick_max",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "fenwick_min_test",
    srcs = ["fenwick_min_test.cpp"],
    deps = [
        "//ds/fenwick:base_fenwick_macros",
        "//ds/fenwick:fenwick_min",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "fenwick_sum_test",
    srcs = ["fenwick_sum_test.cpp"],
    deps = [
        "//ds/fenwick:base_fenwick_macros",
        "//ds/fenwick:fenwick_sum",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
