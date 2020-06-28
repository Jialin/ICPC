load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "min_prime_tagger_test",
    srcs = ["min_prime_tagger_test.cpp"],
    deps = [
        "//math/prime:min_prime_tagger",
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
    name = "prime_iterator_test",
    srcs = ["prime_iterator_test.cpp"],
    deps = [
        "//math/prime:prime_iterator",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "segmented_prime_iterator_test",
    srcs = ["segmented_prime_iterator_test.cpp"],
    deps = [
        "//math/prime:segmented_prime_iterator",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
