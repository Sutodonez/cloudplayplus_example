
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 * FUN_1407017b0(undefined8 *param_1)

{
  LPCWSTR **pppWVar1;
  DWORD DVar2;
  undefined8 uVar3;
  longlong lVar4;
  ulonglong uVar5;
  void *_Dst;
  LPCWSTR ***ppppWVar6;
  ulonglong uVar7;
  undefined1 auStackY_e8 [32];
  LPCWSTR ***appppWStack_a8 [2];
  ulonglong uStack_98;
  ulonglong uStack_90;
  undefined1 auStack_88 [32];
  undefined1 auStack_68 [32];
  undefined1 auStack_48 [32];
  ulonglong uStack_28;
  
  uStack_28 = DAT_141e01000 ^ (ulonglong)auStackY_e8;
  thunk_FUN_1406fb180(auStack_88,L"conpty_bridge.exe",0);
  uVar3 = thunk_FUN_140271740(auStack_48);
  uVar3 = thunk_FUN_1401680e0(auStack_68,uVar3);
  thunk_FUN_1401648d0(appppWStack_a8,uVar3);
  thunk_FUN_14016c430(auStack_68);
  thunk_FUN_14016c430(auStack_48);
  thunk_FUN_14016c430(auStack_88);
  ppppWVar6 = (LPCWSTR ***)appppWStack_a8;
  if (7 < uStack_90) {
    ppppWVar6 = appppWStack_a8[0];
  }
  DVar2 = GetFileAttributesW((LPCWSTR)ppppWVar6);
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  if (DVar2 == 0xffffffff) {
    param_1[3] = 7;
    *(undefined2 *)param_1 = 0;
    if (uStack_90 < 8) {
      return param_1;
    }
    if (uStack_90 * 2 + 2 < 0x1000) goto LAB_1407018be;
    lVar4 = (longlong)appppWStack_a8[0] - (longlong)appppWStack_a8[0][-1];
  }
  else {
    param_1[3] = 0;
    ppppWVar6 = (LPCWSTR ***)appppWStack_a8;
    if (7 < uStack_90) {
      ppppWVar6 = appppWStack_a8[0];
    }
    if (0x7ffffffffffffffe < uStack_98) {
                    /* WARNING: Subroutine does not return */
      thunk_FUN_14016c500();
    }
    if (uStack_98 < 8) {
      param_1[2] = uStack_98;
      param_1[3] = 7;
      pppWVar1 = ppppWVar6[1];
      *param_1 = *ppppWVar6;
      param_1[1] = pppWVar1;
    }
    else {
      uVar5 = uStack_98 | 7;
      if (uVar5 < 0x7fffffffffffffff) {
        if (uVar5 < 10) {
          uVar5 = 10;
        }
        if (0x7fffffffffffffff < uVar5 + 1) {
                    /* WARNING: Subroutine does not return */
          thunk_FUN_14016c130();
        }
        uVar7 = (uVar5 + 1) * 2;
        if (uVar7 != 0) goto LAB_140701959;
        _Dst = (void *)0x0;
      }
      else {
        uVar7 = 0xfffffffffffffffe;
        uVar5 = 0x7ffffffffffffffe;
LAB_140701959:
        if (uVar7 < 0x1000) {
          _Dst = (void *)thunk_FUN_140aba630();
        }
        else {
          _Dst = (void *)thunk_FUN_14015f520();
        }
      }
      *param_1 = _Dst;
      param_1[2] = uStack_98;
      param_1[3] = uVar5;
      memcpy(_Dst,ppppWVar6,uStack_98 * 2 + 2);
    }
    if (uStack_90 < 8) {
      return param_1;
    }
    if (uStack_90 * 2 + 2 < 0x1000) goto LAB_1407018be;
    lVar4 = (longlong)appppWStack_a8[0] - (longlong)appppWStack_a8[0][-1];
  }
  if (0x1f < lVar4 - 8U) {
                    /* WARNING: Subroutine does not return */
    _invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
  }
LAB_1407018be:
  FUN_14005a335();
  return param_1;
}

