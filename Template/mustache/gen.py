import os
import sys

from collections_.convex_hull_tricks.convex_hull_tricks import (
    JOBS as collectionsConvexHullTricksJobs,
)
from collections_.convex_hull_tricks.convex_hull_tricks_mono_add import (
    JOBS as collectionsConvexHullTricksMonoAddJobs,
)
from collections_.convex_hull_tricks.convex_hull_tricks_mono_add_query import (
    JOBS as collectionsConvexHullTricksMonoAddQueryJobs,
)
from collections_.convex_hull_tricks.li_chao_tree_known_queries import (
    JOBS as collectionsConvexHullTricksLiChaoTreeKnownQueries,
)
from math_.floor_div import JOBS as mathFloorDivJobs
from math_.mod_utils import JOBS as mathModUtilJobs
from math_.sgn import JOBS as mathSgnJobs
from math_.sgn_fraction import JOBS as mathSgnFractionJobs
from math_.sgn_product_unsigned import JOBS as mathSgnProductUnsignedJobs

ALL_JOBS = [
    collectionsConvexHullTricksJobs,
    collectionsConvexHullTricksMonoAddQueryJobs,
    collectionsConvexHullTricksMonoAddJobs,
    collectionsConvexHullTricksLiChaoTreeKnownQueries,
    mathFloorDivJobs,
    mathModUtilJobs,
    mathSgnJobs,
    mathSgnFractionJobs,
    mathSgnProductUnsignedJobs,
]

for jobs in ALL_JOBS:
    for mustache, contexts in jobs:
        for context in contexts:
            # print("Handling mustache:{} context:{}".format(mustache, context))
            mustache.genFile(context)
