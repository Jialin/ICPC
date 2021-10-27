load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "max_sparse_table_test",
    srcs = ["max_sparse_table_test.cpp"],
    deps = [
        "//ds/sparse_table:max_sparse_table",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "min_sparse_table_test",
    srcs = ["min_sparse_table_test.cpp"],
    deps = [
        "//ds/sparse_table:min_sparse_table",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
