load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "write_char",
    hdrs = ["write_char.h"],
)

cc_library(
    name = "write_int",
    hdrs = ["write_int.h"],
    deps = [":write_char"],
)
