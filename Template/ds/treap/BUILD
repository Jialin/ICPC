load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "base_treap_macros",
    hdrs = ["base_treap_macros.h"],
)

cc_library(
    name = "base_treap",
    hdrs = ["base_treap.h"],
    deps = [
        "//common:macros",
        "//debug:debug_basic",
    ],
)

cc_library(
    name = "treap_set",
    hdrs = ["treap_set.h"],
    deps = [":base_treap"],
)

cc_library(
    name = "treap_sum",
    hdrs = ["treap_sum.h"],
    deps = [":base_treap"],
)
