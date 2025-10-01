import ImportScript
from CMakeCogLib import *

def getCmake():
    s = []
    cmc = CMakeCog("Bal")


    genApp = GenHpp(cmc.exeName)
    genApp.makeDirectories = ["${CMAKE_CURRENT_BINARY_DIR}/hpp"]
    genApp.hppGenFilesTemplates = ["${CMAKE_SOURCE_DIR}/scripts/hppTemplates.txt"]
    genApp.hppGenFilesGlobes = ['hpp/*.hpp']
    genApp.parseHppPyPath = "${CMAKE_SOURCE_DIR}/scripts/parseHpp.py"


    s.append(genApp.getStr())

    cmc.libFilesExtendCppAndH([''])

    cmc.libFiles.extend(genApp.getDefineFiles("${CMAKE_CURRENT_BINARY_DIR}/"))


    s.append(cmc.add_library())


    s.append(genApp.add_dependencies())
    return "\n".join(s)

print(getCmake())
