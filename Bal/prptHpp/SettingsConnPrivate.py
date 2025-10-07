import ImportScript
from propertyLib import create_prpt, PrptClass


ary = [
    create_prpt("QString", 'serialPortName',
                init_val = '{""}',
                is_writable  = True,
                is_notify = True,
                is_list = False
                ),
    create_prpt("int", 'baudRate',
                init_val = "{9600}",
                is_writable  = True,
                is_notify = True, 
                is_list = False
                ),
    create_prpt("int", 'dataBits',
                init_val = '{8}',
                is_writable  = True,
                is_notify = True,
                is_list = False
                ),
    create_prpt("int", 'parity',
                init_val = '{0}',
                is_writable  = True,
                is_notify = True,
                is_list = False
                ),
    create_prpt("int", 'stopBits',
                init_val = '{1}',
                is_writable  = True,
                is_notify = True,
                is_list = False
                ),
    create_prpt("int", 'flowControl',
                init_val = '{0}',
                is_writable  = True,
                is_notify = True,
                is_list = False
                ),
    create_prpt("bool", 'isLocalEcho',
                init_val = '{true}',
                is_writable  = True,
                is_notify = True,
                is_list = False
                ),
]

enumClasss = []

prptClass = PrptClass("SettingsConnPrivate", ary, enumClasss)
