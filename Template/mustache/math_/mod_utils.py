from mustache import AbstractMustache


class ModUtilMustache(AbstractMustache):
    def templateFile(self):
        return "math_/mod_utils.mustache"

    def partials(self):
        return {}

    def outputFile(self):
        return (
            "math/mod_operators/mod_utils"
            "{{#fix.v}}_fix{{/fix.v}}"
            "{{#add.v}}_add{{/add.v}}"
            "{{#addi.v}}_addi{{/addi.v}}"
            "{{#sub.v}}_sub{{/sub.v}}"
            "{{#mul.v}}_mul{{/mul.v}}"
            "{{#muli.v}}_muli{{/muli.v}}"
            "{{#exp.v}}_exp{{/exp.v}}"
            "{{#div.v}}_div{{/div.v}}"
            ".h"
        )


def variables(
    fix=False,
    add=False,
    addi=False,
    sub=False,
    mul=False,
    muli=False,
    exp=False,
    div=False,
):
    return {
        "fix": {"v": fix},
        "add": {"v": add},
        "addi": {"v": addi},
        "sub": {"v": sub},
        "mul": {"v": mul},
        "muli": {"v": muli},
        "exp": {"v": exp},
        "div": {"v": div},
    }


JOBS = [(ModUtilMustache(""), [variables(fix=True, add=True, sub=True, mul=True)])]
