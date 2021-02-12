load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "forward_star_macros",
    hdrs = ["forward_star_macros.h"],
)

cc_library(
    name = "forward_star",
    hdrs = ["forward_star.h"],
    deps = [":forward_star_macros"],
)
