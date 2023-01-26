name = "krita"

authors = [
    "KDE Krita"
]

# NOTE: version = <external_version>.sse.<sse_version>
version = "4.4.8.sse.1.0.0"

description = \
    """
    Krita
    """

with scope("config") as c:
    # Determine location to release: internal (int) vs external (ext)

    # NOTE: Modify this variable to reflect the current package situation
    release_as = "ext"

    # The `c` variable here is actually rezconfig.py
    # `release_packages_path` is a variable defined inside rezconfig.py

    import os
    if release_as == "int":
        c.release_packages_path = os.environ["SSE_REZ_REPO_RELEASE_INT"]
    elif release_as == "ext":
        c.release_packages_path = os.environ["SSE_REZ_REPO_RELEASE_EXT"]

    #c.build_thread_count = "physical_cores"

requires = [
    #"qt-5.15.2",
    "PyQt5",
    "PyQt5_Qt5",
    "PyQt5_sip",
    "boost-1.70",
    "libpng",
    "libtiff",
    "libjpeg",
    "kSeExpr",
    "lcms",
    "exiv2",
    "eigen",
    "vc",
    "quazip",
    "openexr-2.2.0",
    "ocio-1.0.9",
]

private_build_requires = [
    "ecm",
]

variants = [
    ["platform-linux", "arch-x86_64", "os-centos-7", "python-3.9"],
]

# Pass cmake arguments:
# rez-build -i -- -DBoost_NO_BOOST_CMAKE=On -DBoost_NO_SYSTEM_PATHS=True
# rez-release -- -DBoost_NO_BOOST_CMAKE=On -DBoost_NO_SYSTEM_PATHS=True

def pre_build_commands():
    command("source /opt/rh/devtoolset-6/enable")

def commands():

    # NOTE: REZ package versions can have ".sse." to separate the external
    # version from the internal modification version.
    split_versions = str(version).split(".sse.")
    external_version = split_versions[0]
    internal_version = None
    if len(split_versions) == 2:
        internal_version = split_versions[1]

    env.KRITA_VERSION = external_version
    env.KRITA_PACKAGE_VERSION = external_version
    if internal_version:
        env.KRITA_PACKAGE_VERSION = internal_version

    env.KRITA_ROOT.append("{root}")
    env.KRITA_LOCATION.append("{root}")

    env.PATH.append("{root}/bin")
    env.QT_QPA_FONTDIR = "/usr/share/X11/fonts/Type1/"

uuid = "repository.krita"
