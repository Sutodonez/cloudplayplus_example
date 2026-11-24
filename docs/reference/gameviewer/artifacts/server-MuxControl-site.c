
void FUN_140714230(longlong param_1,undefined8 *param_2)

{
  longlong *plVar1;
  ulonglong uVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  char *pcVar6;
  uint uVar7;
  uint uVar8;
  longlong lVar9;
  undefined8 uStackX_18;
  undefined1 auStackX_20 [8];
  longlong lStack_198;
  undefined8 uStack_190;
  int aiStack_188 [2];
  int iStack_180;
  ulonglong uStack_170;
  int aiStack_168 [6];
  undefined1 auStack_150 [280];
  
  lVar9 = 0;
  uStackX_18 = uStackX_18 & 0xffffffff00000000;
  thunk_FUN_140276890(auStackX_20,*param_2);
  cVar3 = thunk_FUN_140279870(auStackX_20);
  if (cVar3 == '\0') {
    cVar3 = thunk_FUN_140202db0(4);
    if (cVar3 != '\0') {
      lVar5 = thunk_FUN_1402088f0(auStack_150,4,"Terminal.MuxControl",
                                  "D:\\nrd-windows-client-gitlab\\work\\1131\\408844\\source\\src\\server_core\\business\\terminal\\terminal_mux_control_server.cpp"
                                  ,0x52,0);
      lVar9 = 1;
      uStackX_18 = CONCAT44(uStackX_18._4_4_,1);
      if (*(char *)(lVar5 + 0xf8) != '\0') {
        thunk_FUN_14015d4f0(lVar5 + 0x10,"terminal_mux_control result=failed stage=impersonate");
      }
    }
    if (lVar9 != 0) {
      thunk_FUN_140208c50(auStack_150);
    }
    iVar4 = _Mtx_lock(param_1 + 0x78);
    if (iVar4 != 0) {
LAB_1407147db:
                    /* WARNING: Subroutine does not return */
      std::_Throw_Cpp_error(5);
    }
    if (*(int *)(param_1 + 0xc4) == 0x7fffffff) {
LAB_1407147c9:
      *(undefined4 *)(param_1 + 0xc4) = 0x7ffffffe;
                    /* WARNING: Subroutine does not return */
      std::_Throw_Cpp_error(6);
    }
    *(undefined2 *)(param_1 + 0x111) = 1;
    _Mtx_unlock(param_1 + 0x78);
    _Cnd_broadcast(param_1 + 200);
  }
  else {
    plVar1 = (longlong *)(param_1 + 0x48);
    lStack_198 = (longlong)plVar1;
    if (0xf < *(ulonglong *)(param_1 + 0x60)) {
      lStack_198 = *plVar1;
    }
    uStack_190 = *(undefined8 *)(param_1 + 0x58);
    thunk_FUN_140d5b470(*(undefined8 *)(param_1 + 0x40),aiStack_168,&lStack_198);
    iVar4 = _Mtx_lock(param_1 + 0x78);
    if (iVar4 != 0) goto LAB_1407147db;
    if (*(int *)(param_1 + 0xc4) == 0x7fffffff) goto LAB_1407147c9;
    *(bool *)(param_1 + 0x112) = aiStack_168[0] == 0;
    *(undefined1 *)(param_1 + 0x111) = 1;
    _Mtx_unlock(param_1 + 0x78);
    _Cnd_broadcast(param_1 + 200);
    if (aiStack_168[0] == 0) {
      cVar3 = thunk_FUN_140202db0(2);
      if (cVar3 != '\0') {
        lVar5 = thunk_FUN_1402088f0(auStack_150,2,"Terminal.MuxControl",
                                    "D:\\nrd-windows-client-gitlab\\work\\1131\\408844\\source\\src\\server_core\\business\\terminal\\terminal_mux_control_server.cpp"
                                    ,0x66,0);
        lVar9 = 4;
        uStackX_18 = CONCAT44(uStackX_18._4_4_,4);
        if (*(char *)(lVar5 + 0xf8) != '\0') {
          thunk_FUN_14015d4f0(lVar5 + 0x10,"terminal_mux_control result=started server_name=");
        }
        if (*(char *)(lVar5 + 0xf8) != '\0') {
          thunk_FUN_14015ece0(lVar5 + 0x10,plVar1);
        }
      }
      if (lVar9 != 0) {
        thunk_FUN_140208c50(auStack_150);
      }
      uVar8 = 0;
      lStack_198 = param_1 + 0x110;
      pcVar6 = (char *)thunk_FUN_1401dea50(lStack_198);
      cVar3 = *pcVar6;
      while (cVar3 == '\0') {
        cVar3 = thunk_FUN_140202db0(2);
        uVar7 = uVar8;
        if (cVar3 != '\0') {
          lVar9 = thunk_FUN_1402088f0(auStack_150,2,"Terminal.MuxControl",
                                      "D:\\nrd-windows-client-gitlab\\work\\1131\\408844\\source\\src\\server_core\\business\\terminal\\terminal_mux_control_server.cpp"
                                      ,0x68,0);
          uVar7 = uVar8 | 8;
          uStackX_18 = CONCAT44(uStackX_18._4_4_,uVar8) | 8;
          if (*(char *)(lVar9 + 0xf8) != '\0') {
            thunk_FUN_14015d4f0(lVar9 + 0x10,"terminal_mux_control stage=accept_wait server_name=");
          }
          if (*(char *)(lVar9 + 0xf8) != '\0') {
            thunk_FUN_14015ece0(lVar9 + 0x10,plVar1);
          }
        }
        if ((uVar7 & 8) != 0) {
          uVar7 = uVar7 & 0xfffffff7;
          thunk_FUN_140208c50(auStack_150);
        }
        thunk_FUN_140d5a0a0(*(undefined8 *)(param_1 + 0x40),aiStack_188);
        if (aiStack_188[0] != 0) {
          pcVar6 = (char *)thunk_FUN_1401dea50(lStack_198);
          if (*pcVar6 == '\0') {
            cVar3 = thunk_FUN_140202db0(4);
            uVar8 = uVar7;
            if (cVar3 != '\0') {
              lVar9 = thunk_FUN_1402088f0(auStack_150,4,"Terminal.MuxControl",
                                          "D:\\nrd-windows-client-gitlab\\work\\1131\\408844\\source\\src\\server_core\\business\\terminal\\terminal_mux_control_server.cpp"
                                          ,0x6c,0);
              uVar8 = 0x10;
              uStackX_18 = CONCAT44(uStackX_18._4_4_,uVar7) | 0x10;
              if (*(char *)(lVar9 + 0xf8) != '\0') {
                thunk_FUN_14015d4f0(lVar9 + 0x10,
                                    "terminal_mux_control result=failed stage=accept server_name=");
              }
              if ((((*(char *)(lVar9 + 0xf8) != '\0') &&
                   (thunk_FUN_14015ece0(lVar9 + 0x10,plVar1), *(char *)(lVar9 + 0xf8) != '\0')) &&
                  (thunk_FUN_14015d4f0(lVar9 + 0x10," status="), *(char *)(lVar9 + 0xf8) != '\0'))
                 && ((thunk_FUN_140d59360(lVar9 + 0x10,aiStack_188[0]),
                     *(char *)(lVar9 + 0xf8) != '\0' &&
                     (thunk_FUN_14015d4f0(lVar9 + 0x10," os_code="), *(char *)(lVar9 + 0xf8) != '\0'
                     )))) {
                std::basic_ostream<char,std::char_traits<char>_>::operator<<
                          ((basic_ostream<char,std::char_traits<char>_> *)(lVar9 + 0x10),iStack_180)
                ;
              }
            }
            if ((uVar8 & 0x10) != 0) {
              thunk_FUN_140208c50(auStack_150);
            }
          }
          uVar2 = uStack_170;
          if (uStack_170 != 0) {
            thunk_FUN_140d59270(uStack_170);
            FUN_14005a335(uVar2,8);
          }
          break;
        }
        cVar3 = thunk_FUN_140202db0(2);
        uVar8 = uVar7;
        if (cVar3 != '\0') {
          lVar9 = thunk_FUN_1402088f0(auStack_150,2,"Terminal.MuxControl",
                                      "D:\\nrd-windows-client-gitlab\\work\\1131\\408844\\source\\src\\server_core\\business\\terminal\\terminal_mux_control_server.cpp"
                                      ,0x71,0);
          uVar8 = uVar7 | 0x20;
          uStackX_18 = CONCAT44(uStackX_18._4_4_,uVar7) | 0x20;
          if (*(char *)(lVar9 + 0xf8) != '\0') {
            thunk_FUN_14015d4f0(lVar9 + 0x10,"terminal_mux_control stage=accepted server_name=");
          }
          if (*(char *)(lVar9 + 0xf8) != '\0') {
            thunk_FUN_14015ece0(lVar9 + 0x10,plVar1);
          }
        }
        if ((uVar8 & 0x20) != 0) {
          uVar8 = uVar8 & 0xffffffdf;
          thunk_FUN_140208c50(auStack_150);
        }
        uStackX_18 = uStack_170;
        uStack_170 = 0;
        thunk_FUN_140714960(param_1,&uStackX_18);
        uVar2 = uStack_170;
        if (uStack_170 != 0) {
          thunk_FUN_140d59270(uStack_170);
          FUN_14005a335(uVar2,8);
        }
        cVar3 = *pcVar6;
      }
    }
    else {
      cVar3 = thunk_FUN_140202db0(4);
      if (cVar3 != '\0') {
        lVar5 = thunk_FUN_1402088f0(auStack_150,4,"Terminal.MuxControl",
                                    "D:\\nrd-windows-client-gitlab\\work\\1131\\408844\\source\\src\\server_core\\business\\terminal\\terminal_mux_control_server.cpp"
                                    ,99,0);
        lVar9 = 2;
        uStackX_18 = CONCAT44(uStackX_18._4_4_,2);
        if (*(char *)(lVar5 + 0xf8) != '\0') {
          thunk_FUN_14015d4f0(lVar5 + 0x10,"terminal_mux_control result=failed stage=listen code=");
        }
        if (*(char *)(lVar5 + 0xf8) != '\0') {
          thunk_FUN_140d59360(lVar5 + 0x10,aiStack_168[0]);
        }
      }
      if (lVar9 != 0) {
        thunk_FUN_140208c50(auStack_150);
      }
    }
  }
  thunk_FUN_140276ad0(auStackX_20);
  thunk_FUN_140166360(param_2);
  return;
}

