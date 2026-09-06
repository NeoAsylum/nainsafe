import tomllib
P = "parameter.toml"
with open(P, "rb") as f:
    d = tomllib.load(f)

def flach(x, p=""):
    aus = {}
    for k, v in x.items():
        if isinstance(v, dict):
            aus.update(flach(v, p + k + "."))
        else:
            aus[p + k] = v
    return aus

fn = flach(d)
print(len(fn))
for k, v in fn.items():
    print(" ", k, "=", v)
