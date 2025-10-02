from property import create_prpt, PrptClass


ary = [
    create_prpt("QString", 'name',
                init_val = '{"The backend init val"}',
                is_writable  = False, 
                is_notify = True, 
                is_list = False
                ),
]

enumClasss = []

prptClass = PrptClass("MyTypePrivate", ary, enumClasss)