load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "ext_gcd_test",
    srcs = ["ext_gcd_test.cpp"],
    deps = [
        "//math:ext_gcd",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
