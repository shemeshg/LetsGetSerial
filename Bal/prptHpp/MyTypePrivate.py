import ImportScript
from propertyLib import create_prpt, PrptClass, EnumClass


ary = [
    create_prpt("QString", 'statusText',
                init_val = '{"Not connected"}',
                is_writable  = True,
                is_notify = True, 
                is_list = False
                ),
    create_prpt("SettingsConn *", 'settingsConn', is_writable=False, init_val = "= new SettingsConn(this)"),
    create_prpt("ConnStatus", 'connStatus', init_val = "= ConnStatus::NOT_CONNECTED"),
]

enumClasss = [    EnumClass("ConnStatus",
        [
            "NOT_CONNECTED",
            "CONNECTED",
            "ERR"
        ])]

prptClass = PrptClass("MyTypePrivate", ary, enumClasss)
