load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "base_treap_forest_macros",
    hdrs = ["base_treap_forest_macros.h"],
)

cc_library(
    name = "base_treap_forest",
    hdrs = ["base_treap_forest.h"],
    deps = [
        ":base_treap",
        "//common:macros",
        "//debug:debug_basic",
    ],
)

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
    name = "treap_forest_set_macros",
    hdrs = ["treap_forest_set_macros.h"],
)

cc_library(
    name = "treap_forest_set",
    hdrs = ["treap_forest_set.h"],
    deps = [
        ":base_treap_forest",
        ":base_treap_forest_macros",
        ":base_treap_macros",
    ],
)

cc_library(
    name = "treap_multiset_macros",
    hdrs = ["treap_multiset_macros.h"],
    deps = [":base_treap_macros"],
)

cc_library(
    name = "treap_multiset",
    hdrs = ["treap_multiset.h"],
    deps = [":base_treap"],
)

cc_library(
    name = "treap_set_macros",
    hdrs = ["treap_set_macros.h"],
    deps = [":base_treap_macros"],
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
