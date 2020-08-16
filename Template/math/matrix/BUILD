load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "matrix_fix_inline",
    hdrs = ["matrix_fix_inline.h"],
    deps = [
        ":matrix",
        "//math/mod:fix_inline",
    ],
)

cc_library(
    name = "matrix_mod_exp_utils",
    hdrs = ["matrix_mod_exp_utils.h"],
    deps = [
        ":matrix",
        ":matrix_fix_inline",
        ":matrix_mul_inline",
        "//math/mod:slight_fix",
    ],
)

cc_library(
    name = "matrix_mul_inline",
    hdrs = ["matrix_mul_inline.h"],
    deps = [
        ":matrix",
        ":matrix_fix_inline",
        "//math/mod:add",
        "//math/mod:mul_safe",
    ],
)

cc_library(
    name = "matrix",
    hdrs = ["matrix.h"],
)
