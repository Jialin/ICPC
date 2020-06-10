load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "fib_partial_sum",
    hdrs = ["fib_partial_sum.h"],
    deps = [
        ":fib",
    ],
)

cc_library(
    name = "fib_utils",
    hdrs = ["fib_utils.h"],
    deps = [
        "//math/matrix:matrix_mod_exp_utils",
    ],
)

cc_library(
    name = "fib",
    hdrs = ["fib.h"],
    deps = [
        "//math/mod:add",
        "//math/mod:mul",
        "//math/mod:slight_fix",
        "//math/mod:sub",
    ],
)