load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "ext_gcd",
    hdrs = ["ext_gcd.h"],
    deps = [
        "//debug",
    ],
)

cc_library(
    name = "gcd",
    hdrs = ["gcd.h"],
    deps = [
        "//math/bit:ctz",
    ],
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
        "//math:ctz128",
    ],
)
