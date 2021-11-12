load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "base_disjoint_set_value_macros",
    hdrs = ["base_disjoint_set_value_macros.h"],
)

cc_library(
    name = "base_disjoint_set_value",
    hdrs = ["base_disjoint_set_value.h"],
    deps = ["//common:macros"],
)

cc_library(
    name = "disjoint_set_groups_macros",
    hdrs = ["disjoint_set_groups_macros.h"],
)

cc_library(
    name = "disjoint_set_groups",
    hdrs = ["disjoint_set_groups.h"],
)

cc_library(
    name = "disjoint_set_macros",
    hdrs = ["disjoint_set_macros.h"],
)

cc_library(
    name = "disjoint_set_max",
    hdrs = ["disjoint_set_max.h"],
    deps = [":base_disjoint_set_value"],
)

cc_library(
    name = "disjoint_set_min_max",
    hdrs = ["disjoint_set_min_max.h"],
    deps = [":base_disjoint_set_value"],
)

cc_library(
    name = "disjoint_set_parity_macros",
    hdrs = ["disjoint_set_parity_macros.h"],
)

cc_library(
    name = "disjoint_set_parity",
    hdrs = ["disjoint_set_parity.h"],
)

cc_library(
    name = "disjoint_set",
    hdrs = ["disjoint_set.h"],
)
