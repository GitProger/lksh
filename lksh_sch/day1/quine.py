def escape(s):
    return s.translate(str.maketrans({
        "'": "\\'",
        "\"": "\\\"",
        "\\": "\\\\",
        "\n": "\\n"
    }))    

def get_src():
    r = 'def escape(s):\n    return s.translate(str.maketrans({\n        \"\'\": \"\\\\\'\",\n        \"\\\"\": \"\\\\\\\"\",\n        \"\\\\\": \"\\\\\\\\\",\n        \"\\n\": \"\\\\n\"\n    }))    \n\ndef get_src():\n    r = \'$\'\n    r = r.replace(r, escape(r))\n    return r;\n	\nprint(get_src())\n'
    r = r.replace('$', escape(r))
    return r;
	
print(get_src())
