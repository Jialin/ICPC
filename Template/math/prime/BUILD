load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "divisor",
    hdrs = ["divisor.h"],
    deps = [
        ":min_prime_tagger",
    ],
)

cc_library(
    name = "divisor64",
    hdrs = ["divisor64.h"],
    deps = [
        ":miller_rabin64",
        ":rho64",
    ],
)

cc_library(
    name = "factorize",
    hdrs = ["factorize.h"],
    deps = [
        ":min_prime_tagger",
    ],
)

cc_library(
    name = "factorize64",
    hdrs = ["factorize64.h"],
    deps = [
        ":miller_rabin64",
        ":rho64",
    ],
)

cc_library(
    name = "factorize128",
    hdrs = ["factorize128.h"],
    deps = [
        ":miller_rabin128",
        ":rho128",
    ],
)

cc_library(
    name = "miller_rabin64",
    hdrs = ["miller_rabin64.h"],
    deps = [
        "//math/mod:exp",
        "//math/mod:mul_inline",
    ],
)

cc_library(
    name = "miller_rabin128",
    hdrs = ["miller_rabin128.h"],
    deps = [
        "//math:ctz128",
        "//math:montgomery_mul",
        "//math/mod:exp128",
    ],
)

cc_library(
    name = "min_prime_tagger",
    hdrs = ["min_prime_tagger.h"],
)

cc_library(
    name = "phi_all",
    hdrs = ["phi_all.h"],
)

cc_library(
    name = "prime_checker",
    hdrs = ["prime_checker.h"],
)

cc_library(
    name = "prime_iterator",
    hdrs = ["prime_iterator.h"],
)

cc_library(
    name = "rho64",
    hdrs = ["rho64.h"],
    deps = [
        "//math:gcd64",
        "//math/mod:add",
        "//math/mod:mul_inline",
    ],
)

cc_library(
    name = "rho128",
    hdrs = ["rho128.h"],
    deps = [
        "//math:gcd128",
        "//math:montgomery_mul",
        "//math/mod:add",
    ],
)

cc_library(
    name = "segmented_prime_iterator",
    hdrs = ["segmented_prime_iterator.h"],
)
