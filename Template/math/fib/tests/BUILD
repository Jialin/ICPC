load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "fib_sum_test",
    srcs = ["fib_sum_test.cpp"],
    deps = [
        "//math/fib:fib_sum",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "fib_test",
    srcs = ["fib_test.cpp"],
    deps = [
        "//math/fib",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "fib_utils_test",
    srcs = ["fib_utils_test.cpp"],
    deps = [
        "//math/fib:fib_utils",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "pisano_period_test",
    srcs = ["pisano_period_test.cpp"],
    deps = [
        "//math/fib:pisano_period",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "pisano_period64_test",
    srcs = ["pisano_period64_test.cpp"],
    deps = [
        "//math/fib:pisano_period64",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
