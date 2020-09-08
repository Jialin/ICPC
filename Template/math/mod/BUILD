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
    deps = [":mul_inline"],
)

cc_library(
    name = "exp_safe",
    hdrs = ["exp_safe.h"],
    deps = [
        ":fix_inline",
        ":mul_inline_safe",
    ],
)

cc_library(
    name = "exp128",
    hdrs = ["exp128.h"],
    deps = [
        "//math:montgomery_mul",
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
        "//debug",
        "//math/gcd:ext_gcd",
    ],
)

cc_library(
    name = "inv_all",
    hdrs = ["inv_all.h"],
    deps = [":mul"],
)

cc_library(
    name = "log",
    hdrs = ["log.h"],
    deps = [
        ":log_coprime",
        "//math/gcd",
    ],
)

cc_library(
    name = "log_coprime",
    hdrs = ["log_coprime.h"],
    deps = [
        ":exp",
        ":fix",
        ":mul",
    ],
)

cc_library(
    name = "mod_exp_utils",
    hdrs = ["mod_exp_utils.h"],
    deps = [
        ":fix_inline",
        ":mul_inline_safe",
    ],
)

cc_library(
    name = "mul",
    hdrs = ["mul.h"],
    deps = [":mul_inline"],
)

cc_library(
    name = "mul_safe",
    hdrs = ["mul_safe.h"],
    deps = [":mul_inline_safe"],
)

cc_library(
    name = "mul_inline",
    hdrs = ["mul_inline.h"],
)

cc_library(
    name = "mul_inline_safe",
    hdrs = ["mul_inline_safe.h"],
    deps = [
        ":add",
        ":fix_inline",
    ],
)

cc_library(
    name = "power_tower",
    hdrs = ["power_tower.h"],
    deps = [
        ":exp",
        ":fix",
    ],
)

cc_library(
    name = "slight_fix_inline",
    hdrs = ["slight_fix_inline.h"],
)

cc_library(
    name = "slight_fix",
    hdrs = ["slight_fix.h"],
)

cc_library(
    name = "sub",
    hdrs = ["sub.h"],
    deps = [
        ":fix_inline",
    ],
)
