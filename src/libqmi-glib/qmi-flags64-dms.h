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
 * Copyright (C) 2012 Lanedo GmbH.
 * Copyright (C) 2012 Google, Inc.

 */

#ifndef _LIBQMI_GLIB_QMI_FLAGS64_DMS_H_
#define _LIBQMI_GLIB_QMI_FLAGS64_DMS_H_

#if !defined (__LIBQMI_GLIB_H_INSIDE__) && !defined (LIBQMI_GLIB_COMPILATION)
#error "Only <libqmi-glib.h> can be included directly."
#endif

#include <glib.h>

/*****************************************************************************/
/* Helper enums for the 'QMI DMS Get Band Capability' message */

/**
 * QmiDmsBandCapability:
 * @QMI_DMS_BAND_CAPABILITY_BC_0_A_SYSTEM: Band class 0, A-system.
 * @QMI_DMS_BAND_CAPABILITY_BC_0_B_SYSTEM: Band class 0, B-system.
 * @QMI_DMS_BAND_CAPABILITY_BC_1_ALL_BLOCKS: Band class 1, all blocks.
 * @QMI_DMS_BAND_CAPABILITY_BC_2: Band class 2.
 * @QMI_DMS_BAND_CAPABILITY_BC_3_A_SYSTEM: Band class 3, A-system.
 * @QMI_DMS_BAND_CAPABILITY_BC_4_ALL_BLOCKS: Band class 4, all blocks.
 * @QMI_DMS_BAND_CAPABILITY_BC_5_ALL_BLOCKS: Band class 5, all blocks.
 * @QMI_DMS_BAND_CAPABILITY_BC_6: Band class 6.
 * @QMI_DMS_BAND_CAPABILITY_BC_7: Band class 7.
 * @QMI_DMS_BAND_CAPABILITY_BC_8: Band class 8.
 * @QMI_DMS_BAND_CAPABILITY_BC_9: Band class 9.
 * @QMI_DMS_BAND_CAPABILITY_BC_10: Band class 10.
 * @QMI_DMS_BAND_CAPABILITY_BC_11: Band class 11.
 * @QMI_DMS_BAND_CAPABILITY_BC_12: Band class 12.
 * @QMI_DMS_BAND_CAPABILITY_BC_14: Band class 14.
 * @QMI_DMS_BAND_CAPABILITY_BC_15: Band class 15.
 * @QMI_DMS_BAND_CAPABILITY_BC_16: Band class 16.
 * @QMI_DMS_BAND_CAPABILITY_BC_17: Band class 17.
 * @QMI_DMS_BAND_CAPABILITY_BC_18: Band class 18.
 * @QMI_DMS_BAND_CAPABILITY_BC_19: Band class 19.
 * @QMI_DMS_BAND_CAPABILITY_GSM_DCS_1800: GSM DCS band.
 * @QMI_DMS_BAND_CAPABILITY_GSM_900_EXTENDED: GSM Extended GSM band (900).
 * @QMI_DMS_BAND_CAPABILITY_GSM_900_PRIMARY: GSM Primary GSM band (900).
 * @QMI_DMS_BAND_CAPABILITY_GSM_450: GSM 450 band.
 * @QMI_DMS_BAND_CAPABILITY_GSM_480: GSM 480 band.
 * @QMI_DMS_BAND_CAPABILITY_GSM_750: GSM 750 band.
 * @QMI_DMS_BAND_CAPABILITY_GSM_850: GSM 850 band.
 * @QMI_DMS_BAND_CAPABILITY_GSM_900_RAILWAYS: GSM railways band (900).
 * @QMI_DMS_BAND_CAPABILITY_GSM_PCS_1900: GSM PCS band (1900).
 * @QMI_DMS_BAND_CAPABILITY_WCDMA_2100: WCDMA 2100 band (Europe, Japan, China).
 * @QMI_DMS_BAND_CAPABILITY_WCDMA_PCS_1900: WCDMA PCS 1900 band (US).
 * @QMI_DMS_BAND_CAPABILITY_WCDMA_DCS_1800: WCDMA DCS 1800 band (Europe, China).
 * @QMI_DMS_BAND_CAPABILITY_WCDMA_1700_US: WCDMA 1700 band (US).
 * @QMI_DMS_BAND_CAPABILITY_WCDMA_850_US: WCDMA 850 band (US).
 * @QMI_DMS_BAND_CAPABILITY_WCDMA_800: QWCDMA 850 band (Japan).
 * @QMI_DMS_BAND_CAPABILITY_WCDMA_2600: WCDMA 2600 band (Europe).
 * @QMI_DMS_BAND_CAPABILITY_WCDMA_900: WCDMA 900 band (Europe, Japan).
 * @QMI_DMS_BAND_CAPABILITY_WCDMA_1700_JAPAN: WCDMA 1700 band (Japan).
 * @QMI_DMS_BAND_CAPABILITY_WCDMA_850_JAPAN: WCDMA 850 band (Japan)
 * @QMI_DMS_BAND_CAPABILITY_WCDMA_1500: WCDMA 1500 band.
 *
 * Frequency band capabilities.
 */
typedef enum {
    QMI_DMS_BAND_CAPABILITY_BC_0_A_SYSTEM    = 1 << 0,
    QMI_DMS_BAND_CAPABILITY_BC_0_B_SYSTEM    = 1 << 1,
    QMI_DMS_BAND_CAPABILITY_BC_1_ALL_BLOCKS  = 1 << 2,
    QMI_DMS_BAND_CAPABILITY_BC_2             = 1 << 3,
    QMI_DMS_BAND_CAPABILITY_BC_3_A_SYSTEM    = 1 << 4,
    QMI_DMS_BAND_CAPABILITY_BC_4_ALL_BLOCKS  = 1 << 5,
    QMI_DMS_BAND_CAPABILITY_BC_5_ALL_BLOCKS  = 1 << 6,
    QMI_DMS_BAND_CAPABILITY_GSM_DCS_1800     = 1 << 7,
    QMI_DMS_BAND_CAPABILITY_GSM_900_EXTENDED = 1 << 8,
    QMI_DMS_BAND_CAPABILITY_GSM_900_PRIMARY  = 1 << 9,
    QMI_DMS_BAND_CAPABILITY_BC_6             = 1 << 10,
    QMI_DMS_BAND_CAPABILITY_BC_7             = 1 << 11,
    QMI_DMS_BAND_CAPABILITY_BC_8             = 1 << 12,
    QMI_DMS_BAND_CAPABILITY_BC_9             = 1 << 13,
    QMI_DMS_BAND_CAPABILITY_BC_10            = 1 << 14,
    QMI_DMS_BAND_CAPABILITY_BC_11            = 1 << 15,
    QMI_DMS_BAND_CAPABILITY_GSM_450          = 1 << 16,
    QMI_DMS_BAND_CAPABILITY_GSM_480          = 1 << 17,
    QMI_DMS_BAND_CAPABILITY_GSM_750          = 1 << 18,
    QMI_DMS_BAND_CAPABILITY_GSM_850          = 1 << 19,
    QMI_DMS_BAND_CAPABILITY_GSM_900_RAILWAYS = 1 << 20,
    QMI_DMS_BAND_CAPABILITY_GSM_PCS_1900     = 1 << 21,
    QMI_DMS_BAND_CAPABILITY_WCDMA_2100       = 1 << 22,
    QMI_DMS_BAND_CAPABILITY_WCDMA_PCS_1900   = 1 << 23,
    QMI_DMS_BAND_CAPABILITY_WCDMA_DCS_1800   = 1 << 24,
    QMI_DMS_BAND_CAPABILITY_WCDMA_1700_US    = 1 << 25,
    QMI_DMS_BAND_CAPABILITY_WCDMA_850_US     = 1 << 26,
    QMI_DMS_BAND_CAPABILITY_WCDMA_800        = 1 << 27,
    QMI_DMS_BAND_CAPABILITY_BC_12            = 1 << 28,
    QMI_DMS_BAND_CAPABILITY_BC_14            = 1 << 29,
    /* Bit 30 reserved */
    QMI_DMS_BAND_CAPABILITY_BC_15            = ((guint64) 1) << 31,
    /* Bits 32-47 reserved */
    QMI_DMS_BAND_CAPABILITY_WCDMA_2600       = ((guint64) 1) << 48,
    QMI_DMS_BAND_CAPABILITY_WCDMA_900        = ((guint64) 1) << 49,
    QMI_DMS_BAND_CAPABILITY_WCDMA_1700_JAPAN = ((guint64) 1) << 50,
    /* Bits 51-55 reserved */
    QMI_DMS_BAND_CAPABILITY_BC_16            = ((guint64) 1) << 56,
    QMI_DMS_BAND_CAPABILITY_BC_17            = ((guint64) 1) << 57,
    QMI_DMS_BAND_CAPABILITY_BC_18            = ((guint64) 1) << 58,
    QMI_DMS_BAND_CAPABILITY_BC_19            = ((guint64) 1) << 59,
    QMI_DMS_BAND_CAPABILITY_WCDMA_850_JAPAN  = ((guint64) 1) << 60,
    QMI_DMS_BAND_CAPABILITY_WCDMA_1500       = ((guint64) 1) << 61
    /* Bits 62-63 reserved */
} QmiDmsBandCapability;

/**
 * qmi_dms_band_capability_build_string_from_mask:
 *
 * Since: 1.0
 */

/**
 * QmiDmsLteBandCapability:
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_1: LTE EUTRAN Band 1
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_2: LTE EUTRAN Band 2.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_3: LTE EUTRAN Band 3.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_4: LTE EUTRAN Band 4.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_5: LTE EUTRAN Band 5.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_6: LTE EUTRAN Band 6.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_7: LTE EUTRAN Band 7.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_8: LTE EUTRAN Band 8.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_9: LTE EUTRAN Band 9.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_10: LTE EUTRAN Band 10.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_11: LTE EUTRAN Band 11.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_12: LTE EUTRAN Band 12.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_13: LTE EUTRAN Band 13.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_14: LTE EUTRAN Band 14.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_17: LTE EUTRAN Band 17.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_18: LTE EUTRAN Band 18.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_19: LTE EUTRAN Band 19.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_20: LTE EUTRAN Band 20.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_21: LTE EUTRAN Band 21.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_24: LTE EUTRAN Band 24.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_25: LTE EUTRAN Band 25.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_33: LTE EUTRAN Band 33.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_34: LTE EUTRAN Band 34.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_35: LTE EUTRAN Band 35.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_36: LTE EUTRAN Band 36.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_37: LTE EUTRAN Band 37.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_38: LTE EUTRAN Band 38.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_39: LTE EUTRAN Band 39.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_40: LTE EUTRAN Band 40.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_41: LTE EUTRAN Band 41.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_42: LTE EUTRAN Band 42.
 * @QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_43: LTE EUTRAN Band 43.
 *
 * LTE-specific Frequency bands.
 */
typedef enum {
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_1  = 1 << 0,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_2  = 1 << 1,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_3  = 1 << 2,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_4  = 1 << 3,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_5  = 1 << 4,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_6  = 1 << 5,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_7  = 1 << 6,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_8  = 1 << 7,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_9  = 1 << 8,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_10 = 1 << 9,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_11 = 1 << 10,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_12 = 1 << 11,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_13 = 1 << 12,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_14 = 1 << 13,
    /* Bit 14-15 reserved */
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_17 = 1 << 16,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_18 = 1 << 17,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_19 = 1 << 18,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_20 = 1 << 19,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_21 = 1 << 20,
    /* Bit 21-22 reserved */
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_24 = 1 << 23,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_25 = 1 << 24,
    /* Bit 25-31 reserved */
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_33 = ((guint64) 1) << 32,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_34 = ((guint64) 1) << 33,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_35 = ((guint64) 1) << 34,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_36 = ((guint64) 1) << 35,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_37 = ((guint64) 1) << 36,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_38 = ((guint64) 1) << 37,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_39 = ((guint64) 1) << 38,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_40 = ((guint64) 1) << 39,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_41 = ((guint64) 1) << 40,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_42 = ((guint64) 1) << 41,
    QMI_DMS_LTE_BAND_CAPABILITY_EUTRAN_43 = ((guint64) 1) << 42
    /* Bit 43-64 reserved */
} QmiDmsLteBandCapability;

/**
 * qmi_dms_lte_band_capability_build_string_from_mask:
 *
 * Since: 1.0
 */

#endif /* _LIBQMI_GLIB_QMI_FLAGS64_DMS_H_ */
