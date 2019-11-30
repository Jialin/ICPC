from mustache import AbstractMustache


class FloorDivMustache(AbstractMustache):
  def templateFile(self):
    return 'math_/floor_div.mustache'

  def partials(self):
    return {}

  def outputFile(self):
    return 'math/floor_div.cpp'


JOBS = [(FloorDivMustache('math'), [{}])]
