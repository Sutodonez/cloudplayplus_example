
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_1405aef00(undefined1 *param_1,undefined1 param_2)

{
  undefined8 uVar1;
  char cVar2;
  size_t sVar3;
  longlong lVar4;
  bool bVar5;
  undefined1 auStackY_1a8 [32];
  undefined1 auStack_170 [272];
  ulonglong auStack_60 [9];
  
  auStack_60[8] = DAT_141e01000 ^ (ulonglong)auStackY_1a8;
  bVar5 = false;
  uVar1 = *(undefined8 *)(param_1 + 8);
  auStack_60[4] = 0;
  auStack_60[5] = 0;
  auStack_60[6] = 0;
  auStack_60[7] = 0;
  thunk_FUN_14015f910(auStack_60 + 4,L"virtual_mouse_switch",0x14);
  auStack_60[0] = 0;
  auStack_60[1] = 0;
  auStack_60[2] = 0;
  auStack_60[3] = 0;
  sVar3 = wcslen(L"global");
  thunk_FUN_14015f910(auStack_60,L"global",sVar3);
  thunk_FUN_14022b240(uVar1,auStack_60);
  if (7 < auStack_60[3]) {
    if (0xfff < auStack_60[3] * 2 + 2) {
      if (0x1f < (auStack_60[0] - *(longlong *)(auStack_60[0] - 8)) - 8) {
                    /* WARNING: Subroutine does not return */
        _invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
      }
    }
    FUN_14005a335();
  }
  auStack_60[2] = 0;
  auStack_60[3] = 7;
  auStack_60[0] = auStack_60[0] & 0xffffffffffff0000;
  if (7 < auStack_60[7]) {
    if (0xfff < auStack_60[7] * 2 + 2) {
      if (0x1f < (auStack_60[4] - *(longlong *)(auStack_60[4] + -8)) - 8) {
                    /* WARNING: Subroutine does not return */
        _invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
      }
    }
    FUN_14005a335();
  }
  *param_1 = param_2;
  cVar2 = thunk_FUN_140202db0(2);
  if (cVar2 != '\0') {
    lVar4 = thunk_FUN_1402088f0(auStack_170,2,"Server.Settings",
                                "D:\\nrd-windows-client-gitlab\\work\\1131\\408844\\source\\src\\server_core\\business\\input\\mouse\\virtual_mouse_switch_setting_manager.cpp"
                               );
    bVar5 = true;
    if (*(char *)(lVar4 + 0xf8) != '\0') {
      thunk_FUN_14015d4f0(lVar4 + 0x10,"virtual_mouse_setting result=updated enabled=");
    }
    if (*(char *)(lVar4 + 0xf8) != '\0') {
      std::basic_ostream<char,std::char_traits<char>_>::operator<<
                ((basic_ostream<char,std::char_traits<char>_> *)(lVar4 + 0x10),(bool)*param_1);
    }
  }
  if (bVar5) {
    thunk_FUN_140208c50(auStack_170);
  }
  return;
}

