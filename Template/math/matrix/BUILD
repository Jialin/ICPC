load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "kitamasa",
    hdrs = ["kitamasa.h"],
    deps = [
        "//debug",
        "//math/mod:add",
        "//math/mod:fix",
        "//math/mod:mul",
    ],
)

cc_library(
    name = "matrix_array",
    hdrs = ["matrix_array.h"],
)

cc_library(
    name = "matrix_fix_inline",
    hdrs = ["matrix_fix_inline.h"],
    deps = [
        ":matrix_vector",
        "//math/mod:fix_inline",
    ],
)

cc_library(
    name = "matrix_mod_exp_utils",
    hdrs = ["matrix_mod_exp_utils.h"],
    deps = [
        ":matrix_fix_inline",
        ":matrix_mul_inline",
        ":matrix_vector",
        "//math/mod:slight_fix",
    ],
)

cc_library(
    name = "matrix_mul_inline",
    hdrs = ["matrix_mul_inline.h"],
    deps = [
        ":matrix_fix_inline",
        ":matrix_vector",
        "//math/mod:add",
        "//math/mod:mul_safe",
    ],
)

cc_library(
    name = "matrix_vector",
    hdrs = ["matrix_vector.h"],
)
