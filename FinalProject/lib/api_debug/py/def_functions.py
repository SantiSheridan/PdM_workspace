defines = {}
enums = {}

functions = {
    'register_set' : {
        'type': 'function',
        'returns': 'retType',
        'comment': '',
        'args': {
            'addr' : {
                'type': 'U32',
                'count': 1,
                'comment':''
            },
            'value': {
                'type': 'U32',
                'count': 1,
                'comment':''
            }
        }
    },
    'register_get' : {
        'type': 'function',
        'returns': 'retType',
        'comment': '',
        'args': {
            'addr' : {
                'type': 'U32',
                'count':1,
                'comment':''
            },
            'value': {
                'type': 'PR_U32',
                'count' : 1,
                'comment':''
            }
        }
    },
    'suma' : {
        'type': 'function',
        'returns': 'retType',
        'comment': '',
        'args': {
            'valu8' : {
                'type': 'U8',
                'count': 1,
                'comment':''
            },
            'valu16': {
                'type': 'U16',
                'count':1,
                'comment':''
            },
            'resultado': {
                'type':'PR_U32',
                'count' : 1,
                'comment':''
            }
        }
    }
}