import qbs 1.0

Project {

    Application {
        id: applicationId
        name: "Cavewhere Sketch"

        Depends { name: "cpp" }
        Depends { name: "Qt";
            submodules: [ "core",
                "gui",
                "widgets",
                "bluetooth"
            ]
        }

        Qt.core.buildVariant: [
            "debug"
        ]

        cpp.includePaths: [
            "src"
        ]

        cpp.rpaths: [
            "/Users/vpicaver/Documents/Projects/qt5/qtbase/lib/"
        ]

        files: [
            "src/*.cpp",
            "src/*.h"
        ]
    }
}
