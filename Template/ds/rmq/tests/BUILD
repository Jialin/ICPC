load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "min_rmq_test",
    srcs = ["min_rmq_test.cpp"],
    deps = [
        "//ds/rmq:min_rmq",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
