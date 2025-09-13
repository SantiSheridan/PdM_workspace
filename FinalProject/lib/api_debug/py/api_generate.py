import os
import sys
import argparse
import jinja2 as jinja
import importlib
import re
from api_types import argTypes
import def_functions as f

def parse_functions():
    funcDict = {}
    func_id = 0
    for name, vals in f.functions.items():
        args = [arg for arg in vals['args']] # [addr, value]
        nargs = len(vals['args']) # 2
        arg_types = [vals['args'][arg]['type'] for arg in args] # [U32, U32]
        arg_lens = [argTypes[argType]['len'] for argType in arg_types] # [4, 4]
        arg_count = [vals['args'][arg]['count'] for arg in args]
        cargs = [argTypes[argType]['carg'] for argType in arg_types] # [u32, u32]

        wargs = []
        rargs = []
        for i in range(nargs):
            if arg_types[i].startswith("PR"):
                rargs.append(args[i])
            else:
                wargs.append(args[i])

        funcDict[name] = {
            'id':func_id,               # 0
            'args':args,                # [addr, value]
            'nargs':nargs,              # 2
            'wargs':wargs,              # [addr]
            'rargs':rargs,              # [value]
            'arg_types':arg_types,      # [U32, PR_U32]
            'arg_lens':arg_lens,        # [4, 4]
            'arg_count':arg_count,      # [1, 1]
            'cargs':cargs               # [u32, u32 *]
        }
        func_id+=1

    return funcDict

def generate_c():
    funcDict = parse_functions()
    env = jinja.Environment(loader=jinja.FileSystemLoader('.'))
    template = env.get_template('api_functions_c.jinja')

    output = template.render(funcDict=funcDict)
    print(funcDict)
    with open('functions_fptrs.c', 'w') as f:
        f.write(output)

def generate_py():
    funcDict = parse_functions()
    env = jinja.Environment(loader=jinja.FileSystemLoader('.'))
    template = env.get_template('api_functions_py.jinja')

    output = template.render(funcDict=funcDict)
    with open('function_fptrs.py', 'w') as f:
        f.write(output)


    
