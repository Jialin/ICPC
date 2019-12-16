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
        '{{minmax}}_convex_hull_tricks_'\
        'add_{{addorder}}_query_{{queryorder}}.cpp'


JOBS = [(ConvexHullTricksMonoAddQueryMustache('collections'),
         [{'MinMax': 'Min', 'AddOrder': 'Decreasing', 'QueryOrder': 'Increasing', 'minmax': 'min', 'addorder': 'decreasing', 'queryorder': 'increasing'}])]
