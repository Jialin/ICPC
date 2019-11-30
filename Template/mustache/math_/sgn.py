from mustache import AbstractMustache


class SgnMustache(AbstractMustache):
  def templateFile(self):
    return 'math_/sgn.mustache'

  def partials(self):
    return {}

  def outputFile(self):
    return 'math/sgn.cpp'


JOBS = [(SgnMustache('math'), [{}])]
