load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "combination",
    hdrs = ["combination.h"],
    deps = [
        "//math/mod:inv",
        "//math/mod:mul",
    ],
)

cc_library(
    name = "combination_full",
    hdrs = ["combination_full.h"],
    deps = [
        ":combination_prime",
        "//math:chinese_remainder",
        "//math/prime:factorize_use_primes",
    ],
)

cc_library(
    name = "combination_prime",
    hdrs = ["combination_prime.h"],
    deps = [
        "//math/mod:fix",
        "//math/mod:inv",
        "//math/mod:mul",
    ],
)

cc_library(
    name = "stirling_first",
    hdrs = ["stirling_first.h"],
    deps = [
        "//math/mod:add",
        "//math/mod:fix",
        "//math/mod:mul",
    ],
)
