load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "max_rmq_test",
    srcs = ["max_rmq_test.cpp"],
    deps = [
        "//ds/rmq:max_rmq",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "min_rmq_test",
    srcs = ["min_rmq_test.cpp"],
    deps = [
        "//ds/rmq:min_rmq",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
