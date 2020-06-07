load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "fib_partial_sum_test",
    srcs = ["fib_partial_sum_test.cpp"],
    deps = [
        "//math/fib:fib_partial_sum",
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
