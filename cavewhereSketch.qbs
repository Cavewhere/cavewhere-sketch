import qbs 1.0

Project {

    Application {
        id: applicationId
        name: "Cavewhere Sketch"

        Depends { name: "cpp" }
        Depends { name: "Qt";
            submodules: [ "core",
                "gui",
                "widgets"]
        }

        cpp.includePaths: [
            "src"
        ]

        files: [
            "src/*.cpp",
            "src/*.h"
        ]
    }
}
