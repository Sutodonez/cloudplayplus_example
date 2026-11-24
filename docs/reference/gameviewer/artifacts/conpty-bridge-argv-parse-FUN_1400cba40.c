
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ulonglong FUN_1400cba40(int param_1,longlong param_2,ushort *param_3)

{
  wchar_t *pwVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  ushort *puVar5;
  size_t sVar6;
  undefined8 uVar7;
  ushort *puVar8;
  byte bVar9;
  int iVar10;
  longlong lVar11;
  bool bVar12;
  undefined1 auStack_98 [32];
  undefined4 local_78;
  wchar_t *local_68;
  size_t local_60;
  ulonglong local_48;
  
  local_48 = DAT_1405ddb40 ^ (ulonglong)auStack_98;
  bVar12 = false;
  iVar10 = 1;
  local_78 = 0;
  if (1 < param_1) {
    do {
      lVar11 = (longlong)iVar10;
      pwVar1 = *(wchar_t **)(param_2 + lVar11 * 8);
      iVar3 = wcscmp(pwVar1,L"--shell");
      iVar4 = iVar10 + 1;
      if ((iVar3 == 0) && (iVar4 < param_1)) {
        pwVar1 = *(wchar_t **)(param_2 + 8 + lVar11 * 8);
        local_60 = wcslen(pwVar1);
        local_68 = pwVar1;
        puVar5 = (ushort *)thunk_FUN_14010d0f0(&local_68,param_3);
        iVar10 = iVar4;
        if ((char)puVar5 == '\0') goto LAB_1400cbad1;
      }
      else {
        iVar3 = wcscmp(pwVar1,L"--cols");
        if ((iVar3 == 0) && (iVar4 < param_1)) {
          iVar10 = _wtoi(*(wchar_t **)(param_2 + (longlong)iVar4 * 8));
          *(int *)(param_3 + 0x10) = iVar10;
          iVar10 = iVar4;
        }
        else {
          iVar3 = wcscmp(pwVar1,L"--rows");
          if ((iVar3 == 0) && (iVar4 < param_1)) {
            iVar10 = _wtoi(*(wchar_t **)(param_2 + (longlong)iVar4 * 8));
            *(int *)(param_3 + 0x12) = iVar10;
            iVar10 = iVar4;
          }
          else {
            iVar3 = wcscmp(pwVar1,L"--display-name");
            if ((iVar3 == 0) && (iVar4 < param_1)) {
              pwVar1 = *(wchar_t **)(param_2 + (longlong)iVar4 * 8);
              sVar6 = wcslen(pwVar1);
              thunk_FUN_1400c7510(param_3 + 0x18,pwVar1,sVar6);
              iVar10 = iVar4;
            }
            else {
              iVar3 = wcscmp(pwVar1,L"--stdin-handle");
              if ((iVar3 == 0) && (iVar4 < param_1)) {
                uVar7 = wcstoull(*(undefined8 *)(param_2 + 8 + lVar11 * 8),0,0x10);
                *(undefined8 *)(param_3 + 0x28) = uVar7;
                iVar10 = iVar4;
              }
              else {
                iVar3 = wcscmp(pwVar1,L"--stdout-handle");
                if ((iVar3 == 0) && (iVar4 < param_1)) {
                  uVar7 = wcstoull(*(undefined8 *)(param_2 + 8 + lVar11 * 8),0,0x10);
                  *(undefined8 *)(param_3 + 0x2c) = uVar7;
                  iVar10 = iVar4;
                }
                else {
                  iVar3 = wcscmp(pwVar1,L"--ctl-handle");
                  if ((iVar3 == 0) && (iVar4 < param_1)) {
                    uVar7 = wcstoull(*(undefined8 *)(param_2 + 8 + lVar11 * 8),0,0x10);
                    *(undefined8 *)(param_3 + 0x30) = uVar7;
                    iVar10 = iVar4;
                  }
                  else {
                    iVar3 = wcscmp(pwVar1,L"--uuyc-mux-session");
                    if ((iVar3 == 0) && (iVar4 < param_1)) {
                      sVar6 = wcslen(*(wchar_t **)(param_2 + 8 + lVar11 * 8));
                      thunk_FUN_1400c7510(param_3 + 0x34,*(undefined8 *)(param_2 + 8 + lVar11 * 8),
                                          sVar6);
                      iVar10 = iVar4;
                    }
                    else {
                      iVar3 = wcscmp(pwVar1,L"--uuyc-mux-config");
                      if ((iVar3 == 0) && (iVar4 < param_1)) {
                        sVar6 = wcslen(*(wchar_t **)(param_2 + 8 + lVar11 * 8));
                        thunk_FUN_1400c7510(param_3 + 0x44,*(undefined8 *)(param_2 + 8 + lVar11 * 8)
                                            ,sVar6);
                        iVar10 = iVar4;
                      }
                      else {
                        iVar4 = wcscmp(pwVar1,L"--uuyc-mux-attach-existing");
                        if (iVar4 == 0) {
                          *(undefined1 *)(param_3 + 0x14) = 1;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      iVar10 = iVar10 + 1;
    } while (iVar10 < param_1);
  }
  puVar5 = param_3;
  if (0xf < *(ulonglong *)(param_3 + 0xc)) {
    puVar5 = *(ushort **)param_3;
  }
  if (*(longlong *)(param_3 + 8) == 10) {
    lVar11 = *(longlong *)puVar5 + -0x6568737265776f70;
    if (lVar11 == 0) {
      puVar8 = puVar5 + 4;
      puVar5 = (ushort *)0x6c6c;
      lVar11 = (ulonglong)*puVar8 - 0x6c6c;
    }
    if (lVar11 != 0) goto LAB_1400cbd08;
  }
  else {
LAB_1400cbd08:
    puVar8 = param_3;
    if (0xf < *(ulonglong *)(param_3 + 0xc)) {
      puVar8 = *(ushort **)param_3;
    }
    if (*(longlong *)(param_3 + 8) != 3) goto LAB_1400cbad1;
    puVar5 = (ushort *)0x6d63;
    iVar10 = *puVar8 - 0x6d63;
    if (iVar10 == 0) {
      iVar10 = (byte)puVar8[1] - 100;
    }
    if (iVar10 != 0) goto LAB_1400cbad1;
  }
  if ((((*(int *)(param_3 + 0x10) < 1) || (*(int *)(param_3 + 0x12) < 1)) ||
      (puVar5 = *(ushort **)(param_3 + 0x30), puVar5 == (ushort *)&DAT_ffffffffffffffff)) ||
     (puVar5 == (ushort *)0x0)) {
LAB_1400cbad1:
    return (ulonglong)puVar5 & 0xffffffffffffff00;
  }
  if (*(longlong *)(param_3 + 0x3c) != 0) {
    thunk_FUN_1400c3bd0(&local_68,param_3 + 0x44,0);
    bVar12 = true;
    cVar2 = thunk_FUN_1400cb900(&local_68);
    if (cVar2 != '\0') {
      bVar9 = 1;
      goto LAB_1400cbd9a;
    }
  }
  bVar9 = 0;
LAB_1400cbd9a:
  if (bVar12) {
    thunk_FUN_1400c7020(&local_68);
  }
  return (ulonglong)bVar9;
}

