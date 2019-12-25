from math_.floor_div import FloorDivMustache
from mustache import AbstractMustache


class ConvexHullTricksMonoAddMustache(AbstractMustache):
  def templateFile(self):
    return 'collections_/convex_hull_tricks/' \
        'convex_hull_tricks_mono_add.mustache'

  def partials(self):
    return {'floor_div': FloorDivMustache().genText()}

  def outputFile(self):
    return 'collections/convex_hull_tricks/' \
        '{{#minmax}}{{v}}{{/minmax}}_convex_hull_tricks_' \
        'add_{{#incdec}}{{v}}{{/incdec}}.cpp'


JOBS = [(ConvexHullTricksMonoAddMustache('collections'),
         [{'container': {'v': 'vector', 'reserve': True},
           'minmax': {'v': 'min', 'cap': 'Min', 'cmp': '<', 'inf_rev': 'max'},
           'frontback': {'v': 'back', 'cmp': '<', 'inf': 'min'},
           'incdec': {'v': 'decreasing', 'cap': 'Decreasing'}}])]
