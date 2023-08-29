# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include".split(';') if "${prefix}/include" != "" else []
PROJECT_CATKIN_DEPENDS = "roscpp;rospy;std_msgs;enu_msgs".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-llla2enu".split(';') if "-llla2enu" != "" else []
PROJECT_NAME = "lla2enu"
PROJECT_SPACE_DIR = "/usr/local"
PROJECT_VERSION = "0.0.0"
