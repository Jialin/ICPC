load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "base_fenwick_2d_array_macros",
    hdrs = ["base_fenwick_2d_array_macros.h"],
)

cc_library(
    name = "base_fenwick_2d_array",
    hdrs = ["base_fenwick_2d_array.h"],
    deps = ["//common:macros"],
)

cc_library(
    name = "base_fenwick_macros",
    hdrs = ["base_fenwick_macros.h"],
)

cc_library(
    name = "base_fenwick",
    hdrs = ["base_fenwick.h"],
)

cc_library(
    name = "fenwick_2d_array_sum",
    hdrs = ["fenwick_2d_array_sum.h"],
    deps = [
        ":base_fenwick_2d_array",
        ":base_fenwick_2d_array_macros",
    ],
)

cc_library(
    name = "fenwick_sum",
    hdrs = ["fenwick_sum.h"],
    deps = [
        ":base_fenwick",
        ":base_fenwick_macros",
    ],
)
