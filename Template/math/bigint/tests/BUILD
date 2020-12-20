load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "bigint_test",
    srcs = ["bigint_test.cpp"],
    deps = [
        "//math/bigint",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
