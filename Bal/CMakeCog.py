import ImportScript
from CMakeCogLib import CMakeCog
from GenHpp import GenHpp

def getCmake():
    s = []
    cmc = CMakeCog("Bal")


    genHpp = GenHpp(cmc.exeName)
    genHpp.makeDirectories = ["${CMAKE_CURRENT_BINARY_DIR}/hpp", "${CMAKE_CURRENT_BINARY_DIR}/prptHpp"]
    genHpp.hppGenFilesTemplates = ["${CMAKE_SOURCE_DIR}/scripts/hppTemplates.txt"]
    genHpp.hppGenFilesGlobes = ['hpp/*.hpp','prptHpp/*.hpp']
    genHpp.parseHppPyPath = "${CMAKE_SOURCE_DIR}/scripts/parseHpp.py"


    s.append(genHpp.getStr())

    cmc.find_package_qt_components =["SerialPort"]
    s.append(cmc.find_package_qt())

    cmc.libFilesExtendCppAndH([''])

    cmc.libFiles.extend(genHpp.getDefineFiles("${CMAKE_CURRENT_BINARY_DIR}/"))
    cmc.targetIncludeDirs += genHpp.makeDirectories 



    s.append(cmc.add_library())
    s.append(cmc.add_qt6_add_qml_module())

    s.append(cmc.target_include_directories())
    s.append(cmc.target_link_libraries())

    s.append(genHpp.add_dependencies())
    return "\n".join(s)

#print(getCmake())
