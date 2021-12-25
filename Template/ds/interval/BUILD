load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "base_grouping_intervals_container",
    hdrs = ["base_grouping_intervals_container.h"],
)

cc_library(
    name = "base_intervals_container_macros",
    hdrs = ["base_intervals_container_macros.h"],
)

cc_library(
    name = "base_intervals_container",
    hdrs = ["base_intervals_container.h"],
    deps = [
        ":base_intervals_container_macros",
    ],
)
