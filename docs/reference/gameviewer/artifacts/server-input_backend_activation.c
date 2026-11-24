
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

char FUN_140e03580(longlong param_1,char param_2)

{
  longlong lVar1;
  int *piVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  longlong lVar6;
  longlong lVar7;
  int *piVar8;
  char cVar9;
  __uint64 _Var10;
  undefined1 auStackY_1c8 [32];
  char *pcStack_190;
  longlong lStack_188;
  longlong lStack_178;
  undefined1 auStack_170 [280];
  char *pcStack_58;
  longlong lStack_50;
  undefined8 uStack_48;
  ulonglong uStack_40;
  ulonglong uStack_38;
  
  uStack_38 = DAT_141e01000 ^ (ulonglong)auStackY_1c8;
  lVar7 = 0;
  lVar1 = param_1 + 8;
  lStack_178 = lVar1;
  iVar4 = _Mtx_lock(lVar1);
  if (iVar4 != 0) {
                    /* WARNING: Subroutine does not return */
    std::_Throw_Cpp_error(5);
  }
  if (*(int *)(param_1 + 0x54) == 0x7fffffff) {
    *(undefined4 *)(param_1 + 0x54) = 0x7ffffffe;
                    /* WARNING: Subroutine does not return */
    std::_Throw_Cpp_error(6);
  }
  cVar9 = *(char *)(param_1 + 0xcc);
  if (param_2 != cVar9) {
    if (param_2 == '\0') {
      FUN_140dfd230(param_1,"probe_unavailable");
      FUN_140e00f80(param_1);
      *(undefined2 *)(param_1 + 0xcd) = 0;
      *(undefined1 *)(param_1 + 0xcf) = 0;
      cVar9 = '\0';
    }
    else {
      cVar9 = (**(code **)(**(longlong **)(param_1 + 0x58) + 8))();
      if (cVar9 == '\0') {
        cVar9 = thunk_FUN_140202db0(3);
        if (cVar9 != '\0') {
          lVar6 = thunk_FUN_1402088f0(auStack_170,3);
          lVar7 = 1;
          if (*(char *)(lVar6 + 0xf8) != '\0') {
            thunk_FUN_14015d4f0(lVar6 + 0x10,
                                "input_backend_activation result=failed current=send_input requested=vhid reason=vhid_open_failed"
                               );
          }
        }
        if (lVar7 != 0) {
          thunk_FUN_140208c50(auStack_170);
        }
        pcStack_58 = (char *)0x0;
        lStack_50 = 0;
        uStack_48 = 0;
        uStack_40 = 0;
        pcStack_58 = (char *)thunk_FUN_140aba630(0x60);
        uStack_48 = 0x51;
        uStack_40 = 0x5f;
        builtin_strncpy(pcStack_58,
                        "[InputDiag] side=server stage=vhid_activate result=failed reason=vhid_open_failed"
                        ,0x52);
        thunk_FUN_140df60d0(&pcStack_58);
        if (0xf < uStack_40) {
          if ((0xfff < uStack_40 + 1) &&
             ((char *)0x1f < pcStack_58 + (-8 - *(longlong *)(pcStack_58 + -8)))) {
                    /* WARNING: Subroutine does not return */
            _invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
          }
          FUN_14005a335();
        }
        cVar9 = '\0';
      }
      else {
        thunk_FUN_140e8a420(param_1 + 0xa0,&pcStack_190);
        pcStack_58 = pcStack_190;
        lStack_50 = (lStack_188 - (longlong)pcStack_190) / 0x28;
        uVar5 = FUN_140e031a0(param_1,&pcStack_58);
        piVar8 = (int *)(pcStack_190 + (ulonglong)uVar5 * 0x28);
        _Var10 = (lStack_188 - (longlong)pcStack_190) / 0x28 - (ulonglong)uVar5;
        piVar2 = piVar8 + _Var10 * 10;
        for (; piVar8 != piVar2; piVar8 = piVar8 + 10) {
          if (*piVar8 == 0) {
            (**(code **)(**(longlong **)(param_1 + 0x58) + 0x18))();
            cVar9 = thunk_FUN_140202db0(3);
            if (cVar9 != '\0') {
              lVar6 = thunk_FUN_1402088f0(auStack_170,3);
              lVar7 = 2;
              if (*(char *)(lVar6 + 0xf8) != '\0') {
                thunk_FUN_14015d4f0(lVar6 + 0x10,
                                    "input_backend_activation result=failed current=send_input requested=vhid reason=mouse_neutral_partial residue="
                                   );
              }
              if (*(char *)(lVar6 + 0xf8) != '\0') {
                std::basic_ostream<char,std::char_traits<char>_>::operator<<
                          ((basic_ostream<char,std::char_traits<char>_> *)(lVar6 + 0x10),_Var10);
              }
            }
            if (lVar7 != 0) {
              thunk_FUN_140208c50(auStack_170);
            }
            pcStack_58 = (char *)0x0;
            lStack_50 = 0;
            uStack_48 = 0;
            uStack_40 = 0;
            pcStack_58 = (char *)thunk_FUN_140aba630(0x60);
            uStack_48 = 0x56;
            uStack_40 = 0x5f;
            builtin_strncpy(pcStack_58,
                            "[InputDiag] side=server stage=vhid_activate result=failed reason=mouse_neutral_partial"
                            ,0x57);
            thunk_FUN_140df60d0(&pcStack_58);
            if (0xf < uStack_40) {
              if ((0xfff < uStack_40 + 1) &&
                 ((char *)0x1f < pcStack_58 + (-8 - *(longlong *)(pcStack_58 + -8)))) {
                    /* WARNING: Subroutine does not return */
                _invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
              }
              FUN_14005a335();
            }
            cVar9 = '\0';
            goto LAB_140e03b89;
          }
        }
        if (_Var10 != 0) {
          cVar9 = thunk_FUN_140202db0(3);
          if (cVar9 != '\0') {
            lVar6 = thunk_FUN_1402088f0(auStack_170,3);
            lVar7 = 4;
            if (*(char *)(lVar6 + 0xf8) != '\0') {
              thunk_FUN_14015d4f0(lVar6 + 0x10,
                                  "input_backend_activation result=success current=vhid requested=vhid reason=keyboard_neutral_partial residue="
                                 );
            }
            if (*(char *)(lVar6 + 0xf8) != '\0') {
              std::basic_ostream<char,std::char_traits<char>_>::operator<<
                        ((basic_ostream<char,std::char_traits<char>_> *)(lVar6 + 0x10),_Var10);
            }
          }
          if (lVar7 != 0) {
            thunk_FUN_140208c50(auStack_170);
          }
        }
        bVar3 = false;
        thunk_FUN_140e8d660(param_1 + 0xc0);
        *(undefined1 *)(param_1 + 0xcc) = 1;
        cVar9 = thunk_FUN_140202db0(2);
        if (cVar9 != '\0') {
          lVar7 = thunk_FUN_1402088f0(auStack_170,2);
          bVar3 = true;
          if (*(char *)(lVar7 + 0xf8) != '\0') {
            thunk_FUN_14015d4f0(lVar7 + 0x10,
                                "input_backend_transition from=send_input to=vhid reason=probe_available"
                               );
          }
        }
        if (bVar3) {
          thunk_FUN_140208c50(auStack_170);
        }
        pcStack_58 = (char *)0x0;
        lStack_50 = 0;
        uStack_48 = 0;
        uStack_40 = 0;
        pcStack_58 = (char *)thunk_FUN_140aba630(0x50);
        uStack_48 = 0x46;
        uStack_40 = 0x4f;
        builtin_strncpy(pcStack_58,
                        "[InputDiag] side=server stage=vhid_activate result=success path=driver",
                        0x47);
        thunk_FUN_140df60d0(&pcStack_58);
        if (0xf < uStack_40) {
          if ((0xfff < uStack_40 + 1) &&
             ((char *)0x1f < pcStack_58 + (-8 - *(longlong *)(pcStack_58 + -8)))) {
                    /* WARNING: Subroutine does not return */
            _invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
          }
          FUN_14005a335();
        }
        cVar9 = '\x01';
LAB_140e03b89:
        thunk_FUN_1405d9960(&pcStack_190);
      }
    }
  }
  _Mtx_unlock(lVar1);
  return cVar9;
}

