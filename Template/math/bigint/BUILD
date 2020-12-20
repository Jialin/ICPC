load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "bigint",
    hdrs = ["bigint.h"],
    deps = [
        ":bigint_macros",
        "//debug:debug_basic",
        "//io:write_int",
        "//math:pow10",
    ],
)

cc_library(
    name = "bigint_macros",
    hdrs = ["bigint_macros.h"],
)
