load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "bitset",
    hdrs = ["bitset.h"],
)

cc_library(
    name = "hashset",
    hdrs = ["hashset.h"],
    deps = [
        ":vector2d",
        "//math/mod:fix",
    ],
)

cc_library(
    name = "unique_counter",
    hdrs = ["unique_counter.h"],
)

cc_library(
    name = "vector2d",
    hdrs = ["vector2d.h"],
)
