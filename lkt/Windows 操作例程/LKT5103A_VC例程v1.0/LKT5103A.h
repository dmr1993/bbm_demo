int WINAPI EK_Open(int p); 
int WINAPI EK_Close(); 
int WINAPI EK_Reset(int *AtrLen, unsigned char *atr); 
int WINAPI EK_Exchange_APDU(int CmdLen, unsigned char *cmd, int *ResLen, unsigned char *ResBuf);