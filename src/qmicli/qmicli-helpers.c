/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * qmicli -- Command line interface to control QMI devices
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2015 Velocloud Inc.
 * Copyright (C) 2012-2017 Aleksander Morgado <aleksander@aleksander.es>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "qmicli-helpers.h"

gchar *
qmicli_get_raw_data_printable (const GArray *data,
                               gsize max_line_length,
                               const gchar *line_prefix)
{
    gsize i;
    gsize j;
    gsize k;
    gsize new_str_length;
    gchar *new_str;
    gsize prefix_len;
    guint n_lines;
    gboolean is_new_line;

    g_return_val_if_fail (max_line_length >= 3, NULL);

    if (!data)
        return g_strdup ("");

    /* Get new string length. If input string has N bytes, we need:
     * - 1 byte for last NUL char
     * - 2N bytes for hexadecimal char representation of each byte...
     * - N-1 bytes for the separator ':'
     * So... a total of (1+2N+N-1) = 3N bytes are needed... */
    new_str_length =  3 * data->len;

    /* Effective max line length needs to be multiple of 3, we don't want to
     * split in half a given byte representation */
    while (max_line_length % 3 != 0)
        max_line_length--;

    /* Prefix len includes the newline character plus the length of the input
     * prefix */
    prefix_len = strlen (line_prefix) + 1;
    /* We don't consider the last NUL byte when counting lines to generate */
    n_lines = (new_str_length - 1) / max_line_length;
    if ((new_str_length - 1) % max_line_length != 0)
        n_lines++;

    /* Build new str length expected when we prefix the string and we limit the
     * line length */
    new_str_length += (n_lines * prefix_len);

    /* Allocate memory for new array and initialize contents to NUL */
    new_str = g_malloc0 (new_str_length);

    /* Print hexadecimal representation of each byte... */
    is_new_line = TRUE;
    for (i = 0, j = 0, k = 0; i < data->len; i++) {
        if (is_new_line) {
            strcpy (&new_str[j], line_prefix);
            j += strlen (line_prefix);
            is_new_line = FALSE;
        }

        /* Print character in output string... */
        snprintf (&new_str[j], 3, "%02X", g_array_index (data, guint8, i));
        j+=2;
        k+=2;

        if (i != (data->len - 1) ) {
            new_str[j] = ':';
            j++;
            k++;
        }

        if (k % max_line_length == 0 ||
            i == (data->len -1)) {
            new_str[j] = '\n';
            j++;
            is_new_line = TRUE;
        }
    }

    /* Set output string */
    return new_str;
}

gchar *
qmicli_get_firmware_image_unique_id_printable (const GArray *unique_id)
{
    gchar    *unique_id_str;
    guint     i;
    guint     n_ascii = 0;
    gboolean  end = FALSE;

#define UNIQUE_ID_LEN 16

    g_warn_if_fail (unique_id->len <= UNIQUE_ID_LEN);
    unique_id_str = g_malloc0 (UNIQUE_ID_LEN + 1);
    memcpy (unique_id_str, unique_id->data, UNIQUE_ID_LEN);

    /* We want an ASCII string that, if finished before the 16 bytes,
     * is suffixed with NUL bytes. */
    for (i = 0; i < UNIQUE_ID_LEN; i++) {
        /* If a byte isn't ASCII, stop */
        if (unique_id_str[i] & 0x80)
            break;
        /* If string isn't finished yet... */
        if (!end) {
            /* String finished now */
            if (unique_id_str[i] == '\0')
                end = TRUE;
            else
                n_ascii++;
        } else {
            /* String finished but we then got
             * another ASCII byte? not possible */
            if (unique_id_str[i] != '\0')
                break;
        }
    }

    if (i == UNIQUE_ID_LEN && n_ascii > 0)
        return unique_id_str;

#undef UNIQUE_ID_LEN

    g_free (unique_id_str);

    /* Get a raw hex string otherwise */
    unique_id_str = qmicli_get_raw_data_printable (unique_id, 80, "");
    unique_id_str[strlen (unique_id_str) - 1] = '\0'; /* remove EOL */

    return unique_id_str;
}

gboolean
qmicli_read_dms_uim_pin_id_from_string (const gchar *str,
                                        QmiDmsUimPinId *out)
{
    if (!str || str[0] == '\0') {
        g_printerr ("error: expected 'PIN' or 'PIN2', got: none\n");
        return FALSE;
    }

    if (g_str_equal (str, "PIN")) {
        *out = QMI_DMS_UIM_PIN_ID_PIN;
        return TRUE;
    }

    if (g_str_equal (str, "PIN2")) {
        *out = QMI_DMS_UIM_PIN_ID_PIN2;
        return TRUE;
    }

    g_printerr ("error: expected 'PIN' or 'PIN2', got: '%s'\n", str);
    return FALSE;
}

gboolean
qmicli_read_uim_pin_id_from_string (const gchar *str,
                                    QmiUimPinId *out)
{
    if (!str || str[0] == '\0') {
        g_printerr ("error: expected 'PIN1', 'PIN2' or 'UPIN', got: none\n");
        return FALSE;
    }

    if (g_str_equal (str, "PIN1")) {
        *out = QMI_UIM_PIN_ID_PIN1;
        return TRUE;
    }

    if (g_str_equal (str, "PIN2")) {
        *out = QMI_UIM_PIN_ID_PIN2;
        return TRUE;
    }
    if (g_str_equal (str, "UPIN")) {
        *out = QMI_UIM_PIN_ID_UPIN;
        return TRUE;
    }

    g_printerr ("error: expected 'PIN1', 'PIN2' or 'UPIN', got: '%s'\n", str);
    return FALSE;
}

gboolean
qmicli_read_operating_mode_from_string (const gchar *str,
                                        QmiDmsOperatingMode *out)
{
    GType type;
    GEnumClass *enum_class;
    GEnumValue *enum_value;

    type = qmi_dms_operating_mode_get_type ();
    enum_class = G_ENUM_CLASS (g_type_class_ref (type));
    enum_value = g_enum_get_value_by_nick (enum_class, str);

    if (enum_value)
        *out = (QmiDmsOperatingMode)enum_value->value;
    else
        g_printerr ("error: invalid operating mode value given: '%s'\n", str);

    g_type_class_unref (enum_class);
    return !!enum_value;
}

gboolean
qmicli_read_rat_mode_pref_from_string (const gchar *str,
                                       QmiNasRatModePreference *out)
{
    GType type;
    GFlagsClass *flags_class;
    GFlagsValue *flags_value;
    gboolean success = TRUE, set = FALSE;
    char **items, **iter;

    type = qmi_nas_rat_mode_preference_get_type ();
    flags_class = G_FLAGS_CLASS (g_type_class_ref (type));

    *out = 0;

    items = g_strsplit_set (str, "|", 0);
    for (iter = items; iter && *iter && success; iter++) {
        if (!*iter[0])
            continue;

        flags_value = g_flags_get_value_by_nick (flags_class, *iter);
        if (flags_value) {
            *out |= (QmiNasRatModePreference)flags_value->value;
            set = TRUE;
        } else {
            g_printerr ("error: invalid rat mode pref value given: '%s'\n", *iter);
            success = FALSE;
        }
    }

    if (!set)
        g_printerr ("error: invalid rat mode pref input given: '%s'\n", str);

    if (items)
        g_strfreev (items);
    g_type_class_unref (flags_class);
    return success && set;
}

gboolean
qmicli_read_facility_from_string (const gchar *str,
                                  QmiDmsUimFacility *out)
{
    GType type;
    GEnumClass *enum_class;
    GEnumValue *enum_value;

    type = qmi_dms_uim_facility_get_type ();
    enum_class = G_ENUM_CLASS (g_type_class_ref (type));
    enum_value = g_enum_get_value_by_nick (enum_class, str);

    if (enum_value)
        *out = (QmiDmsUimFacility)enum_value->value;
    else
        g_printerr ("error: invalid facility value given: '%s'\n", str);

    g_type_class_unref (enum_class);
    return !!enum_value;
}

gboolean
qmicli_read_enable_disable_from_string (const gchar *str,
                                        gboolean *out)
{
    if (!str || str[0] == '\0') {
        g_printerr ("error: expected 'disable' or 'enable', got: none\n");
        return FALSE;
    }

    if (g_str_equal (str, "disable")) {
        *out = FALSE;
        return TRUE;
    }

    if (g_str_equal (str, "enable")) {
        *out = TRUE;
        return TRUE;
    }

    g_printerr ("error: expected 'disable' or 'enable', got: '%s'\n", str);
    return FALSE;
}

gboolean
qmicli_read_yes_no_from_string (const gchar *str,
                                gboolean *out)
{
    if (!str || str[0] == '\0') {
        g_printerr ("error: expected 'true', 'false', 'yes' or 'no', got: none\n");
        return FALSE;
    }

    if ((g_strcasecmp (str, "yes") == 0) || (g_strcasecmp (str, "true") == 0)) {
        *out = TRUE;
        return TRUE;
    }

    if ((g_strcasecmp (str, "no") == 0) || (g_strcasecmp (str, "false") == 0)) {
        *out = FALSE;
        return TRUE;
    }

    g_printerr ("error: expected 'true', 'false', 'yes' or 'no', got: %s\n", str);
    return FALSE;
}

gboolean
qmicli_read_non_empty_string (const gchar *str,
                              const gchar *description,
                              gchar **out)
{
    if (!str || str[0] == '\0') {
        g_printerr ("error: empty %s given\n", description);
        return FALSE;
    }

    *out = (gchar *)str;
    return TRUE;
}

gboolean
qmicli_read_firmware_id_from_string (const gchar *str,
                                     QmiDmsFirmwareImageType *out_type,
                                     guint *out_index)
{
    const gchar *index_str;

    if (g_str_has_prefix (str, "modem")) {
        *out_type = QMI_DMS_FIRMWARE_IMAGE_TYPE_MODEM;
        index_str = &str[5];
    } else if (g_str_has_prefix (str, "pri")) {
        *out_type = QMI_DMS_FIRMWARE_IMAGE_TYPE_PRI;
        index_str = &str[3];
    } else {
        g_printerr ("error: invalid firmware image type value given: '%s'\n", str);
        return FALSE;
    }

    return qmicli_read_uint_from_string (index_str, out_index);
}

gboolean
qmicli_read_binary_array_from_string (const gchar *str,
                                      GArray **out)
{
    gsize i, j, len;

    g_return_val_if_fail (out != NULL, FALSE);
    g_return_val_if_fail (str, FALSE);

    /* Length must be a multiple of 2 */
    len = strlen (str);
    if (len & 1)
        return FALSE;

    *out = g_array_sized_new (FALSE, TRUE, sizeof (guint8), len >> 1);
    g_array_set_size (*out, len >> 1);

    for (i = 0, j = 0; i < len; i += 2, j++) {
        gint a, b;

        a = g_ascii_xdigit_value (str[i]);
        b = g_ascii_xdigit_value (str[i + 1]);
        if (a < 0 || b < 0) {
            g_array_unref (*out);
            return FALSE;
        }

        g_array_index (*out, guint8, j) = (a << 4) | b;
    }

    return TRUE;
}

gboolean
qmicli_read_pdc_configuration_type_from_string (const gchar *str,
                                                QmiPdcConfigurationType *out)
{
    GType type;
    GEnumClass *enum_class;
    GEnumValue *enum_value;

    type = qmi_pdc_configuration_type_get_type ();
    enum_class = G_ENUM_CLASS (g_type_class_ref (type));
    enum_value = g_enum_get_value_by_nick (enum_class, str);

    if (enum_value)
        *out = (QmiPdcConfigurationType)enum_value->value;
    else
        g_printerr ("error: invalid configuration type value given: '%s'\n", str);

    g_type_class_unref (enum_class);
    return !!enum_value;
}

gboolean
qmicli_read_radio_interface_from_string (const gchar *str,
                                         QmiNasRadioInterface *out)
{
    GType type;
    GEnumClass *enum_class;
    GEnumValue *enum_value;

    type = qmi_nas_radio_interface_get_type ();
    enum_class = G_ENUM_CLASS (g_type_class_ref (type));
    enum_value = g_enum_get_value_by_nick (enum_class, str);

    if (enum_value)
        *out = (QmiNasRadioInterface)enum_value->value;
    else
        g_printerr ("error: invalid radio interface value given: '%s'\n", str);

    g_type_class_unref (enum_class);
    return !!enum_value;
}

gboolean
qmicli_read_net_open_flags_from_string (const gchar *str,
                                        QmiDeviceOpenFlags *out)
{
    GType type;
    GFlagsClass *flags_class;
    GFlagsValue *flags_value;
    gboolean success = TRUE, set = FALSE;
    char **items, **iter;

    type = qmi_device_open_flags_get_type ();
    flags_class = G_FLAGS_CLASS (g_type_class_ref (type));

    *out = 0;

    items = g_strsplit_set (str, "|", 0);
    for (iter = items; iter && *iter && success; iter++) {
        if (!*iter[0])
            continue;

        flags_value = g_flags_get_value_by_nick (flags_class, *iter);
        if (flags_value) {
            *out |= (QmiDeviceOpenFlags)flags_value->value;
            set = TRUE;
        } else {
            g_printerr ("error: invalid net open flags value given: '%s'\n", *iter);
            success = FALSE;
        }
    }

    if (!set)
        g_printerr ("error: invalid net open flags input given: '%s'\n", str);

    if (items)
        g_strfreev (items);

    if (*out & QMI_DEVICE_OPEN_FLAGS_NET_802_3 &&
        *out & QMI_DEVICE_OPEN_FLAGS_NET_RAW_IP) {
        g_printerr ("error: cannot give both 802.3 and raw-IP options\n");
        success = FALSE;
    }

    if (*out & QMI_DEVICE_OPEN_FLAGS_NET_QOS_HEADER &&
        *out & QMI_DEVICE_OPEN_FLAGS_NET_NO_QOS_HEADER) {
        g_printerr ("error: cannot request both QoS and no-QoS headers\n");
        success = FALSE;
    }

    if ((*out & (QMI_DEVICE_OPEN_FLAGS_NET_802_3 | QMI_DEVICE_OPEN_FLAGS_NET_RAW_IP)) &&
        !(*out & (QMI_DEVICE_OPEN_FLAGS_NET_QOS_HEADER | QMI_DEVICE_OPEN_FLAGS_NET_NO_QOS_HEADER))) {
        g_printerr ("error: missing QoS or no-QoS header request\n");
        success = FALSE;
    }

    if ((*out & (QMI_DEVICE_OPEN_FLAGS_NET_QOS_HEADER | QMI_DEVICE_OPEN_FLAGS_NET_NO_QOS_HEADER)) &&
        !(*out & (QMI_DEVICE_OPEN_FLAGS_NET_802_3 | QMI_DEVICE_OPEN_FLAGS_NET_RAW_IP))) {
        g_printerr ("error: missing link protocol (802.3 or raw IP)\n");
        success = FALSE;
    }

    g_type_class_unref (flags_class);
    return success && set;
}

gboolean
qmicli_read_expected_data_format_from_string (const gchar *str,
                                              QmiDeviceExpectedDataFormat *out)
{
    GType type;
    GEnumClass *enum_class;
    GEnumValue *enum_value;

    type = qmi_device_expected_data_format_get_type ();
    enum_class = G_ENUM_CLASS (g_type_class_ref (type));
    enum_value = g_enum_get_value_by_nick (enum_class, str);

    if (enum_value)
        *out = (QmiDeviceExpectedDataFormat)enum_value->value;
    else
        g_printerr ("error: invalid expected data format value given: '%s'\n", str);

    g_type_class_unref (enum_class);
    return !!enum_value;
}

gboolean
qmicli_read_link_layer_protocol_from_string (const gchar *str,
                                             QmiWdaLinkLayerProtocol *out)
{
    GType type;
    GEnumClass *enum_class;
    GEnumValue *enum_value;

    type = qmi_wda_link_layer_protocol_get_type ();
    enum_class = G_ENUM_CLASS (g_type_class_ref (type));
    enum_value = g_enum_get_value_by_nick (enum_class, str);

    if (enum_value)
        *out = (QmiWdaLinkLayerProtocol)enum_value->value;
    else
        g_printerr ("error: invalid link layer protocol value given: '%s'\n", str);

    g_type_class_unref (enum_class);
    return !!enum_value;
}

gboolean
qmicli_read_data_aggregation_protocol_from_string (const gchar *str,
                                                   QmiWdaDataAggregationProtocol *out)
{
    GType type;
    GEnumClass *enum_class;
    GEnumValue *enum_value;

    type = qmi_wda_data_aggregation_protocol_get_type ();
    enum_class = G_ENUM_CLASS (g_type_class_ref (type));
    enum_value = g_enum_get_value_by_nick (enum_class, str);

    if (enum_value)
        *out = (QmiWdaDataAggregationProtocol)enum_value->value;
    else
        g_printerr ("error: invalid data aggregation protocol value given: '%s'\n", str);

    g_type_class_unref (enum_class);
    return !!enum_value;
}

gboolean
qmicli_read_data_endpoint_type_from_string (const gchar *str,
                                            QmiDataEndpointType *out)
{
    GType type;
    GEnumClass *enum_class;
    GEnumValue *enum_value;

    type = qmi_data_endpoint_type_get_type ();
    enum_class = G_ENUM_CLASS (g_type_class_ref (type));
    enum_value = g_enum_get_value_by_nick (enum_class, str);

    if (enum_value)
        *out = (QmiDataEndpointType)enum_value->value;
    else
        g_printerr ("error: invalid data aggregation protocol value given: '%s'\n", str);

    g_type_class_unref (enum_class);
    return !!enum_value;
}

gboolean
qmicli_read_autoconnect_setting_from_string (const gchar *str,
                                             QmiWdsAutoconnectSetting *out)
{
    GType type;
    GEnumClass *enum_class;
    GEnumValue *enum_value;

    type = qmi_wds_autoconnect_setting_get_type ();
    enum_class = G_ENUM_CLASS (g_type_class_ref (type));
    enum_value = g_enum_get_value_by_nick (enum_class, str);

    if (enum_value)
        *out = (QmiWdsAutoconnectSetting)enum_value->value;
    else
        g_printerr ("error: invalid autoconnect setting value given: '%s'\n", str);

    g_type_class_unref (enum_class);
    return !!enum_value;
}

gboolean
qmicli_read_autoconnect_setting_roaming_from_string (const gchar *str,
                                                     QmiWdsAutoconnectSettingRoaming *out)
{
    GType type;
    GEnumClass *enum_class;
    GEnumValue *enum_value;

    type = qmi_wds_autoconnect_setting_roaming_get_type ();
    enum_class = G_ENUM_CLASS (g_type_class_ref (type));
    enum_value = g_enum_get_value_by_nick (enum_class, str);

    if (enum_value)
        *out = (QmiWdsAutoconnectSettingRoaming)enum_value->value;
    else
        g_printerr ("error: invalid autoconnect setting roaming value given: '%s'\n", str);

    g_type_class_unref (enum_class);
    return !!enum_value;
}

gboolean
qmicli_read_authentication_from_string (const gchar *str,
                                        QmiWdsAuthentication *out)
{
    if (g_ascii_strcasecmp (str, "PAP") == 0)
        *out = QMI_WDS_AUTHENTICATION_PAP;
    else if (g_ascii_strcasecmp (str, "CHAP") == 0)
        *out = QMI_WDS_AUTHENTICATION_CHAP;
    else if (g_ascii_strcasecmp (str, "BOTH") == 0)
        *out = (QMI_WDS_AUTHENTICATION_PAP | QMI_WDS_AUTHENTICATION_CHAP);
    else if (!str[0] || g_ascii_strcasecmp (str, "NONE") == 0)
        *out = QMI_WDS_AUTHENTICATION_NONE;
    else
        return FALSE;

    return TRUE;
}

gboolean
qmicli_read_boot_image_download_mode_from_string (const gchar *str,
                                                  QmiDmsBootImageDownloadMode *out)
{
    GType type;
    GEnumClass *enum_class;
    GEnumValue *enum_value;

    type = qmi_dms_boot_image_download_mode_get_type ();
    enum_class = G_ENUM_CLASS (g_type_class_ref (type));
    enum_value = g_enum_get_value_by_nick (enum_class, str);

    if (enum_value)
        *out = (QmiDmsBootImageDownloadMode)enum_value->value;
    else
        g_printerr ("error: invalid boot image download mode value given: '%s'\n", str);

    g_type_class_unref (enum_class);
    return !!enum_value;
}

gboolean
qmicli_read_hp_device_mode_from_string (const gchar *str,
                                        QmiDmsHpDeviceMode *out)
{
    GType type;
    GEnumClass *enum_class;
    GEnumValue *enum_value;

    type = qmi_dms_hp_device_mode_get_type ();
    enum_class = G_ENUM_CLASS (g_type_class_ref (type));
    enum_value = g_enum_get_value_by_nick (enum_class, str);

    if (enum_value)
        *out = (QmiDmsHpDeviceMode)enum_value->value;
    else
        g_printerr ("error: invalid HP device mode value given: '%s'\n", str);

    g_type_class_unref (enum_class);
    return !!enum_value;
}

gboolean
qmicli_read_swi_usb_composition_from_string (const gchar *str,
                                             QmiDmsSwiUsbComposition *out)
{
    GType type;
    GEnumClass *enum_class;
    GEnumValue *enum_value;

    type = qmi_dms_swi_usb_composition_get_type ();
    enum_class = G_ENUM_CLASS (g_type_class_ref (type));
    enum_value = g_enum_get_value_by_nick (enum_class, str);

    if (enum_value)
        *out = (QmiDmsSwiUsbComposition)enum_value->value;
    else
        g_printerr ("error: invalid SWI USB Composition value given: '%s'\n", str);

    g_type_class_unref (enum_class);
    return !!enum_value;
}

gboolean
qmicli_read_uint_from_string (const gchar *str,
                              guint *out)
{
    gulong num;

    if (!str || !str[0])
        return FALSE;

    for (num = 0; str[num]; num++) {
        if (!g_ascii_isdigit (str[num]))
            return FALSE;
    }

    errno = 0;
    num = strtoul (str, NULL, 10);
    if (!errno && num <= G_MAXUINT) {
        *out = (guint)num;
        return TRUE;
    }
    return FALSE;
}

gchar *
qmicli_get_supported_messages_list (const guint8 *data,
                                    gsize len)
{
    GString *str = NULL;

    if (len > 0 && data) {
        guint bytearray_i;

        for (bytearray_i = 0; bytearray_i < len; bytearray_i++) {
            guint bit_i;

            for (bit_i = 0; bit_i < 8; bit_i++) {
                if (data[bytearray_i] & (1 << bit_i)) {
                    if (!str)
                        str = g_string_new ("");
                    g_string_append_printf (str, "\t0x%04X\n", (guint16) (bit_i + (8 * bytearray_i)));
                }
            }
        }
    }

    return (str ? g_string_free (str, FALSE) : g_strdup ("\tnone\n"));
}

/******************************************************************************/

typedef struct {
    guint16      min;
    guint16      max;
    const gchar *name;
} EarfcnRange;

/* http://niviuk.free.fr/lte_band.php */
static const EarfcnRange earfcn_ranges[] = {
    {     0,   599, "E-UTRA band 1: 2100"           },
    {   600,  1199, "E-UTRA band 2: 1900 PCS"       },
    {  1200,  1949, "E-UTRA band 3: 1800+"          },
    {  1950,  2399, "E-UTRA band 4: AWS-1"          },
    {  2400,  2649, "E-UTRA band 5: 850"            },
    {  2650,  2749, "E-UTRA band 6: UMTS only"      },
    {  2750,  3449, "E-UTRA band 7: 2600"           },
    {  3450,  3799, "E-UTRA band 8: 900"            },
    {  3800,  4149, "E-UTRA band 9: 1800"           },
    {  4150,  4749, "E-UTRA band 10: AWS-1+"        },
    {  4750,  4999, "E-UTRA band 11: 1500 Lower"    },
    {  5000,  5179, "E-UTRA band 12: 700 a"         },
    {  5180,  5279, "E-UTRA band 13: 700 c"         },
    {  5280,  5379, "E-UTRA band 14: 700 PS"        },
    {  5730,  5849, "E-UTRA band 17: 700 b"         },
    {  5850,  5999, "E-UTRA band 18: 800 Lower"     },
    {  6000,  6149, "E-UTRA band 19: 800 Upper"     },
    {  6150,  6449, "E-UTRA band 20: 800 DD"        },
    {  6450,  6599, "E-UTRA band 21: 1500 Upper"    },
    {  6600,  7399, "E-UTRA band 22: 3500"          },
    {  7500,  7699, "E-UTRA band 23: 2000 S-band"   },
    {  7700,  8039, "E-UTRA band 24: 1600 L-band"   },
    {  8040,  8689, "E-UTRA band 25: 1900+"         },
    {  8690,  9039, "E-UTRA band 26: 850+"          },
    {  9040,  9209, "E-UTRA band 27: 800 SMR"       },
    {  9210,  9659, "E-UTRA band 28: 700 APT"       },
    {  9660,  9769, "E-UTRA band 29: 700 d"         },
    {  9770,  9869, "E-UTRA band 30: 2300 WCS"      },
    {  9870,  9919, "E-UTRA band 31: 450"           },
    {  9920, 10359, "E-UTRA band 32: 1500 L-band"   },
    { 36000, 36199, "E-UTRA band 33: TD 1900"       },
    { 36200, 36349, "E-UTRA band 34: TD 2000"       },
    { 36350, 36949, "E-UTRA band 35: TD PCS Lower"  },
    { 36950, 37549, "E-UTRA band 36: TD PCS Upper"  },
    { 37550, 37749, "E-UTRA band 37: TD PCS Center" },
    { 37750, 38249, "E-UTRA band 38: TD 2600"       },
    { 38250, 38649, "E-UTRA band 39: TD 1900+"      },
    { 38650, 39649, "E-UTRA band 40: TD 2300"       },
    { 39650, 41589, "E-UTRA band 41: TD 2500"       },
    { 41590, 43589, "E-UTRA band 42: TD 3500"       },
    { 43590, 45589, "E-UTRA band 43: TD 3700"       },
    { 45590, 46589, "E-UTRA band 44: TD 700"        },
};

const char *
qmicli_earfcn_to_eutra_band_string (guint16 earfcn)
{
    guint i;

    for (i = 0; i < G_N_ELEMENTS (earfcn_ranges); i++) {
        if (earfcn <= earfcn_ranges[i].max && earfcn >= earfcn_ranges[i].min)
            return earfcn_ranges[i].name;
    }
    return "unknown";
}

/* Expecting input as:
 *   key1=string,key2=true,key3=false...
 * Strings may also be passed enclosed between double or single quotes, like:
 *   key1="this is a string", key2='and so is this'
 *
 * Based on libmbim's mbimcli_parse_key_value_string().
 */
gboolean
qmicli_parse_key_value_string (const gchar *str,
                               GError **error,
                               QmiParseKeyValueForeachFn callback,
                               gpointer user_data)
{
    GError *inner_error = NULL;
    gchar *dupstr, *p, *key, *key_end, *value, *value_end, quote;

    g_return_val_if_fail (callback != NULL, FALSE);
    g_return_val_if_fail (str != NULL, FALSE);

    /* Allow empty strings, we'll just return with success */
    while (g_ascii_isspace (*str))
        str++;
    if (!str[0])
        return TRUE;

    dupstr = g_strdup (str);
    p = dupstr;

    while (TRUE) {
        gboolean keep_iteration = FALSE;

        /* Skip leading spaces */
        while (g_ascii_isspace (*p))
            p++;

        /* Key start */
        key = p;
        if (!g_ascii_isalnum (*key)) {
            inner_error = g_error_new (QMI_CORE_ERROR,
                                       QMI_CORE_ERROR_FAILED,
                                       "Key must start with alpha/num, starts with '%c'",
                                       *key);
            break;
        }

        /* Key end */
        while (g_ascii_isalnum (*p) || (*p == '-') || (*p == '_'))
            p++;
        key_end = p;
        if (key_end == key) {
            inner_error = g_error_new (QMI_CORE_ERROR,
                                       QMI_CORE_ERROR_FAILED,
                                       "Couldn't find a proper key");
            break;
        }

        /* Skip whitespaces, if any */
        while (g_ascii_isspace (*p))
            p++;

        /* Equal sign must be here */
        if (*p != '=') {
            inner_error = g_error_new (QMI_CORE_ERROR,
                                       QMI_CORE_ERROR_FAILED,
                                       "Couldn't find equal sign separator");
            break;
        }
        /* Skip the equal */
        p++;

        /* Skip whitespaces, if any */
        while (g_ascii_isspace (*p))
            p++;

        /* Do we have a quote-enclosed string? */
        if (*p == '\"' || *p == '\'') {
            quote = *p;
            /* Skip the quote */
            p++;
            /* Value start */
            value = p;
            /* Find the closing quote */
            p = strchr (p, quote);
            if (!p) {
                inner_error = g_error_new (QMI_CORE_ERROR,
                                           QMI_CORE_ERROR_FAILED,
                                           "Unmatched quotes in string value");
                break;
            }

            /* Value end */
            value_end = p;
            /* Skip the quote */
            p++;
        } else {
            /* Value start */
            value = p;

            /* Value end */
            while ((*p != ',') && (*p != '\0') && !g_ascii_isspace (*p))
                p++;
            value_end = p;
        }

        /* Note that we allow value == value_end here */

        /* Skip whitespaces, if any */
        while (g_ascii_isspace (*p))
            p++;

        /* If a comma is found, we should keep the iteration */
        if (*p == ',') {
            /* skip the comma */
            p++;
            keep_iteration = TRUE;
        }

        /* Got key and value, prepare them and run the callback */
        *value_end = '\0';
        *key_end = '\0';
        if (!callback (key, value, &inner_error, user_data)) {
            /* We were told to abort */
            break;
        }
        g_assert (!inner_error);

        if (keep_iteration)
            continue;

        /* Check if no more key/value pairs expected */
        if (*p == '\0')
            break;

        inner_error = g_error_new (QMI_CORE_ERROR,
                                   QMI_CORE_ERROR_FAILED,
                                   "Unexpected content (%s) after value",
                                   p);
        break;
    }

    g_free (dupstr);

    if (inner_error) {
        g_propagate_error (error, inner_error);
        return FALSE;
    }

    return TRUE;
}
