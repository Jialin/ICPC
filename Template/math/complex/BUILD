load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "complex_macros",
    hdrs = ["complex_macros.h"],
)

cc_library(
    name = "complex",
    hdrs = ["complex.h"],
    deps = [":complex_macros"],
)
