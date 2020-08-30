load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "combination_prime_test",
    srcs = ["combination_prime_test.cpp"],
    deps = [
        "//math/combination:combination_prime",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "combination_test",
    srcs = ["combination_test.cpp"],
    deps = [
        "//math/combination",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "stirling_first_test",
    srcs = ["stirling_first_test.cpp"],
    deps = [
        "//math/combination:stirling_first",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
