/****************************************************************************
 * Copyright (C) 2010
 * by Dimok
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any
 * damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any
 * purpose, including commercial applications, and to alter it and
 * redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you
 * must not claim that you wrote the original software. If you use
 * this software in a product, an acknowledgment in the product
 * documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and
 * must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 *
 * for WiiXplorer 2010
 ***************************************************************************/
#ifndef DEVICE_HANDLER_HPP_
#define DEVICE_HANDLER_HPP_

#include "PartitionHandle.h"

enum
{
    SD = 0,
    USB1,
    USB2,
    USB3,
    USB4,
    USB5,
    USB6,
    USB7,
    USB8,
    GCSDA,
    GCSDB,
    MAXDEVICES
};

const char DeviceName[MAXDEVICES][6] =
{
    "sd",
    "usb1",
    "usb2",
    "usb3",
    "usb4",
    "usb5",
    "usb6",
    "usb7",
    "usb8",
    "gca",
    "gcb",
};

class DeviceHandler
{
    public:
		static DeviceHandler * Instance();
		static void DestroyInstance();

        bool MountAll();
        void UnMountAll();
        bool Mount(int dev);
        bool IsInserted(int dev);
        void UnMount(int dev);

        //! Individual Mounts/UnMounts...
		bool MountSD();
		bool MountUSB(int part);
		bool MountAllUSB();
		bool MountGCA();
		bool MountGCB();

		bool SD_Inserted() { if(sd) return sd->IsInserted(); return false; };
		bool USB_Inserted() { if(usb) return usb->IsInserted(); return false; };
		bool GCA_Inserted() { if(gca) return gca->IsInserted(); return false; };
		bool GCB_Inserted() { if(gcb) return gcb->IsInserted(); return false; };

		void UnMountSD() { if(sd) delete sd; sd = NULL; };
		void UnMountUSB(int pos);
		void UnMountAllUSB();
		void UnMountGCA() { if(gca) delete gca; gca = NULL; };
		void UnMountGCB() { if(gcb) delete gcb; gcb = NULL; };

		const PartitionHandle * GetSDHandle() { return sd; };
		const PartitionHandle * GetUSBHandle() { return usb; };
		const PartitionHandle * GetGCAHandle() { return gca; };
		const PartitionHandle * GetGCBHandle() { return gcb; };

		static bool SetWatchdog(unsigned int timeout);
		static int PathToDriveType(const char * path);
        static const char * GetFSName(int dev);
		static int GetFSType(int dev);
		s16 GetMountedCount(int dev);
        static const char * PathToFSName(const char * path) { return GetFSName(PathToDriveType(path)); };
		static wbfs_t * GetWbfsHandle(int dev);
		//static u32 GetLBAStart(int dev);
		s32 Open_WBFS(int dev);

    private:
        DeviceHandler() : sd(0), usb(0), gca(0), gcb(0) { };
        ~DeviceHandler();
		static bool InternalSetWatchdog(unsigned int timeout);

		static DeviceHandler * instance;
		static unsigned int watchdog_timeout;

        PartitionHandle * sd;
        PartitionHandle * usb;
        PartitionHandle * gca;
        PartitionHandle * gcb;
};

#endif
