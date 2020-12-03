load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "fib",
    hdrs = ["fib.h"],
    deps = [
        "//math/mod:add",
        "//math/mod:mul_safe",
        "//math/mod:slight_fix",
        "//math/mod:sub",
    ],
)

cc_library(
    name = "fib_power_sum",
    hdrs = ["fib_power_sum.h"],
    deps = [
        "//math/combination",
        "//math/mod:add",
        "//math/mod:exp",
        "//math/mod:fix",
        "//math/mod:mul",
        "//math/mod:sub",
    ],
)

cc_library(
    name = "fib_sum",
    hdrs = ["fib_sum.h"],
    deps = [
        ":fib",
    ],
)

cc_library(
    name = "fib_utils",
    hdrs = ["fib_utils.h"],
    deps = [
        "//math/matrix:matrix_array",
        "//math/matrix:matrix_mod_exp_utils",
    ],
)

cc_library(
    name = "pisano_period",
    hdrs = ["pisano_period.h"],
    deps = [
        ":fib",
        "//math/gcd:gcd32",
        "//math/prime:divisor_use_tagger",
        "//math/prime:min_prime_tagger",
    ],
)

cc_library(
    name = "pisano_period64",
    hdrs = ["pisano_period64.h"],
    deps = [
        ":pisano_period",
        "//math/gcd:gcd64",
        "//math/prime:divisor64",
        "//math/prime:factorize64",
    ],
)
