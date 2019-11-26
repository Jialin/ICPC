from abc import ABC, abstractmethod
from os import environ, path
from subprocess import call

from pymustache import render

HOME = environ['ICPC_HOME']


def loadFileContent(filePath):
  with open(filePath, 'r') as file:
    return ''.join(file.readlines())


def loadFileContentSilent(filePath):
  try:
    return loadFileContent(filePath)
  except FileNotFoundError:
    return ''


class AbstractMustache(ABC):

  def __init__(self, namespace=None):
    self.namespace = namespace

  @abstractmethod
  def templateFile(self):
    pass

  @abstractmethod
  def partials(self):
    pass

  @abstractmethod
  def outputFile(self):
    pass

  def genText(self, context={}):
    rawContent = loadFileContent(self.templateFile())
    if self.namespace:
      rawContent = '''namespace {namespace} {{

{rawContent}
}} // namespace {namespace}'''.format(namespace=self.namespace, rawContent=rawContent)
    return render(rawContent, context, partials=self.partials())

  def genFile(self, context={}):
    fileName = render(self.outputFile(), context)
    filePath = path.join(HOME, 'Template', fileName)
    oldContent = loadFileContentSilent(filePath)
    file = open(filePath, 'w')
    file.write('// @autogen\n' + self.genText(context))
    file.close()
    call(['clang-format', '-i', filePath])
    newContent = loadFileContentSilent(filePath)
    if oldContent != newContent:
      print(fileName + " updated.")
