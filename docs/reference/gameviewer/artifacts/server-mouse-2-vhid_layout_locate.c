
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 * FUN_140dfcf80(undefined4 *param_1,undefined8 param_2)

{
  char cVar1;
  ulong uVar2;
  longlong lVar3;
  longlong lVar4;
  undefined1 auStack_308 [32];
  undefined4 *puStack_2e8;
  uint uStack_2e0;
  ulong uStack_2d8;
  undefined4 uStack_2d4;
  undefined4 uStack_2d0;
  undefined4 uStack_2cc;
  undefined1 auStack_2c8 [272];
  undefined1 auStack_1b8 [400];
  ulonglong uStack_28;
  
  uStack_28 = DAT_141e01000 ^ (ulonglong)auStack_308;
  lVar4 = 0;
  uStack_2d0 = 0;
  memset(auStack_1b8,0,400);
  uStack_2d8 = 0;
  uStack_2cc = 400;
  uStack_2e0 = 0;
  puStack_2e8 = &uStack_2cc;
  uVar2 = CM_Get_Device_Interface_PropertyW(param_2,&DAT_1416b88a8,&uStack_2d8,auStack_1b8);
  if ((uVar2 == 0) && (uStack_2d8 == 0x12)) {
    uStack_2d4 = 0;
    uVar2 = CM_Locate_DevNodeW(&uStack_2d4,auStack_1b8,0);
    if (uVar2 == 0) {
      *param_1 = uStack_2d4;
      *(undefined1 *)(param_1 + 1) = 1;
      return param_1;
    }
    cVar1 = thunk_FUN_140202db0(3);
    if (cVar1 != '\0') {
      uStack_2e0 = uStack_2e0 & 0xffffff00;
      puStack_2e8 = (undefined4 *)CONCAT44(puStack_2e8._4_4_,0x38);
      lVar3 = thunk_FUN_1402088f0(auStack_2c8,3,"Server.Input",
                                  "D:\\nrd-windows-client-gitlab\\work\\1131\\408844\\source\\src\\server_core\\support\\input\\input_injector.cpp"
                                 );
      lVar4 = 2;
      uStack_2d0 = 2;
      if (*(char *)(lVar3 + 0xf8) != '\0') {
        thunk_FUN_14015d4f0(lVar3 + 0x10,
                            "vhid_report_layout result=failed stage=locate_device code=");
      }
      if (*(char *)(lVar3 + 0xf8) != '\0') {
        std::basic_ostream<char,std::char_traits<char>_>::operator<<
                  ((basic_ostream<char,std::char_traits<char>_> *)(lVar3 + 0x10),uVar2);
      }
    }
  }
  else {
    cVar1 = thunk_FUN_140202db0(3);
    if (cVar1 != '\0') {
      uStack_2e0 = uStack_2e0 & 0xffffff00;
      puStack_2e8 = (undefined4 *)CONCAT44(puStack_2e8._4_4_,0x32);
      lVar3 = thunk_FUN_1402088f0(auStack_2c8,3,"Server.Input",
                                  "D:\\nrd-windows-client-gitlab\\work\\1131\\408844\\source\\src\\server_core\\support\\input\\input_injector.cpp"
                                 );
      lVar4 = 1;
      uStack_2d0 = 1;
      if (*(char *)(lVar3 + 0xf8) != '\0') {
        thunk_FUN_14015d4f0(lVar3 + 0x10,
                            "vhid_report_layout result=failed stage=interface_instance code=");
      }
      if (((*(char *)(lVar3 + 0xf8) != '\0') &&
          (std::basic_ostream<char,std::char_traits<char>_>::operator<<
                     ((basic_ostream<char,std::char_traits<char>_> *)(lVar3 + 0x10),uVar2),
          *(char *)(lVar3 + 0xf8) != '\0')) &&
         (thunk_FUN_14015d4f0(lVar3 + 0x10," property_type="), *(char *)(lVar3 + 0xf8) != '\0')) {
        std::basic_ostream<char,std::char_traits<char>_>::operator<<
                  ((basic_ostream<char,std::char_traits<char>_> *)(lVar3 + 0x10),uStack_2d8);
      }
    }
  }
  if (lVar4 != 0) {
    thunk_FUN_140208c50(auStack_2c8);
  }
  *(undefined1 *)(param_1 + 1) = 0;
  return param_1;
}

