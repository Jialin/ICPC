load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "kitamasa_and_xor",
    hdrs = ["kitamasa_and_xor.h"],
    deps = [
        "//debug",
    ],
)

cc_library(
    name = "kitamasa_once",
    hdrs = ["kitamasa_once.h"],
    deps = [
        "//debug",
        "//math/mod:accumulator",
        "//math/mod:add",
        "//math/mod:fix",
        "//math/mod:mul",
    ],
)

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
