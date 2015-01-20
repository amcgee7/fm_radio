/*
 * Copyright 2014 Collabora Ltd.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 *  Author : Frederic Plourde <frederic.plourde@collabora.co.uk>
 */

#define FM_RADIO_SERVICE_DBUS_NAME  "com.jlr.fmradioservice"
#define FM_RADIO_SERVICE_DBUS_PATH  "/com/jlr/fmradioservice"
#define FM_RADIO_SERVICE_DBUS_IFACE "com.jlr.fmradioservice"

/* Symbolic constants for the signal names to use with GLib.
   These need to map into the D-Bus signal names. */
#define SIGNAL_ON_ENABLED           "onenabled"
#define SIGNAL_ON_DISABLED          "ondisabled"
#define SIGNAL_ON_ANTENNA_CHANGED   "onantennachanged"
#define SIGNAL_ON_FREQUENCY_CHANGED "onfrequencychanged"
