load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "base_rmq_macros",
    hdrs = ["base_rmq_macros.h"],
)

cc_library(
    name = "base_rmq",
    hdrs = ["base_rmq.h"],
    deps = [
        ":base_rmq_macros",
        "//common:macros",
    ],
)

cc_library(
    name = "max_rmq",
    hdrs = ["max_rmq.h"],
    deps = [":base_rmq"],
)

cc_library(
    name = "min_rmq",
    hdrs = ["min_rmq.h"],
    deps = [":base_rmq"],
)
