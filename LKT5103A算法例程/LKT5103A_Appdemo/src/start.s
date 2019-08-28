;=============ÇëÎðÐÞ¸Ä=====================================
                AREA    RESET, DATA, READONLY
                AREA    |.text|, CODE, READONLY

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  __main

                LDR     R0, =__main
                BX      R0
                ENDP


                END
;==========================================================