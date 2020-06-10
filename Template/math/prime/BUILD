load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "gen_primes",
    hdrs = ["gen_primes.h"],
)

cc_library(
    name = "mark_primes",
    hdrs = ["mark_primes.h"],
    deps = [
        "//collections:bitset",
    ],
)
