load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "chinese_remainder",
    hdrs = ["chinese_remainder.h"],
    deps = [
        "//math/gcd:ext_gcd",
        "//math/mod:add",
        "//math/mod:fix",
        "//math/mod:mul",
    ],
)

cc_library(
    name = "linear_diophantine",
    hdrs = ["linear_diophantine.h"],
    deps = [
        "//math/gcd:ext_gcd",
    ],
)

cc_library(
    name = "montgomery_mul",
    hdrs = ["montgomery_mul.h"],
    deps = [
        ":uint256",
    ],
)

cc_library(
    name = "pow10",
    hdrs = ["pow10.h"],
)

cc_library(
    name = "uint256",
    hdrs = ["uint256.h"],
)
