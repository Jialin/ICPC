load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "z_function_macros",
    hdrs = ["z_function_macros.h"],
)

cc_library(
    name = "z_function",
    hdrs = ["z_function.h"],
    deps = [
        ":z_function_macros",
        "//common:macros",
    ],
)
