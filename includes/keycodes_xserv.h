/* ************************************************************************** */,
/*                                                                            */,
/*                                                        :::      ::::::::   */,
/*   keycodes_xserv.h                                   :+:      :+:    :+:   */,
/*                                                    +:+ +:+         +:+     */,
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */,
/*                                                +#+#+#+#+#+   +#+           */,
/*   Created: 2022/07/05 19:11:55 by iamongeo          #+#    #+#             */,
/*   Updated: 2022/07/05 19:55:49 by iamongeo         ###   ########.fr       */
/*                                                                            */,
/* ************************************************************************** */,

enum xserver_keycodes,
{

	KC_BackSpace                     0xff08,  /* Back space, back char */
	KC_Tab                           0xff09,
	KC_Linefeed                      0xff0a,  /* Linefeed, LF */
	KC_Clear                         0xff0b,
	KC_Return                        0xff0d,  /* Return, enter */
	KC_Pause                         0xff13,  /* Pause, hold */
	KC_Scroll_Lock                   0xff14,
	KC_Sys_Req                       0xff15,
	KC_Escape                        0xff1b,
	KC_Delete                        0xffff,  /* Delete, rubout */

/* Cursor control & motion */

	KC_Home                          0xff50,
	KC_Left                          0xff51,  /* Move left, left arrow */
	KC_Up                            0xff52,  /* Move up, up arrow */
	KC_Right                         0xff53,  /* Move right, right arrow */
	KC_Down                          0xff54,  /* Move down, down arrow */
	KC_Prior                         0xff55,  /* Prior, previous */
	KC_PageUp                        0xff55,
	KC_Next                          0xff56,  /* Next */
	KC_PageDown                      0xff56,
	KC_End                           0xff57,  /* EOL */
	KC_Begin                         0xff58,  /* BOL */


/* Misc functions */

	KC_Select                        0xff60,  /* Select, mark */
	KC_Print                         0xff61,
	KC_Execute                       0xff62,  /* Execute, run, do */
	KC_Insert                        0xff63,  /* Insert, insert here */
	KC_Undo                          0xff65,
	KC_Redo                          0xff66,  /* Redo, again */
	KC_Menu                          0xff67,
	KC_Find                          0xff68,  /* Find, search */
	KC_Cancel                        0xff69,  /* Cancel, stop, abort, exit */
	KC_Help                          0xff6a,  /* Help */
	KC_Break                         0xff6b,
	KC_Mode_switch                   0xff7e,  /* Character set switch */
	KC_Script_Switch                 0xff7e,  /* Alias for mode_switch */
	KC_Num_Lock                      0xff7f,

/* Keypad functions, keypad numbers cleverly chosen to map to ASCII */

	KC_KP_Space                      0xff80,  /* Space */
	KC_KP_Tab                        0xff89,
	KC_KP_Enter                      0xff8d,  /* Enter */
	KC_KP_F1                         0xff91,  /* PF1, KP_A, ... */
	KC_KP_F2                         0xff92,
	KC_KP_F3                         0xff93,
	KC_KP_F4                         0xff94,
	KC_KP_Home                       0xff95,
	KC_KP_Left                       0xff96,
	KC_KP_Up                         0xff97,
	KC_KP_Right                      0xff98,
	KC_KP_Down                       0xff99,
	KC_KP_Prior                      0xff9a,
	KC_KP_PageUp                     0xff9a,
	KC_KP_Next                       0xff9b,
	KC_KP_PageDown                   0xff9b,
	KC_KP_End                        0xff9c,
	KC_KP_Begin                      0xff9d,
	KC_KP_Insert                     0xff9e,
	KC_KP_Delete                     0xff9f,
	KC_KP_Equal                      0xffbd,  /* Equals */
	KC_KP_Multiply                   0xffaa,
	KC_KP_Add                        0xffab,
	KC_KP_Separator                  0xffac,  /* Separator, often comma */
	KC_KP_Subtract                   0xffad,
	KC_KP_Decimal                    0xffae,
	KC_KP_Divide                     0xffaf,

	KC_KP_0                          0xffb0,
	KC_KP_1                          0xffb1,
	KC_KP_2                          0xffb2,
	KC_KP_3                          0xffb3,
	KC_KP_4                          0xffb4,
	KC_KP_5                          0xffb5,
	KC_KP_6                          0xffb6,
	KC_KP_7                          0xffb7,
	KC_KP_8                          0xffb8,
	KC_KP_9                          0xffb9,

/*
 * Auxilliary functions; note the duplicate definitions for left and right
 * function keys;  Sun keyboards and a few other manufactures have such
 * function key groups on the left and/or right sides of the keyboard.
 * We've not found a keyboard with more than 35 function keys total.
 */

	KC_F1                            0xffbe,
	KC_F2                            0xffbf,
	KC_F3                            0xffc0,
	KC_F4                            0xffc1,
	KC_F5                            0xffc2,
	KC_F6                            0xffc3,
	KC_F7                            0xffc4,
	KC_F8                            0xffc5,
	KC_F9                            0xffc6,
	KC_F10                           0xffc7,
	KC_F11                           0xffc8,
	KC_L1                            0xffc8,
	KC_F12                           0xffc9,
	KC_L2                            0xffc9,
	KC_F13                           0xffca,
	KC_L3                            0xffca,
	KC_F14                           0xffcb,
	KC_L4                            0xffcb,
	KC_F15                           0xffcc,
	KC_L5                            0xffcc,
	KC_F16                           0xffcd,
	KC_L6                            0xffcd,
	KC_F17                           0xffce,
	KC_L7                            0xffce,
	KC_F18                           0xffcf,
	KC_L8                            0xffcf,
	KC_F19                           0xffd0,
	KC_L9                            0xffd0,
	KC_F20                           0xffd1,
	KC_L10                           0xffd1,
	KC_F21                           0xffd2,
	KC_R1                            0xffd2,
	KC_F22                           0xffd3,
	KC_R2                            0xffd3,
	KC_F23                           0xffd4,
	KC_R3                            0xffd4,
	KC_F24                           0xffd5,
	KC_R4                            0xffd5,
	KC_F25                           0xffd6,
	KC_R5                            0xffd6,
	KC_F26                           0xffd7,
	KC_R6                            0xffd7,
	KC_F27                           0xffd8,
	KC_R7                            0xffd8,
	KC_F28                           0xffd9,
	KC_R8                            0xffd9,
	KC_F29                           0xffda,
	KC_R9                            0xffda,
	KC_F30                           0xffdb,
	KC_R10                           0xffdb,
	KC_F31                           0xffdc,
	KC_R11                           0xffdc,
	KC_F32                           0xffdd,
	KC_R12                           0xffdd,
	KC_F33                           0xffde,
	KC_R13                           0xffde,
	KC_F34                           0xffdf,
	KC_R14                           0xffdf,
	KC_F35                           0xffe0,
	KC_R15                           0xffe0,

/* Modifiers */

	KC_Shift_L                       0xffe1,  /* Left shift */
	KC_Shift_R                       0xffe2,  /* Right shift */
	KC_Control_L                     0xffe3,  /* Left control */
	KC_Control_R                     0xffe4,  /* Right control */
	KC_Caps_Lock                     0xffe5,  /* Caps lock */
	KC_Shift_Lock                    0xffe6,  /* Shift lock */

	KC_Meta_L                        0xffe7,  /* Left meta */
	KC_Meta_R                        0xffe8,  /* Right meta */
	KC_Alt_L                         0xffe9,  /* Left alt */
	KC_Alt_R                         0xffea,  /* Right alt */
	KC_Super_L                       0xffeb,  /* Left super */
	KC_Super_R                       0xffec,  /* Right super */
	KC_Hyper_L                       0xffed,  /* Left hyper */
	KC_Hyper_R                       0xffee,  /* Right hyper */
	
	KC_Space                         0x0020,  /* U+0020 SPACE */
	KC_Exclam                        0x0021,  /* U+0021 EXCLAMATION MARK */
	KC_Quotedbl                      0x0022,  /* U+0022 QUOTATION MARK */
	KC_Numbersign                    0x0023,  /* U+0023 NUMBER SIGN */
	KC_Dollar                        0x0024,  /* U+0024 DOLLAR SIGN */
	KC_Percent                       0x0025,  /* U+0025 PERCENT SIGN */
	KC_Ampersand                     0x0026,  /* U+0026 AMPERSAND */
	KC_Apostrophe                    0x0027,  /* U+0027 APOSTROPHE */
	KC_Quote_R                       0x0027,  /* deprecated */
	KC_Paren_L                       0x0028,  /* U+0028 LEFT PARENTHESIS */
	KC_Paren_R                       0x0029,  /* U+0029 RIGHT PARENTHESIS */
	KC_Asterisk                      0x002a,  /* U+002A ASTERISK */
	KC_Plus                          0x002b,  /* U+002B PLUS SIGN */
	KC_Comma                         0x002c,  /* U+002C COMMA */
	KC_Minus                         0x002d,  /* U+002D HYPHEN-MINUS */
	KC_Period                        0x002e,  /* U+002E FULL STOP */
	KC_Slash                         0x002f,  /* U+002F SOLIDUS */
	KC_0                             0x0030,  /* U+0030 DIGIT ZERO */
	KC_1                             0x0031,  /* U+0031 DIGIT ONE */
	KC_2                             0x0032,  /* U+0032 DIGIT TWO */
	KC_3                             0x0033,  /* U+0033 DIGIT THREE */
	KC_4                             0x0034,  /* U+0034 DIGIT FOUR */
	KC_5                             0x0035,  /* U+0035 DIGIT FIVE */
	KC_6                             0x0036,  /* U+0036 DIGIT SIX */
	KC_7                             0x0037,  /* U+0037 DIGIT SEVEN */
	KC_8                             0x0038,  /* U+0038 DIGIT EIGHT */
	KC_9                             0x0039,  /* U+0039 DIGIT NINE */
	KC_Colon                         0x003a,  /* U+003A COLON */
	KC_Semicolon                     0x003b,  /* U+003B SEMICOLON */
	KC_Less                          0x003c,  /* U+003C LESS-THAN SIGN */
	KC_Equal                         0x003d,  /* U+003D EQUALS SIGN */
	KC_Greater                       0x003e,  /* U+003E GREATER-THAN SIGN */
	KC_Question                      0x003f,  /* U+003F QUESTION MARK */
	KC_At                            0x0040,  /* U+0040 COMMERCIAL AT */
	KC_A                             0x0041,  /* U+0041 LATIN CAPITAL LETTER A */
	KC_B                             0x0042,  /* U+0042 LATIN CAPITAL LETTER B */
	KC_C                             0x0043,  /* U+0043 LATIN CAPITAL LETTER C */
	KC_D                             0x0044,  /* U+0044 LATIN CAPITAL LETTER D */
	KC_E                             0x0045,  /* U+0045 LATIN CAPITAL LETTER E */
	KC_F                             0x0046,  /* U+0046 LATIN CAPITAL LETTER F */
	KC_G                             0x0047,  /* U+0047 LATIN CAPITAL LETTER G */
	KC_H                             0x0048,  /* U+0048 LATIN CAPITAL LETTER H */
	KC_I                             0x0049,  /* U+0049 LATIN CAPITAL LETTER I */
	KC_J                             0x004a,  /* U+004A LATIN CAPITAL LETTER J */
	KC_K                             0x004b,  /* U+004B LATIN CAPITAL LETTER K */
	KC_L                             0x004c,  /* U+004C LATIN CAPITAL LETTER L */
	KC_M                             0x004d,  /* U+004D LATIN CAPITAL LETTER M */
	KC_N                             0x004e,  /* U+004E LATIN CAPITAL LETTER N */
	KC_O                             0x004f,  /* U+004F LATIN CAPITAL LETTER O */
	KC_P                             0x0050,  /* U+0050 LATIN CAPITAL LETTER P */
	KC_Q                             0x0051,  /* U+0051 LATIN CAPITAL LETTER Q */
	KC_R                             0x0052,  /* U+0052 LATIN CAPITAL LETTER R */
	KC_S                             0x0053,  /* U+0053 LATIN CAPITAL LETTER S */
	KC_T                             0x0054,  /* U+0054 LATIN CAPITAL LETTER T */
	KC_U                             0x0055,  /* U+0055 LATIN CAPITAL LETTER U */
	KC_V                             0x0056,  /* U+0056 LATIN CAPITAL LETTER V */
	KC_W                             0x0057,  /* U+0057 LATIN CAPITAL LETTER W */
	KC_X                             0x0058,  /* U+0058 LATIN CAPITAL LETTER X */
	KC_Y                             0x0059,  /* U+0059 LATIN CAPITAL LETTER Y */
	KC_Z                             0x005a,  /* U+005A LATIN CAPITAL LETTER Z */
	KC_Bracket_L                     0x005b,  /* U+005B LEFT SQUARE BRACKET */
	KC_Backslash                     0x005c,  /* U+005C REVERSE SOLIDUS */
	KC_Bracket_R                     0x005d,  /* U+005D RIGHT SQUARE BRACKET */
	KC_asciicircum                   0x005e,  /* U+005E CIRCUMFLEX ACCENT */
	KC_Underscore                    0x005f,  /* U+005F LOW LINE */
	KC_Grave                         0x0060,  /* U+0060 GRAVE ACCENT */
	KC_Quote_L                       0x0060,  /* deprecated */
	KC_a                             0x0061,  /* U+0061 LATIN SMALL LETTER A */
	KC_b                             0x0062,  /* U+0062 LATIN SMALL LETTER B */
	KC_c                             0x0063,  /* U+0063 LATIN SMALL LETTER C */
	KC_d                             0x0064,  /* U+0064 LATIN SMALL LETTER D */
	KC_e                             0x0065,  /* U+0065 LATIN SMALL LETTER E */
	KC_f                             0x0066,  /* U+0066 LATIN SMALL LETTER F */
	KC_g                             0x0067,  /* U+0067 LATIN SMALL LETTER G */
	KC_h                             0x0068,  /* U+0068 LATIN SMALL LETTER H */
	KC_i                             0x0069,  /* U+0069 LATIN SMALL LETTER I */
	KC_j                             0x006a,  /* U+006A LATIN SMALL LETTER J */
	KC_k                             0x006b,  /* U+006B LATIN SMALL LETTER K */
	KC_l                             0x006c,  /* U+006C LATIN SMALL LETTER L */
	KC_m                             0x006d,  /* U+006D LATIN SMALL LETTER M */
	KC_n                             0x006e,  /* U+006E LATIN SMALL LETTER N */
	KC_o                             0x006f,  /* U+006F LATIN SMALL LETTER O */
	KC_p                             0x0070,  /* U+0070 LATIN SMALL LETTER P */
	KC_q                             0x0071,  /* U+0071 LATIN SMALL LETTER Q */
	KC_r                             0x0072,  /* U+0072 LATIN SMALL LETTER R */
	KC_s                             0x0073,  /* U+0073 LATIN SMALL LETTER S */
	KC_t                             0x0074,  /* U+0074 LATIN SMALL LETTER T */
	KC_u                             0x0075,  /* U+0075 LATIN SMALL LETTER U */
	KC_v                             0x0076,  /* U+0076 LATIN SMALL LETTER V */
	KC_w                             0x0077,  /* U+0077 LATIN SMALL LETTER W */
	KC_x                             0x0078,  /* U+0078 LATIN SMALL LETTER X */
	KC_y                             0x0079,  /* U+0079 LATIN SMALL LETTER Y */
	KC_z                             0x007a,  /* U+007A LATIN SMALL LETTER Z */
	KC_Brace_L                       0x007b,  /* U+007B LEFT CURLY BRACKET */
	KC_Bar                           0x007c,  /* U+007C VERTICAL LINE */
	KC_Brace_R                       0x007d,  /* U+007D RIGHT CURLY BRACKET */
	KC_asciitilde                    0x007e  /* U+007E TILDE */
};
