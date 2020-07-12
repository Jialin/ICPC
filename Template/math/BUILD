load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "ctz128",
    hdrs = ["ctz128.h"],
)

cc_library(
    name = "ext_gcd",
    hdrs = ["ext_gcd.h"],
)

cc_library(
    name = "gcd",
    hdrs = ["gcd.h"],
)

cc_library(
    name = "gcd32",
    hdrs = ["gcd32.h"],
)

cc_library(
    name = "gcd64",
    hdrs = ["gcd64.h"],
)

cc_library(
    name = "gcd128",
    hdrs = ["gcd128.h"],
    deps = [
        ":ctz128",
    ],
)

cc_library(
    name = "linear_diophantine",
    hdrs = ["linear_diophantine.h"],
    deps = [
        ":ext_gcd",
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
    name = "uint256",
    hdrs = ["uint256.h"],
)
