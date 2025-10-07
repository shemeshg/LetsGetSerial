import ImportScript
from propertyLib import create_prpt, PrptClass


ary = [
    create_prpt("QString", 'name',
                init_val = '{"The backend init val"}',
                is_writable  = False, 
                is_notify = True, 
                is_list = False
                ),
    create_prpt("SettingsConn *", 'settingsConn', is_writable=False, init_val = "= new SettingsConn(this)"),
]

enumClasss = []

prptClass = PrptClass("MyTypePrivate", ary, enumClasss)
