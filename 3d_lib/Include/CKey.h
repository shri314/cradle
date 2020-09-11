#ifndef __CKEY_H
 #define __CKEY_H

 #include <bios.h>   //for _bios_keybrd,bioskey,etc

 #define K_WAIT_HIT   (0)     //Wait until a key is hit. Like getch(). (Non-preemptive)
 #define K_IF_HIT_L   (1)     //GetKey only if key is hit and latch the value until next call. (Preemptive)
 #define K_IF_HIT_C   (2)     //GetKey only if key is hit and clear the value if no hit is present during next call. (Preemptive)


 #define K_MSC        _MSC()
 #define K_AC         _AC()
 #define K_SC         _SC()
 #define K_SHFT_Pr    _SHFT_Pr()
 #define K_RSHT_Pr    _RSHT_Pr()
 #define K_LSHT_Pr    _LSHT_Pr()
 #define K_CTRL_Pr    _CTRL_Pr()
 #define K_ALT_Pr     _ALT_Pr()
 #define K_SCLK_On    _SCLK_ON()
 #define K_NMLK_On    _NMLK_ON()
 #define K_CPLK_On    _CPLK_ON()
 #define K_INS_On     _INS_ON()
 #define K_LCTRL_Pr   _LCTRL_Pr()
 #define K_LALT_Pr    _LALT_Pr()
 #define K_RCTRL_Pr   _RCTRL_Pr()
 #define K_RALT_Pr    _RALT_Pr()
 #define K_SCLK_Pr    _SCLK_Pr()
 #define K_NMLK_Pr    _NMLK_Pr()
 #define K_CPLK_Pr    _CPLK_Pr()
 #define K_SYRQ_Pr    _SYRQ_Pr()

 //////////////////////////////////////////////////////////////////////

 #define K_NO_KEY                    (0)
 #define K_ESCAPE                    (1)
 #define K_F1                       (59)
 #define K_F2	                    (60)
 #define K_F3	                    (61)
 #define K_F4	                    (62)
 #define K_F5	                    (63)
 #define K_F6	                    (64)
 #define K_F7	                    (65)
 #define K_F8	                    (66)
 #define K_F9	                    (67)
 #define K_F10	                    (68)
 #define K_BEGIN_QUOTE              (41)
 #define K_TILDE                    (41)
 #define K_1                         (2)
 #define K_EXCLAMATION               (2)
 #define K_2                         (3)
 #define K_AT_THE_RATE_OF            (3)
 #define K_3                         (4)
 #define K_HASH                      (4)
 #define K_4                         (5)
 #define K_DOLLAR                    (5)
 #define K_5                         (6)
 #define K_PERCENT                   (6)
 #define K_6                         (7)
 #define K_CARET                     (7)
 #define K_CIRCUMFLEX                (7)
 #define K_7                         (8)
 #define K_AMRERSAND                 (8)
 #define K_8                         (9)
 #define K_MULTIPLY                  (9)
 #define K_STAR                      (9)
 #define K_9                        (10)
 #define K_BEGIN_PARENTHESES        (10)
 #define K_0                        (11)
 #define K_END_PARENTHESES          (11)
 #define K_MINUS                    (12)
 #define K_DASH                     (12)
 #define K_UNDERSCORE               (12)
 #define K_EQUALTO                  (13)
 #define K_PLUS                     (13)
 #define K_BACKSLASH                (43)
 #define K_PIPE                     (43)
 #define K_BACK_SPACE               (14)
 #define K_INSERT                   (82)
 #define K_HOME                     (71)
 #define K_PAGE_UP                  (73)
 #define K_TAB                      (15)
 #define K_Q                        (16)
 #define K_q                        (16)
 #define K_W                        (17)
 #define K_w                        (17)
 #define K_E                        (18)
 #define K_e                        (18)
 #define K_R                        (19)
 #define K_r                        (19)
 #define K_T                        (20)
 #define K_t                        (20)
 #define K_Y                        (21)
 #define K_y                        (21)
 #define K_U                        (22)
 #define K_u                        (22)
 #define K_I                        (23)
 #define K_i                        (23)
 #define K_O                        (24)
 #define K_o                        (24)
 #define K_P                        (25)
 #define K_p                        (25)
 #define K_OPEN_SQUARE_BRACE        (26)
 #define K_OPEN_CURLY_BRACE         (26)
 #define K_OPEN_BRACE               (26)
 #define K_CLOSE_SQUARE_BRACE       (27)
 #define K_CLOSE_CURLY_BRACE        (27)
 #define K_CLOSE_BRACE              (27)
 #define K_ENTER                    (28)
 #define K_RETURN                   (28)
 #define K_DELETE                   (83)
 #define K_END                      (79)
 #define K_PAGE_DOWN                (81)
 #define K_A                        (30)
 #define K_a                        (30)
 #define K_S                        (31)
 #define K_s                        (31)
 #define K_D                        (32)
 #define K_d                        (32)
 #define K_F                        (33)
 #define K_f                        (33)
 #define K_G                        (34)
 #define K_g                        (34)
 #define K_H                        (35)
 #define K_h                        (35)
 #define K_J                        (36)
 #define K_j                        (36)
 #define K_K                        (37)
 #define K_k                        (37)
 #define K_L                        (38)
 #define K_l                        (38)
 #define K_SEMI_COLON               (39)
 #define K_COLON                    (39)
 #define K_END_QUOTE                (40)
 #define K_DOUBLE_QUOTES            (40)
 #define K_Z                        (44)
 #define K_z                        (44)
 #define K_X                        (45)
 #define K_x                        (45)
 #define K_C                        (46)
 #define K_c                        (46)
 #define K_V                        (47)
 #define K_v                        (47)
 #define K_B                        (48)
 #define K_b                        (48)
 #define K_N                        (49)
 #define K_n                        (49)
 #define K_M                        (50)
 #define K_m                        (50)
 #define K_COMMA                    (51)
 #define K_LESS_THAN                (51)
 #define K_DOT                      (52)
 #define K_FULL_STOP                (52)
 #define K_DECIMAL_POINT            (52)
 #define K_GREATER_THAN             (52)
 #define K_SLASH                    (53)
 #define K_DIVIDE                   (53)
 #define K_QUESTION_MARK            (53)
 #define K_UP_ARROW                 (72)
 #define K_SPACE                    (57)
 #define K_LEFT_ARROW               (75)
 #define K_DOWN_ARROW               (80)
 #define K_RIGHT_ARROW              (77)
 //////////////////////////////////////////////////////////

 #define K_NUM_SLASH                (53)
 #define K_NUM_DIVIDE               (53)
 #define K_NUM_MULTIPLY             (55)
 #define K_NUM_STAR                 (55)
 #define K_NUM_DASH                 (74)
 #define K_NUM_MINUS                (74)
 #define K_NUM_HOME                 (71)
 #define K_NUM_7                    (71)
 #define K_NUM_UP_ARROW             (72)
 #define K_NUM_8                    (72)
 #define K_NUM_PAGE_UP              (73)
 #define K_NUM_9                    (73)
 #define K_NUM_PLUS                 (78)
 #define K_NUM_LEFT_ARROW           (75)
 #define K_NUM_4                    (75)
 #define K_NUM_5                    (76)  //   ONLY WHEN NUM NOT LOCKED
 #define K_NUM_RIGHT_ARROW          (77)
 #define K_NUM_6                    (77)
 #define K_NUM_END                  (79)
 #define K_NUM_1                    (79)
 #define K_NUM_DOWN_ARROW           (80)
 #define K_NUM_2                    (80)
 #define K_NUM_PAGE_DOWN            (81)
 #define K_NUM_3                    (81)
 #define K_NUM_ENTER                (28)
 #define K_NUM_RETURN               (28)
 #define K_NUM_INSERT               (82)
 #define K_NUM_0                    (82)
 #define K_NUM_DELETE               (83)
 #define K_NUM_DOT                  (83)
 #define K_NUM_DECIMAL_POINT        (83)
 #define K_NUM_FULL_STOP            (83)
////////////////////////////////////////////////////////////////////////////

union __SPKY
{
   unsigned int v;
   struct
   {
      unsigned int aRSHT_P  : 1;
      unsigned int aLSHT_P  : 1;
      unsigned int aCTRL_P  : 1;
      unsigned int aALT_P   : 1;
      unsigned int aSCLK_ON : 1;
      unsigned int aNMLK_ON : 1;
      unsigned int aCPLK_ON : 1;
      unsigned int aINS_ON  : 1;
      unsigned int aLCTRL_P : 1;
      unsigned int aLALT_P  : 1;
      unsigned int aRCTRL_P : 1;
      unsigned int aRALT_P  : 1;
      unsigned int aSCLK_P  : 1;
      unsigned int aNMLK_P  : 1;
      unsigned int aCPLK_P  : 1;
      unsigned int aSYRQ_P  : 1;
   } a;
};

union __CODE
{
   unsigned int v;
   unsigned char c[2];
};


class CKey
{
   private:
      static __SPKY s;
      static __CODE k;
      static unsigned int msc;

   public:
      static int GetKey(int command = 0);
      static void Clear()             {   s.v = 0, k.v = 0;                     }
      static unsigned int _AC()       {   return k.c[0];                        }
      static unsigned int _SC()       {   return k.c[1];                        }
      static unsigned int _SHFT_Pr()  {   return (s.a.aLSHT_P | s.a.aRSHT_P);   }
      static unsigned int _RSHT_Pr()  {   return s.a.aRSHT_P;                   }
      static unsigned int _LSHT_Pr()  {   return s.a.aLSHT_P;                   }
      static unsigned int _CTRL_Pr()  {   return s.a.aCTRL_P;                   }
      static unsigned int _ALT_Pr()   {   return s.a.aALT_P;                    }
      static unsigned int _SCLK_ON()  {   return s.a.aSCLK_ON;                  }
      static unsigned int _NMLK_ON()  {   return s.a.aNMLK_ON;                  }
      static unsigned int _CPLK_ON()  {   return s.a.aCPLK_ON;                  }
      static unsigned int _INS_ON()   {   return s.a.aINS_ON;                   }
      static unsigned int _LCTRL_Pr() {   return s.a.aLCTRL_P;                  }
      static unsigned int _LALT_Pr()  {   return s.a.aLALT_P;                   }
      static unsigned int _RCTRL_Pr() {   return s.a.aRCTRL_P;                  }
      static unsigned int _RALT_Pr()  {   return s.a.aRALT_P;                   }
      static unsigned int _SCLK_Pr()  {   return s.a.aSCLK_P;                   }
      static unsigned int _NMLK_Pr()  {   return s.a.aNMLK_P;                   }
      static unsigned int _CPLK_Pr()  {   return s.a.aCPLK_P;                   }
      static unsigned int _SYRQ_Pr()  {   return s.a.aSYRQ_P;                   }
      static unsigned int _MSC();
};

#endif