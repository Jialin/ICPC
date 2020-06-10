load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "gen_primes_test",
    srcs = ["gen_primes_test.cpp"],
    deps = [
        "//math/prime:gen_primes",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "mark_primes_test",
    srcs = ["mark_primes_test.cpp"],
    deps = [
        "//math/prime:mark_primes",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
