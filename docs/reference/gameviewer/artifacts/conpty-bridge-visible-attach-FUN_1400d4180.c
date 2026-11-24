
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ulonglong FUN_1400d4180(int param_1,longlong param_2,longlong param_3)

{
  wchar_t *_Str;
  wchar_t *pwVar1;
  char cVar2;
  size_t sVar3;
  size_t sVar4;
  size_t sVar5;
  byte bVar6;
  char cVar7;
  uint uVar8;
  undefined8 *puVar9;
  int iVar10;
  longlong lVar11;
  undefined1 auStack_c8 [32];
  char local_a8;
  char local_a7;
  char local_a6;
  char local_a5;
  char local_a4;
  char local_a3;
  char local_a2;
  uint local_a0;
  int local_9c;
  longlong local_98;
  undefined8 local_88;
  undefined8 uStack_80;
  longlong local_78;
  wchar_t *local_68;
  size_t local_60;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  ulonglong local_38;
  
  local_38 = DAT_1405ddb40 ^ (ulonglong)auStack_c8;
  iVar10 = 1;
  local_a0 = 0;
  local_a5 = '\0';
  local_a4 = '\0';
  local_a8 = '\0';
  local_a7 = '\0';
  local_a6 = '\0';
  local_a2 = '\0';
  local_a3 = '\0';
  uVar8 = 0;
  local_9c = param_1;
  local_98 = param_2;
  if (1 < param_1) {
    puVar9 = (undefined8 *)(param_2 + 0x10);
    lVar11 = 1;
    local_78 = (longlong)param_1;
    do {
      cVar2 = local_a5;
      _Str = *(wchar_t **)(local_98 + lVar11 * 8);
      sVar3 = wcslen(_Str);
      sVar4 = sVar3;
      if ((sVar3 == 0x10) &&
         (sVar4 = thunk_FUN_1400d9780(_Str,L"--visible-attach",0x10), (int)sVar4 == 0)) {
        if (cVar2 != '\0') goto LAB_1400d4593;
        local_a5 = '\x01';
        goto LAB_1400d4508;
      }
      iVar10 = iVar10 + 1;
      if (local_9c <= iVar10) goto LAB_1400d4593;
      pwVar1 = (wchar_t *)*puVar9;
      lVar11 = lVar11 + 1;
      local_60 = wcslen(pwVar1);
      local_68 = pwVar1;
      sVar4 = FUN_1400d3690(&local_68);
      if ((char)sVar4 != '\0') goto LAB_1400d4593;
      puVar9 = puVar9 + 1;
      pwVar1 = *(wchar_t **)(local_98 + lVar11 * 8);
      local_88 = pwVar1;
      sVar5 = wcslen(pwVar1);
      uStack_80 = sVar5;
      if (sVar3 == 0xc) {
        sVar4 = thunk_FUN_1400d9780(_Str,L"--ipc-server",0xc);
        if ((int)sVar4 == 0) {
          if (local_a4 != (char)sVar4) goto LAB_1400d4593;
          cVar2 = '\x01';
          local_a4 = '\x01';
          thunk_FUN_1400c7510(param_3,pwVar1,sVar5);
          goto LAB_1400d450d;
        }
        sVar4 = thunk_FUN_1400d9780(_Str,L"--session-id",0xc);
        if ((int)sVar4 != 0) goto LAB_1400d4449;
        if (local_a8 != (char)sVar4) goto LAB_1400d4593;
        local_58 = (undefined4)local_88;
        uStack_54 = local_88._4_4_;
        uStack_50 = (undefined4)uStack_80;
        uStack_4c = uStack_80._4_4_;
        sVar4 = FUN_1400d4100(&local_58,param_3 + 0x20);
        if ((char)sVar4 == '\0') goto LAB_1400d4593;
        local_a8 = '\x01';
        cVar2 = local_a4;
LAB_1400d4513:
        cVar7 = local_a3;
      }
      else {
        if (sVar3 != 0xf) {
          sVar4 = sVar5;
          if (sVar3 == 0x10) {
            sVar4 = thunk_FUN_1400d9780(_Str,L"--candidate-type",0x10);
            if (((int)sVar4 != 0) || (local_a6 != (char)sVar4)) goto LAB_1400d4593;
            local_58 = (undefined4)local_88;
            uStack_54 = local_88._4_4_;
            uStack_50 = (undefined4)uStack_80;
            uStack_4c = uStack_80._4_4_;
            sVar4 = FUN_1400d4020(&local_58,param_3 + 0x48);
            if ((char)sVar4 == '\0') goto LAB_1400d4593;
            local_a6 = '\x01';
          }
          else {
LAB_1400d4449:
            if (sVar3 != 0x12) goto LAB_1400d444f;
            sVar4 = thunk_FUN_1400d9780(_Str,L"--uuyc-mux-session",0x12);
            if (((int)sVar4 != 0) || (local_a2 != (char)sVar4)) goto LAB_1400d4593;
            local_a2 = '\x01';
            thunk_FUN_1400c7510(param_3 + 0x50,pwVar1,sVar5);
          }
LAB_1400d4508:
          cVar2 = local_a4;
LAB_1400d450d:
          goto LAB_1400d4513;
        }
        sVar4 = thunk_FUN_1400d9780(_Str,L"--attempt-token",0xf);
        if ((int)sVar4 == 0) {
          if (local_a7 != (char)sVar4) goto LAB_1400d4593;
          local_58 = (undefined4)local_88;
          uStack_54 = local_88._4_4_;
          uStack_50 = (undefined4)uStack_80;
          uStack_4c = uStack_80._4_4_;
          sVar4 = thunk_FUN_14010d0f0(&local_58,param_3 + 0x28);
          if ((char)sVar4 == '\0') goto LAB_1400d4593;
          local_a7 = '\x01';
          goto LAB_1400d4508;
        }
LAB_1400d444f:
        if (((sVar3 != 0x11) ||
            (sVar4 = thunk_FUN_1400d9780(_Str,L"--uuyc-mux-config",0x11), (int)sVar4 != 0)) ||
           (local_a3 != (char)sVar4)) {
LAB_1400d4593:
          return sVar4 & 0xffffffffffffff00;
        }
        cVar7 = '\x01';
        local_a3 = '\x01';
        thunk_FUN_1400c7510(param_3 + 0x70,pwVar1,sVar5);
        cVar2 = local_a4;
      }
      iVar10 = iVar10 + 1;
      lVar11 = lVar11 + 1;
      puVar9 = puVar9 + 1;
    } while (lVar11 < local_78);
    if ((((local_a5 == '\0') || (cVar2 == '\0')) ||
        ((local_a8 == '\0' || ((local_a7 == '\0' || (local_a6 == '\0')))))) ||
       ((local_a2 == '\0' ||
        ((((cVar7 == '\0' || (*(longlong *)(param_3 + 0x10) == 0)) ||
          (*(longlong *)(param_3 + 0x38) == 0)) || (*(longlong *)(param_3 + 0x60) == 0)))))) {
      uVar8 = local_a0;
    }
    else {
      thunk_FUN_1400c3bd0(&local_58,param_3 + 0x70,0);
      uVar8 = 1;
      cVar2 = thunk_FUN_1400cb900(&local_58);
      if (cVar2 != '\0') {
        bVar6 = 1;
        goto LAB_1400d459d;
      }
    }
  }
  bVar6 = 0;
LAB_1400d459d:
  if ((uVar8 & 1) != 0) {
    thunk_FUN_1400c7020(&local_58);
  }
  return (ulonglong)bVar6;
}

