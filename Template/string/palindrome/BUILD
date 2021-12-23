load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "manacher_macros",
    hdrs = ["manacher_macros.h"],
)

cc_library(
    name = "manacher",
    hdrs = ["manacher.h"],
    deps = [
        ":manacher_macros",
        "//common:macros",
    ],
)
