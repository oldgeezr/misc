################################################################################
#
# xlib_libICE -- X.Org ICE library
#
################################################################################

XLIB_LIBICE_VERSION = 1.0.6
XLIB_LIBICE_SOURCE = libICE-$(XLIB_LIBICE_VERSION).tar.bz2
XLIB_LIBICE_SITE = http://xorg.freedesktop.org/releases/individual/lib
XLIB_LIBICE_AUTORECONF = NO
XLIB_LIBICE_LIBTOOL_PATCH = NO
XLIB_LIBICE_INSTALL_STAGING = YES
XLIB_LIBICE_DEPENDENCIES = xlib_xtrans xproto_xproto
XLIB_LIBICE_CONF_OPT = --enable-shared --disable-static

$(eval $(call AUTOTARGETS,package/x11r7,xlib_libICE))
