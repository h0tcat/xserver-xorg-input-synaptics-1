/*
 *   Copyright 2004 Peter Osterlund <petero2@telia.com>
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation; either version 2
 *   of the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */
#ifndef _SYNPROTO_H_
#define _SYNPROTO_H_

#include <sys/ioctl.h>
#include <xf86Xinput.h>

/*
 * A structure to describe the state of the touchpad hardware (buttons and pad)
 */
struct SynapticsHwState {
    int millis;			/* Timestamp in milliseconds */
    int x;			/* X position of finger */
    int y;			/* Y position of finger */
    int z;			/* Finger pressure */
    int numFingers;
    int fingerWidth;

    Bool left;
    Bool right;
    Bool up;
    Bool down;

    Bool multi[8];
    Bool middle;		/* Some ALPS touchpads have a middle button */

    Bool guest_left;		/* guest device */
    Bool guest_mid;
    Bool guest_right;
    int  guest_dx;
    int  guest_dy;
};


enum SynapticsProtocol {
    SYN_PROTO_PSAUX,		/* Raw psaux device */
    SYN_PROTO_EVENT		/* Linux kernel event interface */
};

struct synapticshw;
struct _SynapticsPrivateRec;
struct CommData;

struct SynapticsProtocolOperations {
    void (*DeviceOnHook)(LocalDevicePtr local);
    void (*DeviceOffHook)(LocalDevicePtr local);
    Bool (*QueryHardware)(LocalDevicePtr local, struct synapticshw *synhw);
    Bool (*ReadHwState)(LocalDevicePtr local, struct synapticshw *synhw,
			struct CommData *comm, struct SynapticsHwState *hwRet);
};

extern struct SynapticsProtocolOperations psaux_proto_operations;
extern struct SynapticsProtocolOperations event_proto_operations;


#endif /* _SYNPROTO_H_ */