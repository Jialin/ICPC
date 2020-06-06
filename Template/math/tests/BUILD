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

cc_test(
    name = "gcd_test",
    srcs = ["gcd_test.cpp"],
    deps = [
        "//math:gcd",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "linear_diophantine_test",
    srcs = ["linear_diophantine_test.cpp"],
    deps = [
        "//math:linear_diophantine",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
