/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * libqmi-glib -- GLib/GIO based library to control QMI devices
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 * Copyright (C) 2012 Lanedo GmbH <aleksander@lanedo.com>
 */

#ifndef _LIBQMI_GLIB_QMI_ENUMS_DMS_H_
#define _LIBQMI_GLIB_QMI_ENUMS_DMS_H_

/*****************************************************************************/
/* Helper enums for the 'QMI DMS Get Capabilities' message */

/**
 * QmiDmsDataServiceCapability:
 * @QMI_DMS_DATA_SERVICE_CAPABILITY_NONE: No data services supported.
 * @QMI_DMS_DATA_SERVICE_CAPABILITY_CS: Only CS supported.
 * @QMI_DMS_DATA_SERVICE_CAPABILITY_PS: Only PS supported.
 * @QMI_DMS_DATA_SERVICE_CAPABILITY_SIMULTANEOUS_CS_PS: Simultaneous CS and PS supported.
 * @QMI_DMS_DATA_SERVICE_CAPABILITY_NON_SIMULTANEOUS_CS_PS: Non simultaneous CS and PS supported.
 *
 * Data service capability.
 */
typedef enum {
    QMI_DMS_DATA_SERVICE_CAPABILITY_NONE                   = 0,
    QMI_DMS_DATA_SERVICE_CAPABILITY_CS                     = 1,
    QMI_DMS_DATA_SERVICE_CAPABILITY_PS                     = 2,
    QMI_DMS_DATA_SERVICE_CAPABILITY_SIMULTANEOUS_CS_PS     = 3,
    QMI_DMS_DATA_SERVICE_CAPABILITY_NON_SIMULTANEOUS_CS_PS = 4
} QmiDmsDataServiceCapability;

/**
 * QmiDmsSimCapability:
 * @QMI_DMS_SIM_CAPABILITY_NOT_SUPPORTED: SIM not supported.
 * @QMI_DMS_SIM_CAPABILITY_SUPPORTED: SIM is supported.
 *
 * SIM capability.
 */
typedef enum {
    QMI_DMS_SIM_CAPABILITY_NOT_SUPPORTED = 1,
    QMI_DMS_SIM_CAPABILITY_SUPPORTED     = 2
} QmiDmsSimCapability;

/**
 * QmiDmsRadioInterface:
 * @QMI_DMS_RADIO_INTERFACE_CDMA20001X: CDMA2000 1x.
 * @QMI_DMS_RADIO_INTERFACE_EVDO: CDMA2000 HRPD (1xEV-DO)
 * @QMI_DMS_RADIO_INTERFACE_GSM: GSM.
 * @QMI_DMS_RADIO_INTERFACE_UMTS: UMTS.
 * @QMI_DMS_RADIO_INTERFACE_LTE: LTE.
 *
 * Radio interface type.
 */
typedef enum {
    QMI_DMS_RADIO_INTERFACE_CDMA20001X = 1,
    QMI_DMS_RADIO_INTERFACE_EVDO       = 2,
    QMI_DMS_RADIO_INTERFACE_GSM        = 4,
    QMI_DMS_RADIO_INTERFACE_UMTS       = 5,
    QMI_DMS_RADIO_INTERFACE_LTE        = 8
} QmiDmsRadioInterface;


/*****************************************************************************/
/* Helper enums for the 'QMI DMS Get Power State' message */

/**
 * QmiDmsPowerState:
 * @QMI_DMS_POWER_STATE_EXTERNAL_SOURCE: Powered by an external source.
 * @QMI_DMS_POWER_STATE_BATTERY_CONNECTED: Battery is connected.
 * @QMI_DMS_POWER_STATE_BATTERY_CHARGING: Battery is currently being charged.
 * @QMI_DMS_POWER_STATE_FAULT: Recognized power fault.
 *
 * Flags specifying the current power state.
 *
 * If @QMI_DMS_POWER_STATE_EXTERNAL_SOURCE is set, the device is powerered by an
 * external source; otherwise it is powered by a battery.
 *
 * If @QMI_DMS_POWER_STATE_BATTERY_CONNECTED is set, the battery is connected;
 * otherwise the battery is not connected.
 *
 * If @QMI_DMS_POWER_STATE_BATTERY_CHARGING is set, the battery is being charged;
 * otherwise the battery is not being charged.
 *
 * If @QMI_DMS_POWER_STATE_FAULT is set, a power fault has been detected.
 */
typedef enum {
    QMI_DMS_POWER_STATE_EXTERNAL_SOURCE   = 1 << 0,
    QMI_DMS_POWER_STATE_BATTERY_CONNECTED = 1 << 1,
    QMI_DMS_POWER_STATE_BATTERY_CHARGING  = 1 << 2,
    QMI_DMS_POWER_STATE_FAULT             = 1 << 3,
} QmiDmsPowerState;


/*****************************************************************************/
/* Helper enums for the 'QMI DMS Set PIN Protection' message */

/**
 * QmiDmsPinId:
 * @QMI_DMS_PIN_ID_PIN: PIN.
 * @QMI_DMS_PIN_ID_PIN2: PIN2.
 *
 * The PIN identifier.
 */
typedef enum {
    QMI_DMS_PIN_ID_PIN  = 1,
    QMI_DMS_PIN_ID_PIN2 = 2
} QmiDmsPinId;

#endif /* _LIBQMI_GLIB_QMI_ENUMS_DMS_H_ */