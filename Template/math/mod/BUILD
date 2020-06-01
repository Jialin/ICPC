load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "add",
    hdrs = ["add.h"],
    deps = [
        ":fix_inline",
    ],
)

cc_library(
    name = "exp",
    hdrs = ["exp.h"],
    deps = [
        ":mul",
    ],
)

cc_library(
    name = "fix_inline",
    hdrs = ["fix_inline.h"],
    deps = [":slight_fix_inline"],
)

cc_library(
    name = "fix",
    hdrs = ["fix.h"],
    deps = [":fix_inline"],
)

cc_library(
    name = "inv",
    hdrs = ["inv.h"],
    deps = [
        ":slight_fix_inline",
        "//math:ext_gcd",
    ],
)

cc_library(
    name = "mod_exp_utils",
    hdrs = ["mod_exp_utils.h"],
    deps = [
        ":fix_inline",
        ":mul_inline",
    ],
)

cc_library(
    name = "mul_inline",
    hdrs = ["mul_inline.h"],
    deps = [":fix_inline"],
)

cc_library(
    name = "mul",
    hdrs = ["mul.h"],
    deps = [":mul_inline"],
)

cc_library(
    name = "slight_fix_inline",
    hdrs = ["slight_fix_inline.h"],
)

cc_library(
    name = "sub",
    hdrs = ["sub.h"],
    deps = [
        ":fix_inline",
    ],
)