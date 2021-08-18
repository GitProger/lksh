import sys, os
def escape(s):
    return s.translate(str.maketrans({
        "'": "\\'",
        "\"": "\\\"",
        "\\": "\\\\",
        "\n": "\\n"
    }))


for line in sys.stdin:
    print(escape(line), end="")
