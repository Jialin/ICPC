load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "gen_primemin_prime_tagger_test",
    srcs = ["min_prime_tagger_test.cpp"],
    deps = [
        "//math/prime:min_prime_tagger",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "prime_checker_quick_test",
    srcs = ["prime_checker_quick_test.cpp"],
    deps = [
        "//math/prime:prime_checker_quick",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "prime_checker_slow_test",
    srcs = ["prime_checker_slow_test.cpp"],
    deps = [
        "//math/prime:prime_checker_slow",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "prime_checker_test",
    srcs = ["prime_checker_test.cpp"],
    deps = [
        "//math/prime:prime_checker",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "prime_gen_test",
    srcs = ["prime_gen_test.cpp"],
    deps = [
        "//math/prime:prime_gen",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "segmented_prime_checker_test",
    srcs = ["segmented_prime_checker_test.cpp"],
    deps = [
        "//math/prime:segmented_prime_checker",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
