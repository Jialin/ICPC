load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "base_sliding_window_macros",
    hdrs = ["base_sliding_window_macros.h"],
)

cc_library(
    name = "base_sliding_window",
    hdrs = ["base_sliding_window.h"],
    deps = [
        ":base_sliding_window_macros",
        "//common:macros",
    ],
)

cc_library(
    name = "max_sliding_window",
    hdrs = ["max_sliding_window.h"],
    deps = [":base_sliding_window"],
)
