from math_.floor_div import FloorDivMustache
from mustache import AbstractMustache


class ConvexHullTricksMonoAddQueryMustache(AbstractMustache):
  def templateFile(self):
    return 'collections_/convex_hull_tricks/'\
        'convex_hull_tricks_mono_add_query.mustache'

  def partials(self):
    return {'floor_div': FloorDivMustache().genText()}

  def outputFile(self):
    return 'collections/convex_hull_tricks/' \
        '{{MinMax}}ConvexHullTricksAdd{{addOrder}}Query{{queryOrder}}' \
        'ConvexHullTricks.cpp'


JOBS = [(ConvexHullTricksMonoAddQueryMustache('collections'),
         [{'MinMax': 'Min', 'AddOrder': 'Decreasing', 'QueryOrder': 'Increasing'}])]
