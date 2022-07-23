/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes_macos.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:07:16 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/05 20:00:19 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *  Summary:
 *    Virtual keycodes
 *  
 *  Discussion:
 *    These constants are the virtual keycodes defined originally in
 *    Inside Mac Volume V, pg. V-191. They identify physical keys on a
 *    keyboard. Those constants with "ANSI" in the name are labeled
 *    according to the key position on an ANSI-standard US keyboard.
 *    For example, KC_A indicates the virtual keycode for the key
 *    with the letter 'A' in the US keyboard layout. Other keyboard
 *    layouts may have the 'A' key label on a different physical key;
 *    in this case, pressing 'A' will generate a different virtual
 *    keycode.
 */
enum {
  KC_A                    = 0x00,
  KC_S                    = 0x01,
  KC_D                    = 0x02,
  KC_F                    = 0x03,
  KC_H                    = 0x04,
  KC_G                    = 0x05,
  KC_Z                    = 0x06,
  KC_X                    = 0x07,
  KC_C                    = 0x08,
  KC_V                    = 0x09,
  KC_B                    = 0x0B,
  KC_Q                    = 0x0C,
  KC_W                    = 0x0D,
  KC_E                    = 0x0E,
  KC_R                    = 0x0F,
  KC_Y                    = 0x10,
  KC_T                    = 0x11,
  KC_1                    = 0x12,
  KC_2                    = 0x13,
  KC_3                    = 0x14,
  KC_4                    = 0x15,
  KC_6                    = 0x16,
  KC_5                    = 0x17,
  KC_Equal                = 0x18,
  KC_9                    = 0x19,
  KC_7                    = 0x1A,
  KC_Minus                = 0x1B,
  KC_8                    = 0x1C,
  KC_0                    = 0x1D,
  KC_Bracket_R         = 0x1E,
  KC_O                    = 0x1F,
  KC_U                    = 0x20,
  KC_Bracket_L          = 0x21,
  KC_I                    = 0x22,
  KC_P                    = 0x23,
  KC_L                    = 0x25,
  KC_J                    = 0x26,
  KC_Quote                = 0x27,
  KC_K                    = 0x28,
  KC_Semicolon            = 0x29,
  KC_Backslash            = 0x2A,
  KC_Comma                = 0x2B,
  KC_Slash                = 0x2C,
  KC_N                    = 0x2D,
  KC_M                    = 0x2E,
  KC_Period               = 0x2F,
  KC_Grave                = 0x32,
  KC_KP_Decimal        = 0x41,
  KC_KP_Multiply       = 0x43,
  KC_KP_Plus           = 0x45,
  KC_KP_Clear          = 0x47,
  KC_KP_Divide         = 0x4B,
  KC_KP_Enter          = 0x4C,
  KC_KP_Minus          = 0x4E,
  KC_KP_Equals         = 0x51,
  KC_KP_0              = 0x52,
  KC_KP_1              = 0x53,
  KC_KP_2              = 0x54,
  KC_KP_3              = 0x55,
  KC_KP_4              = 0x56,
  KC_KP_5              = 0x57,
  KC_KP_6              = 0x58,
  KC_KP_7              = 0x59,
  KC_KP_8              = 0x5B,
  KC_KP_9              = 0x5C
};

/* keycodes for keys that are independent of keyboard layout*/
enum {
  KC_Enter                    = 0x24,
  KC_Tab                       = 0x30,
  KC_Space                     = 0x31,
  KC_Delete                    = 0x33,
  KC_Escape                    = 0x35,
  KC_Command                   = 0x37,
  KC_Shift_L                     = 0x38,
  KC_CapsLock                  = 0x39,
  KC_Option                    = 0x3A,
  KC_Control                   = 0x3B,
  KC_Shift_R                = 0x3C,
  KC_Option_R               = 0x3D,
  KC_Control_R              = 0x3E,
  KC_Function                  = 0x3F,
  KC_F17                       = 0x40,
  KC_VolumeUp                  = 0x48,
  KC_VolumeDown                = 0x49,
  KC_Mute                      = 0x4A,
  KC_F18                       = 0x4F,
  KC_F19                       = 0x50,
  KC_F20                       = 0x5A,
  KC_F5                        = 0x60,
  KC_F6                        = 0x61,
  KC_F7                        = 0x62,
  KC_F3                        = 0x63,
  KC_F8                        = 0x64,
  KC_F9                        = 0x65,
  KC_F11                       = 0x67,
  KC_F13                       = 0x69,
  KC_F16                       = 0x6A,
  KC_F14                       = 0x6B,
  KC_F10                       = 0x6D,
  KC_F12                       = 0x6F,
  KC_F15                       = 0x71,
  KC_Help                      = 0x72,
  KC_Home                      = 0x73,
  KC_PageUp                    = 0x74,
  KC_ForwardDelete             = 0x75,
  KC_F4                        = 0x76,
  KC_End                       = 0x77,
  KC_F2                        = 0x78,
  KC_PageDown                  = 0x79,
  KC_F1                        = 0x7A,
  KC_Left                 = 0x7B,
  KC_Right                = 0x7C,
  KC_Down                 = 0x7D,
  KC_Up                   = 0x7E
};
