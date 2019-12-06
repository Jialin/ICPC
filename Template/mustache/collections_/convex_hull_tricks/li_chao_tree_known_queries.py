from math_.floor_div import FloorDivMustache
from mustache import AbstractMustache


class LiChaoTreeKnownQueriesMustache(AbstractMustache):
  def templateFile(self):
    return 'collections_/convex_hull_tricks/li_chao_tree_known_queries.mustache'

  def partials(self):
    return {'floor_div': FloorDivMustache().genText()}

  def outputFile(self):
    return 'collections/convex_hull_tricks/{{minMax}}_li_chao_tree_known_queries.cpp'


JOBS = [(LiChaoTreeKnownQueriesMustache('collections'),
         [{'minMax': 'max', 'MinMax': 'Max', 'lessOp': '<'},
          {'minMax': 'min', 'MinMax': 'Min', 'lessOp': '>'}])]
