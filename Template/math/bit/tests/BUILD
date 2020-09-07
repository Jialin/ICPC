load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "ctz_test",
    srcs = ["ctz_test.cpp"],
    deps = [
        "//math/bit:ctz",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
