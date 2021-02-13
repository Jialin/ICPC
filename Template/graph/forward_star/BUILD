load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "forward_star_edge_weighted_macros",
    hdrs = ["forward_star_edge_weighted_macros.h"],
    deps = [":forward_star_macros"],
)

cc_library(
    name = "forward_star_edge_weighted",
    hdrs = ["forward_star_edge_weighted.h"],
    deps = [
        ":forward_star",
        ":forward_star_edge_weighted_macros",
        "//common:macros",
        "//debug:debug_basic",
    ],
)

cc_library(
    name = "forward_star_macros",
    hdrs = ["forward_star_macros.h"],
)

cc_library(
    name = "forward_star",
    hdrs = ["forward_star.h"],
    deps = [":forward_star_macros"],
)
